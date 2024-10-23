#include <iostream>

#include "./headers/monomial.hpp"
#include "./headers/polynomial.hpp"

using namespace Vath;

int main(int argc, char *argv[])
{

    Polynomial A(CoefficientList{3, 4, 5, 7});
    Polynomial B(CoefficientList{3, 4, 5, 7});
    Polynomial result = A/B;

    Monomial m(3, 5);
    Monomial n(-4.34, -8);

    // std::cout << m;
    // std::cout << std::endl;
    // std::cout << n << std::endl;



    return 0;
}