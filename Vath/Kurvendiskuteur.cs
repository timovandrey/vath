using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Vath.Components;

namespace Vath
{

    // https://www.youtube.com/watch?v=UzjNEhpSNqA
    // https://www.youtube.com/watch?v=0F0CeyAbpmA


    #region TODOs
    /*
     * Definitionsmenge
     * Nullstellen
     * Schnittstellen mit der y-Achse
     * Asymptoten
     * Symmetrie
     * Grenzverhalten
     * Extrempunkte
     * Wendepunkte
     * Monotonie
     * Krümmung
     * 
     */
    #endregion


    public class Kurvendiskuteur
    {
        #region Constants
        #endregion
        #region Constructors

        public Kurvendiskuteur(Polynomial function) 
        {
            this.function.numerator = function;
            this.function.denominator = null;
            this.definitionRange = "?";
            this.zeros = new List<double>();
            this.poles = new List<double>();
            this.wendepunkte = new List<Tuple<double, double>>();
            this.maxima = new List<Tuple<double, double>>();
            this.minima = new List<Tuple<double, double>>();
            this.yAxisCross = null;
            this.symmetry = SymmetryType.IDontKnowYetMan;
            this.asymptotes = new List<Polynomial>();
        }

        public Kurvendiskuteur(PolynomialFraction rationalFunction)
        {
            this.function.numerator = rationalFunction.numerator;
            this.function.denominator = rationalFunction.denominator;
            this.definitionRange = "?";
            this.zeros = new List<double>();
            this.poles = new List<double>();
            this.wendepunkte = new List<Tuple<double, double>>();
            this.maxima = new List<Tuple<double, double>>();
            this.minima = new List<Tuple<double, double>>();
            this.yAxisCross = null;
            this.symmetry = SymmetryType.IDontKnowYetMan;
            this.asymptotes = new List<Polynomial>();
        }

        #endregion
        #region Variables / Properties

        PolynomialFraction function;

        string definitionRange;
        List<double> zeros;
        List<double> poles;
        List<Tuple<double, double>> wendepunkte;
        List<Tuple<double, double>> maxima;
        List<Tuple<double, double>> minima;
        double? yAxisCross;
        SymmetryType symmetry;
        List<Polynomial> asymptotes;

        List<PolynomialFraction> derivatives;
        List<PolynomialFraction> integrals;
        

        #endregion
        #region Overridden operators
        #endregion
        #region Standard overridden functions
        #endregion
        #region Instance methods
        #endregion
        #region Class functions
        public void FullDiscussion()
        {

        }

        public void CalculateDerivatives()
        {
            PolynomialFraction currentDerivative = this.function;
            for(int i = 0; i < 3; i++)
            {
                this.derivatives.Add(Polynomial.DifferentiateRationalPolynomial(currentDerivative));
                currentDerivative = this.derivatives[i];
            }
        }

        // TODO: Yeah no this wont happen
        public void CalculateIntegrals()
        {
            PolynomialFraction currentDerivative = this.function;
            for (int i = 0; i < 3; i++)
            {
                this.derivatives.Add(Polynomial.DifferentiateRationalPolynomial(currentDerivative));
                currentDerivative = this.derivatives[i];
            }
        }

        #endregion


    }

    public enum SymmetryType
    {
        IDontKnowYetMan,
        AxialSymmetric,
        Pointsymmetric,
        NonSymmetry
    }

}
