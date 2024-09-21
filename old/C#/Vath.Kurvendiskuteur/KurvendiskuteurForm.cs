using ScottPlot;
using ScottPlot.DataGenerators;
using System;
using ScottPlot.DataSources;
using Vath.Components;
using Vath;


namespace Vath.KurvendiskussionsApplet
{
    using CoefficientList = List<decimal>;
    using Terms = List<Monomial>;

    public partial class KurvendiskuteurForm : Form
    {
        const int X_PADDING = 8; // Pixel
        const int Y_PADDING = 8; // Pixel
        const int STD_BUTTON_HEIGHT = 32;

        PolynomialFraction debugPolynomial = new PolynomialFraction() with
        {
            numerator = new Polynomial(new CoefficientList() { 1.0m, 2.0m, 3.0m }),
            denominator = new Polynomial(new CoefficientList() { 1.0m, 2.0m, 3.0m})
        };

        bool updateRequired = true;

        Kurvendiskuteur kurvendiskussion;
        

        public KurvendiskuteurForm()
        {
            InitializeComponent();
            kurvendiskussion = new Kurvendiskuteur(debugPolynomial);
        }

        private void StartPage_Click(object sender, EventArgs e)
        {

        }

        private void ForwardButton_Click(object sender, EventArgs e)
        {
            //// https://scottplot.net/cookbook/5.0/Scatter/
            //double[] xValsArray = new double[] { 1, 2, 3, 4, 5, 6 };
            //double[] yValsArray = new double[] { 11, 12, 33, 44, 15, 16 };

            //var xValsArray2 = ScottPlot.Generate.Consecutive();
            //var yValsArray2 = ScottPlot.Generate.Sin(xValsArray.Length, 2, 1, 4, 0);
            //ScottPlot.Generate.AddNoise(yValsArray, 2);

            //this.MainPlotWindow.Plot.Add.ScatterLine(xValsArray, yValsArray);
            //this.MainPlotWindow.Plot.Add.ScatterLine(xValsArray2, yValsArray2, ScottPlot.Color.FromColor(System.Drawing.Color.RebeccaPurple));

            //this.InfoTextBox.Text = "lahgoaeig!!!";
            int newTabIndex = TabContentPage.SelectedIndex + 1;
            int.Clamp(newTabIndex, 0, TabContentPage.TabCount - 1);
            TabContentPage.SelectedIndex = newTabIndex;
        }

        private void BackButton_Click(object sender, EventArgs e)
        {
            int newTabIndex = TabContentPage.SelectedIndex - 1;
            int.Clamp(newTabIndex, 0, TabContentPage.TabCount - 1);
            TabContentPage.SelectedIndex = newTabIndex;
        }

        private void TabContentPage_StartPage_OnPaint(object sender, PaintEventArgs e)
        {
            this.InfoTextBox.Text = "StartPage!";
            BackButton.Enabled = false;
            if(!updateRequired)
            {
                return;
            }
        }

        private void TabContentPage_DerivativesPage_OnPaint(object sender, PaintEventArgs e)
        {
            this.InfoTextBox.Text = "TabContentPage_DerivativesPage_OnPaint!";
            BackButton.Enabled = true;
            if (!updateRequired)
            {
                return;
            }



        }

        private void TabContentPage_IntegralsPage_OnPaint(object sender, PaintEventArgs e)
        {
            this.InfoTextBox.Text = "TabContentPage_IntegralsPage_OnPaint!";
            BackButton.Enabled = true;
            if (!updateRequired)
            {
                return;
            }
        }

        private void TabContentPage_YAxisPage_OnPaint(object sender, PaintEventArgs e)
        {
            this.InfoTextBox.Text = "TabContentPage_YAxisPage_OnPaint!";
            BackButton.Enabled = true;
            if (!updateRequired)
            {
                return;
            }
        }

        private void TabContentPage_ZerosAndPolesPage_OnPaint(object sender, PaintEventArgs e)
        {
            this.InfoTextBox.Text = "TabContentPage_ZerosAndPolesPage_OnPaint!";
            BackButton.Enabled = true;
            if (!updateRequired)
            {
                return;
            }
        }

        private void TabContentPage_AsymptotesPage_OnPaint(object sender, PaintEventArgs e)
        {
            this.InfoTextBox.Text = "TabContentPage_AsymptotesPage_OnPaint!";
            BackButton.Enabled = true;
            if (!updateRequired)
            {
                return;
            }
        }

        private void TabContentPage_LimitsPage_OnPaint(object sender, PaintEventArgs e)
        {
            this.InfoTextBox.Text = "TabContentPage_LimitsPage_OnPaint!";
            BackButton.Enabled = true;
            if (!updateRequired)
            {
                return;
            }
        }

        private void TabContentPage_ExtremesAndTurningPointsPage_OnPaint(object sender, PaintEventArgs e)
        {
            this.InfoTextBox.Text = "TabContentPage_ExtremesAndTurningPointsPage_OnPaint!";
            BackButton.Enabled = true;
            if (!updateRequired)
            {
                return;
            }
        }

        private void TabContentPage_MonotonyPage_OnPaint(object sender, PaintEventArgs e)
        {
            this.InfoTextBox.Text = "TabContentPage_MonotonyPage_OnPaint!";
            BackButton.Enabled = true;
            if (!updateRequired)
            {
                return;
            }
        }

        private void TabContentPage_CurvaturePage_OnPaint(object sender, PaintEventArgs e)
        {
            this.InfoTextBox.Text = "TabContentPage_CurvaturePage_OnPaint!";
            BackButton.Enabled = true;
            if (!updateRequired)
            {
                return;
            }
        }

        private void TabContentPage_DomainPage_OnPaint(object sender, PaintEventArgs e)
        {
            this.InfoTextBox.Text = "TabContentPage_DomainPage_OnPaint!";
            BackButton.Enabled = true;
            if (!updateRequired)
            {
                return;
            }
        }
    }
}
