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

            Polynomial A = new Polynomial();
            A.Rest = new Terms() { new Term(1, 1), new Term(2, 2), new Term(3, 3), new Term(4, 4) };

            Console.WriteLine("... done Progam.");
        }
    }
}