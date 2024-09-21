###############################################################################
# File:         polynomdivision.py
# Author:       Timo Vandrey
# Last edited:  27.04.2024
# Description:
# Takes in two polynomials and tries to divide them!
# TODO: Sysarg-Example!
###############################################################################
# Imports                                                                     #
###############################################################################
import sys
import numpy as np

from test import testArray


###############################################################################
# Constants                                                                   #
###############################################################################
MAX_RANGE_ZERO_FIND = 1000
MIN_STEP_ZERO_FIND = 1/1000


###############################################################################
# Functions                                                                   #
###############################################################################

def frange(start, end, step):
    return list(np.arange(start, end, step))

def createCoeffPowerPairs(polynomial):
    coeffPowerPairs = []
    maxPower = len(polynomial) - 1 
    for i in range(0, maxPower + 1):
        power = maxPower - i
        coeffPowerPairs.append((polynomial[i], power))
    return coeffPowerPairs

def getCoeffArrayFromCoeffPowerPairs(coeffPowerPairPolynomial):
    if(coeffPowerPairPolynomial is None):
        return None
    
    resultCoeffPowerPairs = coeffPowerPairPolynomial
    # Append as many potentials until the last potential is zero (x**0), to pad
    resultCoeffPowerPairs = sorted(resultCoeffPowerPairs, key=lambda x: x[1], reverse=True)
    while(resultCoeffPowerPairs[-1][1] != 0):
        resultCoeffPowerPairs.append((0, resultCoeffPowerPairs[-1][1] - 1))
    result = [pair[0] for pair in resultCoeffPowerPairs]
    return result

def dividePairTerms(pairNumerator, pairDenominator):
    return ((pairNumerator[0]/pairDenominator[0]), pairNumerator[1] - pairDenominator[1])

def multiplyPairTerms(pairNumerator, pairDenominator):
    return ((pairNumerator[0] * pairDenominator[0]), pairNumerator[1] + pairDenominator[1])

def subtractPairTerms(pairNumerator, pairDenominator):
    return ((pairNumerator[0] - pairDenominator[0]), pairNumerator[1])

def addPairTerms(pairNumerator, pairDenominator):
    return ((pairNumerator[0] + pairDenominator[0]), pairNumerator[1])

def divide(numerator, denominator):

    rest = None

    if(len(numerator) < len(denominator)):
        return (denominator, numerator)

    numerator = createCoeffPowerPairs(numerator)
    denominator = createCoeffPowerPairs(denominator)

    foundPolynomial = False
    intermediateAfterMult = []
    intermediateAfterSub = []
    result = []
    workingNumerator = numerator
    while(not foundPolynomial):
    
        # Divide with the highest term from divisor/denominator
        result.append(dividePairTerms(workingNumerator[0], denominator[0]))
        if(getLowestOrderOfCoeffPowerPairPolynom(result)[1] == 0):
            foundPolynomial = True
        
        for i in range(0, len(denominator)):
            intermediateAfterMult.append(multiplyPairTerms(result[-1], denominator[i]))

        # Pad with zeros so we can take the next term from the numerator
        if((len(workingNumerator) > len(intermediateAfterMult)) or 
           (False)):
            intermediateAfterMult.append((0, 0))

        # If we the polynom below the working polynom (numerator) after multiplication is longer than the working polynom (numerator), 
        # we have a problem and need to pull down the next coefficient of the original numerator polynom
        if((getLowestOrderOfCoeffPowerPairPolynom(workingNumerator)[1] > getLowestOrderOfCoeffPowerPairPolynom(intermediateAfterMult)[1])):
            for term in numerator:
                if(term[1] == workingNumerator[0][1] - 1):
                    workingNumerator.append(term)
                    break

        # Go through terms and subtract from another
        for i in range(0, len(intermediateAfterMult)):
            intermediateAfterSub.append(subtractPairTerms(workingNumerator[i], intermediateAfterMult[i]))
        workingNumerator = intermediateAfterSub[1:]
        
        # If the result of the subtraction is 0, we need to take the next term of the input numerator ("pull down")
        if((len(workingNumerator) == 1 and workingNumerator[0][1] != 0 and workingNumerator[0][0] == 0)):
            for term in numerator:
                if(term[1] == workingNumerator[0][1] - 1):
                    workingNumerator.append(term)
                    break

        if(workingNumerator[0][0] == 0 and workingNumerator[0][1] == 0):
            foundPolynomial = True


        if getHighestOrderOfCoeffPowerPairPolynom(workingNumerator)[1] < getHighestOrderOfCoeffPowerPairPolynom(denominator)[1]:
        # Here we found a polynomial, but there is a residual 
            # foundPolynomial = True
            if(workingNumerator[0][0] == 0 and workingNumerator[0][1] == 0):
                rest = None
            else:
                rest = workingNumerator

        intermediateAfterMult = []
        intermediateAfterSub = []

        pass

    return [result, rest]

