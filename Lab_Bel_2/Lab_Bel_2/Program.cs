using System;
using System.Collections.Generic;
using System.Linq;
using CsvHelper;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Net;
using System.Text.RegularExpressions;
using System.IO;

namespace Lab_Bel_2
{

    class Program
    {
        public static void Handling(Uri UriPage, uint level_recurs, int current_level, StreamWriter writeInCsv)
        {
            if (level_recurs >= 0)
            {
                string name = "";
                current_level++;
                HttpWebRequest req = (HttpWebRequest)WebRequest.Create(UriPage);
                req.UserAgent = "Mozilla/5.0 (Windows NT 5.1; rv:35.0) Gecko/20100101 Firefox/35.0";
                HttpWebResponse resp = (HttpWebResponse)req.GetResponse();
                //resp.Headers["User-Agent"] = "Mozilla/5.0";
                Stream istrm = resp.GetResponseStream();
                int text;
                string text_result = "";
                string inp_text = "";
                for (int l = 1; ; l++)
                {
                    text = istrm.ReadByte();
                    if (text == -1)
                        break;
                    text_result += (char)text;
                }


                Uri unit;
                inp_text = "";
                for (int j = Regex.Match(text_result, "<a href=\"").Index + 8; j < Regex.Match(text_result, ">").Index; j++)
                {
                    inp_text += text_result[j];
                }
                if (inp_text != "")
                {
                    level_recurs--;
                    unit = new Uri(inp_text);
                    Handling(unit, level_recurs, current_level, writeInCsv);//здесь происходит рекурсия

                }




                string new_result = "";
                new_result += " [Уровень ";
                new_result += current_level.ToString();
                new_result += "] ";
                for (int k = 0; k < current_level; k++)
                    new_result += "|-";
                inp_text = "";
                name = "";
                for (int j = Regex.Match(text_result, "<title>").Index + 7; j < Regex.Match(text_result, "</title>").Index; j++)
                {
                    name += text_result[j];
                }
                for (int j = Regex.Match(text_result, "https://").Index + 7; j < Regex.Match(text_result, ".jpg").Index; j++)
                {
                    inp_text += text_result[j];
                }
                for (int j = Regex.Match(text_result, "https://").Index + 7; j < Regex.Match(text_result, ".png").Index; j++)
                {
                    inp_text += text_result[j];
                }
                for (int j = Regex.Match(text_result, "https://").Index + 7; j < Regex.Match(text_result, ".svg").Index; j++)
                {
                    inp_text += text_result[j];
                }
                for (int j = Regex.Match(text_result, "https://").Index + 7; j < Regex.Match(text_result, ".jpg").Index; j++)
                {
                    inp_text += text_result[j];
                }
                Regex regex = new Regex(@"https://(\w*).jpg");
                MatchCollection matches = regex.Matches(text_result);
                if (matches.Count > 0)
                {
                    foreach (Match match in matches)
                    {
                        inp_text += match;
                        inp_text += "; ";
                    }
                }
                regex = new Regex(@"https://(\w*).png");
                matches = regex.Matches(text_result);
                if (matches.Count > 0)
                {
                    foreach (Match match in matches)
                    {
                        inp_text += match;
                        inp_text += "; ";
                    }
                }
                regex = new Regex(@"https://(\w*).svg");
                matches = regex.Matches(text_result);
                if (matches.Count > 0)
                {
                    foreach (Match match in matches)
                    {
                        inp_text += match;
                        inp_text += "; ";
                    }
                }
                regex = new Regex(@"https://(\w*).gif");
                matches = regex.Matches(text_result);
                if (matches.Count > 0)
                {
                    foreach (Match match in matches)
                    {
                        inp_text += match;
                        inp_text += "; ";
                    }
                }

                writeInCsv.WriteLine(new_result + "[ Вкладка: " + name + "] Ссылки: " + inp_text);
                resp.Close();
            }
        }
        public class Web_Analize
        {
            public delegate void Seeking_Properties(Uri UriPage, uint level_recurs, int current_level, StreamWriter writeInCsv);//здесь нужно ещё ввести ссылку на CSV файл
            public event Seeking_Properties Seeking;
            public void Start(Uri UriPage, uint level_recurs, int current_level, StreamWriter writeInCsv)
            {
                Seeking(UriPage, level_recurs, current_level, writeInCsv);
            }

        }
        static void Main(string[] args)
        {
            Web_Analize machine = new Web_Analize();
            machine.Seeking += Handling;
            Console.WriteLine("ВВедите ссылку, которую вы хотите проверить на изображения\n");
            string base_ref;
            base_ref = Console.ReadLine();
            Console.WriteLine("\nВВедите максимальный уровень вложенности\n");
            uint level_recurs = new int();
            level_recurs = uint.Parse(Console.ReadLine());
            FileStream fs1 = new FileStream("list.csv", FileMode.Create);
            StreamWriter writeInCsv = new StreamWriter(fs1, Encoding.Unicode);
            machine.Start(new Uri(base_ref), level_recurs, -1, writeInCsv);
            writeInCsv.Close();
            fs1.Close();
        }
    }
}

