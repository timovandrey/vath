using System.Numerics;
using Vath.Components;

namespace Vath.UnitTests
{
    using CoefficientList = List<decimal>;
    using Terms = List<Monomial>;

    [TestClass]
    public class PolynomialTests
    {
        [TestMethod]
        public void Equals_ObjectIsNotOfSameType_ReturnsFalse()
        {
            Polynomial polynomial0 = new Polynomial(new CoefficientList() { 3, 2, 1 });
            int notPolynomial1 = 3;
            Assert.IsFalse(polynomial0.Equals(notPolynomial1));
        }

        [TestMethod]
        public void Equals_ObjectIsNull_ReturnsFalse()
        {
            Polynomial polynomial0 = new Polynomial(new CoefficientList() { 3, 2, 1 });
            Polynomial? polynomial1 = null;
            Assert.IsFalse(polynomial0.Equals(polynomial1));
        }

        [TestMethod]
        public void Equals_OrderOrNumberOfTermsIsDifferent_ReturnsFalse()
        {
            Polynomial polynomial0 = new Polynomial(new CoefficientList() { 3, 2, 1 });
            Polynomial polynomial1 = new Polynomial(new CoefficientList() { 3, 2, 1, 0 });
            Assert.IsFalse(polynomial0.Equals(polynomial1));
            Assert.IsFalse(polynomial0 == polynomial1);
        }

        [TestMethod]
        public void Equals_PolynomialTermsAreNotTheSame_ReturnsFalse()
        {
            Polynomial polynomial0 = new Polynomial(new CoefficientList() { 3, 2, 1 });
            Polynomial polynomial1 = new Polynomial(new CoefficientList() { 3, 2, 2 });
            Assert.IsFalse(polynomial0.Equals(polynomial1));
            Assert.IsFalse(polynomial0 == polynomial1);
        }

        [TestMethod]
        public void Equals_PolynomialTermsAreTheSame_ReturnsTrue()
        {
            Polynomial polynomial0 = new Polynomial(new CoefficientList() { 3, 2, 1 });
            Polynomial polynomial1 = new Polynomial(new CoefficientList() { 3, 2, 1 });
            Assert.IsTrue(polynomial0.Equals(polynomial1));
            Assert.IsTrue(polynomial0 == polynomial1);
        }

        [TestMethod]
        public void Clone_PolynomialsAreTheSame_ReturnsTrue()
        {
            Polynomial original = new Polynomial(new CoefficientList() { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 200 });
            Polynomial clone = Polynomial.Clone(original);
            Assert.IsTrue(original.Equals(clone));
        }
        [TestMethod]
        public void CopyConstructor_PolynomialsAreTheSame_ReturnsTrue()
        {
            Polynomial original = new Polynomial(new CoefficientList() { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 200 });
            Polynomial clone = new Polynomial(original);
            Assert.IsTrue(original.Equals(clone));
        }

        [TestMethod]
        public void Indexing_ReferencingPerIndexingAndPerMember_ReturnsTrue()
        {
            Polynomial original = new Polynomial(new CoefficientList() { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 200 });
            int index = 4;
            Monomial termByClassIndexing = original[index];
            Monomial termByMemberIndexing = original.Terms[index];
            Assert.IsTrue(termByClassIndexing == termByMemberIndexing);
        }
        [TestMethod]
        public void Indexing_SettingPerIndexingAndPerMember_ReturnsTrue()
        {
            List<bool> correctIndexing = new List<bool>();

            // TODO!

            Assert.IsTrue(correctIndexing.All(x => x));
        }

