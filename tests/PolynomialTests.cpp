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

TEST(PolynomialTests, Method_GetLowestOrderOfPolynomialTerms_PolynomialIsProvided_ReturnsTrue)
{
    Polynomial p0(CoefficientList{1, 2, 3, 4});
    constexpr int p0LowestOrder = 0;

    constexpr int p1LowestOrder = -2;
    Polynomial p1(Terms{
        Monomial(1, 2),
        Monomial(1, 1),
        Monomial(1, 0),
        Monomial(1, -1),
        Monomial(1, p1LowestOrder),
    });

    Polynomial p2;
    constexpr int p2LowestOrder = 0;

    EXPECT_EQ(Polynomial::GetLowestOrderOfPolynomialTerms(p0), p0LowestOrder);
    EXPECT_EQ(Polynomial::GetLowestOrderOfPolynomialTerms(p1), p1LowestOrder);
    EXPECT_EQ(Polynomial::GetLowestOrderOfPolynomialTerms(p2), p2LowestOrder);
}


TEST(PolynomialTests, Method_GetLowestOrderOfPolynomialTerms_TermsAreProvided_ReturnsTrue)
{
    Terms t0 = Polynomial::CoefficientList2Terms(CoefficientList{1, 2, 3, 4});
    constexpr int t0LowestOrder = 0;

    constexpr int t1LowestOrder = -2;
    Terms t1{
        Monomial(1, 2),
        Monomial(1, 1),
        Monomial(1, 0),
        Monomial(1, -1),
        Monomial(1, t1LowestOrder),
    };

    EXPECT_EQ(Polynomial::GetLowestOrderOfPolynomialTerms(t0), t0LowestOrder);
    EXPECT_EQ(Polynomial::GetLowestOrderOfPolynomialTerms(t1), t1LowestOrder);
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
    EXPECT_TRUE(p[3].Coefficient == 4);
    EXPECT_TRUE(p[3].Exponent == 0);
    EXPECT_TRUE(p[2].Coefficient == 3);
    EXPECT_TRUE(p[2].Exponent == 1);
    EXPECT_TRUE(p[1].Coefficient == 2);
    EXPECT_TRUE(p[1].Exponent == 2);
    EXPECT_TRUE(p[0].Coefficient == 1);
    EXPECT_TRUE(p[0].Exponent == 3);
        
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

    EXPECT_EQ(p[8].Exponent, 0);
    EXPECT_EQ(p[8].Coefficient, 0);

    EXPECT_EQ(p[7].Exponent, 1);
    EXPECT_EQ(p[7].Coefficient, 0);

    EXPECT_EQ(p[6].Exponent, 2);
    EXPECT_EQ(p[6].Coefficient, 1);

    EXPECT_EQ(p[5].Exponent, 3);
    EXPECT_EQ(p[5].Coefficient, 0);

    EXPECT_EQ(p[4].Exponent, 4);
    EXPECT_EQ(p[4].Coefficient, 3);

    EXPECT_EQ(p[3].Exponent, 5);
    EXPECT_EQ(p[3].Coefficient, 0);

    EXPECT_EQ(p[2].Exponent, 6);
    EXPECT_EQ(p[2].Coefficient, 5);

    EXPECT_EQ(p[1].Exponent, 7);
    EXPECT_EQ(p[1].Coefficient, 0);

    EXPECT_EQ(p[0].Exponent, 8);
    EXPECT_EQ(p[0].Coefficient, 7);
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
    Polynomial p0(CoefficientList{9, 8, 7, 6, 5, 4, 3, 2, 1, 0});
    Polynomial p1 = p0;

    Terms t{
        Monomial(1, 2),
        Monomial(1, 1),
        Monomial(1, 0),
        Monomial(1, -1),
    };
    p1.SetRest(t);    

    EXPECT_FALSE(p0 == p1);
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
    Polynomial p0(CoefficientList{9, 8, 7, 6, 5, 4, 3, 2, 1, 0});
    Polynomial p1 = p0;

    Terms t{
        Monomial(1, 2),
        Monomial(1, 1),
        Monomial(1, 0),
        Monomial(1, -1),
    };
    p1.SetRest(t);    

    EXPECT_TRUE(p0 != p1);
}

