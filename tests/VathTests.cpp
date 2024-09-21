#include <gtest/gtest.h>

#include "../application/headers/firsttest.hpp"

TEST(VathTests, firsttesttest)
{
    int input = 3;
    int output = testfunction1(input);
    int result = 10;

    EXPECT_EQ(result, output);

    output = testfunction1(input);
    result = input * input;

    EXPECT_EQ(result, output);
}