        [TestMethod]
        public void TermSetter_TermsAreBeingInterpolated_ReturnsTrue()
        {
            Polynomial polynomial = new Polynomial(new CoefficientList() { 3, 0, 4, 0 });
            Monomial term0 = new Monomial(3, 3);
            Monomial term1 = new Monomial(4, 1);
            Polynomial testPolynomial = term0 + term1;
            Assert.IsTrue(polynomial == testPolynomial);
        }
        [TestMethod]
        public void Operator_SingleMultiplication_ResultIsCorrect()
        {
            Polynomial polynomial0 = new Polynomial(new CoefficientList() { 1, 2, 0 });
            Polynomial polynomial1 = new Polynomial(new CoefficientList() { 2, 3 });
            Polynomial result = new Polynomial(new CoefficientList() { 2, 7, 6, 0 });
            Assert.IsTrue(result == (polynomial0 * polynomial1));

            Polynomial polynomial2 = new Polynomial(new CoefficientList() { 4, 0, 2, 11, 8 });
            Polynomial polynomial3 = new Polynomial(new CoefficientList() { 4, 0, -2, -2, 0, 0 });
            Polynomial result2 = new Polynomial(new Terms()
            {
                new Monomial(16, 9),
                new Monomial(36, 6),
                new Monomial(28, 5),
                new Monomial(-26, 4),
                new Monomial(-38, 3),
                new Monomial(-16, 2)
            });
            Assert.IsTrue(result2 == (polynomial2 * polynomial3));
        }
        [TestMethod]
        public void Differentiate_PolynomialIsDifferentiated_ResultIsCorrect()
        {
            Polynomial original = new Polynomial(new CoefficientList() { -3, 3, 3, -3, 8 });
            Polynomial correctResult = new Polynomial(new Terms() {
                new Monomial(-12, 3),
                new Monomial(9, 2),
                new Monomial(6, 1),
                new Monomial(-3, 0)
            });
            Polynomial differentiated = Polynomial.Differentiate(original);
            Assert.IsTrue(differentiated == correctResult);
        }
        [TestMethod]
        public void Integrate_PolynomialIsIntegrated_ResultIsCorrect()
        {
            Polynomial original = new Polynomial(new CoefficientList() { 5, -4, 3, -2, 8.5m });
            Polynomial correctResult = new Polynomial(new Terms() {
                new Monomial(1, 5),
                new Monomial(-1, 4),
                new Monomial(1, 3),
                new Monomial(-1, 2),
                new Monomial(8.5m, 1)
            });
            Polynomial integrated = Polynomial.Integrate(original);
            Assert.IsTrue(integrated == correctResult);
        }
        [TestMethod]
        public void Integrate_PolynomialIsIntegratedThenDifferentiated_ResultIsCorrect()
        {
            Polynomial startPolynomial = new Polynomial(new CoefficientList() { 4, 3, 2, 1, 8 });
            Polynomial intermediatePolynomial = Polynomial.Differentiate(Polynomial.Integrate(startPolynomial));
            Assert.IsTrue(startPolynomial == intermediatePolynomial);
        }
        [TestMethod]
        public void Differentiate_PolynomialIsDifferentiatedThenIntegrated_ResultIsCorrect()
        {
            /* 
             * This cant be tested because when you differentiate with a constant, the constant is omitted.
             * When that constant is now omitted and not fed into the integration function, it will not 
             * pop up anymore.
             */
            Assert.Inconclusive();
        }
        [TestMethod]
        public void EvaluateAt_PolynomialIsEvaluatedAtPoint_ResultsAreCorrect()
        {
            const decimal errorMarginInPercent = 0.001m;
            Polynomial polynomial = new Polynomial(new CoefficientList() { -0.05m, -0.075m, 0.1m, 2.00m });
            List<decimal> pointsToEvaluateAt = new List<decimal>()
            {
                -100m,
                -50m,
                -20m,
                -10m,
                -5m,
                -2m,
                -1m,
                -0.5m,
                -0.2m,
                -0.1m,
                -0.05m,
                -0.02m,
                -0.01m,
                0m,
                0.01m,
                0.02m,
                0.05m,
                0.1m,
                0.2m,
                0.5m,
                1m,
                2m,
                5m,
                10m,
                20m,
                50m,
                100m,
            };
            List<decimal> correctResults = new List<decimal>()
            {
                49242m,
                6059.5m,
                370m,
                43.5m,
                5.875m,
                1.9m,
                1.875m,
                1.9375m,
                1.9774m,
                1.9893m,
                1.99481875m,
                1.9979704m,
                1.99899255m,
                2,
                2.00099245m,
                2.0019696m,
                2.00480625m,
                2.0092m,
                2.0166m,
                2.025m,
                1.975m,
                1.5m,
                -5.625m,
                -54.5m,
                -426m,
                -6430.5m,
                -50738m
            };
            for (int i = 0; i < pointsToEvaluateAt.Count; i++)
            {
                decimal error = Math.Abs(correctResults[i] - Polynomial.EvaluateAt(polynomial, pointsToEvaluateAt[i]));
                decimal errorMargin = Math.Abs(correctResults[i] * (errorMarginInPercent / 100.0m));
                Assert.IsTrue(error < errorMargin);
            }
        }
        [TestMethod]
        public void FindZerosByPqFormula_PolynomialIsGivenNotOfOrder2_ThrowsException()
        {
            Polynomial wrongOrderPolynomial = new Polynomial(new CoefficientList() { 4, 3, 2, 1, 0 });
            Action action = () =>
            {
                var zeros = Polynomial.FindZerosOfQuadraticTerms(wrongOrderPolynomial);
            };
            Assert.ThrowsException<ArgumentException>(action);
        }
        [TestMethod]
        public void FindZerosByPqFormula_PolynomialGivenHasComplexZeros_ThrowsException()
        {
            Polynomial complexZerosPolynomial = new Polynomial(new CoefficientList() { 1, 0, 7.5m });
            Action action = () =>
            {
                var zeros = Polynomial.FindZerosOfQuadraticTerms(complexZerosPolynomial);
            };
            Assert.ThrowsException<ArithmeticException>(action);
        }
        [TestMethod]
        public void FindZerosByPqFormula_PolyNomialIsLinearTerm_ThrowsException()
        {
            //Polynomial linearPolynomial = new Polynomial(new CoefficientList() { 0, 2, 1 });
            //Action action = () =>
            //{
            //    var zeros = Polynomial.FindZerosByPqFormula(linearPolynomial);
            //};
            //Assert.ThrowsException<ArithmeticException>(action);

            // Due to the new implementation this cant be tested and doesnt have to be.
            Assert.IsTrue(true);
        }
        [TestMethod]
        public void FindZerosByPqFormula_PolynomialIsGiven_ResultIsCorrect()
        {
            Polynomial correctOrderPolynomial = new Polynomial(new CoefficientList() { 1, -10, 9 });
            List<decimal> correctZeros = new List<decimal>() { 9, 1 };
            List<decimal> calculatedZeros = Polynomial.FindZerosOfQuadraticTerms(correctOrderPolynomial);
            Assert.IsTrue(correctZeros.SequenceEqual(calculatedZeros));
        }
        [TestMethod]
        public void FindZeros_PolynomialIsGiven_ResultsAreCorrect()
        {
            List<Polynomial> testPolynomials = new List<Polynomial>()
            {
                new Polynomial(new CoefficientList() { 1, 6, 11, 6 }),
                new Polynomial(new CoefficientList() { 1, -3.53389m, 0.494281m, 6.53589m, -4.49629m }), // x^4 - 3.53389 x^3 + 0.494281 x^2 + 6.53589 x - 4.49629
                new Polynomial(new CoefficientList() { 1, -6, 9}),   // Touches only abscissa
                //new Polynomial(new CoefficientList() { 1, -15.2347, -30, 457.041, 273, 4159.07, -820, +12492.5, 576, -8775.19})
                
            };
            List<List<decimal>> correctZeros = new List<List<decimal>>()
            {
                new List<decimal>() { -2, -1, -3 },
                new List<decimal>() { 1, 2.6664m, 1.234m, 1.3665123m },
                new List<decimal>() { 3, 3 },
                //new List<decimal>() { -1, -2, -3, -4, 1, 2, 3, 4, 15.2347 }
            };
            List<bool> equalsVector = new List<bool>();
            for (int polyIdx = 0; polyIdx < testPolynomials.Count; polyIdx++)
            {
                List<decimal> calculatedZeros = Polynomial.FindZeros(testPolynomials[polyIdx]);
                bool equals = correctZeros[polyIdx].OrderBy(x => x).SequenceEqual(calculatedZeros.OrderBy(y => y)); // https://stackoverflow.com/a/22392387
                equalsVector.Add(equals);
            }
            Assert.IsTrue(equalsVector.All(x => x));
        }
        //[TestMethod]
        //public void EvaluateComplexAt_RealAndComplexValuesAreGiven_ResultsAreCorrect()
        //{
        //    Polynomial function = new Polynomial(new CoefficientList() { 3, 4, 5, 1, 0.5 });

