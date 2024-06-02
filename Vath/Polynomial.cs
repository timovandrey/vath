using System.Collections;
using System.Numerics;
using System.Runtime.CompilerServices;

namespace Vath.Components
{
    using CoefficientList = List<double>;
    using Terms = List<Term>;

    /// <summary>
    /// TODO
    /// </summary>
    public class Polynomial : IEnumerable<Term>
    {
        #region Constants

        /// <summary>
        /// This is the upper boundary of the interval when guessing zeros.
        /// </summary>
        const double GUESS_ZERO_INTERVAL_UPPER_BOUNDARY     = 40.0f;
        /// <summary>
        /// This is the lower boundary of the interval when guessing zeros.
        /// </summary>
        const double GUESS_ZERO_INTERVAL_LOWER_BOUNDARY     = -40.0f;
        /// <summary>
        /// This is the step size when guessing zeros.
        /// </summary>
        const double GUESS_ZERO_INTERVAL_INTERATION_STEP    = 0.4f;
        /// <summary>
        /// This is the step size when guessing zeros.
        /// </summary>
        const double GUESS_ZERO_ERROR_MARGIN = 1E-20f;
        /// <summary>
        /// The maximum number of iterations that shall be performed when approximating a zero.
        /// </summary>
        const int GUESS_ZERO_MAX_ITERATIONS = 1000;
        
        #endregion
        #region Constructors
        
        /// <summary>
        /// Creates an instance of a polynomial which only consists of one term: 0*x^0.
        /// It is basically an empty instance and can be interacted with.
        /// </summary>
        public Polynomial()
        {
            Term nullTerm = new Term(0.0f, 0);
            Terms emptyTerms = new Terms() { nullTerm };
            this._terms = emptyTerms;
            this._order = Polynomial.GetHighestOrderOfPolynomialTerms(this.Terms);
        }

        /// <summary>
        /// Creates an instance of a polynomial.
        /// </summary>
        /// <param name="coefficientList">
        /// A list of coefficients (List&lt;float&rt;), where the first element is 
        /// the highest order of the polynomial and the last element is 
        /// always the 0th order. As example, the polynomial 3x^4 - 2x^2 + 8 
        /// would be new List&lt;float&rt;(){3, 0, 2, 0, 8}, because always all 
        /// powers need to be given.
        /// </param>
        public Polynomial(CoefficientList coefficientList)
        {
            Terms terms = new Terms();
            for (int i = (coefficientList.Count - 1); i >= 0; i--)
            {
                terms.Add(new Term(coefficientList[(coefficientList.Count - 1) - i], i));
            }
            this.Terms = terms;
            this._order = Polynomial.GetHighestOrderOfPolynomialTerms(this.Terms);
        }

        /// <summary>
        /// Creates an instance of a polynomial.
        /// </summary>
        /// <param name="terms">The terms of the polynomial. Is a list of the type List&lt;Term&rt;.</param>
        public Polynomial(Terms terms)
        {
            this.Terms = terms;
            if (this._terms is null)
            {
                this.Terms = new Terms();
            }
            this._order = Polynomial.GetHighestOrderOfPolynomialTerms(this.Terms);
        }

        /// <summary>
        /// Copy constructor of polynomial. Takes in a polynomial and creates a copy of it with another reference.
        /// </summary>
        /// <param name="original">The polynomial to be copied.</param>
        public Polynomial(Polynomial original) : this(Term.Clone(original.Terms)) { }
        #endregion
        #region Variables / Properties

        /// <summary>
        /// TODO
        /// </summary>
        //public List<float>? coefficientList
        //{
        //    // TODO: Implement
        //    get { return null; }
        //    set { }
        //}

        /// <summary>
        /// The terms in the polynomial.
        /// </summary>
        public Terms Terms
        {
            get { return this._terms; }
            // Sorts and combines terms 
            set
            {
                Terms? termList = value;
                if (termList is null)
                {
                    termList = new Terms { new Term(0, 0) };
                }
                this._terms = Polynomial.CombineTerms(termList);
                this.Order = Polynomial.GetHighestOrderOfPolynomialTerms(termList);
            }
        }
        private Terms _terms;


