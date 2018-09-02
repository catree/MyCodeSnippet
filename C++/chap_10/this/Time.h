#ifndef TIME_H
#define TIME_H

class Time
{
public:
    Time(int = 0, int = 0, int = 0);

    // set functions (the Time & return types enable cascading)
    Time &setTime(int, int, int);
    Time &setHour(int);
    Time &setMinute(int);
    Time &setSecond(int);

    // get functions (normally declared const)
    int getHour() const;
    int getMinute() const;
    int getSecond() const;

    // print functions (normally decalred const)
    void printUniversal() const;
    void printStandard() const;

private:
    int hour;
    int minute;
    int second;
};

#endif