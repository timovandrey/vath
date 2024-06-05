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


    internal class Kurvendiskuteur
    {
        #region Constants
        #endregion
        #region Constructors
        #endregion
        #region Variables / Properties

        Polynomial numerator;
        Polynomial? denominator;

        string definitionRange;
        List<double> zeros;
        List<double> poles;
        List<Tuple<double, double>> wendepunkte;
        List<Tuple<double, double>> maxima;
        List<Tuple<double, double>> minima;
        double yAxisCross;
        SymmetryType symmetry;
        List<Polynomial> asymptotes;

        #endregion
        #region Overridden operators
        #endregion
        #region Standard overridden functions
        #endregion
        #region Instance methods
        #endregion
        #region Class functions
        #endregion


    }

    public enum SymmetryType
    {
        AxialSymmetric,
        Pointsymmetric,
        NonSymmetry
    }

}
