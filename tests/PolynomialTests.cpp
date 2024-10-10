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

TEST(PolynomialTests, Method_Differentiate_PolynomialIsDifferentiated_ReturnsTrue)
{
    Polynomial original(CoefficientList{-3,3,3,-3,8});
    Polynomial correctResult(Terms{
        Monomial(-12,3),
        Monomial(9,2),
        Monomial(6,1),
        Monomial(-3,0)
    });

    Polynomial differentiated(original);
    differentiated.Differentiate();
    EXPECT_TRUE(differentiated == correctResult);
}

TEST(PolynomialTests, Method_DifferentiateStatic_PolynomialIsDifferentiated_ReturnsTrue)
{
    Polynomial original(CoefficientList{-3,3,3,-3,8});
    Polynomial correctResult(Terms{
        Monomial(-12,3),
        Monomial(9,2),
        Monomial(6,1),
        Monomial(-3,0)
    });

    Polynomial differentiated = Polynomial::Differentiate(original);
    EXPECT_TRUE(differentiated == correctResult);
}

TEST(PolynomialTests, Method_Integrate_PolynomialIsIntegrated_ReturnsTrue)
{
    Polynomial original(CoefficientList{5,-4,3,-2,8.5});
    Polynomial correctResult(Terms{
        Monomial(1, 5),
        Monomial(-1, 4),
        Monomial(1, 3),
        Monomial(-1, 2),
        Monomial(8.5, 1)
    });

    Polynomial integrated(original);
    integrated.Integrate();
    EXPECT_TRUE(integrated == correctResult);
}

TEST(PolynomialTests, Method_IntegrateStatic_PolynomialIsIntegrated_ReturnsTrue)
{
    Polynomial original(CoefficientList{5,-4,3,-2,8.5});
    Polynomial correctResult(Terms{
        Monomial(1, 5),
        Monomial(-1, 4),
        Monomial(1, 3),
        Monomial(-1, 2),
        Monomial(8.5, 1)
    });

    Polynomial integrated = Polynomial::Integrate(original);
    EXPECT_TRUE(integrated == correctResult);
}

TEST(PolynomialTests, Constructor_DefaultConstructorIsInvoked_DefaultConstructorWorks)
{
    Polynomial p;

    EXPECT_TRUE(p.GetOrder() == 0);
    EXPECT_TRUE(p[0].Coefficient == 0);
    EXPECT_TRUE(p[0].Exponent == 0);

    Monomial nullTerm(0,0);
    int restOrder = p.GetRestOrder();
    EXPECT_EQ(restOrder, 0);
    EXPECT_EQ(p.GetRest().size(), 1);
    EXPECT_TRUE(nullTerm == p.GetRest()[0]);
}

TEST(PolynomialTests, Constructor_ConstructorTakesCoefficientList_ConstructorWorks)
{
    CoefficientList cl{1,2,3,4};

    Polynomial p(cl); // Create polynomial
    EXPECT_TRUE(p.GetOrder() == 3);
    EXPECT_TRUE(p[0].Coefficient == 4);
    EXPECT_TRUE(p[0].Exponent == 0);
    EXPECT_TRUE(p[1].Coefficient == 3);
    EXPECT_TRUE(p[1].Exponent == 1);
    EXPECT_TRUE(p[2].Coefficient == 2);
    EXPECT_TRUE(p[2].Exponent == 2);
    EXPECT_TRUE(p[3].Coefficient == 1);
    EXPECT_TRUE(p[3].Exponent == 3);
        
    Monomial nullTerm(0,0);
    int restOrder = p.GetRestOrder();
    EXPECT_EQ(restOrder, 0);
    EXPECT_EQ(p.GetRest().size(), 1);
    EXPECT_TRUE(nullTerm == p.GetRest()[0]);

}

TEST(PolynomialTests, Constructor_ConstructorTakesMonomialList_ConstructorWorks)
{
    Monomial nullTerm(0,0);

    Terms terms {
        Monomial(1,2),
        Monomial(3,4),
        Monomial(5,6),
        Monomial(7,8)
    };

    Polynomial p(terms);
    int order = p.GetOrder();
    int restOrder = p.GetRestOrder();
    EXPECT_EQ(order, 8);
    
    EXPECT_EQ(restOrder, 0);
    EXPECT_EQ(p.GetRest().size(), 1);
    EXPECT_TRUE(nullTerm == p.GetRest()[0]);

    EXPECT_EQ(p[0].Exponent, 0);
    EXPECT_EQ(p[0].Coefficient, 0);

    EXPECT_EQ(p[1].Exponent, 1);
    EXPECT_EQ(p[1].Coefficient, 0);

    EXPECT_EQ(p[2].Exponent, 2);
    EXPECT_EQ(p[2].Coefficient, 1);

    EXPECT_EQ(p[3].Exponent, 3);
    EXPECT_EQ(p[3].Coefficient, 0);

    EXPECT_EQ(p[4].Exponent, 4);
    EXPECT_EQ(p[4].Coefficient, 3);

    EXPECT_EQ(p[5].Exponent, 5);
    EXPECT_EQ(p[5].Coefficient, 0);

    EXPECT_EQ(p[6].Exponent, 6);
    EXPECT_EQ(p[6].Coefficient, 5);

    EXPECT_EQ(p[7].Exponent, 7);
    EXPECT_EQ(p[7].Coefficient, 0);

    EXPECT_EQ(p[8].Exponent, 8);
    EXPECT_EQ(p[8].Coefficient, 7);
}

