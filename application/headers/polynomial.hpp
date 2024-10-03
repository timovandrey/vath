#ifndef _POLYNOMIAL_HPP_
#define _POLYNOMIAL_HPP_

#include <stdbool.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <sstream>
#include <iomanip>
#include <optional>

namespace Vath
{

class Monomial;

/**
 * \brief 
 * 
 */
class Polynomial
{

using Terms = std::vector<Monomial>;
using CoefficientList = std::vector<double>;


public:

/* Public constants **********************************************************/
static constexpr double GUESS_ZERO_INTERVAL_UPPER_BOUNDARY  = 40;       //< This is the upper boundary of the interval when guessing zeros. 
static constexpr double GUESS_ZERO_INTERVAL_LOWER_BOUNDARY  = -40;      //< This is the lower boundary of the interval when guessing zeros.
static constexpr double GUESS_ZERO_INTERVAL_INTERATION_STEP = 0.4;      //< This is the step size when guessing zeros.
static constexpr double GUESS_ZERO_ERROR_MARGIN             = 1E-14;    //< This is the step size when guessing zeros.
static constexpr double GUESS_ZERO_MAX_ITERATIONS           = 1000;     //< The maximum number of iterations that shall be performed when approximating a zero.

/* Public Member variables ***************************************************/
Terms Monomials;
Terms Rest;
int Order;
int RestDegree;

/* Constructors **************************************************************/
Polynomial();                                   //< Default ctor
Polynomial(CoefficientList coefficientList);    //< Initialize with coefficientlist
Polynomial(Terms monomials);                    //< Initialize with list of monomials
Polynomial(const Polynomial& original);         //< Copy constructor

/* Public Methods ************************************************************/

// Operators
bool operator ==(const Polynomial& other) const;
bool operator !=(const Polynomial& other) const;

Polynomial operator +(const Monomial& other) const;
Polynomial operator -(const Monomial& other) const;
Polynomial operator +(const Polynomial& other) const;
Polynomial operator -(const Polynomial& other) const;

Polynomial operator *(double constant) const;
// Polynomial operator *(const Monomial& other) const;
Polynomial operator *(const Polynomial& other) const;

Polynomial operator /(double constant) const;
// Polynomial operator /(const Monomial& other) const;
Polynomial operator /(const Polynomial& other) const;

// Methods
void Integrate();       
void Differentiate();       
void EvaluateAt(double x);       
std::vector<double> Zeros();
std::vector<double> Decompose();
double GetArea(double lowerLimit, double upperLimit);
double GetAreaNumerically(double lowerLimit, double upperLimit);

// Static Methods
static int GetHighestOrderOfPolynomialTerms(const Polynomial& polynomial);
static int GetHighestOrderOfPolynomialTerms(Terms monomials);
static int GetLowestOrderOfPolynomialTerms(const Polynomial& polynomial);
static int GetLowestOrderOfPolynomialTerms(Terms monomials);
static Terms CombineTerms(Terms terms);
static Terms InterpolateTerms(Terms terms);

// Overloaded standard methods
std::string to_string() const;

bool IsEqual(const Polynomial& other) const;

};

/**
 * \brief TODO
 * 
 */
struct PolynomialFraction
{
    Polynomial numerator;
    std::optional<Polynomial> denominator;
};

} // namespace vath

#endif /* _POLYNOMIAL_HPP_ */