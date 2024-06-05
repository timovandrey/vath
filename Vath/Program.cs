using Vath.Components;

namespace Vath.Program
{
    using Terms = List<Monomial>;
    using CoefficientList = List<double>;

    internal class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Started program ...");

            //Polynomial A = new Polynomial(new CoefficientList() { 1, -3, 6 });
            //Polynomial B = new Polynomial(Snew CoefficientList() { 1, -1 });
            //Polynomial Result = A / B;
            //Polynomial New = A * new Polynomial(Result.Rest);

            Polynomial A = new Polynomial(new CoefficientList() { 1, 12, 54, 108, 81 });
            Polynomial B = new Polynomial(new CoefficientList() { 1, 3 });

            Polynomial C = A / B;


            Console.WriteLine("... done Progam.");
        }
    }
}