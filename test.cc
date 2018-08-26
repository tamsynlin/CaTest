#include<iostream>
using namespace std;
 
class Test
{
public:
   Test(const Test &t) { cout << "Copy constructor" << endl; }
   Test()        { cout << "Default constructor" << endl; }

   Test& operator=(const Test& other) { cout << "Assignment operator" << endl; }

   Test(Test&& other)
   {
	   cout << "Move constructor" << endl;
   }

   Test& operator=(Test&& other)
   {
	   cout << "Move assignment operator" << endl;
   }
};
 
Test fun()
{
    cout << "fun() Calledn" << endl;
    Test t;
    return t;
}
 
int main()
{
    Test t1;
    Test t2 = fun();
    Test t3 = t1;
    return 0;
}

