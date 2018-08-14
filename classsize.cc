#include<iostream>
using namespace std;

class A
{

};

class B
{
    int i; 
}; 

class C
{
    void foo();
};

class D
{
    virtual void foo();
};

class E
{
    int i ; 
    virtual void foo();
};

class F
{
    int i; 
    void foo();
};

class G
{
    void foo();
    int i;
    void foo1();
};

class H
{
    int i ;
    /*
    Only the first virtual function in a class increases its size (compiler-dependent, 
    but on most - if not all - it's like this). All subsequent methods do not. Non-virtual 
    functions do not affect the class's size.
    This happens because a class instance doesn't hold pointers to methods themselves, 
    but to a virtual function table, which is one per class.
    */
    virtual void foo();
    virtual void foo1();
};

class I
{
    virtual int foo() = 0;
    virtual int foo2() = 0;
};

int main()
{
    cout <<"sizeof(class A) : " << sizeof(A) << endl ;
    cout <<"sizeof(class B) adding the member int i : " << sizeof(B) << endl ;
    cout <<"sizeof(class C) adding the member void foo() : " << sizeof(C) << endl ;
    cout <<"sizeof(class D) after making foo virtual : " << sizeof(D) << endl ;
    cout <<"sizeof(class E) after adding foo virtual , int : " << sizeof(E) << endl ;
    cout <<"sizeof(class F) after adding foo  , int : " << sizeof(F) << endl ;
    cout <<"sizeof(class G) after adding foo  , int : " << sizeof(G) << endl ;
    G g;
    cout <<"sizeof(class G) after adding foo  , int : " << sizeof(g) << endl ;
    cout <<"sizeof(class H) after adding int 2 virtual " << sizeof(H) << endl ;

    cout <<"sizeof(class I) : " << sizeof(I) << endl ;

    return 0; 
}