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
#include <algorithm>
#include <limits>
#include <deque>

namespace Vath
{

class Monomial; 

using Terms = std::deque<Monomial>;
using CoefficientList = std::deque<double>;

/**
 * \brief 
 * 
 */
class Polynomial
{

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
public:
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/* Public constants **********************************************************/
static constexpr double GUESS_ZERO_INTERVAL_UPPER_BOUNDARY  = 40;       //< This is the upper boundary of the interval when guessing zeros. 
static constexpr double GUESS_ZERO_INTERVAL_LOWER_BOUNDARY  = -40;      //< This is the lower boundary of the interval when guessing zeros.
static constexpr double GUESS_ZERO_INTERVAL_INTERATION_STEP = 0.4;      //< This is the step size when guessing zeros.
static constexpr double GUESS_ZERO_ERROR_MARGIN             = 1E-14;    //< This is the step size when guessing zeros.
static constexpr double GUESS_ZERO_MAX_ITERATIONS           = 1000;     //< The maximum number of iterations that shall be performed when approximating a zero.

/* Constructors **************************************************************/

/**
 * \brief Creates an instance of a polynomial which only consists of one term: 0*x^0.
          It is basically an empty instance and can be interacted with.
 */
Polynomial();                                   // Default ctor

/**
 * \brief Creates an instance of a polynomial.
 * 
 * \param coefficientList A list of coefficients (std::vector<float>()), where the first element is 
          the highest order of the polynomial and the last element is 
          always the 0th order. As example, the polynomial 3x^4 - 2x^2 + 8 
          would be new std::vector<float>(){3, 0, 2, 0, 8}, because always all 
          powers need to be given.
 */
Polynomial(CoefficientList coefficientList);    // Initialize with coefficientlist

/**
 * \brief Construct a new Polynomial object.
 * 
 * \param monomials The terms of the polynomial. Is a list of the type std::vector<Monomial>.
 */
Polynomial(Terms monomials);                    // Initialize with list of monomials

/**
 * \brief Copy constructor of polynomial. Takes in a polynomial and creates a copy of it with another reference.
 * 
 * \param original The polynomial to be copied.
 */
Polynomial(const Polynomial& original);         // Copy constructor

/* Accessors/Mutators ********************************************************/
void SetMonomials(Terms monomials);
Terms GetMonomials() const;

void SetRest(Terms rest);
Terms GetRest() const;

int GetOrder() const;
int GetRestOrder() const;

/* Enabling accessing ********************************************************/

/*
    This section enables the class to be indexed like
    ```
    Polynomial p;
    p[0] = Monomial(2,0);
    ```
    When accessing, the index is the exponent, so that
    p[0] = Monomial(2,0);
    will access the x^0 monomial.
    When assigning, the polynomial will be reordered and interpolated.
*/


// Write access
Monomial& operator[](size_t exponent) 
{
    return this->Monomials[this->Monomials.size() - 1 - exponent];
}

// Read-only access
const Monomial& operator[](size_t exponent) const 
{
    return this->Monomials[this->Monomials.size() - 1 - exponent];
}

auto begin() { return this->Monomials.begin(); }
auto end() { return this->Monomials.end(); }
auto begin() const { return this->Monomials.begin(); }
auto end() const { return this->Monomials.end(); }

/* Public Methods ************************************************************/

// Operators
bool operator ==(const Polynomial& other) const;
bool operator !=(const Polynomial& other) const;

// Methods

/**
 * \brief Integrates the polynomial once.
 */
void Integrate();   

/**
 * \brief Integrates a polynomial and returns it.
 * 
 * \param p The polynomial serving as a base to be integrated.
 * \return Polynomial The polynomial which was integrated from the base polynomial.
 */
static Polynomial Integrate(const Polynomial& p);

/**
 * \brief Differentiates the polynomial once.
 */
void Differentiate();       

/**
 * \brief Differentiates a polynomial and returns it.
 * 
 * \param p The polynomial serving as a base to be differentiated.
 * \return Polynomial The polynomial which was differentiated from the base polynomial.
 */
static Polynomial Differentiate(const Polynomial& p);


void EvaluateAt(double x);       
std::vector<double> Zeros();
std::vector<double> Decompose();
double GetArea(double lowerLimit, double upperLimit);
double GetAreaNumerically(double lowerLimit, double upperLimit);



// Static Methods

// TODO: Somehow inline doesnt work. Why?
/*inline*/ static int GetHighestOrderOfPolynomialTerms(const Polynomial& polynomial);
/*inline*/ static int GetHighestOrderOfPolynomialTerms(const Terms monomials);
/*inline*/ static int GetHighestOrderOfPolynomialCoefficients(const CoefficientList coefficients);
// static inline int GetLowestOrderOfPolynomialTerms(const Polynomial& polynomial);
// static inline int GetLowestOrderOfPolynomialTerms(const Terms monomials);

static Terms CoefficientList2Terms(const CoefficientList coefficients);
static CoefficientList Terms2CoefficientList(const Terms terms);


/**
 * \brief Takes in a list of terms, combines terms with the same exponent and sorts them by exponent.
 * 
 * \param terms A list of terms that should be combined and sorted.
 * \return Terms The sorted and simplified term list.
 */
static Terms CombineTerms(const Terms& terms);

/**
 * \brief This function takes a list of terms and then interpolates the terms by padding the missing powers between the highest order and 0th order.
          Also, removes and preceeding zeros of the polynomial.
 * 
 * \param terms The list of terms to be modified.
 * \return Terms A term list with padded zeros-powers.
 */
static Terms InterpolateTerms(const Terms& terms);

// Overloaded standard methods
std::string to_string() const;

bool IsEqual(const Polynomial& other) const;

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
private:    
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/* Private Member variables ***************************************************/

Terms Monomials;    //< These are the monomials the polynomial is made of.
Terms Rest;         //< This is the rest after an operation. [May be subject to change]
int Order;          //< This is the order of the polynomial.
int RestOrder;     //< This is the order/degree of the rest of the polynomial.

/* Private Methods ************************************************************/

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

// Operators for this class

Polynomial operator +(const Polynomial& left, const Monomial& right);       // tested -------------------
Polynomial operator +(const Polynomial& left, const double right);          // tested -------------------
Polynomial operator +(const Polynomial& left, const Polynomial& right);     // tested -------------------
Polynomial operator +(const Monomial& left, const Polynomial& right);       // tested -------------------
Polynomial operator +(const double left, const Polynomial& right);          // tested -------------------

Polynomial operator -(const Polynomial& left, const Monomial& right);       // tested -------------------
Polynomial operator -(const Polynomial& left, const double right);          // tested -------------------
Polynomial operator -(const Polynomial& left, const Polynomial& right);     // tested -------------------
Polynomial operator -(const Monomial& left, const Polynomial& right);       // tested ------------------- FAILED
Polynomial operator -(const double left, const Polynomial& right);          // tested ------------------- FAILED

// TODO: Test these
Polynomial operator *(const Polynomial& left, const Monomial& right);       
Polynomial operator *(const Polynomial& left, const double right);          
Polynomial operator *(const Polynomial& left, const Polynomial& right);     
Polynomial operator *(const Monomial& left, const Polynomial& right);       
Polynomial operator *(const double left, const Polynomial& right);          


// TODO: Implement these, test these
Polynomial operator /(const Polynomial& left, const Monomial& right);
Polynomial operator /(const Polynomial& left, const double right);
Polynomial operator /(const Polynomial& left, const Polynomial& right);
Polynomial operator /(const Monomial& left, const Polynomial& right);
Polynomial operator /(const double left, const Polynomial& right);

} // namespace vath

#endif /* _POLYNOMIAL_HPP_ */