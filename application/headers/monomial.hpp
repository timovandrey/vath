#ifndef _MONOMIAL_HPP_
#define _MONOMIAL_HPP_

#include <stdbool.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <sstream>
#include <iomanip>
#include <deque>

namespace Vath
{

class Polynomial;
class Monomial;

using highprecision = long double;
using Terms = std::deque<Monomial>;
using CoefficientList = std::deque<highprecision>;

/**
 * \brief This represents a term or rather a coefficient-exponent-pair. It thus represents something like 3x^4, where 3 is the coefficient and 4 is the exponent.
 * 
 * \remarks It is important to note that this doesnt capture different variables, such as x and y. It always assumes it is "x". Also, it is never a fraction, always only a coefficient-exponent term (exponent function).
 */
class Monomial
{

public: 
/* Public constants **********************************************************/
/* ... */

/* Public Member variables ***************************************************/
highprecision   Coefficient;    //< The coefficient of the monomial.
int             Exponent;       //< The exponent of the monomial.

/* Constructors **************************************************************/

/**
 * \brief Construct a new Monomial object. Initializes all members to 0;
 * 
 */
Monomial();

/**
 * \brief Construct a new Monomial object
 * 
 * \param coefficient This is the coefficient of the monomial. This is the A in A*x^y.
 * \param exponent This is the exponent of the monomial. This is the y in A*x^y.
 * \remarks In this version, the "x" of the monomial is assumed as given, so there is no possibility to change the "x variable".
 */
Monomial(highprecision coefficient, int exponent);

/**
 * \brief Construct a new Monomial object from another. This is the copy constructor.
 * 
 * \param other The other Monomial to copy from.
 */
Monomial(const Monomial& other);

/* Public Methods ************************************************************/

/* Enabling toString() *******************************************************/

std::string toString() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

// Friend declaration for operator<<
friend std::ostream& operator<<(std::ostream& os, const Monomial& monomial);

// Operators
bool operator ==(const Monomial& other) const;          
bool operator !=(const Monomial& other) const;

// Methods
/**
 * \brief Integrates this monomial.
 */
void Integrate();       

/**
 * \brief Integrates a monomial and returns the integrated monomial as value.
 * 
 * \param m The monomial to be integrated.
 * \return Monomial The integrated monomial.
 */
static Monomial Integrate(const Monomial& m);

/**
 * \brief Differentiates this monomial.
 */
void Differentiate();

/**
 * \brief Differentiates a monomial and returns the differentiated monomial as value.
 * 
 * \param m The monomial to be differentiated.
 * \return Monomial The differentiated monomial.
 */
static Monomial Differentiate(const Monomial& m);

// Overloaded standard methods
std::string to_string() const;

bool IsEqual(const Monomial& other) const;

/*****************************************************************************/
private:

/* Private Constants *********************************************************/
static constexpr highprecision COMPARISON_PRECISION = 1e-15;

};

Monomial operator *(const Monomial& left, const highprecision right);
Monomial operator *(const Monomial& left, const Monomial& right);
Monomial operator *(const highprecision left, const Monomial& right);

Monomial operator /(const Monomial& left, const highprecision right);
Monomial operator /(const Monomial& left, const Monomial& right);
Monomial operator /(const highprecision left, const Monomial& right);

// Monomial operator +(const Monomial& left, const highprecision right);
Polynomial operator +(const Monomial& left, const Monomial& right);
// Monomial operator +(const highprecision left, const Monomial& right);

// Monomial operator -(const Monomial& left, const highprecision right);
Polynomial operator -(const Monomial& left, const Monomial& right);
// Monomial operator -(const highprecision left, const Monomial& right);



} // namespace vath

#endif /* _MONOMIAL_HPP_ */