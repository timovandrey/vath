from polynomial import Polynomial
import polynomialSolver

def main():

    print("--------------------------------------------------------------")
    numerator = Polynomial([4, 3, 2, 1, 0])
    print("numerator.array = {0}".format(numerator.array))
    print("numerator.pairs = {0}".format(numerator.pairs))
    print("numerator.order = {0}".format(numerator.order()))
    print(numerator)

    print("--------------------------------------------------------------")
    numerator.array = [2, 1, 0]
    print("numerator.array = {0}".format(numerator.array))
    print("numerator.pairs = {0}".format(numerator.pairs))
    print("numerator.order = {0}".format(numerator.order()))
    print(numerator)

    # numerator.order = 80

    print("--------------------------------------------------------------")
    numerator.pairs = [(1, 3), (2, 2), (3, 1)]
    print("numerator.array = {0}".format(numerator.array))
    print("numerator.pairs = {0}".format(numerator.pairs))
    print("numerator.order = {0}".format(numerator.order()))
    print(numerator)
    
    print("--------------------------------------------------------------")

    pass

if __name__ == "__main__":
    main()