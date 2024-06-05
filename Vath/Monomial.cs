using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Vath.Components
{

    using TermList = List<Monomial>;
    using Terms = List<Monomial>;
    using CoefficientList = List<double>;

    /// <summary>
    /// This represents a term or rather a coefficient-exponent-pair. 
    /// It thus represents something like 3x^4, where 3 is the coefficient and 4 is the exponent.
    /// </summary>
    /// <remarks>
    /// It is important to note that this doesnt capture different variables, such as x and y. It always assumes it is "x".
    /// Also, it is never a fraction, always only a coefficient-exponent term (exponent function).
    /// </remarks>
    public class Monomial
    {

        #region Constants

        const double DOUBLE_COMPARISON_PRECISION = 1e-14;

        #endregion
        #region Variables / Properties

        /// <summary>
        /// The coefficient of the term.
        /// </summary>
        public double Coefficient;
        /// <summary>
        /// The exponent of the term.
        /// </summary>
        public int Exponent;

        #endregion
        #region Constructors
        
        /// <summary>
        /// Instantiates a new term.
        /// </summary>
        /// <param name="coeff">The coefficient of the term.</param>
        /// <param name="exponent">The exponent of the term.</param>
        public Monomial(double coeff, int exponent)
        {
            this.Coefficient = coeff;
            this.Exponent = exponent;
        }

        /// <summary>
        /// Copy constructor for terms.
        /// </summary>
        /// <param name="other">The term that needs to be copied.</param>
        public Monomial(Monomial other)
        {
            this.Coefficient = other.Coefficient;
            this.Exponent = other.Exponent;
        }

        #endregion
        #region Overriden operators

        /// <summary>
        /// Multiplies two terms.
        /// A multiplication of two terms with the same variable result in a multiplication of coefficients and summation of exponents.
        /// </summary>
        /// <param name="left">The left term of the operation.</param>
        /// <param name="right">The right term of the operations.</param>
        /// <returns>The resulting term.</returns>
        public static Monomial operator *(Monomial left, Monomial right)
        {
            double newCoeff = left.Coefficient * right.Coefficient;
            int newexponent = left.Exponent + right.Exponent;
            return new Monomial(newCoeff, newexponent);
        }

        /// <summary>
        /// Divides two terms.
        /// A division of two terms with the same variable result in a division of coefficients and subtraction of exponents.
        /// </summary>
        /// <param name="numerator">The numerator of the division (left operand).</param>
        /// <param name="denominator">The denominator of the division (right operand).</param>
        /// <returns>The resulting term.</returns>
        public static Monomial operator /(Monomial numerator, Monomial denominator)
        {
            double newCoeff = numerator.Coefficient / denominator.Coefficient;
            int newExponent = numerator.Exponent - denominator.Exponent;
            return new Monomial(newCoeff, newExponent);
        }

        /// <summary>
        /// An addition of two terms yields in two terms concatenated via a plus sign, thus, a polynomial is created.
        /// </summary>
        /// <remarks>
        /// This operation does not refactor the terms. If the terms are of the same exponent, they will still be shown as two seperate terms.
        /// </remarks>
        /// <param name="left">The term to the left of the plus (operator).</param>
        /// <param name="right">The term to the right of the plus (operator).</param>
        /// <returns>A polynomial with concatenated terms.</returns>
        public static Polynomial operator +(Monomial left, Monomial right)
        {
            Polynomial result;

            if (left.Exponent == right.Exponent)
            {
                Monomial combined = new Monomial(left.Coefficient + right.Coefficient, left.Exponent);
                result = new Polynomial(new Terms { combined });
            }
            else
            {
                result = new Polynomial(new Terms() { new Monomial(left), new Monomial(right) });
            }

            return result;
        }

        /// <summary>
        /// An addition of two terms yields in two terms concatenated via a minus sign, thus, a polynomial is created.
        /// </summary>
        /// <remarks>
        /// This operation does not refactor the terms. If the terms are of the same exponent, they will still be shown as two seperate terms.
        /// This inverts the coefficient of the term to the right!
        /// </remarks>
        /// <param name="left">The term to the left of the minus (operator).</param>
        /// <param name="right">The term to the right of the minus (operator).</param>
        /// <returns>A polynomial with concatenated terms. The right terms coefficient is negated.</returns>
        public static Polynomial operator -(Monomial left, Monomial right)
        {
            Polynomial result;

            if (left.Exponent == right.Exponent)
            {
                Monomial combined = new Monomial(left.Coefficient - right.Coefficient, left.Exponent);
                result = new Polynomial(new Terms { combined });
            }
            else
            {
                result = new Polynomial(new Terms() { new Monomial(left), new Monomial(right.Coefficient * (-1), right.Exponent) });
            }

            return result;
        }
        public static bool operator ==(Monomial? left, Monomial? right)
        {
            if (left is null)
            {
                return false;
            }
            else if (right is null)
            {
                return false;
            }
            return left.Equals(right);
        }
        public static bool operator !=(Monomial? left, Monomial? right)
        {
            if (left is null)
            {
                return true;
            }
            else if (right is null)
            {
                return true;
            }
            return !left.Equals(right);
        }
        public static Monomial operator *(Monomial left, double constantRight)
        {
            return new Monomial(left.Coefficient * constantRight, left.Exponent);
        }
        public static Monomial operator /(Monomial left, double constantRight)
        {
            return new Monomial(left.Coefficient / constantRight, left.Exponent);
        }

        #endregion
        #region Standard overridden functions

        public override string ToString()
        {
            return $"{string.Format("{0:+0.000;-0.000;+0.000}", this.Coefficient)}x{this.Exponent}";
        }

        public override bool Equals(object? obj)
        {
            if (obj is null)
            {
                return false;
            }

            if (obj.GetType() != typeof(Monomial))
            {
                return false;
            }

            Monomial testTerm = (Monomial)obj;
            return ((Math.Abs(this.Coefficient - testTerm.Coefficient) < DOUBLE_COMPARISON_PRECISION) && this.Exponent == testTerm.Exponent);
        }
        #endregion
        #region Class functions

        public static Terms Clone(Terms other)
        {
            Terms newTerms = new Terms();
            foreach (Monomial term in other)
            {
                newTerms.Add(new Monomial(term));
            }
            return newTerms;
        }

        /// <summary>
        /// Differentiates a term.
        /// </summary>
        /// <param name="term">The term to be differentiated.</param>
        /// <returns>The differentiated term.</returns>
        public static Monomial Differentiate(Monomial term)
        {
            Monomial differentiated;
            if (term.Exponent == 0)
            {
                differentiated = new Monomial(0, 0);
            }
            else
            {
                differentiated = new Monomial(term.Coefficient * term.Exponent, (term.Exponent - 1));
            }
            return differentiated;
        }

        /// <summary>
        /// Integrates a term.
        /// </summary>
        /// <param name="term">The term to be integrated.</param>
        /// <returns>The integrated term.</returns>
        public static Monomial Integrate(Monomial term)
        {
            Monomial integrated;
            if (false /* TODO: Do something about the constant ... */)
            {
                // TODO: What about the constant?
            }
            else
            {
                integrated = new Monomial(term.Coefficient / (term.Exponent + 1), term.Exponent + 1);
            }
            return integrated;
        }
        #endregion
    }
}