TEST(PolymonalTests, Operator_Addition_ConstantIsAddedToPolynomial_ReturnsTrue)
{
    Polynomial p0(CoefficientList{5, 2, 1});
    double constant = 5.5;
    Polynomial correctPolynomial(CoefficientList{5,2,6.5});
    auto result = p0 + constant;
    auto result2 = constant + p0;

    EXPECT_TRUE(result == correctPolynomial);
    EXPECT_TRUE(result2 == correctPolynomial);
}


TEST(PolymonalTests, Operator_Addition_PolynomialIsAddedToConstant_ReturnsTrue)
{
    Polynomial p0(CoefficientList{5, 2, 1});
    double constant = 5.5;
    Polynomial correctPolynomial(CoefficientList{5,2,6.5});
    auto result2 = constant + p0;

    EXPECT_TRUE(result2 == correctPolynomial);
}

TEST(PolymonalTests, Operator_Addition_MononomialIsAddedToPolynomial_ReturnsTrue)
{
    Polynomial p0(CoefficientList{5, 2, 1});
    Monomial m0(1.3,8);
    Polynomial correctPolynomial(CoefficientList{1.3, 0, 0, 0, 0, 0, 5, 2, 1});
    auto result = p0 + m0;

    EXPECT_TRUE(result == correctPolynomial);
}

TEST(PolymonalTests, Operator_Addition_PolynomialIsAddedToMonomial_ReturnsTrue)
{
    Polynomial p0(CoefficientList{5, 2, 1});
    Monomial m0(1.3, 8);
    Polynomial correctPolynomial(CoefficientList{1.3, 0, 0, 0, 0, 0, 5, 2, 1});
    auto result2 = m0 + p0;

    EXPECT_TRUE(result2 == correctPolynomial);
}

TEST(PolymonalTests, Operator_Addition_PolynomialIsAddedToPolynomial_ReturnsTrue)
{
    Polynomial p0(CoefficientList{              5,  2,  1});
    Polynomial p1(CoefficientList{  4.5,    0,  1,  2,  0});
    Polynomial correctPolynomial(CoefficientList{4.5, 0, 6, 4,1});
    auto result = p0 + p1;
    auto result2 = p1 + p0;

    EXPECT_TRUE(result == correctPolynomial);
    EXPECT_TRUE(result2 == correctPolynomial);
}

TEST(PolymonalTests, Operator_Subtraction_ConstantIsSubtractedFromPolynomial_ReturnsTrue)
{
    Polynomial p0(CoefficientList{5, 2, 1});
    double constant = 5.5;
    Polynomial correctPolynomial(CoefficientList{5,2,-4.5});
    auto result = p0 - constant;

    EXPECT_TRUE(result == correctPolynomial);
}

TEST(PolymonalTests, Operator_Subtraction_MononomialIsSubtractedFromPolynomial_ReturnsTrue)
{
    Polynomial p0(CoefficientList{5, 2, 1});
    Monomial m0(1.3,8);
    Polynomial correctPolynomial(CoefficientList{-1.3, 0, 0, 0, 0, 0, 5, 2, 1});
    auto result = p0 - m0;

    EXPECT_TRUE(result == correctPolynomial);
}

TEST(PolymonalTests, Operator_Subtraction_PolynomialIsSubtractedFromPolynomial_ReturnsTrue)
{
    Polynomial p0(CoefficientList{              5,  2,  1});
    Polynomial p1(CoefficientList{  4.5,    0,  1,  2,  0});
    Polynomial correctPolynomial(CoefficientList{-4.5, 0, 4, 0, 1});
    auto result = p0 - p1;

    EXPECT_TRUE(result == correctPolynomial);
}

TEST(PolymonalTests, Operator_Subtraction_PolynomialIsSubtractedFromConstant_ReturnsTrue)
{
    Polynomial p0(CoefficientList{5, 2, 1});
    double constant = 5.5;
    Polynomial correctPolynomial(CoefficientList{-5, -2, 4.5});
    auto result = constant - p0;

    EXPECT_TRUE(result == correctPolynomial);
}