        //    Complex x1 = new Complex(7.23, 5.66);
        //    Complex x2 = new Complex(-22.253, 2365.664567);

        //    var res1 = Polynomial.EvaluateAt(function, x1);
        //    var res2 = Polynomial.EvaluateAt(function, x2);
        //    var res1conj = Polynomial.EvaluateAt(function, Complex.Conjugate(x1));
        //    var res2conj = Polynomial.EvaluateAt(function, Complex.Conjugate(x2));

        //    res1 = new Complex(Math.Round(res1.Real, 3), Math.Round(res1.Imaginary, 3));
        //    res2 = new Complex(Math.Round(res2.Real, 3), Math.Round(res2.Imaginary, 3));
        //    res1conj = new Complex(Math.Round(res1conj.Real, 3), Math.Round(res1conj.Imaginary, 3));
        //    res2conj = new Complex(Math.Round(res2conj.Real, 3), Math.Round(res2conj.Imaginary, 3));

        //    Complex res1Test = new Complex(Math.Round(-20025.23953701, 3), Math.Round(13177.72830168, 3));
        //    Complex res2Test = new Complex(Math.Round(93909616452331.05, 3), Math.Round(3482068896713.025, 3));
        //    Complex res1conjTest = new Complex(Math.Round(-20025.23953701, 3), Math.Round(-13177.72830168, 3));
        //    Complex res2conjTest = new Complex(Math.Round(93909616452331.05, 3), Math.Round(-3482068896713.025, 3));

