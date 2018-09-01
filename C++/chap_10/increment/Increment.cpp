#include <iostream>

#include "Increment.h"

using namespace std;

int main()
{
    Increment value(10, 5);

    cout << "before incremnting: ";
    value.print();

    for (int j = 1; j <= 3; j++) {
        value.addIncrement();
        cout << "After increment " << j << ": ";
        value.print();
    }
}