#include <gtest/gtest.h>

#include "../application/headers/monomial.hpp"

using namespace Vath;

TEST(MonomialTests, Method_IsEqual_MonomialValuesAreTheSame_ReturnsTrue)
{
    bool result;

    Monomial m1(1, 2);
    Monomial m2(1, 2);

    result = m1.IsEqual(m2);
    EXPECT_TRUE(result);

    m2.Coefficient = 3;
    m1.Coefficient = 3;
    result = m1.IsEqual(m2);
    EXPECT_TRUE(result);
}

TEST(MonomialTests, Method_IsEqual_MonomialValuesAreNotTheSame_ReturnsFalse)
{
    bool result;

    Monomial m1(1, 2);
    Monomial m2(1, 3);

    result = m1.IsEqual(m2);
    EXPECT_FALSE(result);

    m2.Coefficient = 3;
    m2.Exponent = 2;
    result = m1.IsEqual(m2);
    EXPECT_FALSE(result);
}

TEST(MonomialTests, Method_IsEqual_TermCoefficientIsDifferent_ReturnsFalse)
{
    Monomial testTerm0(1, 2);
    Monomial testTerm1(2.2, 2);

    EXPECT_FALSE(testTerm0.IsEqual(testTerm1));
    EXPECT_FALSE(testTerm0 == testTerm1);
    EXPECT_TRUE(testTerm0 != testTerm1);
}

TEST(MonomialTests, Method_IsEqual_TermExponentIsDifferent_ReturnsFalse)
{
    Monomial testTerm0(2, 5);
    Monomial testTerm1(2, 2);

    EXPECT_FALSE(testTerm0.IsEqual(testTerm1));
    EXPECT_FALSE(testTerm0 == testTerm1);
    EXPECT_TRUE(testTerm0 != testTerm1);
}

TEST(MonomialTests, CopyConstructor_TermIsProvided_TermIsTheSame)
{
    Monomial m1(2.1, 5);
    Monomial copy(m1);

    EXPECT_TRUE(m1 == copy);
}

TEST(MonomialTests, Operator_SingleMultiplication_ResultIsCorrect)
{
    Monomial term0(2, 2);
    Monomial term1(3, 4);
    Monomial correctResult(6, 6);
    EXPECT_TRUE(correctResult == (term0 * term1));
}

TEST(MonomialTests, Operator_SingleDivision_ResultIsCorrect)
{
    Monomial term0(2, 2);
    Monomial term1(3, 4);
    Monomial correctResult(1.5, 2);
    EXPECT_TRUE(correctResult == (term1 / term0));
}

TEST(MonomialTests, Method_Integrate_TermIsIntegrated_ResultIsCorrect)
{
    Monomial test(8, 3);
    Monomial correctResult(2, 4);
    test.Integrate();
    EXPECT_TRUE(correctResult == test);
}

TEST(MonomialTests, Method_IntegrateStatic_TermIsIntegrated_ResultIsCorrect)
{
    Monomial test(8, 3);
    Monomial correctResult(2, 4);
    test = Monomial::Integrate(test);
    EXPECT_TRUE(correctResult == test);
}

TEST(MonomialTests, Method_Differentiate_TermIsDifferentiated_ResultIsCorrect)
{
    Monomial term(8, 3);
    Monomial correctResult(24, 2);
    term.Differentiate();
    EXPECT_TRUE(correctResult == term);
}

TEST(MonomialTests, Method_DifferentiateStatic_TermIsDifferentiated_ResultIsCorrect)
{
    Monomial term(8, 3);
    Monomial correctResult(24, 2);
    term = Monomial::Differentiate(term);
    EXPECT_TRUE(correctResult == term);
}
