#include <iostream>
#include <thread>

void threadCallback(int const & x)
{
    int & y = const_cast<int &>(x);
    y++;
    std::cout<<"Inside Thread x = "<<x<<std::endl;
}

class DummyClass {
public:
    DummyClass()
    {}
    DummyClass(const DummyClass & obj)
    {}
    void sampleMemberFunction(int x)
    {
        std::cout<<"Inside sampleMemberFunction "<<x<<std::endl;
    }
};

int main()
{
    int x = 9;
    std::cout<<"In Main Thread : Before Thread Start x = "<<x<<std::endl;
    /*
    Even if threadCallback accepts arguments as reference but still changes done it are not visible outside the thread.
    Its because x in the thread function threadCallback is reference to the temporary value copied at the new thread’s stack.
    */
    std::thread threadObj(threadCallback, x);
    threadObj.join();
    std::cout<<"In Main Thread : After Thread Joins x = "<<x<<std::endl;

    std::cout<<"In Main Thread : Before Thread Start x = "<<x<<std::endl;
    std::thread threadObj2(threadCallback,std::ref(x));
    threadObj2.join();
    std::cout<<"In Main Thread : After Thread Joins x = "<<x<<std::endl;

    DummyClass dummyObj;
    std::thread threadObj3(&DummyClass::sampleMemberFunction,&dummyObj, x);
    threadObj3.join();

    return 0;
}
