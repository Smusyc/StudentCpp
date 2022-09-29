using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;

namespace TDD
{
    [TestClass]
    public class MathUtils
    {
        public static int Fibonacci(int n)
        {
            return 0;
        }
        
        [TestMethod]
        public void TestMethod1()
        {
            Assert.AreEqual(0, MathUtils.Fibonacci(0));
        }
    }
}
