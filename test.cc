#include<iostream>
using namespace std;
 
class Test
{
public:
   Test(Test &t) { }
   Test()        { }
};
 
Test fun()
{
    cout << "fun() Calledn";
    Test t;
    return t;
}
 
int main()
{
    Test t1;
    Test t2 = fun();
    return 0;
}