        /// <summary>
        /// The residual of the polynomial when doing polynomial division.
        /// </summary>
        /// <remarks>
        /// This is just a temporary implementation. The whole polynomial concept shall be continued in another fashion later on.
        /// </remarks>
        public Terms? Rest
        {
            get { return this._rest; }
            // Sorts and combines terms 
            set
            {
                Terms? termList = value;
                if (termList is null)
                {
                    this._rest = null;
                    this._restDegree = null;
                }
                else
                {
                    this._rest = Polynomial.CombineTerms(termList);
                    this.RestDegree = Polynomial.GetHighestOrderOfPolynomialTerms(termList);
                }
            }
        }
        private Terms? _rest;

        /// <summary>
        /// Contains the order of the polynomial.
        /// </summary>
        public int Order
        { 
            get
            {
                return this._order;
            }
            private set
            {
                this._order = value;
            }
        }
        private int _order;

        /// <summary>
        /// Contains the order of the polynomial.
        /// </summary>
        public int? RestDegree
        {
            get
            {
                return this._restDegree;
            }
            private set
            {
                this._restDegree = value;
            }
        }
        private int? _restDegree;

        #endregion
        #region Overriden operators
        public static Polynomial operator +(Term left, Polynomial right)
        {
            return (right + left);
        }
        public static Polynomial operator -(Term left, Polynomial right)
        {
            Terms? newTerms = Term.Clone(right.Terms);

            if (newTerms is null)
            {
                newTerms = new Terms();
            }
            else
            {
                foreach (Term term in newTerms)
                {
                    term.Coefficient *= (-1);
                }
            }

            return (new Polynomial(newTerms) + left);
        }
        public static Polynomial operator +(Polynomial left, Term right)
        {
            Terms? newTerms = left.Terms;
            if (newTerms is null)
            {
                newTerms = new Terms { new Term(right) };
            }
            else
            {
                newTerms.Add(new Term(right));
            }
            return new Polynomial(newTerms);
        }
        public static Polynomial operator -(Polynomial left, Term right)
        {
            Terms? newTerms = Term.Clone(left.Terms);
            if (newTerms is null)
            {
                newTerms = new Terms();
            }

            Term newRight = new Term(right);
            newRight.Coefficient *= (-1);
            newTerms.Add(newRight);

            return new Polynomial(newTerms);
        }
        public static Polynomial operator +(Polynomial? left, Polynomial? right)
        {
            Terms newTerms = new Terms();
            if (left is not null && right is not null)
            {
                newTerms = Term.Clone(left.Terms.Concat(right.Terms).ToList());
            }
            else if (left is null && right is not null)
            {
                newTerms = Term.Clone(right.Terms);
            }
            else if (right is null && left is not null)
            {
                newTerms = Term.Clone(left.Terms);
            }

            return new Polynomial(newTerms);
        }
        public static Polynomial operator -(Polynomial left, in Polynomial right)
        {
            Terms newRightTerms = new Terms();
            if (right is not null)
            {
                //newRightTerms = right.terms.ToList();
                newRightTerms = Term.Clone(right.Terms);

                foreach (Term term in newRightTerms)
                {
                    term.Coefficient *= (-1);
                }
            }

            return (left + new Polynomial(newRightTerms));
        }
        public static bool operator ==(Polynomial left, Polynomial right)
        {
            if(left is null)
            {
                return false;
            }
            else if(right is null)
            {
                return false;
            }
            return left.Equals(right);
        }
        public static bool operator !=(Polynomial left, Polynomial right)
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
        public static Polynomial operator *(Polynomial left, Polynomial right)
        {
            Polynomial inLeft = new Polynomial(left);
            Polynomial inRight = new Polynomial(right);
            Terms terms = new Terms() { new Term(0, 0) };

            foreach (Term leftTerm in inLeft.Terms)
            {
                foreach (Term rightTerm in inRight.Terms)
                {
                    terms.Add(leftTerm * rightTerm);
                }
            }
            return new Polynomial(terms);
        }
        public static Polynomial operator *(Polynomial left, double constantRight)
        {
            Polynomial input = new Polynomial(left);
            Polynomial output = new Polynomial();
            foreach(Term term in input)
            {
                output += (new Term(term.Coefficient * constantRight, term.Exponent));
            }
            return output;
        }
        public static Polynomial operator /(Polynomial numerator, Polynomial denominator)
        {
            if (denominator == new Polynomial() /* Nullpolynomial */)
            {
                throw new DivideByZeroException("You cant divide a coefficient by zero!");
            }

            if(numerator.Count() < denominator.Count())
            {
                throw new Exception("Division of the two terms yields an irrational polynomial.");
            }

            bool foundPolynomial = false;
            Terms workingNumerator = numerator.Terms;
            Terms result = new Terms();
            Terms interMediateAfterMultiplication = new Terms();
            Terms interMediateAfterSubtraction = new Terms();
            Polynomial endResult = new Polynomial();
            while(!foundPolynomial)
            {

                // Divide with the highest term from divisor/denominator
                result.Add(workingNumerator[0] / denominator[0]);
                if(Polynomial.GetHighestOrderOfPolynomialTerms(result) == 0)
                {
                    foundPolynomial = true;
                }

                for(int i = 0;  i < denominator.Count(); i++) 
                {
                    interMediateAfterMultiplication.Add(result[result.Count() - 1] * denominator[i]);
                }

                // B
                if (workingNumerator.Count() > interMediateAfterMultiplication.Count())
                {
                    // Pad with zeros so we can take the next term from the numerator
                    interMediateAfterMultiplication.Add(new Term(0, 0));
                }

                // A
                // If we the polynom below the working polynom (numerator) after multiplication is longer than the working polynomial (numerator), 
                // we have a problem and need to pull down the next coefficient(s) of the original numerator polynom
                if( Polynomial.GetLowestOrderOfPolynomialTerms(workingNumerator) > 
                    Polynomial.GetLowestOrderOfPolynomialTerms(interMediateAfterMultiplication))
                {
                    foreach(Term term in numerator)
                    {
                        if(term.Exponent == workingNumerator[workingNumerator.Count()-1].Exponent - 1)
                        {
                            workingNumerator.Add(term);
                            break;
                        }
                    }
                }
                
                // Go through terms and subtract from another
                for (int i = 0; i < interMediateAfterMultiplication.Count(); i++)
                {
                    Term subtracted = new Term(
                        workingNumerator[i].Coefficient - interMediateAfterMultiplication[i].Coefficient,
                        workingNumerator[i].Exponent
                        );
                    interMediateAfterSubtraction.Add(subtracted);
                }
                workingNumerator = new Terms(interMediateAfterSubtraction);
                workingNumerator.RemoveAt(0);

                // If the result of the subtraction is 0, we need to take the next term of the input numerator ("pull down")
                if( workingNumerator.Count()        == 1    && 
                    workingNumerator[0].Exponent    != 0    && 
                    workingNumerator[0].Coefficient == 0
                   )
                {
                    foreach(Term term in numerator)
                    {
                        if(term.Exponent == workingNumerator[workingNumerator.Count()-1].Exponent-1)
                        {
                            workingNumerator.Add(term);
                            break;
                        }
                    }
                }

                if (workingNumerator[0].Coefficient == 0 && workingNumerator[0].Exponent == 0)
                {
                    foundPolynomial = true;
                }

                // Here we found a polynomial, but there is a residual
                if( Polynomial.GetHighestOrderOfPolynomialTerms(workingNumerator) < 
                    Polynomial.GetHighestOrderOfPolynomialTerms(denominator))
                {
                    foundPolynomial = true;
                    if (workingNumerator[0].Coefficient == 0 && workingNumerator[0].Exponent == 0)
                    {
                        endResult.Rest = null;
                    }
                    else
                    {
                        endResult.Rest = workingNumerator;
                    }
                }

                interMediateAfterMultiplication = new Terms();
                interMediateAfterSubtraction = new Terms();

                endResult.Terms = result;
            }

            return endResult;
        }
        public static Polynomial operator /(Polynomial left, double constantRight)
        {
            if(constantRight == 0)
            {
                throw new DivideByZeroException("You cant divide a coefficient by zero!");
            }

            Polynomial input = new Polynomial(left);
            Polynomial output = new Polynomial();
            foreach (Term term in input)
            {
                output += (new Term(term.Coefficient / constantRight, term.Exponent));
            }
            return output;
        }

