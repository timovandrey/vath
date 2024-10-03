#include "../headers/monomial.hpp"
#include "../headers/polynomial.hpp"

namespace Vath 
{

/* Constructors **************************************************************/

Polynomial::Polynomial()
{
    Monomial nullTerm(0, 0);
    Terms emptyTerms{ nullTerm };
    this->Monomials = emptyTerms;
    this->Order = Polynomial::GetHighestOrderOfPolynomialTerms(this->Monomials);
}

Polynomial::Polynomial(CoefficientList coefficientList)
{
    Terms terms;
    for(int i = (coefficientList.size() - 1); i >= 0; i--)
    {
        terms.push_back(Monomial(coefficientList[(coefficientList.size()-1)-i], i));
    }
    this->Monomials = terms;
    this->Order = Polynomial::GetHighestOrderOfPolynomialTerms(this->Monomials);
}

Polynomial::Polynomial(Terms terms)
{
    this->Monomials = terms;
    if(this->Monomials.size() <= 0)
    {
        Monomial nullTerm(0, 0);
        Terms emptyTerms{ nullTerm };   
        this->Monomials = emptyTerms;
    }
    this->Order = Polynomial::GetHighestOrderOfPolynomialTerms(this->Monomials);
}

Polynomial::Polynomial(const Polynomial& original)
{
    // Just take the terms of the original and put it into another ctor.
    Polynomial(original.Monomials); 
}

int Polynomial::GetHighestOrderOfPolynomialTerms(Terms monomials)
{
    return 1;
}











}