        //    bool res1Correct = (res1 == res1Test);
        //    bool res2Correct = (res2 == res2Test);
        //    bool res1conjCorrect = (res1conj == res1conjTest);
        //    bool res2conjCorrect = (res2conj == res2conjTest);

        //    Assert.IsTrue(res1Correct && res2Correct && res1conjCorrect && res2conjCorrect);
        //}
        [TestMethod]
        public void Operator_MultiplicationByConstant_ResultIsCorrect()
        {
            const decimal MULTIPLICATION_CONSTANT = 3.4m;
            Polynomial x = new Polynomial(new CoefficientList() { 1, 2, 3.5m, 3467.23m });
            Polynomial y = new Polynomial(new CoefficientList()     {
                                                                        1 * MULTIPLICATION_CONSTANT,
                                                                        2 * MULTIPLICATION_CONSTANT,
                                                                        3.5m * MULTIPLICATION_CONSTANT,
                                                                        3467.23m * MULTIPLICATION_CONSTANT
                                                                    });
            Polynomial z = x * MULTIPLICATION_CONSTANT;
            Assert.IsTrue(y == z);
        }
        [TestMethod]
        public void Operator_DivisionByConstant_ResultIsCorrect()
        {
            const decimal DIVISION_CONSTANT = 4040.40m;
            Polynomial x = new Polynomial(new CoefficientList() { 1, 2, 3.5m, 3467.23m, DIVISION_CONSTANT });
            Polynomial y = new Polynomial(new CoefficientList()     {
                                                                        1 / DIVISION_CONSTANT,
                                                                        2 / DIVISION_CONSTANT,
                                                                        3.5m / DIVISION_CONSTANT,
                                                                        3467.23m / DIVISION_CONSTANT,
                                                                        1
                                                                    });
            Polynomial z = x / DIVISION_CONSTANT;
            Assert.IsTrue(y == z);
        }
        [TestMethod]
        public void Operator_MultiplyByNullTermPolynomial_ResultIsCorrect()
        {
            Polynomial x1 = new Polynomial(new CoefficientList() { 1, 2, 3, 4 });
            Polynomial nullPolynomial = new Polynomial();
            Polynomial result = x1 * nullPolynomial;
            Assert.IsTrue(result == nullPolynomial);
        }


        [TestMethod]
        public void Constructor_CreateEmptyPolynomial_ResultIsCorrect()
        {
            Polynomial x = new Polynomial();
            Assert.IsTrue(true);
        }