        /// <summary>
        /// Direct passthrough to the terms property to get it.
        /// </summary>
        /// <param name="index"></param>
        /// <returns></returns>
        public Term this[int index]
        {
            get
            {
                return this.Terms[index];
            }
            set
            {
                this.Terms[index] = new Term(value);
            }
        }

        public IEnumerator<Term> GetEnumerator()
        { 
            return Terms.GetEnumerator();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return (IEnumerator)GetEnumerator();
        }
        #endregion
        #region Standard overridden functions
        public override string ToString()
        {
            string? stringRepresentation = "";
            foreach(Term term in this)
            {
                stringRepresentation += term.ToString();
            }
            return stringRepresentation;
        }

        public override bool Equals(object? obj)
        {
            if(obj is null)
            {
                return false;
            }

            if(obj.GetType() != typeof(Polynomial))
            {
                return false;
            }

            bool isEqual;
            Polynomial testPolynomial = (Polynomial)obj;

            isEqual = (this.Order == testPolynomial.Order);
            if(!isEqual)
            {
                return false;
            }

            isEqual = (this.Terms.Count == testPolynomial.Terms.Count);
            if(!isEqual)
            {
                return false;
            }

            for(int termIdx = 0; termIdx < this.Terms.Count; termIdx++)
            {
                if (this.Terms[termIdx] != testPolynomial.Terms[termIdx])
                {
                    return false;
                }
            }

            return true;
        }

