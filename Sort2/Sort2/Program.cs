using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Sort2
{
    class Program
    {
        static void Main(string[] args)
        {
            bool flag = true;
            int a;
            int[] riad = new int[7];
            riad[0] = 7;
            riad[1] = 2;
            riad[2] = 28;
            riad[3] = 0;
            riad[4] = 12;
            riad[5] = 12;
            riad[6] = 74;
            while (flag)
            {
                flag = false;
                for (int i = 1; i <= 6; ++i)
                {
                    if (riad[i] < riad[i - 1])
                    {
                        flag = true;
                        a = riad[i];
                        riad[i] = riad[i - 1];
                        riad[i - 1] = a;
                    }

                }
            }
            for (int i = 0; i <= 6; ++i)
            {
                Console.WriteLine("\n" + riad[i]);
            }
        }
    }
}
