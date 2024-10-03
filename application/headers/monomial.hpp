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


namespace Vath
{

class Polynomial;

/**
 * \brief This represents a term or rather a coefficient-exponent-pair. It thus represents something like 3x^4, where 3 is the coefficient and 4 is the exponent.
 * 
 * \remarks It is important to note that this doesnt capture different variables, such as x and y. It always assumes it is "x". Also, it is never a fraction, always only a coefficient-exponent term (exponent function).
 */
class Monomial
{

using Terms = std::vector<Monomial>;
using CoefficientList = std::vector<double>;

public: 
/* Public constants **********************************************************/
/* ... */

/* Public Member variables ***************************************************/
double  Coefficient;    //< The coefficient of the monomial.
int     Exponent;       //< The exponent of the monomial.

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
Monomial(double coefficient, int exponent);

/**
 * \brief Construct a new Monomial object from another. This is the copy constructor.
 * 
 * \param other The other Monomial to copy from.
 */
Monomial(const Monomial& other);

/* Public Methods ************************************************************/

// Operators
bool operator ==(const Monomial& other) const;          
bool operator !=(const Monomial& other) const;

Monomial operator *(const double constant) const;
Monomial operator /(const double constant) const;
// Monomial operator +(const double constant) const; // We dont do these kinds of things here
// Monomial operator -(const double constant) const;

Monomial operator *(const Monomial& other) const;
Monomial operator /(const Monomial& other) const;
Polynomial operator +(const Monomial& other) const;
Polynomial operator -(const Monomial& other) const;

// Methods
/**
 * \brief Integrates this monomial.
 */
void Integrate();       
/**
 * \brief Differentiates this monomial.
 */
void Differentiate();

// Overloaded standard methods
std::string to_string() const;

bool IsEqual(const Monomial& other) const;

/*****************************************************************************/
private:

/* Private Constants *********************************************************/
static constexpr double COMPARISON_PRECISION = 1e-15;

};

} // namespace vath

#endif /* _MONOMIAL_HPP_ */