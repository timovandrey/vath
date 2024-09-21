using Vath.Components;

namespace Vath.Program
{
    using Terms = List<Monomial>;
    using CoefficientList = List<decimal>;

    internal class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Started program ...");

            Polynomial A = new Polynomial(new CoefficientList() { 1.0m, -3.0m, 6.0m });
            Polynomial B = new Polynomial(new CoefficientList() { 1.0m, -1.0m });

            Polynomial Result = A / B;
            //Polynomial New = A * new Polynomial(Result.Rest);

            //Polynomial A = new Polynomial(new CoefficientList() { 1, 12, 54, 108, 81 });
            //Polynomial B = new Polynomial(new CoefficientList() { 1, 3 });

            //Polynomial C = A / B;

            Polynomial x = new Polynomial(new Terms() { new Monomial(0.000333225m, 11), new Monomial(0.123m, 7), new Monomial(-0.38947m, 3) });
            Polynomial x2 = x.Integrate();



            Console.WriteLine("... done Progam.");
        }
    }
}