def getHighestOrderOfCoeffPowerPairPolynom(coeffPowerPairPolynom):
    highestOrder = max(coeffPowerPairPolynom, key=lambda x: x[1])
    return highestOrder

def getLowestOrderOfCoeffPowerPairPolynom(coeffPowerPairPolynom):
    lowestOrder = min(coeffPowerPairPolynom, key=lambda x: x[1])
    return lowestOrder

def findZerosByPqFormula(polynomial):
    # TODO: Also find complex zeros
    if(len(polynomial) > 3):
        raise Exception("Cant work with polynomials greater than 2 with pq-formula.")
    
    normCoeff = polynomial[0]
    for i in range(0, len(polynomial)):
        polynomial[i] /= normCoeff
    p = polynomial[1]
    q = polynomial[2]

    rootTerm = np.sqrt((p/2)**2 - q)
    preTerm = -p/2

    zero1 = preTerm + rootTerm
    zero2 = preTerm - rootTerm

    return [zero1, zero2]

def findZeros(polynom):
    # By Horner Schema
    # Horner Schema is only applicable for polynomial divisions
    # with linear terms (i. e. (x-3))
    # ^ This comment does not have anything to do with the method implemented below, just an information


    # For more complex polinomials, use actual polynomial division
    # TODO: Also find complex zeros
    zeros = []
    # Guess one zero
    workingPolynom = polynom
    # Break because when term length == 3, we can solve per pq-formula
    while(len(workingPolynom) > 3):
        # Need to guess one zero
        guessedZero = None
        for i in range(-MAX_RANGE_ZERO_FIND, MAX_RANGE_ZERO_FIND + 1):
            tmp = findValueOfX(workingPolynom, i)
            if(tmp == 0):
                guessedZero = i
                break
        if(guessedZero is None):
            for i in frange(-MAX_RANGE_ZERO_FIND, MAX_RANGE_ZERO_FIND, MIN_STEP_ZERO_FIND):
                tmp = findValueOfX(workingPolynom, i)
                if(tmp == 0):
                    guessedZero = i
                    break
        if(guessedZero is None):
            raise Exception("Cant guess zero in polynomial. Is it complex?")
        
        belowPolynomial = []
        below = 0
        middle = 0
        for coeff in workingPolynom:
            belowPolynomial.append(below)
            below = coeff + middle
            middle = below * guessedZero
        if(below == 0):
            zeros.append(guessedZero)
        workingPolynom = belowPolynomial[1:]
    remainingZeros = findZerosByPqFormula(workingPolynom)
    zeros.append(remainingZeros[0])
    zeros.append(remainingZeros[1])

    return zeros

def findValueOfX(polynom, value):
    # By Horner Schema because less multiplications
    below = 0
    middle = 0
    for coeff in polynom:
        below = coeff + middle
        middle = below * value
    return below

