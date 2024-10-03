#include <gtest/gtest.h>

#include "../application/headers/polynomial.hpp"
#include "../application/headers/monomial.hpp"

using namespace Vath;

TEST(PolynomialTests, Constructor_DefaultConstructorIsInvoked_DefaultConstructorWorks)
{
    Polynomial p;

    EXPECT_TRUE(p.Monomials.size() == 1);
    EXPECT_TRUE(p.Monomials[0].Coefficient == 0);
    EXPECT_TRUE(p.Monomials[0].Exponent == 0);
}

TEST(PolynomialTests, Constructor_ConstructorTakesCoefficientList_ConstructorWorks)
{
    CoefficientList cl;
    cl.push_back(1);
    cl.push_back(2);
    cl.push_back(3);
    cl.push_back(4);

    Polynomial p(cl); // Create polynomial
    EXPECT_TRUE(p.Monomials.size() == 4);
    EXPECT_TRUE(p.Monomials[0].Coefficient == 1);
    EXPECT_TRUE(p.Monomials[0].Exponent == 3);
    EXPECT_TRUE(p.Monomials[1].Coefficient == 2);
    EXPECT_TRUE(p.Monomials[1].Exponent == 2);
    EXPECT_TRUE(p.Monomials[2].Coefficient == 3);
    EXPECT_TRUE(p.Monomials[2].Exponent == 1);
    EXPECT_TRUE(p.Monomials[3].Coefficient == 4);
    EXPECT_TRUE(p.Monomials[3].Exponent == 0);
}