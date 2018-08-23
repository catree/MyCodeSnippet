#include <iostream>


double betsy(int lns)
{
    return 0.05 * lns;
}

double pam(int lns)
{
    return 0.03 * lns + 0.0004 * lns * lns;
}

void estimate(int lines, double (*pf)(int))
{
    std::cout << lines << " lines will take ";
    std::cout << (*pf)(lines) << " hour(s) \n";
}

int main()
{
    int code;
    
    std::cout << "how many lines of code do you need?\n";
    std::cin >> code;
    std::cout << "Here is Betsy's estimate:\n";
    estimate(code, betsy);
    std::cout << "Here is Pam's estimate:\n";
    estimate(code, pam);
}