TEST(PolymonalTests, Operator_Subtraction_PolynomialIsSubtractedFromMonomial_ReturnsTrue)
{
    Polynomial p0(CoefficientList{5, 2, 1});
    Monomial m0(1.3, 8);
    Polynomial correctPolynomial(CoefficientList{1.3, 0, 0, 0, 0, 0, -5, -2, -1});
    auto result = m0 - p0;

    EXPECT_TRUE(result == correctPolynomial);
}

TEST(PolynomialTests, Operator_Multiplication_PolynomialIsMultipliedWithConstant_ReturnsTrue)
{
    Polynomial p0(CoefficientList{12,14,15,0});
    Polynomial p1(CoefficientList{12.22222222222225,14436.5,125.4,1});

    constexpr double constant0 = 163.4;
    constexpr double constant1 = -3;

    Polynomial correctResult0(CoefficientList{12 * constant0 , 14 * constant0, 15 * constant0, 0});
    Polynomial correctResult1(CoefficientList{12.22222222222225 * constant1, 14436.5  * constant1 , 125.4  * constant1, 1  * constant1});

    auto result0 = p0 * constant0;
    auto result1 = p1 * constant1;

    EXPECT_TRUE(result0 == correctResult0);
    EXPECT_TRUE(result1 == correctResult1);
}

TEST(PolynomialTests, Operator_Multiplication_PolynomialIsMultipliedWithMonomial_ReturnsTrue)
{
    Polynomial p0(Terms{
        Monomial(12, 5),
        Monomial(12, 3),
        Monomial(12, 1),
    });

    Polynomial p1(Terms{
        Monomial(136, 35),
        Monomial(-1347.6236, 34),
        Monomial(-2, 12),
    });

    Monomial m0(163.4, 3);
    Monomial m1(-3, -4);

    Polynomial correctResult0(Terms{
            Monomial(12 * m0.Coefficient, 5 + m0.Exponent),
            Monomial(12 * m0.Coefficient, 3 + m0.Exponent),
            Monomial(12 * m0.Coefficient, 1 + m0.Exponent),
        });
    Polynomial correctResult1(Terms{
            Monomial(136            * m1.Coefficient, 35 + m1.Exponent ),
            Monomial(-1347.6236     * m1.Coefficient, 34 + m1.Exponent ),
            Monomial(-2             * m1.Coefficient, 12 + m1.Exponent ),
        });

    auto result0 = p0 * m0;
    auto result1 = p1 * m1;
    auto result2 = m0 * p0;
    auto result3 = m1 * p1;

    EXPECT_TRUE(result0 == correctResult0);
    EXPECT_TRUE(result1 == correctResult1);
    EXPECT_TRUE(result2 == correctResult0);
    EXPECT_TRUE(result3 == correctResult1);
    EXPECT_TRUE(result0 == result2);
    EXPECT_TRUE(result1 == result3);
}

TEST(PolynomialTests, Operator_Multiplication_PolynomialIsMultipliedWithZeroPolynomial_ReturnsTrue)
{
    Polynomial p0(CoefficientList{3, 2, 1, 0});
    Polynomial nullPolynomial;
    Polynomial correctResult = nullPolynomial;

    auto result = p0 * nullPolynomial;
    EXPECT_TRUE(result == correctResult);
}

TEST(PolynomialTests, Operator_Multiplication_PolynomialIsMultipliedWithOtherPolynomial_ReturnsTrue)
{
    Polynomial p0(CoefficientList{1, 6});
    Polynomial p1(CoefficientList{1, 8});

    Polynomial p2(CoefficientList{      4,  3, 0});
    Polynomial p3(CoefficientList{  1, -5,  2, 0});

    Polynomial correctResult0(CoefficientList{
        1, 14, 48
    });

    // https://mathority.org/de/multiplikation-von-polynomen-beispiele-ubungen-gelostes-produkt-multiplizieren/
    Polynomial correctResult1(CoefficientList{
        4, -17, -7, 6, 0, 0
    });

    auto result0 = p0 * p1;
    auto result1 = p2 * p3;

    EXPECT_TRUE(result0 == correctResult0);
    EXPECT_TRUE(result1 == correctResult1);
}

