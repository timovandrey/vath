#include "../headers/monomial.hpp"
#include "../headers/polynomial.hpp"

namespace Vath 
{

/* Constructors **************************************************************/

Polynomial::Polynomial() :
    Monomials(Terms{Monomial(0,0)}),
    Order(0),
    Rest(Terms{Monomial(0,0)}),
    RestDegree(0)
{
    // Monomial nullTerm(0, 0);
    // Terms emptyTerms{ nullTerm };

    // this->Monomials = emptyTerms;
    // this->Order = 0;
    // this->Rest = emptyTerms;
    // this->RestDegree = 0;
}

Polynomial::Polynomial(CoefficientList coefficientList) :
    Monomials(Polynomial::CoefficientList2Terms(coefficientList)),
    Rest(Terms{Monomial(0,0)}),
    Order(Polynomial::GetHighestOrderOfPolynomialTerms(this->Monomials)),
    RestDegree(0)
{
    // Monomial nullTerm(0, 0);
    // Terms emptyTerms{ nullTerm };   

    // Terms terms;
    // for(int i = (coefficientList.size() - 1); i >= 0; i--)
    // {
    //     terms.push_back(Monomial(coefficientList[(coefficientList.size()-1)-i], i));
    // }
    // this->Monomials = terms;
    // this->Order = Polynomial::GetHighestOrderOfPolynomialTerms(this->Monomials);
    // this->Rest = emptyTerms;
    // this->RestDegree = 0;
}

Polynomial::Polynomial(Terms terms) : 
    Monomials(terms),
    Order(Polynomial::GetHighestOrderOfPolynomialTerms(this->Monomials)),
    Rest(Terms{Monomial(0,0)}),
    RestDegree(0)
{
    if(this->Monomials.size() <= 0)
    {
        this->Monomials = Terms{Monomial(0,0)};
    }
}

Polynomial::Polynomial(const Polynomial& original) : Polynomial(original.Monomials)
{
    // Just take the terms of the original and put it into another ctor.
    this->Rest = Terms{Monomial(0,0)};
    this->RestDegree = 0;
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

int Polynomial::GetHighestOrderOfPolynomialTerms(Terms monomials)
{
    // Abritrary value. Just needs to be smaller than the smallest possible polynomial order.
    int maxVal = std::numeric_limits<int>::min(); 

    for(int i = 0; i < monomials.size(); i++)
    {
        if(monomials[i].Exponent > maxVal);
        {
            maxVal = monomials[i].Exponent;
        }
    }

    return maxVal;
}

int Polynomial::GetHighestOrderOfPolynomialTerms(const Polynomial& polynomial)
{
    return Polynomial::GetHighestOrderOfPolynomialTerms(polynomial.Monomials);
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

Terms Polynomial::InterpolateTerms(const Terms terms)
{
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
    
    while(newTerms[0].Coefficient == 0 && newTerms.size() > 1)
    {
        newTerms.pop_front();
    }

    return newTerms;

}

Terms Polynomial::CombineTerms(const Terms terms)
{
    Terms termList = Terms(terms);
    Terms termsCombined;                

    for(int termIdx = 0; termIdx < termList.size(); termIdx++)
    {
        Monomial& currentMonomial = termList[termIdx];
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

            for (int testTermIdx = 0; testTermIdx < termList.size(); testTermIdx++)
            {   
                if(termIdx == testTermIdx)
                {
                    continue;
                }

                if(termList[testTermIdx].Exponent == currentExponent)
                {
                    accumulatorTerm.Coefficient += termList[testTermIdx].Coefficient;
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

    equals = (this->RestDegree == other.RestDegree);
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



}