        // TODO: Override plus/minus, multiply, divide and use that to work with polynomials.
        #endregion
        #region Instance methods
        /* TODO */
        #endregion
        #region Class functions

        /// <summary>
        /// Clones a polynomial and gives a new object with different reference.
        /// </summary>
        /// <param name="other">The polynomial to be cloned.</param>
        /// <returns>A clones polynomial object with different reference.</returns>
        public static Polynomial Clone(Polynomial other)
        {
            Terms newTerms = Term.Clone(other.Terms);
            return new Polynomial(newTerms);
        }

        /// <summary>
        /// Takes in a polynomial and gets the highest order term where the coefficient is non-zero.
        /// </summary>
        /// <param name="polynomial">The polynomial from where to get the highest order term.</param>
        /// <returns>The order of the polynomial.</returns>
        static public int GetHighestOrderOfPolynomialTerms(Polynomial polynomial)
        {
            return polynomial.Terms.Max(term => term.Exponent);
        }

        /// <summary>
        /// Takes in a list of terms and gets the highest order term where the coefficient is non-zero.
        /// </summary>
        /// <param name="terms">The list of terms from where to get the highest order term.</param>
        /// <returns>The order of the polynomial.</returns>
        static public int GetHighestOrderOfPolynomialTerms(Terms terms)
        {
            return terms.Max(term => term.Exponent);
        }

        /// <summary>
        /// Takes in a polynomial and gets the lowest order term where the coefficient is non-zero.
        /// </summary>
        /// <param name="polynomial">The polynomial from where to get the lowest order term.</param>
        /// <returns>The order of the lowest exponential in the polynomial.</returns>
        static public int GetLowestOrderOfPolynomialTerms(Polynomial polynomial)
        {
            return polynomial.Terms.Min(term => term.Exponent);
        }

        /// <summary>
        /// Takes in a list of terms and gets the lowest order term where the coefficient is non-zero.
        /// </summary>
        /// <param name="terms">The list of terms from where to get the lowest order term.</param>
        /// <returns>The order of the lowest exponential in the list of terms.</returns>
        static public int GetLowestOrderOfPolynomialTerms(Terms terms)
        {
            return terms.Min(term => term.Exponent);
        }

        /// <summary>
        /// Takes in a list of terms, combines terms with the same expnent and sorts them by exponent.
        /// </summary>
        /// <param name="terms">A list of terms that should be combined and sorted.</param>
        /// <returns>The sorted and simplified term list.</returns>
        private static Terms CombineTerms(Terms terms)
        {
            Terms termList = Term.Clone(terms);
            Terms termsCombined = new Terms();

            for (int termIdx = 0; termIdx < termList.Count; termIdx++)
            {
                int currentExponent = termList[termIdx].Exponent;
                Term? alreadyInListTerm = termsCombined.Find(item => item.Exponent == currentExponent);

                if (alreadyInListTerm is null)
                {
                    Term accumulatorTerm = new Term(termList[termIdx]);

                    for (int testTermIdx = 0; testTermIdx < termList.Count; testTermIdx++)
                    {
                        if (termIdx == testTermIdx)
                        {
                            continue;
                        }

                        if (termList[testTermIdx].Exponent == currentExponent)
                        {
                            accumulatorTerm.Coefficient = accumulatorTerm.Coefficient + termList[testTermIdx].Coefficient;
                        }
                    }

                    termsCombined.Add(accumulatorTerm);
                }
            }

            termsCombined = Polynomial.InterpolateTerms(termsCombined);
            termsCombined = termsCombined.OrderByDescending(term => term.Exponent).ToList();

            return termsCombined;
        }

