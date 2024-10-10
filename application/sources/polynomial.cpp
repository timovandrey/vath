#include "../headers/monomial.hpp"
#include "../headers/polynomial.hpp"

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

// Operators

bool Polynomial::operator ==(const Polynomial& other) const
{
    return this->IsEqual(other);
}

bool Polynomial::operator !=(const Polynomial& other) const
{
    return !this->IsEqual(other);
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
    Terms newTerms = terms;
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
    
    while(newTerms[0].Coefficient == 0 && newTerms.size() > 1)
    {
        newTerms.pop_front();
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

}