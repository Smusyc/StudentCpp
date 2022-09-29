using System;
using System.Collections.Generic;
namespace tester
{
    
    class Program
    {
        static void Main(string[] args)
        {
            int result = 0, a=1,b=0;
            result = ((2 * a + (Math.Abs(a - b) - 1)) * (Math.Abs(a - b) / 2));
            Console.WriteLine(result);
        }
    }
}
