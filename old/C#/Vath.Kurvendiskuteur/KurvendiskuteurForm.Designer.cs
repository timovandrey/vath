namespace Vath.KurvendiskussionsApplet
{
    partial class KurvendiskuteurForm
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            MainView = new SplitContainer();
            DataView = new SplitContainer();
            MainPlotWindow = new ScottPlot.WinForms.FormsPlot();
            InfoTextBox = new RichTextBox();
            TabContentPage = new TabControl();
            StartPage = new TabPage();
            StartPage_TableLayout = new TableLayoutPanel();
            StartPage_DenominatorLabel = new Label();
            StartPage_NumeratorTextBox = new TextBox();
            StartPage_DenominatorTextBox = new TextBox();
            StartPage_NumeratorLabel = new Label();
            DerivativesPage = new TabPage();
            IntegralPage = new TabPage();
            YAxisPage = new TabPage();
            ZerosAndPolesPage = new TabPage();
            AsymptotesPage = new TabPage();
            LimitsPage = new TabPage();
            ExtremesAndTurningPointsPage = new TabPage();
            MonotonyPage = new TabPage();
            CurvaturePage = new TabPage();
            DomainPage = new TabPage();
            ForwardButton = new Button();
            BackButton = new Button();
            ((System.ComponentModel.ISupportInitialize)MainView).BeginInit();
            MainView.Panel1.SuspendLayout();
            MainView.Panel2.SuspendLayout();
            MainView.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)DataView).BeginInit();
            DataView.Panel1.SuspendLayout();
            DataView.Panel2.SuspendLayout();
            DataView.SuspendLayout();
            TabContentPage.SuspendLayout();
            StartPage.SuspendLayout();
            StartPage_TableLayout.SuspendLayout();
            SuspendLayout();
            // 
            // MainView
            // 
            MainView.Dock = DockStyle.Fill;
            MainView.FixedPanel = FixedPanel.Panel2;
            MainView.Location = new Point(0, 0);
            MainView.Name = "MainView";
            MainView.Orientation = Orientation.Horizontal;
            // 
            // MainView.Panel1
            // 
            MainView.Panel1.Controls.Add(DataView);
            // 
            // MainView.Panel2
            // 
            MainView.Panel2.Controls.Add(TabContentPage);
            MainView.Panel2.Controls.Add(ForwardButton);
            MainView.Panel2.Controls.Add(BackButton);
            MainView.Size = new Size(976, 527);
            MainView.SplitterDistance = 325;
            MainView.TabIndex = 0;
            // 
            // DataView
            // 
            DataView.Dock = DockStyle.Fill;
            DataView.Location = new Point(0, 0);
            DataView.Name = "DataView";
            // 
            // DataView.Panel1
            // 
            DataView.Panel1.Controls.Add(MainPlotWindow);
            // 
            // DataView.Panel2
            // 
            DataView.Panel2.Controls.Add(InfoTextBox);
            DataView.Size = new Size(976, 325);
            DataView.SplitterDistance = 750;
            DataView.TabIndex = 0;
            // 
            // MainPlotWindow
            // 
            MainPlotWindow.DisplayScale = 1F;
            MainPlotWindow.Dock = DockStyle.Fill;
            MainPlotWindow.Location = new Point(0, 0);
            MainPlotWindow.Name = "MainPlotWindow";
            MainPlotWindow.Size = new Size(750, 325);
            MainPlotWindow.TabIndex = 0;
            // 
            // InfoTextBox
            // 
            InfoTextBox.Dock = DockStyle.Fill;
            InfoTextBox.Location = new Point(0, 0);
            InfoTextBox.Name = "InfoTextBox";
            InfoTextBox.Size = new Size(222, 325);
            InfoTextBox.TabIndex = 0;
            InfoTextBox.Text = "";
            // 
            // TabContentPage
            // 
            TabContentPage.Controls.Add(StartPage);
            TabContentPage.Controls.Add(DerivativesPage);
            TabContentPage.Controls.Add(IntegralPage);
            TabContentPage.Controls.Add(YAxisPage);
            TabContentPage.Controls.Add(ZerosAndPolesPage);
            TabContentPage.Controls.Add(AsymptotesPage);
            TabContentPage.Controls.Add(LimitsPage);
            TabContentPage.Controls.Add(ExtremesAndTurningPointsPage);
            TabContentPage.Controls.Add(MonotonyPage);
            TabContentPage.Controls.Add(CurvaturePage);
            TabContentPage.Controls.Add(DomainPage);
            TabContentPage.Dock = DockStyle.Fill;
            TabContentPage.Location = new Point(75, 0);
            TabContentPage.Name = "TabContentPage";
            TabContentPage.SelectedIndex = 0;
            TabContentPage.Size = new Size(826, 198);
            TabContentPage.TabIndex = 2;
            // 
            // StartPage
            // 
            StartPage.Controls.Add(StartPage_TableLayout);
            StartPage.Location = new Point(4, 24);
            StartPage.Name = "StartPage";
            StartPage.Padding = new Padding(3);
            StartPage.Size = new Size(818, 170);
            StartPage.TabIndex = 0;
            StartPage.Text = "Start";
            StartPage.UseVisualStyleBackColor = true;
            StartPage.Click += StartPage_Click;
            StartPage.Paint += TabContentPage_StartPage_OnPaint;
            // 
            // StartPage_TableLayout
            // 
            StartPage_TableLayout.ColumnCount = 2;
            StartPage_TableLayout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 11.576355F));
            StartPage_TableLayout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 88.423645F));
            StartPage_TableLayout.Controls.Add(StartPage_DenominatorLabel, 0, 1);
            StartPage_TableLayout.Controls.Add(StartPage_NumeratorTextBox, 1, 0);
            StartPage_TableLayout.Controls.Add(StartPage_DenominatorTextBox, 1, 1);
            StartPage_TableLayout.Controls.Add(StartPage_NumeratorLabel, 0, 0);
            StartPage_TableLayout.Dock = DockStyle.Fill;
            StartPage_TableLayout.Location = new Point(3, 3);
            StartPage_TableLayout.Name = "StartPage_TableLayout";
            StartPage_TableLayout.RowCount = 2;
            StartPage_TableLayout.RowStyles.Add(new RowStyle(SizeType.Percent, 50F));
            StartPage_TableLayout.RowStyles.Add(new RowStyle(SizeType.Percent, 50F));
            StartPage_TableLayout.Size = new Size(812, 164);
            StartPage_TableLayout.TabIndex = 4;
            // 
            // StartPage_DenominatorLabel
            // 
            StartPage_DenominatorLabel.AutoSize = true;
            StartPage_DenominatorLabel.Location = new Point(3, 82);
            StartPage_DenominatorLabel.Name = "StartPage_DenominatorLabel";
            StartPage_DenominatorLabel.Size = new Size(77, 15);
            StartPage_DenominatorLabel.TabIndex = 1;
            StartPage_DenominatorLabel.Text = "Denominator";
            // 
            // StartPage_NumeratorTextBox
            // 
            StartPage_NumeratorTextBox.Dock = DockStyle.Bottom;
            StartPage_NumeratorTextBox.Location = new Point(97, 56);
            StartPage_NumeratorTextBox.Name = "StartPage_NumeratorTextBox";
            StartPage_NumeratorTextBox.Size = new Size(712, 23);
            StartPage_NumeratorTextBox.TabIndex = 2;
            // 
            // StartPage_DenominatorTextBox
            // 
            StartPage_DenominatorTextBox.Dock = DockStyle.Top;
            StartPage_DenominatorTextBox.Location = new Point(97, 85);
            StartPage_DenominatorTextBox.Name = "StartPage_DenominatorTextBox";
            StartPage_DenominatorTextBox.Size = new Size(712, 23);
            StartPage_DenominatorTextBox.TabIndex = 3;
            // 
            // StartPage_NumeratorLabel
            // 
            StartPage_NumeratorLabel.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
            StartPage_NumeratorLabel.AutoSize = true;
            StartPage_NumeratorLabel.Location = new Point(3, 67);
            StartPage_NumeratorLabel.Name = "StartPage_NumeratorLabel";
            StartPage_NumeratorLabel.Size = new Size(65, 15);
            StartPage_NumeratorLabel.TabIndex = 0;
            StartPage_NumeratorLabel.Text = "Numerator";
            // 
            // DerivativesPage
            // 
            DerivativesPage.Location = new Point(4, 24);
            DerivativesPage.Name = "DerivativesPage";
            DerivativesPage.Padding = new Padding(3);
            DerivativesPage.Size = new Size(818, 170);
            DerivativesPage.TabIndex = 1;
            DerivativesPage.Text = "Derivatives";
            DerivativesPage.UseVisualStyleBackColor = true;
            DerivativesPage.Paint += TabContentPage_DerivativesPage_OnPaint;
            // 
            // IntegralPage
            // 
            IntegralPage.Location = new Point(4, 24);
            IntegralPage.Name = "IntegralPage";
            IntegralPage.Padding = new Padding(3);
            IntegralPage.Size = new Size(818, 170);
            IntegralPage.TabIndex = 2;
            IntegralPage.Text = "Integrals";
            IntegralPage.UseVisualStyleBackColor = true;
            IntegralPage.Paint += TabContentPage_IntegralsPage_OnPaint;
            // 
            // YAxisPage
            // 
            YAxisPage.Location = new Point(4, 24);
            YAxisPage.Name = "YAxisPage";
            YAxisPage.Padding = new Padding(3);
            YAxisPage.Size = new Size(818, 170);
            YAxisPage.TabIndex = 10;
            YAxisPage.Text = "Y-Axis";
            YAxisPage.UseVisualStyleBackColor = true;
            YAxisPage.Paint += TabContentPage_YAxisPage_OnPaint;
            // 
            // ZerosAndPolesPage
            // 
            ZerosAndPolesPage.Location = new Point(4, 24);
            ZerosAndPolesPage.Name = "ZerosAndPolesPage";
            ZerosAndPolesPage.Padding = new Padding(3);
            ZerosAndPolesPage.Size = new Size(818, 170);
            ZerosAndPolesPage.TabIndex = 3;
            ZerosAndPolesPage.Text = "Zeros/Poles";
            ZerosAndPolesPage.UseVisualStyleBackColor = true;
            ZerosAndPolesPage.Paint += TabContentPage_ZerosAndPolesPage_OnPaint;
            // 
            // AsymptotesPage
            // 
            AsymptotesPage.Location = new Point(4, 24);
            AsymptotesPage.Name = "AsymptotesPage";
            AsymptotesPage.Padding = new Padding(3);
            AsymptotesPage.Size = new Size(818, 170);
            AsymptotesPage.TabIndex = 4;
            AsymptotesPage.Text = "Asymptotes";
            AsymptotesPage.UseVisualStyleBackColor = true;
            AsymptotesPage.Paint += TabContentPage_AsymptotesPage_OnPaint;
            // 
            // LimitsPage
            // 
            LimitsPage.Location = new Point(4, 24);
            LimitsPage.Name = "LimitsPage";
            LimitsPage.Padding = new Padding(3);
            LimitsPage.Size = new Size(818, 170);
            LimitsPage.TabIndex = 9;
            LimitsPage.Text = "Limits";
            LimitsPage.UseVisualStyleBackColor = true;
            LimitsPage.Paint += TabContentPage_LimitsPage_OnPaint;
            // 
            // ExtremesAndTurningPointsPage
            // 
            ExtremesAndTurningPointsPage.Location = new Point(4, 24);
            ExtremesAndTurningPointsPage.Name = "ExtremesAndTurningPointsPage";
            ExtremesAndTurningPointsPage.Padding = new Padding(3);
            ExtremesAndTurningPointsPage.Size = new Size(818, 170);
            ExtremesAndTurningPointsPage.TabIndex = 5;
            ExtremesAndTurningPointsPage.Text = "Extremes/Turning points";
            ExtremesAndTurningPointsPage.UseVisualStyleBackColor = true;
            ExtremesAndTurningPointsPage.Paint += TabContentPage_ExtremesAndTurningPointsPage_OnPaint;
            // 
            // MonotonyPage
            // 
            MonotonyPage.Location = new Point(4, 24);
            MonotonyPage.Name = "MonotonyPage";
            MonotonyPage.Padding = new Padding(3);
            MonotonyPage.Size = new Size(818, 170);
            MonotonyPage.TabIndex = 6;
            MonotonyPage.Text = "Monotony";
            MonotonyPage.UseVisualStyleBackColor = true;
            MonotonyPage.Paint += TabContentPage_MonotonyPage_OnPaint;
            // 
            // CurvaturePage
            // 
            CurvaturePage.Location = new Point(4, 24);
            CurvaturePage.Name = "CurvaturePage";
            CurvaturePage.Padding = new Padding(3);
            CurvaturePage.Size = new Size(818, 170);
            CurvaturePage.TabIndex = 7;
            CurvaturePage.Text = "Curvature";
            CurvaturePage.UseVisualStyleBackColor = true;
            CurvaturePage.Paint += TabContentPage_CurvaturePage_OnPaint;
            // 
            // DomainPage
            // 
            DomainPage.Location = new Point(4, 24);
            DomainPage.Name = "DomainPage";
            DomainPage.Padding = new Padding(3);
            DomainPage.Size = new Size(818, 170);
            DomainPage.TabIndex = 8;
            DomainPage.Text = "Domain";
            DomainPage.UseVisualStyleBackColor = true;
            DomainPage.Paint += TabContentPage_DomainPage_OnPaint;
            // 
            // ForwardButton
            // 
            ForwardButton.Dock = DockStyle.Right;
            ForwardButton.Location = new Point(901, 0);
            ForwardButton.Name = "ForwardButton";
            ForwardButton.Size = new Size(75, 198);
            ForwardButton.TabIndex = 1;
            ForwardButton.Text = ">";
            ForwardButton.UseVisualStyleBackColor = true;
            ForwardButton.Click += ForwardButton_Click;
            // 
            // BackButton
            // 
            BackButton.Dock = DockStyle.Left;
            BackButton.Location = new Point(0, 0);
            BackButton.Name = "BackButton";
            BackButton.Size = new Size(75, 198);
            BackButton.TabIndex = 0;
            BackButton.Text = "<";
            BackButton.UseMnemonic = false;
            BackButton.UseVisualStyleBackColor = true;
            BackButton.Click += BackButton_Click;
            // 
            // KurvendiskuteurForm
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(976, 527);
            Controls.Add(MainView);
            MinimumSize = new Size(800, 480);
            Name = "KurvendiskuteurForm";
            Text = "Kurvendiskuteur";
            MainView.Panel1.ResumeLayout(false);
            MainView.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)MainView).EndInit();
            MainView.ResumeLayout(false);
            DataView.Panel1.ResumeLayout(false);
            DataView.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)DataView).EndInit();
            DataView.ResumeLayout(false);
            TabContentPage.ResumeLayout(false);
            StartPage.ResumeLayout(false);
            StartPage_TableLayout.ResumeLayout(false);
            StartPage_TableLayout.PerformLayout();
            ResumeLayout(false);
        }

        #endregion
        private GroupBox groupBox1;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private SplitContainer MainView;
        private SplitContainer DataView;
        private TabControl TabContentPage;
        private TabPage StartPage;
        private TabPage DerivativesPage;
        private Button ForwardButton;
        private Button BackButton;
        private RichTextBox InfoTextBox;
        private TabPage IntegralPage;
        private TabPage ZerosAndPolesPage;
        private TabPage AsymptotesPage;
        private TabPage ExtremesAndTurningPointsPage;
        private TabPage MonotonyPage;
        private TabPage CurvaturePage;
        private TabPage DomainPage;
        private TabPage LimitsPage;
        private TabPage YAxisPage;
        private TextBox StartPage_DenominatorTextBox;
        private TextBox StartPage_NumeratorTextBox;
        private Label StartPage_DenominatorLabel;
        private Label StartPage_NumeratorLabel;
        private TableLayoutPanel StartPage_TableLayout;
        private ScottPlot.WinForms.FormsPlot MainPlotWindow;
    }
}