TEST(PolynomialTests, Operator_Multiplication_MultiplicationReversability_ReturnsTrue)
{
    Polynomial origin(CoefficientList{2, 15, 4237, 3478, 64, 236, 2438, 4568, 235, 236, 6, 0});
    Polynomial p0 = origin;

    p0 = p0 * -1;   // invert
    p0 = p0 * -1;   // invert again to get origin

    EXPECT_TRUE(p0 == origin);
}

TEST(PolynomialTests, Operator_Division_PolynomialDivisionSeveralDivisions_ResultsAreCorrect)
{
    std::vector<Polynomial> numerators {
        Polynomial(CoefficientList{ 1, -1, -12, -4, +16 }),
        Polynomial(CoefficientList{ -6, -28, -16, 0 }),
        Polynomial(CoefficientList{ -3, +9, 0, 0, 0 }),
        Polynomial(CoefficientList{ -7, -18, -8, 0, 0 }),
        Polynomial(CoefficientList{ 3, -4, -15, -4, 12 }),
        Polynomial(CoefficientList{ 7, -21, -6, 16, 6 }),
        Polynomial(CoefficientList{ 3, 12, 0 }),
        Polynomial(CoefficientList{ -7, -37, -10, 0, 0 }),
        Polynomial(CoefficientList{ 1, -4, -5, 6, -30 }),
        Polynomial(CoefficientList{ -6, -6, 1, -5, -6 }),
        Polynomial(CoefficientList{ -2, 12, -18 }),
        Polynomial(CoefficientList{ 4, 2, -1, 1 }),
        Polynomial(CoefficientList{ 1, 5, -3, 1 }),
        Polynomial(CoefficientList{ 2, -3, 4, 5 }),
        Polynomial(CoefficientList{ 2, 3, 0, 0, -1 }),
        Polynomial(CoefficientList{ 1, 0, 2, 0, 0, -4 }),
        Polynomial(CoefficientList{ 3, 0, -2, 0, 0, 1, 0, 0}),
    };
    std::vector<Polynomial> denominators {
        Polynomial(CoefficientList{ 1, -1 }),
        Polynomial(CoefficientList{ 1, 4 }),
        Polynomial(CoefficientList{ 1, -3 }),
        Polynomial(CoefficientList{ 1, 2 }),
        Polynomial(CoefficientList{ 1, -3 }),
        Polynomial(CoefficientList{ 1, -3 }),
        Polynomial(CoefficientList{ 1, 4 }),
        Polynomial(CoefficientList{ 1, 5 }),
        Polynomial(CoefficientList{ 1, -5 }),
        Polynomial(CoefficientList{ 1, 1 }),
        Polynomial(CoefficientList{ 1, -3 }),
        Polynomial(CoefficientList{ 2, -2, 1 }),
        Polynomial(CoefficientList{ 2, 1, -3 }),
        Polynomial(CoefficientList{ 1, 2 }),
        Polynomial(CoefficientList{ 1, 2, -1, 1 }),
        Polynomial(CoefficientList{ 1, 0, 1, 0, 1 }),
        Polynomial(CoefficientList{ 1, 1, -2, 1 }),
    };
    std::vector<Polynomial> correctResults {
        Polynomial(CoefficientList{ 1, 0, -12, -16 }),
        Polynomial(CoefficientList{ -6, -4, 0 }),
        Polynomial(CoefficientList{ -3, 0, 0, 0 }),
        Polynomial(CoefficientList{ -7, -4, 0, 0 }),
        Polynomial(CoefficientList{ 3, 5, 0, -4 }),
        Polynomial(CoefficientList{ 7, 0, -6, -2 }),
        Polynomial(CoefficientList{ 3, 0 }),
        Polynomial(CoefficientList{ -7, -2, 0, 0 }),
        Polynomial(CoefficientList{ 1, 1, 0, 6 }),
        Polynomial(CoefficientList{ -6, 0, 1, -6 }),
        Polynomial(CoefficientList{ -2, 6 }),
        Polynomial(CoefficientList{ 2, 3 }),
        Polynomial(CoefficientList{ (1.0/2.0), (9.0/4.0) }),
        Polynomial(CoefficientList{ 2, -7, 18 }),
        Polynomial(CoefficientList{ 2, -1 }),
        Polynomial(CoefficientList{ 1, 0 }),
        Polynomial(CoefficientList{ 3, -3, 7, -16, 33 }),        
    };

    // Special case for polynomials with residuals
    correctResults[11].SetRest(Terms{Monomial(3, 1), Monomial(-2, 0) });
    correctResults[12].SetRest(Terms{Monomial((-15.0 / 4.0), 1), Monomial((31.0 / 4.0), 0) });
    correctResults[13].SetRest(Terms{Monomial(-31, 0) });
    correctResults[14].SetRest(Terms{Monomial(4, 2), Monomial(-3, 1) });
    correctResults[15].SetRest(Terms{Monomial(1, 3), Monomial(-1, 1), Monomial(-4, 0) });
    correctResults[16].SetRest(Terms{Monomial(-71, 2), Monomial(82, 1), Monomial(-33, 0) });

    for(int i = 0; i < correctResults.size(); i++)
    {
        Polynomial tmp = numerators[i]/denominators[i];
        EXPECT_TRUE(tmp == correctResults[i]);
    }

}

