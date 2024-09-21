using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Vath.UnitTests
{
    [TestClass]
    public class UltraPrecisionDecimalTests
    {
        [TestMethod]
        public void IsValidValue_Test0DecimalPoint_ReturnsTrue()
        {
            Assert.IsTrue(UltraPrecisionDecimal.IsValidValue("0.01"));
        }
        [TestMethod]
        public void IsValidValue_Test1DecimalPoint_ReturnsTrue()
        {
            Assert.IsTrue(UltraPrecisionDecimal.IsValidValue("131456.011346130938146098394068093846901903469081390486901834906813904869013846908139048690138469081390468901384690813046"));
        }
        [TestMethod]
        public void IsValidValue_Test2DecimalPoint_ReturnsTrue()
        {
            Assert.IsTrue(UltraPrecisionDecimal.IsValidValue("0.0234"));
        }
        [TestMethod]
        public void IsValidValue_Test3DecimalPoint_ReturnsTrue()
        {
            Assert.IsTrue(UltraPrecisionDecimal.IsValidValue("010.0234"));
        }
        [TestMethod]
        public void IsValidValue_Test4DecimalPoint_ReturnsTrue()
        {
            Assert.IsTrue(UltraPrecisionDecimal.IsValidValue("+0.01"));
        }
        [TestMethod]
        public void IsValidValue_Test5DecimalPoint_ReturnsTrue()
        {
            Assert.IsTrue(UltraPrecisionDecimal.IsValidValue("-131456.011346130938146098394068093846901903469081390486901834906813904869013846908139048690138469081390468901384690813046"));
        }
        [TestMethod]
        public void IsValidValue_Test6DecimalPoint_ReturnsTrue()
        {
            Assert.IsTrue(UltraPrecisionDecimal.IsValidValue("-0.0234"));
        }
        [TestMethod]
        public void IsValidValue_Test7DecimalPoint_ReturnsTrue()
        {
            Assert.IsTrue(UltraPrecisionDecimal.IsValidValue("+010.0234"));
        }

        // TODO: Do more "validation" of numbers as strings

        [TestMethod]
        public void DecomposeToList_NumberIsEntered0_ReturnsTrue()
        {
            double x = 31415.9988001;
            UltraPrecisionDecimal ultra = new UltraPrecisionDecimal(x);
            Tuple<List<int>,List<int>> beforeAndAfter = UltraPrecisionDecimal.DecomposeToList(ultra);

            float y = 0.006f;
            ultra = new UltraPrecisionDecimal(y);
            Tuple<List<int>, List<int>> beforeAndAfter1 = UltraPrecisionDecimal.DecomposeToList(ultra);

            string z = "12345678910112233445566778899100111222333444555666777888999";
            ultra = new UltraPrecisionDecimal(z);
            Tuple<List<int>, List<int>> beforeAndAfter2 = UltraPrecisionDecimal.DecomposeToList(ultra);
            
            // TODO: Do proper testing

            Assert.Inconclusive();
        }
        [TestMethod]
        public void Recompose_NumberIsEntered0_ReturnsTrue()
        {
            // TODO: Do proper testing!
            List<int> before = new List<int> { 1, 2, 3 };
            List<int> after = new List<int> { 4, 5, 6, 7 };

            UltraPrecisionDecimal test = new UltraPrecisionDecimal(new Tuple<List<int>,List<int>>(before, after));
            Assert.IsTrue(test.ToString() == "123,4567");
        }
    }   
}

