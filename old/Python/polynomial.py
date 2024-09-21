"""!

\file polynomial.py

\author Timo Vandrey

\date 30.04.2024

\brief Implements the Polynomial class.

"""

from typing import Any

class Polynomial:
    """!
    \brief Abstracts a polynomial so that it can be used further in other programs  
    """

### Constants #################################################################
    COEFF_IDX = 0
    POWER_IDX = 1

### Variables #################################################################    
    array : list = [] 
    pairs : list = []
    __order : int = None

### Properties ################################################################
    
    def order(self):
        return self.__order

### Inherent methods ##########################################################
    def __init__(self, polynomialArrayOrPairs) -> None:
        """
        \brief Initializes the polynomial class.
        \param polynomialArrayOrPairs Is either a list of linearly descending coefficients or a list of tuples with (coefficient, power), linearly descending.
        """
        if(not isinstance(polynomialArrayOrPairs, list)):
            return None
        if(isinstance(polynomialArrayOrPairs[0], tuple)):
            self.pairs = polynomialArrayOrPairs
            # self.array = self.__coeffPowerPairs2CoeffArray(polynomialArrayOrPairs)
        else:
            # self.pairs = self.__coeffArray2PowerPairs(polynomialArrayOrPairs)
            self.array = polynomialArrayOrPairs        
        # self.__order = self.__getHighestOrderOfPolynomialTerms()[self.POWER_IDX]    

    def __str__(self) -> str:
        if(self.array is None or self.pairs is None):
            raise Exception("Polynomial not correctly initialized.")

        polynomialStringRepresentation = ""

        maxPower = len(self.array) - 1
        for term in self.array:
            polynomialStringRepresentation += "{0:+}".format(term)
            polynomialStringRepresentation += "x{0}".format(maxPower)
            maxPower -= 1

        return polynomialStringRepresentation + "\t(Order: {0})".format(self.__order)

    def __setattr__(self, name: str, value: Any) -> None:
        # TODO: Check for valid forms of assignment (whether the forms [] or [(,),(,)]) are given)
        if(name == "array"):
            self.__dict__[name] = value
            self.__dict__["pairs"] = self.__coeffArray2PowerPairs(value)
            self.__dict__["__order"] = self.__getHighestOrderOfPolynomialTerms()[self.POWER_IDX]
            pass
        elif(name == "pairs"):
            self.__dict__[name] = value
            self.__dict__["array"] = self.__coeffPowerPairs2CoeffArray(value)
            self.__dict__["__order"] = self.__getHighestOrderOfPolynomialTerms()[self.POWER_IDX]
            pass
        else:
            self.__dict__[name] = value

### Methods ###################################################################

    def __coeffPowerPairs2CoeffArray(self, coeffPowerPairPolynomial):
        """
        \brief Takes in a polynomial as list of (coefficient, power) and returns an array with linearly descending coefficients
        
        \param coeffPowerPairPolynomial The polynomials as a list of the tuples in the form of (coefficient, power)

        \return The polynomial as list of coefficients (linearly descending power)
        """
        # TODO: Make sure polynomials zeros are padded if a power is missing
        if(coeffPowerPairPolynomial is None):
            return None
        
        resultCoeffPowerPairs = coeffPowerPairPolynomial
        # Append as many potentials until the last potential is zero (x**0), to pad
        resultCoeffPowerPairs = sorted(resultCoeffPowerPairs, key=lambda x: x[1], reverse=True)
        while(resultCoeffPowerPairs[-1][1] != 0):
            resultCoeffPowerPairs.append((0, resultCoeffPowerPairs[-1][1] - 1))
        result = [pair[0] for pair in resultCoeffPowerPairs]
        return result
    
    def __coeffArray2PowerPairs(self, coeffArrayPolynomial):
        # TODO: Make sure to always check that there are all terms given (0 to N)
        """
        \brief Takes in a polynomial as list of coefficients with linearly descending powers and returns a list of tuples in the form of (coefficient, power).

        \param coeffArrayPolynomial The polynomial as list of coefficients with linearly descending powers.

        \return The polynomial as list of tuples in the form (coefficient, power).        
        """
        coeffPowerPairs = []
        maxPower = len(coeffArrayPolynomial) - 1 
        for i in range(0, maxPower + 1):
            power = maxPower - i
            coeffPowerPairs.append((coeffArrayPolynomial[i], power))
        return coeffPowerPairs
    
    def __getHighestOrderOfPolynomialTerms(self):
        """
        \brief Gets the term with the highest order of the polynomial.

        \return The highest order of the polynomial.
        """
        if(self.array is None or self.pairs is None):
            raise Exception("Polynomial not correctly initialized.")
        highestOrder = max(self.pairs, key=lambda x: x[1])
        return highestOrder

    def __getLowestOrderOfPolynomialTerms(self):
        """
        \brief Gets the term with the lowest order of the polynomial.

        \return The lowest order of the polynomial.
        """
        if(self.array is None or self.pairs is None):
            raise Exception("Polynomial not correctly initialized.")
        lowestOrder = min(self.pairs, key=lambda x: x[1])
        return lowestOrder

        pass