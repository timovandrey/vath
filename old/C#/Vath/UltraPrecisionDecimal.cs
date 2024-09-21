using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System;
using System.Text.RegularExpressions;

namespace Vath
{
    public class UltraPrecisionDecimal
    {

        #region Constants
        private const int DEFAULT_PRECISION = 250;
        private const int MAX_DIGITS_WITH_DECIMAL = 1024*4;
        private const string VALID_VALUE_REGEX_STR = "^[+-]?[0-9]*[\\.|\\,]?[0-9]+$";
        #endregion
        #region Variables / Properties
        private string Number;
        #endregion
        #region Constructors
        public UltraPrecisionDecimal(string number)
        {
            this.Number = number;
        }
        public UltraPrecisionDecimal(decimal number)
        {
            this.Number = number.ToString();
        }
        public UltraPrecisionDecimal(double number)
        {
            this.Number = number.ToString();
        }
        public UltraPrecisionDecimal(float number)
        {
            this.Number = number.ToString();
        }
        public UltraPrecisionDecimal(int number)
        {
            this.Number = number.ToString();
        }
        public UltraPrecisionDecimal(long number)
        {
            this.Number = number.ToString();
        }
        public UltraPrecisionDecimal(short number)
        {
            this.Number = number.ToString();
        }
        public UltraPrecisionDecimal(ushort number)
        {
            this.Number = number.ToString();
        }
        public UltraPrecisionDecimal(uint number)
        {
            this.Number = number.ToString();
        }
        public UltraPrecisionDecimal(byte number)
        {
            this.Number = number.ToString();
        }
        public UltraPrecisionDecimal(sbyte number)
        {
            this.Number = number.ToString();
        }
        public UltraPrecisionDecimal(ulong number)
        {
            this.Number = number.ToString();
        }
        public UltraPrecisionDecimal(Tuple<List<int>,List<int>> numberAsBeforeAndAfterDecimalPointDigitLists)
        {
            this.Number = UltraPrecisionDecimal.Recompose(numberAsBeforeAndAfterDecimalPointDigitLists).Number;
        }
        #endregion
        #region Overridden operators

        public static UltraPrecisionDecimal operator +(UltraPrecisionDecimal left, UltraPrecisionDecimal right)
        {
            var leftDecomposed = UltraPrecisionDecimal.DecomposeToList(left);
            var rightDecomposed = UltraPrecisionDecimal.DecomposeToList(right);

            // TODO: Continue here
            int amountOfZerosToPad = (leftDecomposed.Item2.Count - leftDecomposed.Item2.Count);


            if (amountOfZerosToPad >= 0)
            {
                
            }
            else
            {

            }
            


            return null;
        }

        #endregion
        #region Standard overridden functions

        public override string ToString()
        {
            return this.Number;
        }

        #endregion
        #region Instance methods
        /// <summary>
        /// Checks if the input string is a valid value that can be used as UltraPrecisionDecimal.
        /// </summary>
        /// <param name="value">The value to be checked.</param>
        /// <returns>True if its a valid value string, false if it's not.</returns>
        public static bool IsValidValue(string value)
        {
            Regex regex = new Regex(VALID_VALUE_REGEX_STR, RegexOptions.IgnoreCase);
            long valueLength = value.Length;
            return (regex.IsMatch(value) && valueLength <= MAX_DIGITS_WITH_DECIMAL);
        }
        #endregion
        #region Class functions

        /// <summary>
        /// Decomposes an UltraPrecisionDecimal into a representation of a tuple of two lists which contain the digits as integers.
        /// </summary>
        /// <param name="number">The number to be decomposed.</param>
        /// <returns>A tuple of two lists where the first list contains the digits of the portion before the decimal point and the second list contains the portion after the decimal point.</returns>
        /// <remarks>If its an integer type and no decimal point is given, the second list will be filled with a zero.</remarks>
        public static Tuple<List<int>, List<int>> DecomposeToList(UltraPrecisionDecimal number)
        {
            List<int> digitsBeforeDecimalPoint = new List<int>();
            List<int> digitsAfterDecimalPoint = new List<int>();

            if(!number.Number.ToLower().Contains(".") && !number.Number.ToLower().Contains(","))
            {
                number.Number += ".0";
            }

            string[] splitNumbers = number.Number.Split(',', StringSplitOptions.TrimEntries);
            if(splitNumbers.Length != 2)
            {
                splitNumbers = number.Number.Split('.', StringSplitOptions.TrimEntries);
            }

            for (int position = 0; position < splitNumbers[0].Length; position++)
            {
                digitsBeforeDecimalPoint.Add(int.Parse(new string(new char[] { splitNumbers[0][position] }))); 
            }

            for (int position = 0; position < splitNumbers[1].Length; position++)
            {
                digitsAfterDecimalPoint.Add(int.Parse(new string(new char[] { splitNumbers[1][position] })));
            }
            return new Tuple<List<int>,List<int>>(digitsBeforeDecimalPoint, digitsAfterDecimalPoint);
        }

       /// <summary>
       /// Uses a list of integers acting as digits of a number before and after the decimal point to create a string that will be used to construct a UltraPrecisionDecimal.
       /// </summary>
       /// <param name="beforeAndAfterDecimalIntArray">The tuple of the digits. First item is before the decimal point, second item is after the decimal point.</param>
       /// <returns>An UltraPrecisionDecimal based on those integer digit lists.</returns>
        public static UltraPrecisionDecimal Recompose(Tuple<List<int>, List<int>> beforeAndAfterDecimalIntArray)
        {
            string resultString = "";
            var before = beforeAndAfterDecimalIntArray.Item1;
            var after = beforeAndAfterDecimalIntArray.Item2;

            for (int position = 0; position < before.Count; position++)
            {
                resultString += before[position].ToString();
            }

            resultString += ",";

            for (int position = 0; position < after.Count; position++)
            {
                resultString += after[position].ToString();
            }

            return new UltraPrecisionDecimal(resultString);
        }

        #endregion


    }
}
