#include <gtest/gtest.h>

#include "../application/headers/polynomial.hpp"
#include "../application/headers/monomial.hpp"

using namespace Vath;

TEST(PolynomialTests, Method_IsEqual_OrderOrNumberOfTermsIsDifferent_ReturnsFalse)
{
    Polynomial p0(CoefficientList{3, 2, 1});
    Polynomial p1(CoefficientList{3, 2, 1, 0});
    bool result = p0.IsEqual(p1);
    EXPECT_FALSE(result);
}

TEST(PolynomialTests, Method_CoefficientList2Terms_CoefficientsAreProvided_ReturnsTrue)
{
    CoefficientList coefficients{2, 3.3, 4.1, 5, 6, 8, 112516};

    Terms terms = Polynomial::CoefficientList2Terms(coefficients);
    for(int i = 0; i < terms.size(); i++)
    {
        EXPECT_TRUE((terms[i].Coefficient == coefficients[i]));
    }
}

TEST(PolynomialTests, Method_Terms2CoefficientList_TermsAreProvided_ReturnsTrue)
{
    Terms terms { Monomial(1, 2), Monomial(2.12, 2), Monomial(3.1415, 2), Monomial(2.7e-3, 2)};

    CoefficientList coefficients;
    coefficients = Polynomial::Terms2CoefficientList(terms);
    for(int i = 0; i < coefficients.size(); i++)
    {
        EXPECT_TRUE((terms[i].Coefficient == coefficients[i]));
    }
}

TEST(PolynomialTests, Method_GetHighestOrderOfPolynomialTerms_PolynomialIsProvided_ReturnsTrue)
{
    Terms t{Monomial(1,0), Monomial(1,1), Monomial(1,256)}; 
    Polynomial p(t);
    int order = Polynomial::GetHighestOrderOfPolynomialTerms(p);
    EXPECT_EQ(order, t[t.size()-1].Exponent);
}

TEST(PolynomialTests, Method_GetHighestOrderOfPolynomialTerms_TermsAreProvided_ReturnsTrue)
{
    Terms t{Monomial(1,0), Monomial(1,1), Monomial(1,256)}; 
    int order = Polynomial::GetHighestOrderOfPolynomialTerms(t);
    EXPECT_EQ(order, t[t.size()-1].Exponent);
}

TEST(PolynomialTests, Method_InterpolateTerms_TermsAreProvided_ReturnsCorrectInterpolatedTerms)
{
    Terms t{Monomial(1, 2), Monomial(2, 6), Monomial(2349068, 7)};

    t = Polynomial::InterpolateTerms(t);
    
    EXPECT_EQ(t.size(), 8);
    // Check if every exponent is existant in the polynomial
    for(int i = 0; i < t.size(); i++)
    {
        EXPECT_EQ(t[t.size()-1-i].Exponent, i);
    }
}

TEST(PolynomialTests, Method_CombineTerms_TermsAreProvided_ReturnsCorrectCombinationOfTerms)
{
    Terms t {   Monomial(1, 0), 
                Monomial(2, 1), 
                Monomial(5, 2), 
                Monomial(9, 0), 
                Monomial(8, 1), 
                Monomial(5, 2),
                Monomial(5, 2),
            };

    Terms tCombined = Polynomial::CombineTerms(t);

    EXPECT_EQ(tCombined.size(), 3);
    EXPECT_EQ(tCombined[0].Exponent, 2);
    EXPECT_EQ(tCombined[1].Exponent, 1);
    EXPECT_EQ(tCombined[2].Exponent, 0);
    EXPECT_EQ(tCombined[0].Coefficient, 15);
    EXPECT_EQ(tCombined[1].Coefficient, 10);
    EXPECT_EQ(tCombined[2].Coefficient, 10);
}

TEST(PolynomialTests, Method_IsEqual_OrderOrNumberOfTermsIsTheSame_ReturnsTrue)
{
    Polynomial p0(CoefficientList{3, 2, 1});
    Polynomial p1(CoefficientList{3, 2, 1});
    bool result = p0.IsEqual(p1);
    EXPECT_TRUE(result);
}

TEST(PolynomialTests, Constructor_DefaultConstructorIsInvoked_DefaultConstructorWorks)
{
    Polynomial p;

    EXPECT_TRUE(p.Monomials.size() == 1);
    EXPECT_TRUE(p.Monomials[0].Coefficient == 0);
    EXPECT_TRUE(p.Monomials[0].Exponent == 0);
}

TEST(PolynomialTests, Constructor_ConstructorTakesCoefficientList_ConstructorWorks)
{
    CoefficientList cl{1,2,3,4};

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

TEST(PolynomialTests, Constructor_ConstructorTakesMonimialList_ConstructorWorks)
{
    Terms terms {
        Monomial(1,2),
        Monomial(3,4),
        Monomial(5,6),
        Monomial(7,8)
    };

    Polynomial p(terms); // Create polynomial
    EXPECT_TRUE(p.Monomials.size() == 4);
    EXPECT_TRUE(p.Monomials[0].Coefficient == 1);
    EXPECT_TRUE(p.Monomials[0].Exponent == 2);
    EXPECT_TRUE(p.Monomials[1].Coefficient == 3);
    EXPECT_TRUE(p.Monomials[1].Exponent == 4);
    EXPECT_TRUE(p.Monomials[2].Coefficient == 5);
    EXPECT_TRUE(p.Monomials[2].Exponent == 6);
    EXPECT_TRUE(p.Monomials[3].Coefficient == 7);
    EXPECT_TRUE(p.Monomials[3].Exponent == 8);
}

TEST(PolynomialTests, CopyConstructor_ConstructorIsInvoked_ConstructorWorks)
{
    Terms terms {
        Monomial(1,2),
        Monomial(3,4),
    };

    Polynomial p(terms); // Create polynomial
    EXPECT_TRUE(p.Monomials.size() == 2);

    Polynomial copy(p);
    EXPECT_TRUE(copy.Monomials.size() == 2);
    EXPECT_TRUE(p == copy);
}

