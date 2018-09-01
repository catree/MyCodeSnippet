// A scoping example
#include <iostream>
using namespace std;

void useLocal();        // function prototype
void useStaticLocal();  // function prototype
void useGlobal();       // function prototype

int x = 1;  // global variable

int main()
{
    cout << "global x in main is " << x << endl;
    int x = 5;

    cout << "local x in main's outer scope is " << x << endl;

    {   // start new scope
        int x = 7;  // hides both x in outer scope and global x
        
        cout << "local x in main's inner scope is " << x << endl;
    }

    cout << "local x in main's outer scope is " << x << endl;

    useLocal();
    useStaticLocal();
    useGlobal();
    useStaticLocal();
    useGlobal();

    cout << "\n local x in main is " << x << endl;
}

void useLocal()
{
    int x = 25;

    cout << "\nlocal x is " << x << " on exiting useLocal" << endl;
    x++;
    cout << "local x is " << x << " on exiting useLocal" << endl;
}

void useStaticLocal()
{
    static int x = 50;

    cout << "\nlocal x is " << x << " on entering useStaticLocal" << endl;
    x++;
    cout << "local static x is " << x << " on exiting useStaticLocal" << endl;
}   

void useGlobal()
{
    cout << "\nglobal x is " << x << " on entering useGlobal" << endl;
    x *= 10;
    cout << "global x is " << x << " on exiting useGlobal" << endl;
}