        /// <summary>
        /// This function takes a list of terms and then interpolates the terms by padding the missing powers between the highest order and 0th order.
        /// Also, removes and preceeding zeros of the polynomial.
        /// </summary>
        /// <param name="terms">The list of terms to be modified </param>
        /// <returns>A term list with padded zeros-powers.</returns>
        private static Terms InterpolateTerms(Terms terms)
        {
            Terms newTerms = Term.Clone(terms);
            int highestOrder = terms.Max(term => term.Exponent);
            for (int order = highestOrder; order >= 0; order--)
            {
                bool powerFound = false;
                foreach (Term term in newTerms)
                {
                    if (term.Exponent == order)
                    {
                        powerFound = true;
                        break;
                    }
                }

                if (!powerFound)
                {
                    newTerms.Add(new Term(0, order));
                }
            }
            newTerms = newTerms.OrderByDescending(term => term.Exponent).ToList();

            while (newTerms[0].Coefficient == 0 && newTerms.Count > 1)
            {
                newTerms.RemoveAt(0);
            }

            return newTerms;
        }
        
        /// <summary>
        /// Differentiates a polynomial once.
        /// </summary>
        /// <param name="polynomial">The polynomial to be differentiated.</param>
        /// <returns>The derivative of the input polynomial as polynomial.</returns>
        public static Polynomial Differentiate(Polynomial polynomial)
        {
            Terms newTerms = Term.Clone(polynomial.Terms);
            Terms outTerms = new Terms();
            foreach (Term term in newTerms)
            {
                outTerms.Add(Term.Differentiate(term));
            }
            return new Polynomial(outTerms);
        }
       
        /// <summary>
        /// Integrates a polynomial.
        /// </summary>
        /// <param name="polynomial">The polynomial to be integrated.</param>
        /// <returns>The integrated polynomial of the input polynomial.</returns>
        public static Polynomial Integrate(Polynomial polynomial)
        {
            Terms newTerms = Term.Clone(polynomial.Terms);
            Terms outTerms = new Terms();
            foreach (Term term in newTerms)
            {
                outTerms.Add(Term.Integrate(term));
            }
            return new Polynomial(outTerms);
        }

        /// <summary>
        /// Evaluates the polynomial as a function at the value given (f(x)).
        /// </summary
        /// <param name="x">The point where the function shall be evaluated. Can be complex.</param>
        /// <returns>The function value at x.</returns>
        public static double EvaluateAt(Polynomial function, double x)
        {
            double below = 0, middle = 0;
            foreach (Term term in function)
            {
                below = term.Coefficient + middle;
                middle = below * x;
            }
            return below;
        }

        /// <summary>
        /// Evaluates the polynomial as a function at the value given (f(x)).
        /// </summary>
        /// <param name="x">The point where the function shall be evaluated. Can be complex.</param>
        /// <returns>The function value at x.</returns>
        public static Complex EvaluateAt(Polynomial function, Complex x)
        {
            Complex below = 0, middle = 0;
            foreach (Term term in function)
            {
                below = term.Coefficient + middle;
                middle = below * x;
            }
            return below;
        }