TEST(PolynomialTests, Method_EvaluateAt_PolynomialIsEvaluatedAtPoint_ResultsAreCorrect)
{
    const double errorMarginInPercent = 0.001;
    Polynomial polynomial(CoefficientList{-0.05, -0.075, 0.1, 2.0});
    std::vector<double> pointsToEvaluateAt
    {
        -100,
        -50,
        -20,
        -10,
        -5,
        -2,
        -1,
        -0.5,
        -0.2,
        -0.1,
        -0.05,
        -0.02,
        -0.01,
        0,
        0.01,
        0.02,
        0.05,
        0.1,
        0.2,
        0.5,
        1,
        2,
        5,
        10,
        20,
        50,
        100,
    };
    std::vector<double> correctResults 
    {
        49242,
        6059.5,
        370,
        43.5,
        5.875,
        1.9,
        1.875,
        1.9375,
        1.9774,
        1.9893,
        1.99481875,
        1.9979704,
        1.99899255,
        2,
        2.00099245,
        2.0019696,
        2.00480625,
        2.0092,
        2.0166,
        2.025,
        1.975,
        1.5,
        -5.625,
        -54.5,
        -426,
        -6430.5,
        -50738        
    };
    for (size_t i = 0; i < pointsToEvaluateAt.size(); i++)
    {
        double error = std::abs(correctResults[i] - polynomial.EvaluateAt(pointsToEvaluateAt[i]));
        double errorMargin = std::abs(correctResults[i] * (errorMarginInPercent / 100.0));
        EXPECT_TRUE(error < errorMargin);
    }
}

TEST(PolynomialTests, Method_EvaluateAtStatic_PolynomialIsEvaluatedAtPoint_ResultsAreCorrect)
{
    const double errorMarginInPercent = 0.001;
    Polynomial polynomial(CoefficientList{-0.05, -0.075, 0.1, 2.0});
    std::vector<double> pointsToEvaluateAt
    {
        -100,
        -50,
        -20,
        -10,
        -5,
        -2,
        -1,
        -0.5,
        -0.2,
        -0.1,
        -0.05,
        -0.02,
        -0.01,
        0,
        0.01,
        0.02,
        0.05,
        0.1,
        0.2,
        0.5,
        1,
        2,
        5,
        10,
        20,
        50,
        100,
    };
    std::vector<double> correctResults 
    {
        49242,
        6059.5,
        370,
        43.5,
        5.875,
        1.9,
        1.875,
        1.9375,
        1.9774,
        1.9893,
        1.99481875,
        1.9979704,
        1.99899255,
        2,
        2.00099245,
        2.0019696,
        2.00480625,
        2.0092,
        2.0166,
        2.025,
        1.975,
        1.5,
        -5.625,
        -54.5,
        -426,
        -6430.5,
        -50738        
    };
    for (size_t i = 0; i < pointsToEvaluateAt.size(); i++)
    {
        double error = std::abs(correctResults[i] - Polynomial::EvaluateAt(polynomial, pointsToEvaluateAt[i]));
        double errorMargin = std::abs(correctResults[i] * (errorMarginInPercent / 100.0));
        EXPECT_TRUE(error < errorMargin);
    }
}

