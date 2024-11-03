#include "../headers/monomial.hpp"
#include "../headers/polynomial.hpp"

namespace Vath 
{

/* Constructors **************************************************************/

Monomial::Monomial()
{
    this->Coefficient = 0.0f;
    this->Exponent = 0;
}

Monomial::Monomial(highprecision coefficient, int exponent)
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

// For toString() method
std::ostream& operator <<(std::ostream& os, const Monomial& monomial) 
{
    os  << std::fixed 
        << std::setprecision(4) 
        << std::showpos
        << std::setw(4) 
        << monomial.Coefficient
        << "x";
        if(monomial.Exponent < 0)
        {
            os << std::showpos;
        }
        else
        {
            os << std::noshowpos;
        }
        os << monomial.Exponent;
    return os;
}

// Operators

bool Monomial::operator ==(const Monomial& other) const
{
    return this->IsEqual(other);
}

bool Monomial::operator !=(const Monomial& other) const
{
    return !this->IsEqual(other);
}

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

Monomial Monomial::Integrate(const Monomial& m)
{
    Monomial out(m);

    if(false /* TODO: Do something about the constant ... */)
    {
        // TODO: What about the constant?
    }
    else
    {
        out.Exponent++;
        out.Coefficient = (out.Coefficient / out.Exponent);
    }

    return out;
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

Monomial Monomial::Differentiate(const Monomial& m)
{
    Monomial out(m);

    if(out.Exponent == 0)
    {
        out.Coefficient = 0;
        out.Exponent = 0;
    }
    else
    {
        out.Coefficient = (out.Coefficient * out.Exponent);
        out.Exponent--;
    }

    return out;
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

// Operators for the class

Monomial operator *(const Monomial& left, const highprecision right)
{
    return (Monomial(left.Coefficient * right, left.Exponent));
}

Monomial operator *(const Monomial& left, const Monomial& right)
{
    return (Monomial(left.Coefficient * right.Coefficient, left.Exponent + right.Exponent));
}

Monomial operator *(const highprecision left, const Monomial& right)
{
    return right * left;
}

Monomial operator /(const Monomial& left, const highprecision right)
{
    return (Monomial(left.Coefficient / right, left.Exponent));
}

Monomial operator /(const Monomial& left, const Monomial& right)
{
    return (Monomial(left.Coefficient / right.Coefficient, left.Exponent - right.Exponent));
}

Monomial operator /(const highprecision left, const Monomial& right)
{
    Monomial m(left, 0);
    return m / right;
}

Polynomial operator +(const Monomial& left, const Monomial& right)
{
    return (Polynomial(Terms{left, right}));
}

Polynomial operator -(const Monomial& left, const Monomial& right)
{
    Monomial r(right);
    r.Coefficient *= (-1);
    return (left + (r));
}


}