        /// <summary>
        /// TODO
        /// </summary>
        /// <param name="function"></param>
        /// <returns></returns>
        public static List<double> FindZeros(Polynomial function)
        {
            Polynomial wfunc = new Polynomial(function);
            List<double> zeros = new List<double>();

            // 1. Go through function with coarse values, check for change in signedness
            // 2. Use the value after the signedness change as origin
            // 3. Approximate 0 with Newton-Method
            // 4. Reduce polynomial and do the same but while reducing the polynomial to use the Horner Schema
            // 5. Once the polynomial is of order 2, use pq-formula

            // 1-3 is "guessing" the zero, instead of going through the values always increasing resolution, use 
            // Newton-Method.

            while (wfunc.Order >= 3)
            {
                double currentFuncVal = 0, previousFuncVal = 0, currentDerivVal = 0, previousDerivVal = 0;
                bool firstRun = true, zeroFound = false;
                bool zeroApproxValFound = false;
                Polynomial derivative = Polynomial.Differentiate(wfunc);

                // Find an approximation origin for zero finding a zero
                for (
                            double i = GUESS_ZERO_INTERVAL_LOWER_BOUNDARY;
                            ((i <= GUESS_ZERO_INTERVAL_UPPER_BOUNDARY) || !zeroApproxValFound || !zeroFound);
                            i += GUESS_ZERO_INTERVAL_INTERATION_STEP
                        )
                {
                    previousFuncVal = currentFuncVal;
                    currentFuncVal = Polynomial.EvaluateAt(wfunc, i);
                    previousDerivVal = currentDerivVal;
                    currentDerivVal = Polynomial.EvaluateAt(derivative, i);


                    // Check if signedness changed during testing
                    if (    !firstRun &&
                            (
                                ((previousFuncVal < 0 && currentFuncVal >= 0) || (previousFuncVal >= 0 && currentFuncVal < 0)) ||
                                ((previousDerivVal < 0 && currentDerivVal > 0) || (previousDerivVal > 0 && currentDerivVal < 0))
                            )
                            )
                    {
                        currentFuncVal = i;
                        zeroApproxValFound = true;
                        break;
                    }
                    else if (currentFuncVal == 0)
                    {
                        // TODO: Error: Somehow the iteration is not perfectly 0.x parts, but the last few digits are like 0.0.....3949
                        //       That way, the evaluate-function does not yield 0 -> 0 cant be found...
                        zeroFound = true;
                    }
                    if (firstRun)
                    {
                        firstRun = false;
                    }
                }

                if (!zeroApproxValFound && !zeroFound)
                {
                    string errorMsg = "Cant find a zero between " + GUESS_ZERO_INTERVAL_LOWER_BOUNDARY + " and " + GUESS_ZERO_INTERVAL_UPPER_BOUNDARY + ".";
                    throw new ArithmeticException(errorMsg);
                }

                // Approximate zero by Halleys method
                if(!zeroFound)
                {
                    currentFuncVal = Polynomial.ApproximateZeroByHalleysMethod(wfunc, currentFuncVal);
                }

                // Use Horner Schema to get the next polynomial to be examined for a zero. 
                // Also, check whether the supposed zero is actually a zero.
                double supposedZero = currentFuncVal;
                double below = 0, middle = 0;
                CoefficientList belowRow = new CoefficientList();
                foreach (Term term in wfunc)
                {
                    belowRow.Add(below);
                    below = term.Coefficient + middle;
                    middle = below * supposedZero;
                }
                if(below == 0)
                {
                    zeros.Add(supposedZero);
                }

                wfunc = new Polynomial(belowRow);
            }
            if(wfunc.Order == 2)
            {
                // Somehow it cripples here ...
                var z12 = Polynomial.FindZerosOfQuadraticTerms(wfunc);
                zeros.Add(z12[0]);
                zeros.Add(z12[1]);
            }
            else if(wfunc.Order == 1)
            {
                var z = Polynomial.FindZeroOfLinearTerm(wfunc);
                zeros.Add(z);
            }

            return zeros;
        }
       
