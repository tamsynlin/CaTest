#include <stdio.h>

class ParentWithoutVtable
{    
    char empty;
public:
    ~ParentWithoutVtable ()
    {}
};

class ParentWithVTable
{
    public:
        virtual ~ParentWithVTable () { }
};

/*
 * C++ puts the virtual table pointer as the first element of a class, so the real layout of Derived is something like:

struct __Derived
{
    function_ptr vtable; char empty;
}
 *
 * */
class Derived : public ParentWithoutVtable, public ParentWithVTable
{
};

class CBaseX
{
public:
    int x;
    CBaseX() { x = 10; }
    void foo() { printf("CBaseX::foo() x=%d\n", x); }
};

class CBaseY
{
public:
    int y;
    int* py;
    CBaseY() { y = 20; py = &y; }
    void bar() { printf("CBaseY::bar() y=%d, *py=%d\n", y, *py); }
};

class CDerived : public CBaseX, public CBaseY
{
public:
    int z;
};

int main () {
    ParentWithoutVtable* p = new Derived ();
    Derived* a = reinterpret_cast<Derived*>(p); // (1)
    Derived* b = static_cast<Derived*>(p); // (2)
    Derived* c = (Derived*)(p); // (3)

    printf("Size of ParentWithoutVtable: %d\n", sizeof(ParentWithoutVtable));
    printf("Size of Derived: %d\n", sizeof(Derived));

/*
 It fails because the ParentWitoutVTable* pointer does not point at the beginning of the newly 
 created Derived object in memory, but somewhere else. For example, Visual C++ puts the virtual 
 table pointer as the first element of a class, so the real layout of Derived is something like:

struct __Derived
{
    function_ptr vtable; char empty;
}

So if we obtain a pointer to an object without a vtable, it will point at empty, otherwise access 
via the pointer would fail. Now, the reinterpret_cast has no idea of this, and if you call a Derived 
function, it will think the empty is the vtable. The static_cast does it right, but for this it 
has to know the full declaration of both types. 
*/
    printf("ParentWithoutVtable *p= %x\n", p);
    printf("reinterpret_cast *a= %x\n", a);
    printf("static_cast *b= %x\n", b);
    printf("C-Style casting *c= %x\n", c);

    printf("\n\n\n");

    // Convert between CBaseX* and CBaseY*
    CBaseX* pX = new CBaseX();
    // Error, types pointed to are unrelated
    //CBaseY* pY1 = static_cast<CBaseY*>(pX);
    // Compile OK, but pY2 is not CBaseX
    CBaseY* pY2 = reinterpret_cast<CBaseY*>(pX);
    // System crash!!
    //pY2->bar();

    printf("Size of CBaseX: %d\n", sizeof(CBaseX));
    printf("Size of CBaseY: %d\n", sizeof(CBaseY));
    printf("Size of CDerived: %d\n", sizeof(CDerived));

    printf("Size of ParentWithoutVtable: %d\n", sizeof(ParentWithoutVtable));
    printf("Size of ParentWithVTable: %d\n", sizeof(ParentWithVTable));

    CDerived* pD = new CDerived();
    printf("CDerived* pD = %x\n", pD);
    // static_cast<> CDerived* -> CBaseY* -> CDerived*
    // OK, implicit static_cast<> casting
    CBaseY* pY1 = static_cast<CBaseY*>(pD);
    printf("CBaseY* pY1 = %x\n", pY1);

    CBaseX* pX1 = static_cast<CBaseX*>(pD);
    printf("CBaseX* pX1 = %x\n", pX1);

    // OK, now pD1 = pD
    CDerived* pD1 = static_cast<CDerived*>(pY1);
    printf("CDerived* pD1 = %x\n", (long)pD1);

    // reinterpret_cast
    // OK, but pY2 is not CBaseY*
    CBaseY* pY2a = reinterpret_cast<CBaseY*>(pD);
    printf("CBaseY* pY2 = %x\n", (long)pY2a);

    // unrelated static_cast<>
    CBaseY* pY3 = new CBaseY();
    printf("CBaseY* pY3 = %x\n", (long)pY3);
    // OK, even pY3 is just a "new CBaseY()"
    CDerived* pD3 = static_cast<CDerived*>(pY3);
    printf("CDerived* pD3 = %x\n", (long)pD3);
}
