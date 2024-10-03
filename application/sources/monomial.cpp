#include "../headers/monomial.hpp"

namespace Vath 
{

/* Constructors **************************************************************/

Monomial::Monomial()
{
    this->Coefficient = 0.0f;
    this->Exponent = 0;
}

Monomial::Monomial(double coefficient, int exponent)
{
    this->Coefficient = coefficient;
    this->Exponent = exponent;
}

Monomial::Monomial(const Monomial& other)
{
    this->Coefficient = other.Coefficient;
    this->Exponent = other.Exponent;
}

/* Public Methods ************************************************************/

// Operators

bool Monomial::operator ==(const Monomial& other) const
{
    return this->IsEqual(other);
}

bool Monomial::operator !=(const Monomial& other) const
{
    return !this->IsEqual(other);
}

Monomial Monomial::operator *(const double constant) const
{
    return Monomial((this->Coefficient * constant), this->Coefficient);
}

Monomial Monomial::operator /(const double constant) const
{
    return Monomial((this->Coefficient / constant), this->Coefficient);
}

Monomial Monomial::operator *(const Monomial& other) const
{
    double newCoeff = this->Coefficient * other.Coefficient;
    int newExp = this->Exponent + other.Exponent;    
    return Monomial(newCoeff, newExp);
}

Monomial Monomial::operator /(const Monomial& other) const
{
    double newCoeff = this->Coefficient / other.Coefficient;
    int newExp = this->Exponent - other.Exponent;    
    return Monomial(newCoeff, newExp);
}

// TODO
// Polynomial Monomial::operator +(const Monomial& other) const
// {
// }

// TODO
// Polynomial Monomial::operator -(const Monomial& other) const
// {
// }

// Methods

void Monomial::Integrate()
{
    if(false /* TODO: Do something about the constant ... */)
    {
        // TODO: What about the constant?
    }
    else
    {
        this->Exponent++;
        this->Coefficient = (this->Coefficient / this->Exponent);
    }
}

void Monomial::Differentiate()
{
    if(this->Exponent == 0)
    {
        this->Coefficient = 0;
        this->Exponent = 0;
    }
    else
    {
        this->Coefficient = (this->Coefficient * this->Exponent);
        this->Exponent--;
    }
}

// Overriden methods
std::string Monomial::to_string() const
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(3);
    if (std::abs(Coefficient) < 1e-10) 
    {
        ss << "+0.000";
    } else 
    {
        ss << Coefficient;
    }
    ss << Coefficient;
    ss << "x" << Exponent;
    return ss.str();
}

/* Private Methods ***********************************************************/

bool Monomial::IsEqual(const Monomial& other) const
{
    return (
            (std::abs(this->Coefficient - other.Coefficient) < Monomial::COMPARISON_PRECISION) &&
            (this->Exponent == other.Exponent)
            );
}









}