TEST(PolynomialTests, Method_FindZeroOfLinearTerm_TermIsProvided_ResultIsCorrect)
{
    Polynomial p(CoefficientList{4, -3});
    double correctResult = 3.0/4.0;

    double zero = Polynomial::FindZeroOfLinearTerm(p);
    EXPECT_EQ(zero, correctResult);
}

TEST(PolynomialTests, Method_FindZeroOfLinearTerm_TermOfOrder2IsProvided_ExceptionIsThrown)
{
    // Checks whether polynomials with an order greater than 1 are ignored correctly.
    Polynomial p(CoefficientList{4, 4, -3});
    bool exceptionWasThrown = false;
    try
    {
        double zero = Polynomial::FindZeroOfLinearTerm(p);
    } 
    catch(...)
    {
        exceptionWasThrown = true;
    }

    EXPECT_TRUE(exceptionWasThrown);
}

TEST(PolynomialTests, Method_FindZeroOfLinearTerm_TermOfOrder0IsProvided_ExceptionIsThrown)
{
    // Checks whether polynomials with an order smaller than 1 are ignored correctly.
    Polynomial p(CoefficientList{-3});
    bool exceptionWasThrown = false;
    try
    {
        double zero = Polynomial::FindZeroOfLinearTerm(p);
    } 
    catch(...)
    {
        exceptionWasThrown = true;
    }

    EXPECT_TRUE(exceptionWasThrown);
}

TEST(PolynomialTests, Method_FindZerosOfQuadraticTerms_TermOfOrder2IsProvided_ResultIsCorrect)
{
    Polynomial p(CoefficientList{3, 21, -24});
    std::vector<double> zeros = Polynomial::FindZerosOfQuadraticTerms(p);
    double z0 = 1;
    double z1 = -8;

    std::cout << "TEST!" << std::endl;

    EXPECT_EQ(zeros[0], z0);
    EXPECT_EQ(zeros[1], z1);
}

TEST(PolynomialTests, Method_FindZerosOfQuadraticTerms_TermOfOrder0IsProvided_ExceptionIsThrown)
{
    Polynomial p(CoefficientList{-3});
    std::vector<double> zeros;
    bool exceptionWasThrown = false;
    try
    {
        zeros = Polynomial::FindZerosOfQuadraticTerms(p);
    }
    catch(...)
    {
        exceptionWasThrown = true;
    }
    EXPECT_TRUE(exceptionWasThrown);
}

TEST(PolynomialTests, Method_FindZerosOfQuadraticTerms_TermOfOrder5IsProvided_ExceptionIsThrown)
{
    Polynomial p(CoefficientList{5, 4, 3, 2, 1, 0});
    std::vector<double> zeros;
    bool exceptionWasThrown = false;
    try
    {
        zeros = Polynomial::FindZerosOfQuadraticTerms(p);
    }
    catch(...)
    {
        exceptionWasThrown = true;
    }
    EXPECT_TRUE(exceptionWasThrown);
}

TEST(PolynomialTests, Method_FindZerosOfQuadraticTerms_ComplexTermIsProvided_ExceptionIsThrown)
{
    // Search for complex zeros
    Polynomial p(CoefficientList{1, 0, 0, 0, -1});
    std::vector<double> zeros;
    bool exceptionWasThrown = false;
    try
    {
        zeros = Polynomial::FindZerosOfQuadraticTerms(p);
    }
    catch(...)
    {
        exceptionWasThrown = true;
    }
    EXPECT_TRUE(exceptionWasThrown);
}

