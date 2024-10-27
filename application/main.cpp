#include <iostream>

#include "./headers/monomial.hpp"
#include "./headers/polynomial.hpp"

using namespace Vath;

int main(int argc, char *argv[])
{

    Polynomial A(CoefficientList{2, 0, -2, 3, -1});
    Polynomial B(CoefficientList{2, 0, 1});
    Polynomial result = A/B;

    Monomial m(3, 5);
    Monomial n(-4.34, -8);

    std::cout << "Numerator:\t" << A << std::endl;
    std::cout << "Denominator:\t" << B << std::endl;
    std::cout << "Result:\t\t" << result << std::endl;
    return 0;
}