        /// <summary>
        /// Returns the zeros of the polynomial when it is of 2. order. 
        /// </summary>
        /// <param name="polynomialOfOrder2"></param>
        /// <returns></returns>
        /// <exception cref="ArgumentException"></exception>
        /// <exception cref="ArithmeticException"></exception>
        /// <remarks>It utilizes the pq-formula to achieve this.</remarks>
        public static List<double> FindZerosOfQuadraticTerms(Polynomial polynomialOfOrder2)
        {
            Polynomial workingPolynomial = new Polynomial(polynomialOfOrder2);
            List<double> zeros = new List<double>();
            bool zerosFound = false;
            if (    workingPolynomial[0].Exponent != 2 ||  
                    workingPolynomial[workingPolynomial.Count()-1].Exponent != 0 ||
                    workingPolynomial.Count() != 3)
            {
                throw new ArgumentException("The given polynomial is not of order 2.");
            }
            if(workingPolynomial[0].Coefficient == 0)
            {
                // TODO: Nullstelle ermitteln
                // Polynomial is actually not of order 3 and just weird
                // TODO: Make it so that when a polynomials highest order has the coefficient 0, the term shall be removed.
                //zeros.Add(Polynomial.FindZeroOfLinearTerm(workingPolynomial)); // TODO: Test
                //zerosFound = true;
                // This should never be reached due to the implementation of Polynomial and the above if-statement.
                throw new ArgumentException("The given polynomial is linear. Cant solve with pq-formula.");
            }
            else if (workingPolynomial[0].Coefficient != 1)
            {
                for(int i = 0; i < workingPolynomial.Order + 1;  i++) 
                {
                    // Normalize coefficients
                    workingPolynomial[i].Coefficient = workingPolynomial[i].Coefficient / workingPolynomial[0].Coefficient;
                }
            }
            if(!zerosFound)
            {
                double p = workingPolynomial[1].Coefficient;
                double q = workingPolynomial[2].Coefficient;
                double belowRootTerm = ((p * p) / 4.0f) - q;
                if(belowRootTerm  < 0)
                {
                    throw new ArithmeticException("The term below the root is negative. Complex terms are not supported.");
                }
                double rootTerm = Math.Sqrt(belowRootTerm);
                double firstTerm = -p / 2;
                double zero1 = firstTerm + rootTerm;
                double zero2 = firstTerm - rootTerm;
                zeros.Add(zero1);
                zeros.Add(zero2);
            }
            return zeros;
        }
       
        /// <summary>
        /// TODO
        /// </summary>
        /// <param name="linearPolynomial"></param>
        /// <returns></returns>
        public static double FindZeroOfLinearTerm(Polynomial linearPolynomial)
        {
            if (linearPolynomial[0].Exponent != 1                               ||
                linearPolynomial[linearPolynomial.Count() - 1].Exponent != 0    ||
                linearPolynomial.Count() != 2                                   )
            {
                throw new ArgumentException("The given polynomial is not linear.");
            }
            return ((linearPolynomial[1].Coefficient / linearPolynomial[0].Coefficient) * (-1));
        }

        /// <summary>
        /// Approximates a zero from a starting point (supposedZero) by utilizing the Halleys Method (third order Newton method).
        /// </summary>
        /// <param name="function">The polynomial function which' zero shall be approximated.</param>
        /// <param name="supposedZero">The starting point from where the method shall approximate the zero.</param>
        /// <returns>The approximated zero.</returns>
        /// <remarks>https://en.wikipedia.org/wiki/Halley%27s_method</remarks>
        private static double ApproximateZeroByHalleysMethod(Polynomial function, double supposedZero)
        {
            Polynomial fPrime = Polynomial.Differentiate(function);     // First derivative
            Polynomial fDoublePrime = Polynomial.Differentiate(fPrime); // Second derivative
            int iteration = 1;
            double hn = 0;              // Factor "hn" from the formula, (derivative divided by original function),
                                        // evaluated at the previous value
            double fpByfpp = 0;         // Shortcut factor for the second derivative divided by the first derivative,
                                        // evaluated at the previous value
            double numerator = 0;       // Computed numerator of the formula
            double denominator = 0;     // Computed denominator of the formula
            double currentFuncVal = supposedZero;   // Current value in the iteration, "xn+1"
            double previousFuncVal = 0; // Value from the preceeding iteration, "xn"
                                        // 
            while (Math.Abs(Polynomial.EvaluateAt(function, currentFuncVal)) > GUESS_ZERO_ERROR_MARGIN && iteration < GUESS_ZERO_MAX_ITERATIONS)
            {
                previousFuncVal = currentFuncVal;
                // function / derivative
                hn = -(Polynomial.EvaluateAt(function, previousFuncVal) /
                                        Polynomial.EvaluateAt(fPrime, previousFuncVal));
                // derivative^2 / derivative
                fpByfpp = (Polynomial.EvaluateAt(fDoublePrime, previousFuncVal) /
                                        Polynomial.EvaluateAt(fPrime, previousFuncVal));
                numerator = 1 + 0.5 * fpByfpp * hn;
                denominator = 1 + fpByfpp * hn + 1 / 6 * fpByfpp * hn * hn;
                currentFuncVal = previousFuncVal + hn * numerator / denominator;
                iteration++;

                if (Math.Abs(previousFuncVal - currentFuncVal) == 0)
                {
                    break;
                }
            }
            return currentFuncVal;
        }
        #endregion

    }

}