TEST(PolynomialTests, CopyConstructor_ConstructorIsInvoked_ConstructorWorks)
{
    Terms terms {
        Monomial(1,2),
        Monomial(3,4),
    };

    Polynomial p(terms); // Create polynomial
    EXPECT_TRUE(p.GetOrder() == 4);

    Polynomial copy(p);
    EXPECT_TRUE(copy.GetOrder() == 4);
    EXPECT_TRUE(p == copy);
}

TEST(PolynomialTests, Operator_Equals_SamePolynomialsAreProvided_ReturnsTrue)
{
    Polynomial p0(CoefficientList{1,2.3,236,34.3453,1});
    Polynomial p1(CoefficientList{1,2.3,236,34.3453,1});
    EXPECT_TRUE(p0 == p1);
}

TEST(PolynomialTests, Operator_Equals_DifferentPolynomialsAreProvided_ReturnsFalse)
{
    Polynomial p0(CoefficientList{1,2.3,236,34.3453,1});
    Polynomial p1(CoefficientList{1,2.3,236,34.3455,2,4});
    EXPECT_FALSE(p0 == p1);
}

TEST(PolynomialTests, Operator_Equals_OnePolynomialsRestIsDifferent_ReturnsTrue)
{
    // TODO: Do after you implemented polynomial division
    EXPECT_TRUE(false);
}

TEST(PolynomialTests, Operator_Unequals_SamePolynomialsAreProvided_ReturnsFalse)
{
    Polynomial p0(CoefficientList{1,2.3,236,34.3453,1});
    Polynomial p1(CoefficientList{1,2.3,236,34.3453,1});
    EXPECT_FALSE(p0 != p1);
}

TEST(PolynomialTests, Operator_Unequals_DifferentPolynomialsAreProvided_ReturnsTrue)
{
    Polynomial p0(CoefficientList{1,2.3,236,34.3453,1});
    Polynomial p1(CoefficientList{1,2.3,236,34.3455,2,4});
    EXPECT_TRUE(p0 != p1);   
}

TEST(PolynomialTests, Operator_Unequals_OnePolynomialsRestIsDifferent_ReturnsTrue)
{
    // TODO: Do after you implemented polynomial division
    EXPECT_TRUE(false);
}

TEST(PolymonalTests, Operator_Plus_ConstantIsAddedToPolynomial_ReturnsTrue)
{
    Polynomial p0(CoefficientList{5, 2, 1});
    double constant = 5.5;
    Polynomial correctPolynomial(CoefficientList{5,2,6.5});
    auto result = p0 + constant;
    auto result2 = constant + p0;

    EXPECT_TRUE(result == correctPolynomial);
    EXPECT_TRUE(result2 == correctPolynomial);
}

TEST(PolymonalTests, Operator_Plus_MononomialIsAddedToPolynomial_ReturnsTrue)
{
    Polynomial p0(CoefficientList{5, 2, 1});
    Monomial m0(1.3,8);
    Polynomial correctPolynomial(CoefficientList{1.3, 0, 0, 0, 0, 0, 5, 2, 1});
    auto result = p0 + m0;
    auto result2 = m0 + p0;

    EXPECT_TRUE(result == correctPolynomial);
    EXPECT_TRUE(result2 == correctPolynomial);
}

TEST(PolymonalTests, Operator_Plus_PolynomialIsAddedToPolynomial_ReturnsTrue)
{
    Polynomial p0(CoefficientList{              5,  2,  1});
    Polynomial p1(CoefficientList{  4.5,    0,  1,  2,  0});
    Polynomial correctPolynomial(CoefficientList{4.5, 0, 6, 4,1});
    auto result = p0 + p1;
    auto result2 = p1 + p0;

    EXPECT_TRUE(result == correctPolynomial);
    EXPECT_TRUE(result2 == correctPolynomial);
}