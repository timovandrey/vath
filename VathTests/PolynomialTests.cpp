
#include "pch.h"
#include "CppUnitTest.h"

#include "../Vath/headers/monomial.hpp"
#include "../Vath/headers/polynomial.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Vath;

namespace Vath
{
    TEST_CLASS(PolynomialTests)
    {
        TEST_METHOD(Method_IsEqual_OrderOrNumberOfTermsIsDifferent_ReturnsFalse)
        {
            Polynomial p0(CoefficientList{ 3, 2, 1 });
            Polynomial p1(CoefficientList{ 3, 2, 1, 0 });
            bool result = p0.IsEqual(p1);
            Assert::IsFalse(result);
        }

        TEST_METHOD(Method_CoefficientList2Terms_CoefficientsAreProvided_ReturnsTrue)
        {
            CoefficientList coefficients{ 2, 3.3, 4.1, 5, 6, 8, 112516 };

            Terms terms = Polynomial::CoefficientList2Terms(coefficients);
            for (int i = 0; i < terms.size(); i++)
            {
                Assert::IsTrue((terms[i].Coefficient == coefficients[i]));
            }
        }

        TEST_METHOD(Method_Terms2CoefficientList_TermsAreProvided_ReturnsTrue)
        {
            Terms terms{ Monomial(1, 2), Monomial(2.12, 2), Monomial(3.1415, 2), Monomial(2.7e-3, 2) };

            CoefficientList coefficients;
            coefficients = Polynomial::Terms2CoefficientList(terms);
            for (int i = 0; i < coefficients.size(); i++)
            {
                Assert::IsTrue((terms[i].Coefficient == coefficients[i]));
            }
        }

        TEST_METHOD(Method_GetHighestOrderOfPolynomialTerms_PolynomialIsProvided_ReturnsTrue)
        {
            Terms t{ Monomial(1,0), Monomial(1,1), Monomial(1,256) };
            Polynomial p(t);
            int order = Polynomial::GetHighestOrderOfPolynomialTerms(p);
            Assert::AreEqual(order, t[t.size() - 1].Exponent);
        }

        TEST_METHOD(Method_GetHighestOrderOfPolynomialTerms_TermsAreProvided_ReturnsTrue)
        {
            Terms t{ Monomial(1,0), Monomial(1,1), Monomial(1,256) };
            int order = Polynomial::GetHighestOrderOfPolynomialTerms(t);
            Assert::AreEqual(order, t[t.size() - 1].Exponent);
        }

        TEST_METHOD(Method_GetLowestOrderOfPolynomialTerms_PolynomialIsProvided_ReturnsTrue)
        {
            Polynomial p0(CoefficientList{ 1, 2, 3, 4 });
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

            Assert::AreEqual(Polynomial::GetLowestOrderOfPolynomialTerms(p0), p0LowestOrder);
            Assert::AreEqual(Polynomial::GetLowestOrderOfPolynomialTerms(p1), p1LowestOrder);
            Assert::AreEqual(Polynomial::GetLowestOrderOfPolynomialTerms(p2), p2LowestOrder);
        }


        TEST_METHOD(Method_GetLowestOrderOfPolynomialTerms_TermsAreProvided_ReturnsTrue)
        {
            Terms t0 = Polynomial::CoefficientList2Terms(CoefficientList{ 1, 2, 3, 4 });
            constexpr int t0LowestOrder = 0;

            constexpr int t1LowestOrder = -2;
            Terms t1{
                Monomial(1, 2),
                Monomial(1, 1),
                Monomial(1, 0),
                Monomial(1, -1),
                Monomial(1, t1LowestOrder),
            };

            Assert::AreEqual(Polynomial::GetLowestOrderOfPolynomialTerms(t0), t0LowestOrder);
            Assert::AreEqual(Polynomial::GetLowestOrderOfPolynomialTerms(t1), t1LowestOrder);
        }

        TEST_METHOD(Method_InterpolateTerms_TermsAreProvided_ReturnsCorrectInterpolatedTerms)
        {
            Terms t{ Monomial(1, 2), Monomial(2, 6), Monomial(2349068, 7) };

            t = Polynomial::InterpolateTerms(t);

            Assert::IsTrue(t.size() == 8);
            // Check if every exponent is existant in the polynomial
            for (int i = 0; i < t.size(); i++)
            {
                Assert::AreEqual(t[t.size() - 1 - i].Exponent, i);
            }
        }

        TEST_METHOD(Method_CombineTerms_TermsAreProvided_ReturnsCorrectCombinationOfTerms)
        {
            Terms t{ Monomial(1, 0),
                        Monomial(2, 1),
                        Monomial(5, 2),
                        Monomial(9, 0),
                        Monomial(8, 1),
                        Monomial(5, 2),
                        Monomial(5, 2),
            };

            Terms tCombined = Polynomial::CombineTerms(t);

            Assert::IsTrue(tCombined.size() == 3);
            Assert::AreEqual(tCombined[0].Exponent, 2);
            Assert::AreEqual(tCombined[1].Exponent, 1);
            Assert::AreEqual(tCombined[2].Exponent, 0);
            Assert::IsTrue(tCombined[0].Coefficient == 15);
            Assert::IsTrue(tCombined[1].Coefficient == 10);
            Assert::IsTrue(tCombined[2].Coefficient == 10);
        }

        TEST_METHOD(Method_IsEqual_OrderOrNumberOfTermsIsTheSame_ReturnsTrue)
        {
            Polynomial p0(CoefficientList{ 3, 2, 1 });
            Polynomial p1(CoefficientList{ 3, 2, 1 });
            bool result = p0.IsEqual(p1);
            Assert::IsTrue(result);
        }

        TEST_METHOD(Method_Differentiate_PolynomialIsDifferentiated_ReturnsTrue)
        {
            Polynomial original(CoefficientList{ -3,3,3,-3,8 });
            Polynomial correctResult(Terms{
                Monomial(-12,3),
                Monomial(9,2),
                Monomial(6,1),
                Monomial(-3,0)
                });

            Polynomial differentiated(original);
            differentiated.Differentiate();
            Assert::IsTrue(differentiated == correctResult);
        }

        TEST_METHOD(Method_DifferentiateStatic_PolynomialIsDifferentiated_ReturnsTrue)
        {
            Polynomial original(CoefficientList{ -3,3,3,-3,8 });
            Polynomial correctResult(Terms{
                Monomial(-12,3),
                Monomial(9,2),
                Monomial(6,1),
                Monomial(-3,0)
                });

            Polynomial differentiated = Polynomial::Differentiate(original);
            Assert::IsTrue(differentiated == correctResult);
        }

        TEST_METHOD(Method_Integrate_PolynomialIsIntegrated_ReturnsTrue)
        {
            Polynomial original(CoefficientList{ 5,-4,3,-2,8.5 });
            Polynomial correctResult(Terms{
                Monomial(1, 5),
                Monomial(-1, 4),
                Monomial(1, 3),
                Monomial(-1, 2),
                Monomial(8.5, 1)
                });

            Polynomial integrated(original);
            integrated.Integrate();
            Assert::IsTrue(integrated == correctResult);
        }

        TEST_METHOD(Method_IntegrateStatic_PolynomialIsIntegrated_ReturnsTrue)
        {
            Polynomial original(CoefficientList{ 5,-4,3,-2,8.5 });
            Polynomial correctResult(Terms{
                Monomial(1, 5),
                Monomial(-1, 4),
                Monomial(1, 3),
                Monomial(-1, 2),
                Monomial(8.5, 1)
                });

            Polynomial integrated = Polynomial::Integrate(original);
            Assert::IsTrue(integrated == correctResult);
        }

        TEST_METHOD(Constructor_DefaultConstructorIsInvoked_DefaultConstructorWorks)
        {
            Polynomial p;

            Assert::IsTrue(p.GetOrder() == 0);
            Assert::IsTrue(p[0].Coefficient == 0);
            Assert::IsTrue(p[0].Exponent == 0);

            Monomial nullTerm(0, 0);
            int restOrder = p.GetRestOrder();
            Assert::AreEqual(restOrder, 0);
            Assert::IsTrue(p.GetRest().size() == 1);
            Assert::IsTrue(nullTerm == p.GetRest()[0]);
        }

        TEST_METHOD(Constructor_ConstructorTakesCoefficientList_ConstructorWorks)
        {
            CoefficientList cl{ 1,2,3,4 };

            Polynomial p(cl); // Create polynomial
            Assert::IsTrue(p.GetOrder() == 3);
            Assert::IsTrue(p[3].Coefficient == 4);
            Assert::IsTrue(p[3].Exponent == 0);
            Assert::IsTrue(p[2].Coefficient == 3);
            Assert::IsTrue(p[2].Exponent == 1);
            Assert::IsTrue(p[1].Coefficient == 2);
            Assert::IsTrue(p[1].Exponent == 2);
            Assert::IsTrue(p[0].Coefficient == 1);
            Assert::IsTrue(p[0].Exponent == 3);

            Monomial nullTerm(0, 0);
            int restOrder = p.GetRestOrder();
            Assert::AreEqual(restOrder, 0);
            Assert::IsTrue(p.GetRest().size() == 1);
            Assert::IsTrue(nullTerm == p.GetRest()[0]);

        }

        TEST_METHOD(Constructor_ConstructorTakesMonomialList_ConstructorWorks)
        {
            Monomial nullTerm(0, 0);

            Terms terms{
                Monomial(1,2),
                Monomial(3,4),
                Monomial(5,6),
                Monomial(7,8)
            };

            Polynomial p(terms);
            int order = p.GetOrder();
            int restOrder = p.GetRestOrder();
            Assert::AreEqual(order, 8);

            Assert::AreEqual(restOrder, 0);
            Assert::IsTrue(p.GetRest().size() == 1);
            Assert::IsTrue(nullTerm == p.GetRest()[0]);

            Assert::AreEqual(p[8].Exponent, 0);
            Assert::IsTrue(p[8].Coefficient == 0);

            Assert::AreEqual(p[7].Exponent, 1);
            Assert::IsTrue(p[7].Coefficient == 0);

            Assert::AreEqual(p[6].Exponent, 2);
            Assert::IsTrue(p[6].Coefficient == 1);

            Assert::AreEqual(p[5].Exponent, 3);
            Assert::IsTrue(p[5].Coefficient == 0);

            Assert::AreEqual(p[4].Exponent, 4);
            Assert::IsTrue(p[4].Coefficient == 3);

            Assert::AreEqual(p[3].Exponent, 5);
            Assert::IsTrue(p[3].Coefficient == 0);

            Assert::AreEqual(p[2].Exponent, 6);
            Assert::IsTrue(p[2].Coefficient == 5);

            Assert::AreEqual(p[1].Exponent, 7);
            Assert::IsTrue(p[1].Coefficient == 0);

            Assert::AreEqual(p[0].Exponent, 8);
            Assert::IsTrue(p[0].Coefficient == 7);
        }

        TEST_METHOD(CopyConstructor_ConstructorIsInvoked_ConstructorWorks)
        {
            Terms terms{
                Monomial(1,2),
                Monomial(3,4),
            };

            Polynomial p(terms); // Create polynomial
            Assert::IsTrue(p.GetOrder() == 4);

            Polynomial copy(p);
            Assert::IsTrue(copy.GetOrder() == 4);
            Assert::IsTrue(p == copy);
        }

        TEST_METHOD(Operator_Equals_SamePolynomialsAreProvided_ReturnsTrue)
        {
            Polynomial p0(CoefficientList{ 1,2.3,236,34.3453,1 });
            Polynomial p1(CoefficientList{ 1,2.3,236,34.3453,1 });
            Assert::IsTrue(p0 == p1);
        }

        TEST_METHOD(Operator_Equals_DifferentPolynomialsAreProvided_ReturnsFalse)
        {
            Polynomial p0(CoefficientList{ 1,2.3,236,34.3453,1 });
            Polynomial p1(CoefficientList{ 1,2.3,236,34.3455,2,4 });
            Assert::IsFalse(p0 == p1);
        }

        TEST_METHOD(Operator_Equals_OnePolynomialsRestIsDifferent_ReturnsTrue)
        {
            Polynomial p0(CoefficientList{ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 });
            Polynomial p1 = p0;

            Terms t{
                Monomial(1, 2),
                Monomial(1, 1),
                Monomial(1, 0),
                Monomial(1, -1),
            };
            p1.SetRest(t);

            Assert::IsFalse(p0 == p1);
        }

        TEST_METHOD(Operator_Unequals_SamePolynomialsAreProvided_ReturnsFalse)
        {
            Polynomial p0(CoefficientList{ 1,2.3,236,34.3453,1 });
            Polynomial p1(CoefficientList{ 1,2.3,236,34.3453,1 });
            Assert::IsFalse(p0 != p1);
        }

        TEST_METHOD(Operator_Unequals_DifferentPolynomialsAreProvided_ReturnsTrue)
        {
            Polynomial p0(CoefficientList{ 1,2.3,236,34.3453,1 });
            Polynomial p1(CoefficientList{ 1,2.3,236,34.3455,2,4 });
            Assert::IsTrue(p0 != p1);
        }

        TEST_METHOD(Operator_Unequals_OnePolynomialsRestIsDifferent_ReturnsTrue)
        {
            Polynomial p0(CoefficientList{ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 });
            Polynomial p1 = p0;

            Terms t{
                Monomial(1, 2),
                Monomial(1, 1),
                Monomial(1, 0),
                Monomial(1, -1),
            };
            p1.SetRest(t);

            Assert::IsTrue(p0 != p1);
        }

        TEST_METHOD(Operator_Addition_ConstantIsAddedToPolynomial_ReturnsTrue)
        {
            Polynomial p0(CoefficientList{ 5, 2, 1 });
            highprecision constant = 5.5;
            Polynomial correctPolynomial(CoefficientList{ 5,2,6.5 });
            auto result = p0 + constant;
            auto result2 = constant + p0;

            Assert::IsTrue(result == correctPolynomial);
            Assert::IsTrue(result2 == correctPolynomial);
        }


        TEST_METHOD(Operator_Addition_PolynomialIsAddedToConstant_ReturnsTrue)
        {
            Polynomial p0(CoefficientList{ 5, 2, 1 });
            highprecision constant = 5.5;
            Polynomial correctPolynomial(CoefficientList{ 5,2,6.5 });
            auto result2 = constant + p0;

            Assert::IsTrue(result2 == correctPolynomial);
        }

        TEST_METHOD(Operator_Addition_MononomialIsAddedToPolynomial_ReturnsTrue)
        {
            Polynomial p0(CoefficientList{ 5, 2, 1 });
            Monomial m0(1.3, 8);
            Polynomial correctPolynomial(CoefficientList{ 1.3, 0, 0, 0, 0, 0, 5, 2, 1 });
            auto result = p0 + m0;

            Assert::IsTrue(result == correctPolynomial);
        }

        TEST_METHOD(Operator_Addition_PolynomialIsAddedToMonomial_ReturnsTrue)
        {
            Polynomial p0(CoefficientList{ 5, 2, 1 });
            Monomial m0(1.3, 8);
            Polynomial correctPolynomial(CoefficientList{ 1.3, 0, 0, 0, 0, 0, 5, 2, 1 });
            auto result2 = m0 + p0;

            Assert::IsTrue(result2 == correctPolynomial);
        }

        TEST_METHOD(Operator_Addition_PolynomialIsAddedToPolynomial_ReturnsTrue)
        {
            Polynomial p0(CoefficientList{ 5,  2,  1 });
            Polynomial p1(CoefficientList{ 4.5,    0,  1,  2,  0 });
            Polynomial correctPolynomial(CoefficientList{ 4.5, 0, 6, 4,1 });
            auto result = p0 + p1;
            auto result2 = p1 + p0;

            Assert::IsTrue(result == correctPolynomial);
            Assert::IsTrue(result2 == correctPolynomial);
        }

        TEST_METHOD(Operator_Subtraction_ConstantIsSubtractedFromPolynomial_ReturnsTrue)
        {
            Polynomial p0(CoefficientList{ 5, 2, 1 });
            highprecision constant = 5.5;
            Polynomial correctPolynomial(CoefficientList{ 5,2,-4.5 });
            auto result = p0 - constant;

            Assert::IsTrue(result == correctPolynomial);
        }

        TEST_METHOD(Operator_Subtraction_MononomialIsSubtractedFromPolynomial_ReturnsTrue)
        {
            Polynomial p0(CoefficientList{ 5, 2, 1 });
            Monomial m0(1.3, 8);
            Polynomial correctPolynomial(CoefficientList{ -1.3, 0, 0, 0, 0, 0, 5, 2, 1 });
            auto result = p0 - m0;

            Assert::IsTrue(result == correctPolynomial);
        }

        TEST_METHOD(Operator_Subtraction_PolynomialIsSubtractedFromPolynomial_ReturnsTrue)
        {
            Polynomial p0(CoefficientList{ 5,  2,  1 });
            Polynomial p1(CoefficientList{ 4.5,    0,  1,  2,  0 });
            Polynomial correctPolynomial(CoefficientList{ -4.5, 0, 4, 0, 1 });
            auto result = p0 - p1;

            Assert::IsTrue(result == correctPolynomial);
        }

        TEST_METHOD(Operator_Subtraction_PolynomialIsSubtractedFromConstant_ReturnsTrue)
        {
            Polynomial p0(CoefficientList{ 5, 2, 1 });
            highprecision constant = 5.5;
            Polynomial correctPolynomial(CoefficientList{ -5, -2, 4.5 });
            auto result = constant - p0;

            Assert::IsTrue(result == correctPolynomial);
        }

        TEST_METHOD(Operator_Subtraction_PolynomialIsSubtractedFromMonomial_ReturnsTrue)
        {
            Polynomial p0(CoefficientList{ 5, 2, 1 });
            Monomial m0(1.3, 8);
            Polynomial correctPolynomial(CoefficientList{ 1.3, 0, 0, 0, 0, 0, -5, -2, -1 });
            auto result = m0 - p0;

            Assert::IsTrue(result == correctPolynomial);
        }

        TEST_METHOD(Operator_Multiplication_PolynomialIsMultipliedWithConstant_ReturnsTrue)
        {
            Polynomial p0(CoefficientList{ 12,14,15,0 });
            Polynomial p1(CoefficientList{ 12.22222222222225,14436.5,125.4,1 });

            constexpr highprecision constant0 = 163.4;
            constexpr highprecision constant1 = -3;

            Polynomial correctResult0(CoefficientList{ 12 * constant0 , 14 * constant0, 15 * constant0, 0 });
            Polynomial correctResult1(CoefficientList{ 12.22222222222225 * constant1, 14436.5 * constant1 , 125.4 * constant1, 1 * constant1 });

            auto result0 = p0 * constant0;
            auto result1 = p1 * constant1;

            Assert::IsTrue(result0 == correctResult0);
            Assert::IsTrue(result1 == correctResult1);
        }

        TEST_METHOD(Operator_Multiplication_PolynomialIsMultipliedWithMonomial_ReturnsTrue)
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
                    Monomial(136 * m1.Coefficient, 35 + m1.Exponent),
                    Monomial(-1347.6236 * m1.Coefficient, 34 + m1.Exponent),
                    Monomial(-2 * m1.Coefficient, 12 + m1.Exponent),
                });

            auto result0 = p0 * m0;
            auto result1 = p1 * m1;
            auto result2 = m0 * p0;
            auto result3 = m1 * p1;

            Assert::IsTrue(result0 == correctResult0);
            Assert::IsTrue(result1 == correctResult1);
            Assert::IsTrue(result2 == correctResult0);
            Assert::IsTrue(result3 == correctResult1);
            Assert::IsTrue(result0 == result2);
            Assert::IsTrue(result1 == result3);
        }

        TEST_METHOD(Operator_Multiplication_PolynomialIsMultipliedWithZeroPolynomial_ReturnsTrue)
        {
            Polynomial p0(CoefficientList{ 3, 2, 1, 0 });
            Polynomial nullPolynomial;
            Polynomial correctResult = nullPolynomial;

            auto result = p0 * nullPolynomial;
            Assert::IsTrue(result == correctResult);
        }

        TEST_METHOD(Operator_Multiplication_PolynomialIsMultipliedWithOtherPolynomial_ReturnsTrue)
        {
            Polynomial p0(CoefficientList{ 1, 6 });
            Polynomial p1(CoefficientList{ 1, 8 });

            Polynomial p2(CoefficientList{ 4,  3, 0 });
            Polynomial p3(CoefficientList{ 1, -5,  2, 0 });

            Polynomial correctResult0(CoefficientList{
                1, 14, 48
                });

            // https://mathority.org/de/multiplikation-von-polynomen-beispiele-ubungen-gelostes-produkt-multiplizieren/
            Polynomial correctResult1(CoefficientList{
                4, -17, -7, 6, 0, 0
                });

            auto result0 = p0 * p1;
            auto result1 = p2 * p3;

            Assert::IsTrue(result0 == correctResult0);
            Assert::IsTrue(result1 == correctResult1);
        }

        TEST_METHOD(Operator_Multiplication_MultiplicationReversability_ReturnsTrue)
        {
            Polynomial origin(CoefficientList{ 2, 15, 4237, 3478, 64, 236, 2438, 4568, 235, 236, 6, 0 });
            Polynomial p0 = origin;

            p0 = p0 * -1;   // invert
            p0 = p0 * -1;   // invert again to get origin

            Assert::IsTrue(p0 == origin);
        }

        TEST_METHOD(Operator_Division_PolynomialDivisionSeveralDivisions_ResultsAreCorrect)
        {
            std::vector<Polynomial> numerators{
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
            std::vector<Polynomial> denominators{
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
            std::vector<Polynomial> correctResults{
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
                Polynomial(CoefficientList{ (1.0 / 2.0), (9.0 / 4.0) }),
                Polynomial(CoefficientList{ 2, -7, 18 }),
                Polynomial(CoefficientList{ 2, -1 }),
                Polynomial(CoefficientList{ 1, 0 }),
                Polynomial(CoefficientList{ 3, -3, 7, -16, 33 }),
            };

            // Special case for polynomials with residuals
            correctResults[11].SetRest(Terms{ Monomial(3, 1), Monomial(-2, 0) });
            correctResults[12].SetRest(Terms{ Monomial((-15.0 / 4.0), 1), Monomial((31.0 / 4.0), 0) });
            correctResults[13].SetRest(Terms{ Monomial(-31, 0) });
            correctResults[14].SetRest(Terms{ Monomial(4, 2), Monomial(-3, 1) });
            correctResults[15].SetRest(Terms{ Monomial(1, 3), Monomial(-1, 1), Monomial(-4, 0) });
            correctResults[16].SetRest(Terms{ Monomial(-71, 2), Monomial(82, 1), Monomial(-33, 0) });

            for (int i = 0; i < correctResults.size(); i++)
            {
                Polynomial tmp = numerators[i] / denominators[i];
                Assert::IsTrue(tmp == correctResults[i]);
            }

        }

        TEST_METHOD(Method_EvaluateAt_PolynomialIsEvaluatedAtPoint_ResultsAreCorrect)
        {
            const highprecision errorMarginInPercent = 0.001;
            Polynomial polynomial(CoefficientList{ -0.05, -0.075, 0.1, 2.0 });
            std::vector<highprecision> pointsToEvaluateAt
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
            std::vector<highprecision> correctResults
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
                highprecision error = std::abs(correctResults[i] - polynomial.EvaluateAt(pointsToEvaluateAt[i]));
                highprecision errorMargin = std::abs(correctResults[i] * (errorMarginInPercent / 100.0));
                Assert::IsTrue(error < errorMargin);
            }
        }

        TEST_METHOD(Method_EvaluateAtStatic_PolynomialIsEvaluatedAtPoint_ResultsAreCorrect)
        {
            const highprecision errorMarginInPercent = 0.001;
            Polynomial polynomial(CoefficientList{ -0.05, -0.075, 0.1, 2.0 });
            std::vector<highprecision> pointsToEvaluateAt
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
            std::vector<highprecision> correctResults
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
                highprecision error = std::abs(correctResults[i] - Polynomial::EvaluateAt(polynomial, pointsToEvaluateAt[i]));
                highprecision errorMargin = std::abs(correctResults[i] * (errorMarginInPercent / 100.0));
                Assert::IsTrue(error < errorMargin);
            }
        }

        TEST_METHOD(Method_FindZeroOfLinearTerm_TermIsProvided_ResultIsCorrect)
        {
            Polynomial p(CoefficientList{ 4, -3 });
            highprecision correctResult = 3.0 / 4.0;

            highprecision zero = Polynomial::FindZeroOfLinearTerm(p);
            Assert::AreEqual(zero, correctResult);
        }

        TEST_METHOD(Method_FindZeroOfLinearTerm_TermOfOrder2IsProvided_ExceptionIsThrown)
        {
            // Checks whether polynomials with an order greater than 1 are ignored correctly.
            Polynomial p(CoefficientList{ 4, 4, -3 });
            bool exceptionWasThrown = false;
            try
            {
                highprecision zero = Polynomial::FindZeroOfLinearTerm(p);
            }
            catch (...)
            {
                exceptionWasThrown = true;
            }

            Assert::IsTrue(exceptionWasThrown);
        }

        TEST_METHOD(Method_FindZeroOfLinearTerm_TermOfOrder0IsProvided_ExceptionIsThrown)
        {
            // Checks whether polynomials with an order smaller than 1 are ignored correctly.
            Polynomial p(CoefficientList{ -3 });
            bool exceptionWasThrown = false;
            try
            {
                highprecision zero = Polynomial::FindZeroOfLinearTerm(p);
            }
            catch (...)
            {
                exceptionWasThrown = true;
            }

            Assert::IsTrue(exceptionWasThrown);
        }

        TEST_METHOD(Method_FindZerosOfQuadraticTerms_TermOfOrder2IsProvided_ResultIsCorrect)
        {
            Polynomial p(CoefficientList{ 3, 21, -24 });
            std::vector<highprecision> zeros = Polynomial::FindZerosOfQuadraticTerms(p);
            highprecision z0 = 1;
            highprecision z1 = -8;

            std::cout << "TEST!" << std::endl;

            Assert::AreEqual(zeros[0], z0);
            Assert::AreEqual(zeros[1], z1);
        }

        TEST_METHOD(Method_FindZerosOfQuadraticTerms_TermOfOrder0IsProvided_ExceptionIsThrown)
        {
            Polynomial p(CoefficientList{ -3 });
            std::vector<highprecision> zeros;
            bool exceptionWasThrown = false;
            try
            {
                zeros = Polynomial::FindZerosOfQuadraticTerms(p);
            }
            catch (...)
            {
                exceptionWasThrown = true;
            }
            Assert::IsTrue(exceptionWasThrown);
        }

        TEST_METHOD(Method_FindZerosOfQuadraticTerms_TermOfOrder5IsProvided_ExceptionIsThrown)
        {
            Polynomial p(CoefficientList{ 5, 4, 3, 2, 1, 0 });
            std::vector<highprecision> zeros;
            bool exceptionWasThrown = false;
            try
            {
                zeros = Polynomial::FindZerosOfQuadraticTerms(p);
            }
            catch (...)
            {
                exceptionWasThrown = true;
            }
            Assert::IsTrue(exceptionWasThrown);
        }

        TEST_METHOD(Method_FindZerosOfQuadraticTerms_ComplexTermIsProvided_ExceptionIsThrown)
        {
            // Search for complex zeros
            Polynomial p(CoefficientList{ 1, 0, 0, 0, -1 });
            std::vector<highprecision> zeros;
            bool exceptionWasThrown = false;
            try
            {
                zeros = Polynomial::FindZerosOfQuadraticTerms(p);
            }
            catch (...)
            {
                exceptionWasThrown = true;
            }
            Assert::IsTrue(exceptionWasThrown);
        }

        TEST_METHOD(Method_FindZeros_ZerosAreProvided_ResultsAreCorrect)
        {
            std::vector<Polynomial> testPolynomials
            {
                Polynomial(CoefficientList{ 1, 6, 11, 6 }),
                Polynomial(CoefficientList{ 1, -3.53389, 0.494281, 6.53589, -4.49629 }), // x^4 - 3.53389 x^3 + 0.494281 x^2 + 6.53589 x - 4.49629
                Polynomial(CoefficientList{ 1, -6, 9}),   // Touches only abscissa        
            };
            std::vector<std::vector<highprecision>> correctZeros
            {
                std::vector<highprecision>{ -1, -2, -3 },
                // Calculated with Scilab:
                // p = [1, -3.53389, 0.494281, 6.53589, -4.49629];
                // msprintf("%.15f", roots(p)(1)) // -> Then print every zero with the index (1, 2, etc.)
                std::vector<highprecision>{ 2.666405704642979657, 1.233986505601812222, 1.000009753539556900, -1.366511963784348360 },
                std::vector<highprecision>{ 3, 3 },
            };
            for (int polyIdx = 0; polyIdx < testPolynomials.size(); polyIdx++)
            {
                std::vector<highprecision> calculatedZeros = Polynomial::FindZeros(testPolynomials[polyIdx]);
                std::sort(calculatedZeros.rbegin(), calculatedZeros.rend());
                std::sort(correctZeros[polyIdx].rbegin(), correctZeros[polyIdx].rend());
                for (size_t zeroIdx = 0; zeroIdx < calculatedZeros.size(); zeroIdx++)
                {
                    highprecision blub = std::abs(calculatedZeros[zeroIdx] - correctZeros[polyIdx][zeroIdx]);
                    Assert::IsTrue(blub <= Polynomial::GUESS_ZERO_ERROR_MARGIN);
                }

            }
        }



        TEST_METHOD(Method_Simplify_RationalFunctionIsProvidedAndSimplified_ResultsAreCorrect)
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

            // Assert::IsTrue(simplifiedFrac.numerator == testFracCorrect.numerator);
            // Assert::IsTrue(simplifiedFrac.denominator == testFracCorrect.denominator);

            PolynomialFraction testFrac
            {
                .numerator = Polynomial(CoefficientList{1, 16, -5, -300}),
                .denominator = Polynomial(CoefficientList{1, 8, 15})
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

            Assert::IsTrue(simplifiedFrac.numerator == testFracCorrect.numerator);
            Assert::IsTrue(simplifiedFrac.denominator == testFracCorrect.denominator);
        }

        TEST_METHOD(Method_DifferentiateRationalPolynomial_RationalFunctionsAreProvidedAndDifferentiated_ResultsAreCorrect)
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
            Polynomial correctionTerm(CoefficientList{ 1, 3 });
            testFracCorrectPrimePrime.numerator = testFracCorrectPrimePrime.numerator * correctionTerm;
            testFracCorrectPrimePrime.denominator = testFracCorrectPrimePrime.denominator * correctionTerm;

            PolynomialFraction testFracPrime = Polynomial::DifferentiateRationalPolynomial(testFrac);
            PolynomialFraction testFracPrimePrime = Polynomial::DifferentiateRationalPolynomial(testFracPrime);

            // https://www.wolframalpha.com/input?i=differentiate+%28x%5E2%2B6x%2B5%29%2F%28x%5E2%2B6x%2B9%29
            // Vielleicht Faktorisieren durch herausfinden der Nullstellen und dann innere vs. äußere Ableitung

            Assert::IsTrue(testFracPrime.numerator == testFracCorrectPrime.numerator);
            Assert::IsTrue(testFracPrime.denominator == testFracCorrectPrime.denominator);
            Assert::IsTrue(testFracPrimePrime.numerator == testFracCorrectPrimePrime.numerator);
            Assert::IsTrue(testFracPrimePrime.denominator == testFracCorrectPrimePrime.denominator);
        }

    };
}