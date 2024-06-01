using Vath.Components;

namespace Vath.Program
{
    using Terms = List<Term>;
    using CoefficientList = List<double>;

    internal class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Started program ...");

            //Polynomial A = new Term(3, 3) + new Term(3, 2) + new Term(3, 1) + new Term(3, 1);
            //Console.WriteLine(A);

            Polynomial B = new Polynomial(new CoefficientList() { 0, 0, 3, 2, 1, 0});
            Console.WriteLine(B);
            

            Console.WriteLine("... done program.");
            Console.ReadLine();
        }
    }
}