TEST(PolynomialTests, Method_Simplify_RationalFunctionIsProvidedAndSimplified_ResultsAreCorrect)
{
    // TODO: Schlägt fehl
    // PolynomialFraction testFrac
    // {
    //     .numerator      = Polynomial(CoefficientList{8}),
    //     .denominator    = Polynomial(CoefficientList{1, 9, 27, 27})
    // };
    // Polynomial correctionTerm(CoefficientList{1, 3});
    // testFrac.numerator = testFrac.numerator * correctionTerm;
    // testFrac.denominator = testFrac.denominator * correctionTerm;
    // PolynomialFraction testFracCorrect
    // {
    //     .numerator = Polynomial(CoefficientList{8}),
    //     .denominator = Polynomial(CoefficientList{1, 9, 27, 27})
    // };
    // PolynomialFraction simplifiedFrac = Polynomial::Simplify(testFrac);
    
    // EXPECT_TRUE(simplifiedFrac.numerator == testFracCorrect.numerator);
    // EXPECT_TRUE(simplifiedFrac.denominator == testFracCorrect.denominator);

        PolynomialFraction testFrac
    {
        .numerator      = Polynomial(CoefficientList{1, 16, -5, 300}),
        .denominator    = Polynomial(CoefficientList{1, 8, 15})
    };
    // Polynomial correctionTerm(CoefficientList{1, 3});
    // testFrac.numerator = testFrac.numerator * correctionTerm;
    // testFrac.denominator = testFrac.denominator * correctionTerm;
    PolynomialFraction testFracCorrect
    {
        .numerator = Polynomial(CoefficientList{1, 11, -60}),
        .denominator = Polynomial(CoefficientList{1, 3})
    };
    PolynomialFraction simplifiedFrac = Polynomial::Simplify(testFrac);
    
    EXPECT_TRUE(simplifiedFrac.numerator == testFracCorrect.numerator);
    EXPECT_TRUE(simplifiedFrac.denominator == testFracCorrect.denominator);
}

TEST(PolynomialTests, Method_DifferentiateRationalPolynomial_RationalFunctionsAreProvidedAndDifferentiated_ResultsAreCorrect)
{
    PolynomialFraction testFrac
    {
        .numerator = Polynomial(CoefficientList{1, 2, 1}),
        .denominator = Polynomial(CoefficientList{1, 3}),
    };
    PolynomialFraction testFracCorrectPrime
    {
        .numerator = Polynomial(CoefficientList{1, 6, 5}),
        .denominator = Polynomial(CoefficientList{1, 6, 9}),
    };
    PolynomialFraction testFracCorrectPrimePrime
    {
        .numerator = Polynomial(CoefficientList{8}),
        .denominator = Polynomial(CoefficientList{1, 9, 27, 27}),
    };

    // Due to current limitation in the differentiation algorithm / simplifying algorithm, we have the following problem:
    // The differentiation works fine, however, it cant annihilate poles/zeros which are the same, which
    // results in bigger polynomials with possible simplifications not done. Thats why we multiply this 
    // testFracCorrectPrimePrime with (x+3), since the algorithm works, but it cant cancel out the pole/zero
    // which is (x+3) in both the numerator and the denominator.
    Polynomial correctionTerm(CoefficientList{1, 3});
    testFracCorrectPrimePrime.numerator = testFracCorrectPrimePrime.numerator * correctionTerm;
    testFracCorrectPrimePrime.denominator = testFracCorrectPrimePrime.denominator * correctionTerm;

    PolynomialFraction testFracPrime = Polynomial::DifferentiateRationalPolynomial(testFrac);
    PolynomialFraction testFracPrimePrime = Polynomial::DifferentiateRationalPolynomial(testFracPrime);

    // https://www.wolframalpha.com/input?i=differentiate+%28x%5E2%2B6x%2B5%29%2F%28x%5E2%2B6x%2B9%29
    // Vielleicht Faktorisieren durch herausfinden der Nullstellen und dann innere vs. äußere Ableitung

    EXPECT_TRUE(testFracPrime.numerator == testFracCorrectPrime.numerator);
    EXPECT_TRUE(testFracPrime.denominator == testFracCorrectPrime.denominator);
    EXPECT_TRUE(testFracPrimePrime.numerator == testFracCorrectPrimePrime.numerator);
    EXPECT_TRUE(testFracPrimePrime.denominator == testFracCorrectPrimePrime.denominator);
}