def getPolynomialFromString(polynomialString):

    if(polynomialString.startswith("[") and polynomialString.endswith("]")):
        polynomialString = polynomialString.strip("[")
        polynomialString = polynomialString.strip("]")
    else:
        print("Error: Couldnt find an array of polynomial terms. Exiting.")
        exit(0)

    polynomialStringArray = polynomialString.split(",")
    polynomials = [int(term.strip()) for term in polynomialStringArray]

    return polynomials

def getPolynomialStringRepresentation(polynomial):
    if(not isinstance(polynomial, list)):
        print("Error: Couldnt create polynomial string. Please provide a list!")
        return ""

    polynomialStringRepresentation = ""

    maxPower = len(polynomial) - 1
    for term in polynomial:
        polynomialStringRepresentation += "{0:+}".format(term)
        polynomialStringRepresentation += "x{0}".format(maxPower)
        maxPower -= 1

    return polynomialStringRepresentation

def preprocessSysArgs(args):
    numerator = getPolynomialFromString(args[1])
    numerator = [float(term) for term in numerator]
    denominator = getPolynomialFromString(args[2])
    denominator = [float(term) for term in denominator]
    return (numerator, denominator)

def drawEquationInConsole(numerator, denominator, result, rest):

    if(rest is None):
        numeratorString = getPolynomialStringRepresentation(numerator)
        denominatorString = getPolynomialStringRepresentation(denominator)
        resultString = getPolynomialStringRepresentation(result)
        print(numeratorString)
        for i in range(len(numeratorString)):
            print("-", end="")
        print(" = {0}".format(resultString))
        print(denominatorString)
    else:
        
        numeratorString = getPolynomialStringRepresentation(numerator)
        denominatorString = getPolynomialStringRepresentation(denominator)
        resultString = getPolynomialStringRepresentation(result)
        restString = getPolynomialStringRepresentation(rest)

        print(numeratorString, end="")
        brigdeGap = 3 + len(resultString) + 3
        for i in range(brigdeGap):
            print(" ", end="")
        print(restString)

        for i in range(len(numeratorString)):
            print("-", end="")
        print(" = {0} + ".format(resultString), end="")
        for i in range(len(denominatorString)):
            print("-", end="")
        print()
        
        paddedDenominatorString = denominatorString
        paddedDenominatorString = paddedDenominatorString.rjust(len(numeratorString))
        print(paddedDenominatorString, end="")
        for i in range(brigdeGap):
            print(" ", end="")
        print(denominatorString)

        pass


###############################################################################
# Main                                                                        #
###############################################################################
def main(numerator, denominator):
    # print("Numerator: {0}".format(getPolynomialStringRepresentation(numerator)))
    # print("Denomiator: {0}".format(getPolynomialStringRepresentation(denominator)))

    # result = divide(numerator, denominator)
    # result = getCoeffArrayFromCoeffPowerPairs(result)
    # print("Result: {0}".format(getPolynomialStringRepresentation(result)))

    # for i in range(1, len(testArray)):
    #     expectedResult = testArray[i][2]
    #     expectedResult = [float(x) for x in expectedResult]
    #     [resultAsPairs, restAsPairs] = divide(testArray[i][0], testArray[i][1])
    #     result = getCoeffArrayFromCoeffPowerPairs(resultAsPairs)
    #     print("{0}) {1}".format(
    #         testArray[i][3],
    #         expectedResult == result
    #     ))

    [result, rest] = divide(numerator, denominator)
    result = getCoeffArrayFromCoeffPowerPairs(result)
    rest = getCoeffArrayFromCoeffPowerPairs(rest)
    drawEquationInConsole(numerator, denominator, result, rest)

    pass

###############################################################################
# Entry point                                                                 #
###############################################################################
if(__name__ == "__main__"):
    print("Started program ...")
    blub = sys.argv
    processedSysArgs = preprocessSysArgs(sys.argv)
    main(processedSysArgs[0], processedSysArgs[1])
    print("... done program.")


