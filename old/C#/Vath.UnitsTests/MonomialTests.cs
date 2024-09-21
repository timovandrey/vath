using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using Vath.Components;

namespace Vath.UnitTests
{
    using TermList = List<Monomial>;
    using Terms = List<Monomial>;
    using CoefficientList = List<decimal>;

    [TestClass]
    public class MonomialTests
    {
        [TestMethod]
        public void Equals_ObjectIsNotOfSameType_ReturnsFalse()
        {
            Monomial testTerm0 = new Monomial(0, 1);
            int testTerm1 = 3;
            Assert.IsFalse(testTerm0.Equals(testTerm1));
        }
        [TestMethod]
        public void Equals_ObjectIsNull_ReturnsFalse()
        {
            Monomial testTerm0 = new Monomial(0, 1);
            Monomial? testTerm1 = null;
            Assert.IsFalse(testTerm0.Equals(testTerm1));
            Assert.IsFalse(testTerm0 == testTerm1);
            Assert.IsTrue(testTerm0 != testTerm1);
        }
        [TestMethod]
        public void Equals_TermCoefficientIsDifferent_ReturnsFalse()
        {
            Monomial testTerm0 = new Monomial(1, 2);
            Monomial testTerm1 = new Monomial(2, 2);
            Assert.IsFalse(testTerm0.Equals(testTerm1));
            Assert.IsFalse(testTerm0 == testTerm1);
            Assert.IsTrue(testTerm0 != testTerm1);
        }
        [TestMethod]
        public void Equals_TermExponentIsDifferent_ReturnsFalse()
        {
            Monomial testTerm0 = new Monomial(1, 2);
            Monomial testTerm1 = new Monomial(1, 3);
            Assert.IsFalse(testTerm0.Equals(testTerm1));
            Assert.IsFalse(testTerm0 == testTerm1);
            Assert.IsTrue(testTerm0 != testTerm1);
        }
        [TestMethod]
        public void Equals_TermExponentAndCoefficientIsSame_ReturnsTrue()
        {
            Monomial testTerm0 = new Monomial(1, 2);
            Monomial testTerm1 = new Monomial(1, 2);
            Assert.IsTrue(testTerm0.Equals(testTerm1));
            Assert.IsTrue(testTerm0 == testTerm1);
            Assert.IsFalse(testTerm0 != testTerm1);
        }
        [TestMethod]
        public void CopyConstructor_TermIsProvided_TermIsTheSame()
        {
            Monomial original = new Monomial(99.9m, 101);
            Monomial copy = new Monomial(original);
            Assert.IsTrue(original == copy);
        }
        [TestMethod]
        public void Operator_SingleMultiplication_ResultIsCorrect()
        {
            Monomial term0 = new Monomial(2, 2);
            Monomial term1 = new Monomial(3, 4);
            Monomial correctResult = new Monomial(6, 6);
            Assert.IsTrue(correctResult == (term0 * term1));
        }
        [TestMethod]
        public void Operator_SingleDivision_ResultIsCorrect()
        {
            Monomial term0 = new Monomial(2, 2);
            Monomial term1 = new Monomial(3, 4);
            Monomial correctResult = new Monomial(1.5m, 2);
            Assert.IsTrue(correctResult == (term1 / term0));
        }
        [TestMethod]
        public void Operator_SingleSummation_ResultIsCorrect()
        {
            //Polynomial correctResult = new Polynomial(new CoefficientList() { 3.0m, 0.0m, 4.0m, 0.0m });
            //Monomial term0 = new Monomial(3, 3);
            //Monomial term1 = new Monomial(4, 1);
            //Polynomial result = term0 + term1;
            //Assert.IsTrue(result == correctResult);
            Assert.Inconclusive();
        }
        [TestMethod]
        public void Integrate_TermIsIntegrated_ResultIsCorrect()
        {
            Monomial term = new Monomial(8, 3);
            Monomial correctResult = new Monomial(2, 4);
            Assert.IsTrue(Monomial.Integrate(term) == correctResult);
        }
        [TestMethod]
        public void Differentiate_TermIsDifferentiated_ResultIsCorrect()
        {
            Monomial term = new Monomial(8, 3);
            Monomial correctResult = new Monomial(24, 2);
            Assert.IsTrue(Monomial.Differentiate(term) == correctResult);
        }
        [TestMethod]
        public void Differentiate_TermIsDifferentiatedThenIntegrated_ResultIsCorrect()
        {
            Monomial startTerm = new Monomial(5, 6);
            Monomial intermediateTerm = Monomial.Integrate(Monomial.Differentiate(startTerm));
            Assert.IsTrue(startTerm == intermediateTerm);
        }
        [TestMethod]
        public void Integrate_TermIsIntegratedThenDifferentiated_ResultIsCorrect()
        {
            Monomial startTerm = new Monomial(5.0m, 76);

            Monomial integ = Monomial.Integrate(startTerm);
            Monomial diff = Monomial.Differentiate(integ);

            Monomial intermediateTerm = Monomial.Differentiate(Monomial.Integrate(startTerm));
            Assert.IsTrue(startTerm == intermediateTerm);
        }
        [TestMethod]
        public void Multiply_TermMultipliedByConstant_ResultIsCorrect()
        {
            decimal testConstant = 1233.35m;
            decimal testConstantMultiplier = 3.4m;
            Monomial startTerm = new Monomial(testConstant, 5);
            Monomial result = startTerm * testConstantMultiplier;
            Assert.IsTrue(result.Coefficient == (startTerm.Coefficient * testConstantMultiplier));
        }
        [TestMethod]
        public void Multiply_TermDividedByConstant_ResultIsCorrect()
        {
            decimal testConstant = 1233.35m;
            decimal testConstantDivisor = 3.4m;
            Monomial startTerm = new Monomial(testConstant, 5);
            Monomial result = startTerm / testConstantDivisor;
            Assert.IsTrue(result.Coefficient == (startTerm.Coefficient / testConstantDivisor));
        }
    }
}
