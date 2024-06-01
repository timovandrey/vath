using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using Vath.Components;

namespace Vath.UnitTests
{
    using TermList = List<Term>;
    using Terms = List<Term>;
    using CoefficientList = List<double>;

    [TestClass]
    public class TermTests
    {
        [TestMethod]
        public void Equals_ObjectIsNotOfSameType_ReturnsFalse()
        {
            Term testTerm0 = new Term(0, 1);
            int testTerm1 = 3;
            Assert.IsFalse(testTerm0.Equals(testTerm1));
        }
        [TestMethod]
        public void Equals_ObjectIsNull_ReturnsFalse()
        {
            Term testTerm0 = new Term(0, 1);
            Term? testTerm1 = null;
            Assert.IsFalse(testTerm0.Equals(testTerm1));
            Assert.IsFalse(testTerm0 == testTerm1);
            Assert.IsTrue(testTerm0 != testTerm1);
        }
        [TestMethod]
        public void Equals_TermCoefficientIsDifferent_ReturnsFalse()
        {
            Term testTerm0 = new Term(1, 2);
            Term testTerm1 = new Term(2, 2);
            Assert.IsFalse(testTerm0.Equals(testTerm1));
            Assert.IsFalse(testTerm0 == testTerm1);
            Assert.IsTrue(testTerm0 != testTerm1);
        }
        [TestMethod]
        public void Equals_TermExponentIsDifferent_ReturnsFalse()
        {
            Term testTerm0 = new Term(1, 2);
            Term testTerm1 = new Term(1, 3);
            Assert.IsFalse(testTerm0.Equals(testTerm1));
            Assert.IsFalse(testTerm0 == testTerm1);
            Assert.IsTrue(testTerm0 != testTerm1);
        }
        [TestMethod]
        public void Equals_TermExponentAndCoefficientIsSame_ReturnsTrue()
        {
            Term testTerm0 = new Term(1, 2);
            Term testTerm1 = new Term(1, 2);
            Assert.IsTrue(testTerm0.Equals(testTerm1));
            Assert.IsTrue(testTerm0 == testTerm1);
            Assert.IsFalse(testTerm0 != testTerm1);
        }
        [TestMethod]
        public void CopyConstructor_TermIsProvided_TermIsTheSame()
        {
            Term original = new Term(99.9f, 101);
            Term copy = new Term(original);
            Assert.IsTrue(original == copy);
        }
        [TestMethod]
        public void Operator_SingleMultiplication_ResultIsCorrect()
        {
            Term term0 = new Term(2, 2);
            Term term1 = new Term(3, 4);
            Term correctResult = new Term(6, 6);
            Assert.IsTrue(correctResult == (term0 * term1));
        }
        [TestMethod]
        public void Operator_SingleDivision_ResultIsCorrect()
        {
            Term term0 = new Term(2, 2);
            Term term1 = new Term(3, 4);
            Term correctResult = new Term(1.5f, 2);
            Assert.IsTrue(correctResult == (term1 / term0));
        }
        [TestMethod]
        public void Operator_SingleSummation_ResultIsCorrect()
        {
            Polynomial correctResult = new Polynomial(new CoefficientList() { 3, 0, 4, 0 });
            Term term0 = new Term(3, 3);
            Term term1 = new Term(4, 1);
            Polynomial result = term0 + term1;
            Assert.IsTrue(result == correctResult);
        }
        [TestMethod]
        public void Integrate_TermIsIntegrated_ResultIsCorrect()
        {
            Term term = new Term(8, 3);
            Term correctResult = new Term(2, 4);
            Assert.IsTrue(Term.Integrate(term) == correctResult);
        }
        [TestMethod]
        public void Differentiate_TermIsDifferentiated_ResultIsCorrect()
        {
            Term term = new Term(8, 3);
            Term correctResult = new Term(24, 2);
            Assert.IsTrue(Term.Differentiate(term) == correctResult);
        }
        [TestMethod]
        public void Differentiate_TermIsDifferentiatedThenIntegrated_ResultIsCorrect()
        {
            Term startTerm = new Term(5, 6);
            Term intermediateTerm = Term.Integrate(Term.Differentiate(startTerm));
            Assert.IsTrue(startTerm == intermediateTerm);
        }
        [TestMethod]
        public void Integrate_TermIsIntegratedThenDifferentiated_ResultIsCorrect()
        {
            Term startTerm = new Term(5.0f, 76);

            Term integ = Term.Integrate(startTerm);
            Term diff = Term.Differentiate(integ);

            Term intermediateTerm = Term.Differentiate(Term.Integrate(startTerm));
            Assert.IsTrue(startTerm == intermediateTerm);
        }
        [TestMethod]
        public void Multiply_TermMultipliedByConstant_ResultIsCorrect()
        {
            double testConstant = 1233.35;
            double testConstantMultiplier = 3.4;
            Term startTerm = new Term(testConstant, 5);
            Term result = startTerm * testConstantMultiplier;
            Assert.IsTrue(result.Coefficient == (startTerm.Coefficient * testConstantMultiplier));
        }
        [TestMethod]
        public void Multiply_TermDividedByConstant_ResultIsCorrect()
        {
            double testConstant = 1233.35;
            double testConstantDivisor = 3.4;
            Term startTerm = new Term(testConstant, 5);
            Term result = startTerm / testConstantDivisor;
            Assert.IsTrue(result.Coefficient == (startTerm.Coefficient / testConstantDivisor));
        }
    }
}
