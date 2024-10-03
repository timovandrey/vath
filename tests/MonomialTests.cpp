#include <gtest/gtest.h>

#include "../application/headers/monomial.hpp"


TEST(MonomialTests, Method_IsEqual)
{
    using namespace Vath;

    bool result;

    Monomial m1(1, 2);
    Monomial m2(1, 2);

    result = m1.IsEqual(m2);

    EXPECT_TRUE(result);
}