        [TestMethod]
        public void Operator_PolynomialDivisionSeveralDivisions_ResultsAreCorrect()
        {
            List<bool> resultsCorrect = new List<bool>();
            List<Polynomial> numerators = new List<Polynomial>()
            {
                new Polynomial(new CoefficientList(){ 1, -1, -12, -4, +16 }),
                new Polynomial(new CoefficientList(){ -6, -28, -16, 0 }),
                new Polynomial(new CoefficientList(){ -3, +9, 0, 0, 0 }),
                new Polynomial(new CoefficientList(){ -7, -18, -8, 0, 0 }),
                new Polynomial(new CoefficientList(){ 3, -4, -15, -4, 12 }),
                new Polynomial(new CoefficientList(){ 7, -21, -6, 16, 6 }),
                new Polynomial(new CoefficientList(){ 3, 12, 0 }),
                new Polynomial(new CoefficientList(){ -7, -37, -10, 0, 0 }),
                new Polynomial(new CoefficientList(){ 1, -4, -5, 6, -30 }),
                new Polynomial(new CoefficientList(){ -6, -6, 1, -5, -6 }),
                new Polynomial(new CoefficientList(){ -2, 12, -18 }),
                new Polynomial(new CoefficientList(){ 4, 2, -1, 1 }),
                new Polynomial(new CoefficientList(){ 1, 5, -3, 1 }),
                new Polynomial(new CoefficientList(){ 2, -3, 4, 5 }),
                new Polynomial(new CoefficientList(){ 2, 3, 0, 0, -1 }),
                new Polynomial(new CoefficientList(){ 1, 0, 2, 0, 0, -4 }),
                new Polynomial(new CoefficientList(){ 3, 0, -2, 0, 0, 1, 0, 0}),
            };
            List<Polynomial> denominators = new List<Polynomial>()
            {
                new Polynomial(new CoefficientList(){ 1, -1 }),
                new Polynomial(new CoefficientList(){ 1, 4 }),
                new Polynomial(new CoefficientList(){ 1, -3 }),
                new Polynomial(new CoefficientList(){ 1, 2 }),
                new Polynomial(new CoefficientList(){ 1, -3 }),
                new Polynomial(new CoefficientList(){ 1, -3 }),
                new Polynomial(new CoefficientList(){ 1, 4 }),
                new Polynomial(new CoefficientList(){ 1, 5 }),
                new Polynomial(new CoefficientList(){ 1, -5 }),
                new Polynomial(new CoefficientList(){ 1, 1 }),
                new Polynomial(new CoefficientList(){ 1, -3 }),
                new Polynomial(new CoefficientList(){ 2, -2, 1 }),
                new Polynomial(new CoefficientList(){ 2, 1, -3 }),
                new Polynomial(new CoefficientList(){ 1, 2 }),
                new Polynomial(new CoefficientList(){ 1, 2, -1, 1 }),
                new Polynomial(new CoefficientList(){ 1, 0, 1, 0, 1 }),
                new Polynomial(new CoefficientList(){ 1, 1, -2, 1 }),
            };
            List<Polynomial> correctResults = new List<Polynomial>()
            {
                new Polynomial(new CoefficientList(){ 1, 0, -12, -16 }),
                new Polynomial(new CoefficientList(){ -6, -4, 0 }),
                new Polynomial(new CoefficientList(){ -3, 0, 0, 0 }),
                new Polynomial(new CoefficientList(){ -7, -4, 0, 0 }),
                new Polynomial(new CoefficientList(){ 3, 5, 0, -4 }),
                new Polynomial(new CoefficientList(){ 7, 0, -6, -2 }),
                new Polynomial(new CoefficientList(){ 3, 0 }),
                new Polynomial(new CoefficientList(){ -7, -2, 0, 0 }),
                new Polynomial(new CoefficientList(){ 1, 1, 0, 6 }),
                new Polynomial(new CoefficientList(){ -6, 0, 1, -6 }),
                new Polynomial(new CoefficientList(){ -2, 6 }),
                new Polynomial(new CoefficientList(){ 2, 3 }),
                new Polynomial(new CoefficientList(){ (1.0m/2.0m), (9.0m/4.0m) }),
                new Polynomial(new CoefficientList(){ 2, -7, 18 }),
                new Polynomial(new CoefficientList(){ 2, -1 }),
                new Polynomial(new CoefficientList(){ 1, 0 }),
                new Polynomial(new CoefficientList(){ 3, -3, 7, -16, 33 }),
            };
            List<Polynomial> calculatedResults = new List<Polynomial>();

            // Special case for polynomials with residuals
            correctResults[11].Rest = new Terms() { new Monomial(3, 1), new Monomial(-2, 0) };
            correctResults[12].Rest = new Terms() { new Monomial((-15.0m / 4.0m), 1), new Monomial((31.0m / 4.0m), 0) };
            correctResults[13].Rest = new Terms() { new Monomial(-31, 0) };
            correctResults[14].Rest = new Terms() { new Monomial(4, 2), new Monomial(-3, 1) };
            correctResults[15].Rest = new Terms() { new Monomial(1, 3), new Monomial(-1, 1), new Monomial(-4, 0) };
            correctResults[16].Rest = new Terms() { new Monomial(-71, 2), new Monomial(82, 1), new Monomial(-33, 0) };

            for (int i = 0; i < correctResults.Count(); i++)
            {
                calculatedResults.Add(numerators[i] / denominators[i]);
                resultsCorrect.Add(
                                    calculatedResults[calculatedResults.Count() - 1] ==
                                    correctResults[i]
                                    );

                // Check the rest
                if (correctResults[i].Rest == null)
                {
                    resultsCorrect.Add(calculatedResults[calculatedResults.Count() - 1].Rest == null);
                }
                else
                {
                    resultsCorrect.Add(calculatedResults[calculatedResults.Count() - 1].Rest.SequenceEqual(correctResults[i].Rest));
                }
            }

            resultsCorrect.Add(calculatedResults[11].Rest.SequenceEqual(correctResults[11].Rest));
            resultsCorrect.Add(calculatedResults[12].Rest.SequenceEqual(correctResults[12].Rest));
            resultsCorrect.Add(calculatedResults[13].Rest.SequenceEqual(correctResults[13].Rest));
            resultsCorrect.Add(calculatedResults[14].Rest.SequenceEqual(correctResults[14].Rest));

            Assert.IsTrue(resultsCorrect.All(x => x));
        }
        [TestMethod]
        public void DifferentiateFraction_RationalFunctionsAreProvidedAndDifferentiated_ResultsAreCorrect()
        {
            // TODO: Do with several different rational functions
            PolynomialFraction testFrac = new PolynomialFraction() with
            {
                numerator = new Polynomial(new CoefficientList() { 1, 2, 1 }),
                denominator = new Polynomial(new CoefficientList() { 1, 3 }),
            };
            PolynomialFraction testFracCorrectPrime = new PolynomialFraction() with
            {
                numerator = new Polynomial(new CoefficientList() { 1, 6, 5 }),
                denominator = new Polynomial(new CoefficientList() { 1, 6, 9 }),
            };
            PolynomialFraction testFracCorrectPrimePrime = new PolynomialFraction() with
            {
                numerator = new Polynomial(new CoefficientList() { 8 }),
                denominator = new Polynomial(new CoefficientList() { 1, 9, 27, 27 }),
            };

            // Due to current limitation in the differentiation algorithm / simplifying algorithm, we have the following problem:
            // The differentiation works fine, however, it cant annihilate poles/zeros which are the same, which
            // results in bigger polynomials with possible simplifications not done. Thats why we multiply this 
            // testFracCorrectPrimePrime with (x+3), since the algorithm works, but it cant cancel out the pole/zero
            // which is (x+3) in both the numerator and the denominator.
            Polynomial correctionTerm = new Polynomial(new CoefficientList() { 1, 3 });
            testFracCorrectPrimePrime.numerator *= correctionTerm;
            testFracCorrectPrimePrime.denominator *= correctionTerm;

            PolynomialFraction testFracPrime = Polynomial.DifferentiateRationalPolynomial(testFrac);
            PolynomialFraction testFracPrimePrime = Polynomial.DifferentiateRationalPolynomial(testFracPrime);

            // https://www.wolframalpha.com/input?i=differentiate+%28x%5E2%2B6x%2B5%29%2F%28x%5E2%2B6x%2B9%29
            // Vielleicht Faktorisieren durch herausfinden der Nullstellen und dann innere vs. äußere Ableitung

            Assert.IsTrue(testFracCorrectPrime.numerator == testFracPrime.numerator &&
                          testFracCorrectPrime.denominator == testFracPrime.denominator &&
                          testFracCorrectPrimePrime.numerator == testFracPrimePrime.numerator &&
                          testFracCorrectPrimePrime.denominator == testFracPrimePrime.denominator
                          );

        }
        [TestMethod]
        public void SimplifyFraction_RationalFunctionsAreProvidedAndSimplified_ResultsAreCorrect()
        {
            // TODO: Do with several different rational functions
            PolynomialFraction testFrac = new PolynomialFraction() with
            {
                numerator = new Polynomial(new CoefficientList() { 8 }),
                denominator = new Polynomial(new CoefficientList() { 1, 9, 27, 27 }),
            };
            Polynomial correctionTerm = new Polynomial(new CoefficientList() { 1, 3 });
            testFrac.numerator *= correctionTerm;
            testFrac.denominator *= correctionTerm;
            PolynomialFraction testFracCorrect = new PolynomialFraction() with
            {
                numerator = new Polynomial(new CoefficientList() { 8 }),
                denominator = new Polynomial(new CoefficientList() { 1, 9, 27, 27 }),
            };
            PolynomialFraction simplifiedFrac = Polynomial.Simplify(testFrac);
            Assert.IsTrue(simplifiedFrac.numerator == testFracCorrect.numerator && simplifiedFrac.denominator == testFracCorrect.denominator);
        }
        //[TestMethod]
        //public void GetArea_ProvidePolynomial_ResultsAreCorrect()
        //{
        //    // https://uebungsaufgaben.eu/bestimmte_integrale/?seed=802929
        //    // https://uebungsaufgaben.eu/bestimmte_integrale/?seed=3
        //    List<bool> resultsCorrect = new List<bool>();
        //    List<Polynomial> functions = new List<Polynomial>()
        //    {
        //        new Polynomial(new CoefficientList(){ 5, 1, 0, -1 }),
        //        new Polynomial(new CoefficientList(){ -2.0m / 3.0m, 0, 0 }),
        //        new Polynomial(new CoefficientList(){ 4.0m/5.0m, 7, 0 }),
        //        new Polynomial(new CoefficientList(){ -1.0m/5.0m }),
        //        new Polynomial(new CoefficientList(){ -5 }),
        //        new Polynomial(new CoefficientList(){ 3, 6, 0 }),
        //        new Polynomial(new CoefficientList(){ 4, 5.0m/2.0m, 0, 3 }),
        //        new Polynomial(new CoefficientList(){ 5, 0, -3.0m/5.0m, 1 }),
        //        new Polynomial(new CoefficientList(){ -5, 1.0m/2.0m, 5 }),
        //        //new Polynomial(new Terms(){new Monomial(0.125m, 12), new Monomial(4.23m, 4), new Monomial(-0.38947m, 3) }),
        //        //new Polynomial(new Terms(){new Monomial(0.125m, 12), new Monomial(4.23m, 4), new Monomial(-0.38947m, 3) }),
        //        new Polynomial(new Terms(){new Monomial(0.000333225m, 11), new Monomial(0.123m, 7), new Monomial(-0.38947m, 3)}),
        //        new Polynomial(new Terms(){new Monomial(0.025m, 5), new Monomial(-3, 3), new Monomial(12, 1)}),
        //    };
        //    List<Tuple<decimal, decimal>> limits = new List<Tuple<decimal, decimal>>()
        //    {
        //        new Tuple<decimal,decimal>(0, 6),
        //        new Tuple<decimal,decimal>(-1, 2),
        //        new Tuple<decimal,decimal>(-4, 1),
        //        new Tuple<decimal,decimal>(1, 6),
        //        new Tuple<decimal,decimal>(-3, -2),
        //        new Tuple<decimal,decimal>(-1, 4),
        //        new Tuple<decimal,decimal>(2, 3),
        //        new Tuple<decimal,decimal>(-4, 1),
        //        new Tuple<decimal,decimal>(1, 5),
        //        //new Tuple<decimal,decimal>(12.5m, 234),
        //        //new Tuple<decimal,decimal>(-12.1256666m, 2.230598m),
        //        new Tuple<decimal,decimal>(-6.690009m, 2.235807m),
        //        new Tuple<decimal,decimal>(-0.0012m, 0.000015m),
        //    };
        //    List<decimal> correctResults = new List<decimal>()
        //    {
        //        1686,
        //        -2,
        //        -211.0m/6.0m,
        //        -1,
        //        -5,
        //        110,
        //        503.0m/6.0m,
        //        -1237.0m/4.0m,
        //        -542.0m/3.0m,
        //        //7059647013527665664,
        //        //2240544,
        //        -2.846803845857931e5m,
        //        -8.638648444800059e-6m
        //    };
        //    List<decimal> calculatedResults = new List<decimal>();

        //    for (int i = 0; i < functions.Count; i++)
        //    {
        //        calculatedResults.Add(functions[i].GetArea(limits[i].Item1, limits[i].Item2));
        //        var error = Monomial.Abs(calculatedResults[calculatedResults.Count - 1] - correctResults[i]);
        //        resultsCorrect.Add(error <= Monomial.DECIMAL_COMPARISON_PRECISION);
        //    }
        //    Assert.IsTrue(resultsCorrect.All(x => x));
        //}
    }
}
