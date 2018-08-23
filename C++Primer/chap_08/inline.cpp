#include <iostream>

inline double square(double x)
{
    return x * x;
}

int main()
{
    double a, b;
    double c = 13.0;
    a = square(5.0);
    b = square(4.5 + 7.5);
    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << ", c squared = " << square(c++) << std::endl;
    std::cout << "Now c = " << c << std::endl;
}