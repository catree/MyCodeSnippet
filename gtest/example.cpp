#include <iostream>
#include "gtest/gtest.h"
using namespace std;

int Factorial(int x)
{
    if (x == 0 || x == 1) return 1;
    return x * Factorial(x - 1);
}

TEST(FactorialTest, HandlesZeroInput)
{
    EXPECT_EQ(Factorial(0), 1);
}

TEST(FactorialTest, HandlesPositiveInput)
{
    EXPECT_EQ(Factorial(1), 1);
    EXPECT_EQ(Factorial(2), 2);
    EXPECT_EQ(Factorial(3), 6);
    EXPECT_EQ(Factorial(8), 40320);
}