#include <iostream>

#include "Date.h"

using namespace std;

Date::Date(int mn, int dy, int yr)
{
    if(mn > 0 && mn <= monthsPerYear)
        month = mn;
    else {
        month = 1;
        cout << "Invalid month (" << mn << ") set to 1.\n";
    }

    year = yr;
    day = checkDay(dy);

    cout << "Date object constructor for date ";
    print();
    cout << endl;
}

void Date::print() const
{
    cout << month << "/" << day << "/" << year;
}

Date::~Date()
{
    cout << "Date object destructor for date ";
    print();
    cout << endl;
}

int Date::checkDay(int testDay) const
{
    static const int daysPerMonth[monthsPerYear + 1] = 
        {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // determine whether testDay is valid for specified month
    if (testDay > 0 && testDay <= daysPerMonth[month])
        return testDay;
    
    // February 29 check for leap year
    if (month == 2 && testDay == 29 && (year % 400 == 0 ||
        (year % 4 == 0 && year % 100 != 0)))
        return testDay;
    
    cout << "Invalid day (" << testDay << ") set to 1.\n";
    return 1;
}