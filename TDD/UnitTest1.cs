using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;



namespace TDD2
{
    [TestClass]
    public class MathUtils
    {
        public static int Fibonacci(int n)
        {
            if (n == 0)
                return 0;
            else
                return 1;
        }

        [TestMethod]
        public void TestFirstFibonacciNumber()
        {
            Assert.AreEqual(0, MathUtils.Fibonacci(0));
        }
        
        
        
    }
}
