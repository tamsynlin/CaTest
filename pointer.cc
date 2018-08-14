#include <memory>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

class TestPointer
{
public:
    TestPointer() 
    {
        cout << "Create a object" << endl;
    }

    ~TestPointer() 
    {
        cout << "Destroy a object" << endl;
    }
};

class B;

class A 
{
public:
    ~A()
    {
        std::cout << "A is dead" << std::endl;
    }
    shared_ptr<B> external;
};

class B
{
public:
    ~B()
    {
        std::cout << "B is dead" << std::endl;
    }
    shared_ptr<A> external;
};

int main()
{
    weak_ptr<TestPointer> p_weak;

    {
        shared_ptr<TestPointer> p_share = make_shared<TestPointer>();
        p_weak = p_share;
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> elapsed = end-start;
    std::cout << "Waited " << elapsed.count() << " ms\n";

    if (!p_weak.expired()) {
	    std::cout << "p_weak is valid\n";
    }
    else {
        std::cout << "p_weak is expired\n";
    }

    shared_ptr<A> p_a = make_shared<A>();
    shared_ptr<B> p_b = make_shared<B>();

    //Cyclic Dependency
    p_a->external = p_b;
    p_b->external = p_a;
}
