#include "../headers/monomial.hpp"
#include "../headers/polynomial.hpp"
#include <stdio.h>
#include <cmath>
#include <exception>

namespace Vath 
{

/* Constructors **************************************************************/

Polynomial::Polynomial() :
    Monomials(Terms{Monomial(0,0)}),
    Order(0),
    Rest(Terms{Monomial(0,0)}),
    RestOrder(0)
    {
        this->SetMonomials(Terms{Monomial(0,0)});
        this->SetRest(Terms{Monomial(0,0)});
    }  

Polynomial::Polynomial(CoefficientList coefficientList) :
    Monomials(Polynomial::CoefficientList2Terms(coefficientList)),
    Rest(Terms{Monomial(0,0)}),
    Order(Polynomial::GetHighestOrderOfPolynomialTerms(this->Monomials)),
    RestOrder(0)
    {
        this->SetMonomials(Polynomial::CoefficientList2Terms(coefficientList));
        this->SetRest(Terms{Monomial(0,0)});
    }

Polynomial::Polynomial(Terms terms) : 
    Monomials(terms),
    Order(Polynomial::GetHighestOrderOfPolynomialTerms(this->Monomials)),
    Rest(Terms{Monomial(0,0)}),
    RestOrder(0)
{
    if(this->Monomials.size() <= 0)
    {
        this->SetMonomials(Terms{Monomial(0,0)});
    }
    else
    {
        this->SetMonomials(terms);
    }
    this->SetRest(Terms{Monomial(0,0)});
}

Polynomial::Polynomial(const Polynomial& original) : 
    Polynomial(original.Monomials)
{
    // Just take the terms of the original and put it into another ctor.
    this->SetRest(Terms{Monomial(0,0)});
}

/* Accessors/Mutators ********************************************************/

void Polynomial::SetMonomials(Terms monomials)
{
    this->Monomials = Polynomial::CombineTerms(monomials);
    this->Order = Polynomial::GetHighestOrderOfPolynomialTerms(this->Monomials);
}

Terms Polynomial::GetMonomials() const
{
    return this->Monomials;
}

void Polynomial::SetRest(Terms rest)
{
    this->Rest = Polynomial::CombineTerms(rest);
    this->RestOrder = Polynomial::GetHighestOrderOfPolynomialTerms(this->Rest);
}

Terms Polynomial::GetRest() const
{
    return this->Rest;
}

int Polynomial::GetOrder() const
{
    return this->Order;
}

int Polynomial::GetRestOrder() const
{
    return this->RestOrder;
}

/* Public Methods ************************************************************/

int Polynomial::Count() const
{
    return this->GetMonomials().size();
}

std::ostream& operator <<(std::ostream& os, const Polynomial& polynomial)
{
    for(Monomial m : polynomial.GetMonomials()) 
    {
        os << m << " ";
    }
    return os;
}

// Operators

bool Polynomial::operator ==(const Polynomial& other) const
{
    return this->IsEqual(other);
}

bool Polynomial::operator !=(const Polynomial& other) const
{
    return !this->IsEqual(other);
}

Polynomial& Polynomial::operator =(const Polynomial& right)
{
    this->SetMonomials(right.GetMonomials());
    this->SetRest(right.GetRest());
    return *this;
}


// Methods

int Polynomial::GetHighestOrderOfPolynomialCoefficients(const CoefficientList coefficients)
{
    return (coefficients.size() <= 0 ? 0 : coefficients.size()-1);
}

int Polynomial::GetHighestOrderOfPolynomialTerms(const Terms monomials)
{
    // Abritrary value. Just needs to be smaller than the smallest possible polynomial order.
    int maxVal = std::numeric_limits<int>::min(); 

    for(int i = 0; i < monomials.size(); i++)
    {
        if((monomials[i].Exponent) > maxVal)
        {
            maxVal = monomials[i].Exponent;
        }
    }

    return maxVal;
}

int Polynomial::GetHighestOrderOfPolynomialTerms(const Polynomial& polynomial)
{
    return Polynomial::GetHighestOrderOfPolynomialTerms(polynomial.GetMonomials());
}

int Polynomial::GetLowestOrderOfPolynomialTerms(const Terms monomials)
{
    return monomials[monomials.size()-1].Exponent;
}

int Polynomial::GetLowestOrderOfPolynomialTerms(const Polynomial& polynomial)
{
    return Polynomial::GetLowestOrderOfPolynomialTerms(polynomial.GetMonomials());
}

Terms Polynomial::CoefficientList2Terms(const CoefficientList coefficients)
{
    Terms terms;
    for(int i = (coefficients.size() - 1); i >= 0; i--)
    {
        terms.push_back(Monomial(coefficients[(coefficients.size()-1)-i], i));
    }
    return terms;
}

CoefficientList Polynomial::Terms2CoefficientList(const Terms terms)
{
    CoefficientList coefficients;
    for(Monomial term : terms)
    {
        coefficients.push_back(term.Coefficient);
    }
    return coefficients;
}

Terms Polynomial::InterpolateTerms(const Terms& terms)
{
    if(terms.size() == 1)
    {
        if(terms[0].Exponent == 0 && terms[0].Coefficient == 0)
        {
            return terms;
        }
    }

    Terms newTerms(terms);
    int highestOrder = Polynomial::GetHighestOrderOfPolynomialTerms(newTerms);

    for(int order = highestOrder; order >= 0; order--)
    {
        bool powerFound = false;
        for(Monomial term : newTerms)
        {
            if(term.Exponent == order)
            {
                powerFound = true;
                break;
            }
        }

        if(!powerFound)
        {
            newTerms.push_back(Monomial(0, order));
        }
    }

    // Sort by descending exponent order
    auto compareFn = [](const Monomial& a, const Monomial& b){return a.Exponent > b.Exponent;};
    std::sort(newTerms.begin(), newTerms.end(), compareFn);
    
    
    // Remove terms with zero coefficients from the front
    while(newTerms[0].Coefficient == 0 && newTerms.size() > 1)
    {
        newTerms.pop_front();
    }

    // Remove negative exponents from the back of the polynomial
    while(  newTerms[newTerms.size()-1].Coefficient == 0 && 
            newTerms[newTerms.size()-1].Exponent < 0 && 
            (newTerms.size() > 1)
        )
    {
        newTerms.pop_back();
    }

    return newTerms;
}

Terms Polynomial::CombineTerms(const Terms& terms)
{
    Terms termsCombined;                

    for(int termIdx = 0; termIdx < terms.size(); termIdx++)
    {
        Monomial currentMonomial = terms[termIdx];
        int currentExponent = currentMonomial.Exponent;
        auto exponentServingLambda = [currentMonomial](Monomial x)
                                    {
                                        return x.Exponent == currentMonomial.Exponent;
                                    };
        bool currentExponentExistsInList = std::any_of( termsCombined.begin(), 
                                                        termsCombined.end(), 
                                                        exponentServingLambda
                                                        );
        if(!currentExponentExistsInList)
        {
            Monomial accumulatorTerm(currentMonomial);

            for (int testTermIdx = 0; testTermIdx < terms.size(); testTermIdx++)
            {   
                if(termIdx == testTermIdx)
                {
                    continue;
                }

                if(terms[testTermIdx].Exponent == currentExponent)
                {
                    accumulatorTerm.Coefficient += terms[testTermIdx].Coefficient;
                }
            }

            termsCombined.push_back(accumulatorTerm);
        }
    }

    termsCombined = Polynomial::InterpolateTerms(termsCombined);

    // Order by descending exponent, just for safety
    auto compareFn = [](const Monomial& a, const Monomial& b){return a.Exponent > b.Exponent;};
    std::sort(termsCombined.begin(), termsCombined.end(), compareFn);

    // Apparently, CPP distinguishes between (+)0 and -0, and it cant be checked for 
    // -0 just by `== -0`.
    for(Monomial& m : termsCombined)
    {
        if(std::signbit(m.Coefficient) && m.Coefficient == 0)
        {
            m.Coefficient = 0;
        }
    }

    return termsCombined;
}

void Polynomial::Differentiate()
{
    Terms newTerms(this->GetMonomials());
    Terms outTerms;

    for(Monomial m : newTerms)
    {
        Monomial diff(m);
        diff.Differentiate();
        outTerms.push_back(diff);
    }

    this->SetMonomials(outTerms);
}

Polynomial Polynomial::Differentiate(const Polynomial& p)
{
    Terms newTerms(p.GetMonomials());
    Terms outTerms;

    for(Monomial m : newTerms)
    {
        outTerms.push_back(Monomial::Differentiate(m));
    }

    return Polynomial(outTerms);
}

void Polynomial::Integrate()
{
    Terms newTerms(this->GetMonomials());
    Terms outTerms;

    for(Monomial m : newTerms)
    {
        Monomial diff(m);
        diff.Integrate();
        outTerms.push_back(diff);
    }

    this->SetMonomials(outTerms);
}

Polynomial Polynomial::Integrate(const Polynomial& p)
{
    Terms newTerms(p.GetMonomials());
    Terms outTerms;

    for(Monomial m : newTerms)
    {
        outTerms.push_back(Monomial::Integrate(m));
    }

    return Polynomial(outTerms);
}

double Polynomial::EvaluateAt(double x) const
{
    return Polynomial::EvaluateAt(*this, x);
}

double Polynomial::EvaluateAt(Polynomial function, double x)
{
    double below = 0, middle = 0;
    for (Monomial term : function)
    {
        below = term.Coefficient + middle;
        middle = below * x;
    }
    return below;
}

std::vector<double> Polynomial::Zeros(Polynomial function)
{
    // TODO: Make this multithreaded for faster zero finding. :D

    Polynomial wfunc(function);
    std::vector<double> zeros;

    // 1. Go through function with coarse values, check for change in signedness
    // 2. Use the value after the signedness change as origin
    // 3. Approximate 0 with Newton-Method
    // 4. Reduce polynomial and do the same but while reducing the polynomial to use the Horner Schema
    // 5. Once the polynomial is of order 2, use pq-formula

    // 1-3 is "guessing" the zero, instead of going through the values always increasing resolution, use 
    // Newton-Method.

    while(wfunc.GetOrder() >= 3)
    {
        double currentFuncVal = 0, previousFuncVal = 0, currentDerivVal = 0, previousDerivVal = 0;
        bool firstRun = true, zeroFound = false;
        bool zeroApproxValFound = false;
        Polynomial derivative = Polynomial::Differentiate(wfunc);

        // Find an approximation origin for zero finding a zero
        for (
            double i = Polynomial::GUESS_ZERO_INTERVAL_LOWER_BOUNDARY;
            ((i <= Polynomial::GUESS_ZERO_INTERVAL_UPPER_BOUNDARY) || (!zeroApproxValFound) || !zeroFound);
            i += Polynomial::GUESS_ZERO_INTERVAL_INTERATION_STEP
        )
        {
            previousFuncVal = currentFuncVal;
            currentFuncVal = Polynomial::EvaluateAt(wfunc, i);
            previousDerivVal = currentDerivVal;
            currentDerivVal = Polynomial::EvaluateAt(derivative, i);            

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

            if (!zeroApproxValFound && !zeroFound)
            {
                std::stringstream errorMsg;
                errorMsg    << "Cant find a zero between " 
                            << Polynomial::GUESS_ZERO_INTERVAL_LOWER_BOUNDARY
                            << " and "
                            << Polynomial::GUESS_ZERO_INTERVAL_UPPER_BOUNDARY
                            << ".";
                throw std::runtime_error(errorMsg.str());
            }

            // Approximate zero by Halleys method
            if(!zeroFound)
            {
                currentFuncVal = Polynomial::ApproximateZeroByHalleysMethod(wfunc, currentFuncVal);
            }

            // Use Horner Schema to get the next polynomial to be examined for a zero. 
            // Also, check whether the supposed zero is actually a zero.
            double supposedZero = currentFuncVal;
            double below = 0, middle = 0;
            CoefficientList belowRow;
            for(Monomial term : wfunc)
            {
                belowRow.push_back(below);
                below = term.Coefficient + middle;
                middle = below * supposedZero;
            }
            if(below == 0)
            {
                zeros.push_back(supposedZero);
            }

            wfunc = Polynomial(belowRow);
        }

        if(wfunc.GetOrder() == 2)
        {
            auto z12 = Polynomial::FindZerosOfQuadraticTerms(wfunc);
            zeros.push_back(z12[0]);
            zeros.push_back(z12[1]);
        }
        else if(wfunc.GetOrder() == 1)
        {
            auto z = Polynomial::FindZeroOfLinearTerm(wfunc);
            zeros.push_back(z);
        }
    }

    return zeros;
}

std::vector<double> Polynomial::FindZerosOfQuadraticTerms(Polynomial polynomialOfOrder2)
{
    Polynomial workingPolynomial(polynomialOfOrder2);
    std::vector<double> zeros;
    bool zerosFound = false;
    if  (
            workingPolynomial[0].Exponent != 2                              ||
            workingPolynomial[workingPolynomial.Count()-1].Exponent != 0    ||
            workingPolynomial.Count() != 3
        )
    {
        throw std::runtime_error("The given polynomial is not of order 2.");
    }
    if(workingPolynomial[0].Coefficient == 0)
    {
        // TODO: Nullstelle ermitteln
        // Polynomial is actually not of order 3 and just weird
        // TODO: Make it so that when a polynomials highest order has the coefficient 0, the term shall be removed.
        //zeros.Add(Polynomial.FindZeroOfLinearTerm(workingPolynomial)); // TODO: Test
        //zerosFound = true;
        // This should never be reached due to the implementation of Polynomial and the above if-statement.
        throw std::runtime_error("The given polynomial is linear. Cant solve with pq-formula.");        
    }
    else if(workingPolynomial[0].Coefficient != 1)
    {
        double normalizationFactor = workingPolynomial[0].Coefficient;
        for (size_t i = 0; i < workingPolynomial.Count(); i++)
        {
            // Normalize coefficients
            workingPolynomial[i].Coefficient = workingPolynomial[i].Coefficient / normalizationFactor;
        }
    }
    if(!zerosFound)
    {
        double p = workingPolynomial[1].Coefficient;
        double q = workingPolynomial[2].Coefficient;
        double belowRootTerm = ((p * p) / 4.0) - q;
        if(belowRootTerm < 0)
        {
            throw std::runtime_error("The term below the root is negative. Complex terms are not supported.");
        }
        double rootTerm = std::sqrt(belowRootTerm);
        double firstTerm = -p / 2;
        zeros.push_back(firstTerm + rootTerm);
        zeros.push_back(firstTerm - rootTerm);
    }
    return zeros;
}

double Polynomial::FindZeroOfLinearTerm(Polynomial linearPolynomial)
{
    if( linearPolynomial[0].Exponent != 1                             ||
        linearPolynomial[linearPolynomial.Count() - 1].Exponent != 0  ||
        linearPolynomial.Count() != 2                                 ) 
        {
            throw std::runtime_error("The given polynomial is not linear.");
        }
    return ((linearPolynomial[1].Coefficient / linearPolynomial[0].Coefficient) * (-1));
}

double Polynomial::ApproximateZeroByHalleysMethod(Polynomial function, double supposedZero)
{
    Polynomial fPrime       = Polynomial::Differentiate(function);
    Polynomial fPrimePrime  = Polynomial::Differentiate(function);
    int iteration           = 1;                
    double hn               = 0;                //< Factor "hn" from the formula, (derivative divided by original function), evaluated at the previous value
    double fpByfpp          = 0;                //< Shortcut factor for the second derivative divided by the first derivative, evaluated at the previous value
    double numerator        = 0;                //< Computed numerator of the formula
    double denominator      = 0;                //< Computed denominator of the formula
    double currentFuncVal   = supposedZero;     //< Current value in the iteration ("xn+1")
    double previousFuncVal  = 0;                //< Value from the preceeding iteration ("xn")
    
    while(  std::abs(Polynomial::EvaluateAt(function, currentFuncVal)) > Polynomial::GUESS_ZERO_ERROR_MARGIN &&
            iteration < Polynomial::GUESS_ZERO_MAX_ITERATIONS
            )
    {
        previousFuncVal = currentFuncVal;
        // function / derivative
        hn =
        ( 
            Polynomial::EvaluateAt(function, previousFuncVal) / 
            Polynomial::EvaluateAt(fPrime, previousFuncVal)
        ) * (-1);
        // derivative^2 / derivative
        fpByfpp = 
        (
            Polynomial::EvaluateAt(fPrimePrime, previousFuncVal) /
            Polynomial::EvaluateAt(fPrime, previousFuncVal)
        );
        numerator       = 1 + 0.5 * fpByfpp * hn;
        denominator     = 1 +       fpByfpp * hn + (1/6) * fpByfpp * hn * hn;
        currentFuncVal  = previousFuncVal + hn * numerator / denominator;
        iteration++;

        if(std::abs(previousFuncVal - currentFuncVal) == 0)
        {
            break;
        }
    }
    return currentFuncVal;
}

// Overriden methods

bool Polynomial::IsEqual(const Polynomial& other) const
{
    bool equals = false;
    equals = (this->Order == other.Order);
    if(!equals)
    {
        return false;
    }

    equals = (this->Monomials.size() == other.Monomials.size());
    if(!equals)
    {
        return false;
    }

    equals = (this->Rest == other.Rest);
    if(!equals)
    {
        return false;
    }

    equals = (this->RestOrder == other.RestOrder);
    if(!equals)
    {
        return false;
    }

    for(int termIdx = 0; termIdx < this->Monomials.size(); termIdx++)
    {
        if(this->Monomials[termIdx] != other.Monomials[termIdx])
        {
            return false;
        }
    }

    return true;
}

// Operators for the class

Polynomial operator *(const Polynomial& left, const Monomial& right)
{
    Terms t = left.GetMonomials();
    Terms out;
    for(Monomial m : t)
    {
        out.push_back(m * right);
    }
    Polynomial p(left);
    p.SetMonomials(out);
    return p;
}

Polynomial operator *(const Polynomial& left, const double right)
{
    return (left * Monomial(right, 0));
}

Polynomial operator *(const Polynomial& left, const Polynomial& right)
{
    Terms out;
    Terms rest;

    for(int i = 0; i < (left.GetOrder()+1); i++)
    {
        for(int j = 0; j < (right.GetOrder()+1); j++)
        {
            out.push_back(left[i] * right[j]);
        }
    }

    Terms leftRest, rightRest;
    leftRest = left.GetRest();
    rightRest = right.GetRest();

    for(int i = 0; i < (left.GetRestOrder()+1); i++)
    {
        for(int j = 0; j < (right.GetRestOrder()+1); j++)
        {
            rest.push_back(leftRest[i] * rightRest[j]);
        }
    }

    Polynomial p(left);
    p.SetMonomials(out);
    p.SetRest(rest);
    return p;
}

Polynomial operator *(const Monomial& left, const Polynomial& right)
{
    return right * left;
}

Polynomial operator *(const double left, const Polynomial& right)
{
    return right * left;
}

Polynomial operator +(const Polynomial& left, const Monomial& right)
{
    Terms terms = left.GetMonomials();
    terms.push_back(right);
    Polynomial newPoly(left);
    newPoly.SetMonomials(terms);
    return newPoly;
}

Polynomial operator +(const Polynomial& left, const double right)
{
    Terms terms = left.GetMonomials();
    Monomial constant(right, 0);
    terms.push_back(constant);
    Polynomial newPoly(left);
    newPoly.SetMonomials(terms);
    return newPoly;
}

Polynomial operator +(const Polynomial& left, const Polynomial& right)
{
    Terms terms = left.GetMonomials();
    Terms otherTerms = right.GetMonomials();
    for(Monomial m : otherTerms)
    {
        terms.push_back(m);
    }
    Polynomial newPoly(left);
    newPoly.SetMonomials(terms);
    return newPoly;
}

Polynomial operator +(const Monomial& left, const Polynomial& right)
{
    return (right + left);
}

Polynomial operator +(const double left, const Polynomial& right)
{
    return (right + left);
}

Polynomial operator -(const Polynomial& left, const Monomial& right)
{
    return (left + (right * (-1)));
}

Polynomial operator -(const Polynomial& left, const double right)
{
    return (left + (right * (-1)));
}

Polynomial operator -(const Polynomial& left, const Polynomial& right)
{
    return (left + (right * (-1)));
}

Polynomial operator -(const Monomial& left, const Polynomial& right)
{
    Polynomial p(right);
    p = p * -1;
    return (p + left);
}

Polynomial operator -(const double left, const Polynomial& right)
{
    return (Monomial(left, 0) - right);
}

Polynomial operator /(const Polynomial& nominator, const Monomial& denominator)
{
    Polynomial newPoly(nominator);
    Terms t = newPoly.GetMonomials();
    for(Monomial& m : t)
    {
        m = m / denominator;
    }
    newPoly.SetMonomials(t);
    return newPoly;
}

Polynomial operator /(const Polynomial& numerator, const double denominator)
{
    return (numerator / Monomial(denominator, 0));
}

Polynomial operator /(const Polynomial& numerator, const Polynomial& denominator)
{
    if(denominator == Polynomial())
    {
        throw std::runtime_error("You can't divide a polynomial by 0!");
    }
    
    if(denominator.GetOrder() > numerator.GetOrder())
    {
        throw std::runtime_error("Division of the two polynomials would yield an irrational polynomial.");
    }

    bool foundPolynomial = false;
    Terms workingNumerator(numerator.GetMonomials());
    Terms result;
    Terms interMediateAfterMultiplication;
    Terms interMediateAfterSubtraction;
    Polynomial endResult;
    while(!foundPolynomial)
    {
        auto den = denominator.GetMonomials();
        result.push_back(workingNumerator[0] / denominator[0]);
        if(Polynomial::GetHighestOrderOfPolynomialTerms(result) == 0)
        {
            foundPolynomial = true;
        }

        for(int i = 0; i < denominator.Count(); i++)
        {
            interMediateAfterMultiplication.push_back(result[result.size() - 1] * denominator[i]);
        }

        // B
        if(workingNumerator.size() > interMediateAfterMultiplication.size())
        {
            // Pad with zeros so we can take the next term from the numerator
            interMediateAfterMultiplication.push_back(Monomial(0, 0));
        }

        // A
        // If we the polynom below the working polynom (numerator) after multiplication is longer than the working polynomial (numerator), 
        // we have a problem and need to pull down the next coefficient(s) of the original numerator polynom
        if( Polynomial::GetLowestOrderOfPolynomialTerms(workingNumerator) >
            Polynomial::GetLowestOrderOfPolynomialTerms(interMediateAfterMultiplication) 
            )
        {
            for(Monomial& m : numerator.GetMonomials())
            {
                if(m.Exponent == workingNumerator[workingNumerator.size()-1].Exponent - 1)
                {
                    workingNumerator.push_back(m);
                    break;
                }
            }
        }

        // Go through terms and subtract from another
        for(int i = 0; i < interMediateAfterMultiplication.size(); i++)
        {
            Monomial subtracted(
                workingNumerator[i].Coefficient - interMediateAfterMultiplication[i].Coefficient,
                workingNumerator[i].Exponent
            );
            interMediateAfterSubtraction.push_back(subtracted);
        }
        workingNumerator = Terms(interMediateAfterSubtraction);
        workingNumerator.pop_front();

        // If the result of the subtraction is 0, 
        // we need to take the next term of the input numerator ("pull down")
        if( workingNumerator.size()         == 1    &&
            workingNumerator[0].Exponent    != 0    &&
            workingNumerator[0].Coefficient == 0    
        )
        {
            for(Monomial& m : numerator.GetMonomials())
            {
                if(m.Exponent == workingNumerator[workingNumerator.size()-1].Exponent - 1)
                {
                    workingNumerator.push_back(m);
                    break;
                }
            }
        }

        if( workingNumerator[0].Coefficient == 0 &&
            workingNumerator[0].Exponent == 0
        )
        {
            foundPolynomial = true;
        }

        if( Polynomial::GetHighestOrderOfPolynomialTerms(workingNumerator) < 
            Polynomial::GetHighestOrderOfPolynomialTerms(denominator)    
        )
        {
            foundPolynomial = true;
            if (workingNumerator[0].Coefficient == 0 && workingNumerator[0].Exponent == 0)
            {
                endResult.SetRest(Terms{Monomial(0,0)});
            }
            else
            {
                endResult.SetRest(workingNumerator);
            }            
        }

        interMediateAfterMultiplication = Terms();
        interMediateAfterSubtraction = Terms();

        endResult.SetMonomials(result);
    }

    return endResult;
}




}