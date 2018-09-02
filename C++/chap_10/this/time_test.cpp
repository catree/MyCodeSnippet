#include <iostream>

#include "Time.h"

using namespace std;

int main(int argc, char const *argv[])
{
    Time t;
    t.setHour(18).setMinute(30).setSecond(22);

    cout << "Universal time: ";
    t.printUniversal();

    cout << "Standard time: ";
    t.printStandard();

    cout << "\nnew standard time: ";

    // cascade funciton calls
    t.setTime(20, 20, 20).printStandard();
    cout << endl;
}
