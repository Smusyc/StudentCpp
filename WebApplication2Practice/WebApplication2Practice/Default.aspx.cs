using System;
using System.Collections.Generic;
using System.Net;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.IO;
using MaxMind.GeoIP2;
using System.Text.RegularExpressions;
using System.Text;
using System.Web.UI.WebControls;
using MySql.Data.MySqlClient;

namespace WebApplication2Practice
{
    
    public class Seek_Methods
    {
        public static string Seek_by_Period(string a, string b, string source)
        {

            return "";
        }
        public static string Seek_by_good(string a, string source)
        {

            return "";
        }
    }

    public partial class Отчёты_по_данным : System.Web.UI.Page
    {
        

        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void Analizer_Click(object sender, EventArgs e)
        {
            string connstr = "server=localhost;user=root;database=logs;password=;";
            MySqlConnection conn = new MySqlConnection(connstr);
            conn.Open();
            string result = TextBox1.Text;
            string Otch1, Otch2, Otch3, Otch4, boofer = "";
            string commandMySQL="";
            StreamReader f = new StreamReader(result);
            string data="", time="", IP = "0", cite="",city="",country="",category="",s="";
            MySqlCommand command = new MySqlCommand(commandMySQL, conn);
            command = new MySqlCommand("TRUNCATE TABLE actions", conn);
            command.ExecuteNonQuery();

            int d1 =-1, y1=-1, m1=-1, d2=-1, y2=-1, m2=-1,h1=-1,h2=-1;
            Regex r = new Regex(@"\d{4}-\d{2}-\d{2}", RegexOptions.None, TimeSpan.FromMilliseconds(150));
            int l = 0;
            Match m = r.Match(s);
            WebRequest request;
            WebResponse response;
            while (!f.EndOfStream)
            {
                s = f.ReadLine();

                r = new Regex(@"\d{4}-\d{2}-\d{2}", RegexOptions.None, TimeSpan.FromMilliseconds(150));
                m = r.Match(s);
                if (m.Success)
                    data = m.Value;

                r = new Regex(@"\d{2}:\d{2}:\d{2}", RegexOptions.None, TimeSpan.FromMilliseconds(150));
                m = r.Match(s);
                if (m.Success)
                    time = m.Value;

                if (d1 < 0 && y1 < 0 && m1 < 0 && h1 < 0)
                {
                    r = new Regex(@"\d{4}", RegexOptions.None, TimeSpan.FromMilliseconds(150));
                    m = r.Match(data);
                    y1 = int.Parse(m.Value);

                    r = new Regex(@"-\d{2}-", RegexOptions.None, TimeSpan.FromMilliseconds(150));
                    m = r.Match(data);
                    r = new Regex("-");
                    m1 = int.Parse(r.Replace(m.Value, string.Empty));

                    r = new Regex(@"-\d{2}$", RegexOptions.None, TimeSpan.FromMilliseconds(150));
                    m = r.Match(data);
                    r = new Regex("-");
                    d1 = int.Parse(r.Replace(m.Value, string.Empty));

                    r = new Regex(@"\d{2}:", RegexOptions.None, TimeSpan.FromMilliseconds(150));
                    m = r.Match(time);
                    r = new Regex(":");
                    h1 = int.Parse(r.Replace(m.Value, string.Empty));

                    r = new Regex(@":\d{2}:", RegexOptions.None, TimeSpan.FromMilliseconds(150));
                    m = r.Match(time);
                    r = new Regex(":");
                    if (int.Parse(r.Replace(m.Value, string.Empty)) > 30)
                        h1++;
                }

                r = new Regex(@"(https?:\/\/)?([\w-]{1,32}\.[\w-]{1,32})[^\s@]*$", RegexOptions.None, TimeSpan.FromMilliseconds(150));
                m = r.Match(s);
                if (m.Success)
                    cite = m.Value;

                r = new Regex(@"\d*\.\d*\.\d*\.\d*", RegexOptions.None, TimeSpan.FromMilliseconds(150));
                m = r.Match(s);
                if (m.Success)
                    IP = m.Value;

                using (var client = new WebServiceClient(42, "license_key"))
                {
                    // Do the lookup
                    request = WebRequest.Create("http://api.wipmania.com/"+IP);
                    response = request.GetResponse();
                    string line = "";
                    using (Stream stream = response.GetResponseStream())
                    {
                        using (StreamReader read = new StreamReader(stream))
                        {
                            
                            while ((line = read.ReadLine()) != null)
                            {
                                country += line;
                            }
                        }
                    }
                }
                r =new Regex(@"https://all_to_the_bottom.com/");
                category = r.Replace(cite,string.Empty);
                r = new Regex(@"\/(\w*)\/$");
                m = r.Match(cite);
                if (m.Value != "/all_to_the_bottom.com/")
                    category = m.Value;
                else
                    category = "";
                // что-нибудь делаем с прочитанной строкой s
                //commandMySQL = "INSERT INTO actions (DataTime, IP, Country, Cite, Time) VALUES (" + data + " " + time + ", " + IP + ", " + country + ", " + cite + ", " + time + ")";

                command = new MySqlCommand("INSERT INTO actions (DataTime, IP, Country, Cite, Time) VALUES(?DataTime, ?IP, ?Country, ?Cite, ?Time)",conn);
                command.Parameters.AddWithValue("?DataTime", (data+" "+time));
                command.Parameters.AddWithValue("?IP", (IP));
                command.Parameters.AddWithValue("?Country", (country));
                country = "";
                command.Parameters.AddWithValue("?Cite", (cite));
                command.Parameters.AddWithValue("?Time", (time));

                command.ExecuteNonQuery();

                //command = new MySqlCommand(commandMySQL, conn);
                //cmd.ExecuteNonQuery();
                l++;
            }

            if (d2 < 0 && y2 < 0 && m2 < 0 && h2 < 0)
            {
                r = new Regex(@"\d{4}", RegexOptions.None, TimeSpan.FromMilliseconds(150));
                m = r.Match(data);
                y2 = int.Parse(m.Value);

                r = new Regex(@"-\d{2}-", RegexOptions.None, TimeSpan.FromMilliseconds(150));
                m = r.Match(data);
                r = new Regex("-");
                m2 = int.Parse(r.Replace(m.Value, string.Empty));

                r = new Regex(@"-\d{2}$", RegexOptions.None, TimeSpan.FromMilliseconds(150));
                m = r.Match(data);
                r = new Regex("-");
                d2 = int.Parse(r.Replace(m.Value, string.Empty));

                r = new Regex(@"\d{2}:", RegexOptions.None, TimeSpan.FromMilliseconds(150));
                m = r.Match(time);
                r = new Regex(":");
                h2 = int.Parse(r.Replace(m.Value, string.Empty));

                r = new Regex(@":\d{2}:", RegexOptions.None, TimeSpan.FromMilliseconds(150));
                m = r.Match(time);
                r = new Regex(":");
                if (int.Parse(r.Replace(m.Value, string.Empty)) > 30)
                    h2++;
            }

            int hours1,hours2 = ((y2 - 1) * 365 * 24)+((m2-1)*30*24)+((d2-1)*24)+h2;
            double result_otch4;
            hours1 = ((y1 - 1) * 365 * 24) + ((m1 - 1) * 30 * 24) + ((d1 - 1) * 24) + h1;
            result_otch4 = hours2 - hours1;
            result_otch4 = l / result_otch4;
            Otch4 = "\n4.Средняя нагрузка запросов на сайт за астрономический час: "+ result_otch4.ToString()+" опер/час";

            IDictionary<string, int> countries_act = new Dictionary<string, int>();
            command = new MySqlCommand("SELECT Country FROM actions ", conn);
            MySqlDataReader reader = command.ExecuteReader();
            int temp = 0;
            while (reader.Read())
            {
                if (!countries_act.ContainsKey(reader[0].ToString()))
                {
                    countries_act.Add(reader[0].ToString(), 1);
                }
                else
                {
                    countries_act[reader[0].ToString()] = countries_act[reader[0].ToString()]+1;

                }
            }
            var kvMax = countries_act.First();
            foreach (var kv in countries_act)
            {
                if (kv.Value > kvMax.Value) kvMax = kv;
            }
            Otch2 = "\n2.Пользователи из [";
            foreach (var kv in countries_act)
            {
                if (kv.Value == kvMax.Value) Otch2 += (kv.Key+", ");
            }
            Otch2 += "] совершают больше всего действий на сайте" + "\n";//про действия на сайте


            commandMySQL = "SELECT Cite FROM actions WHERE "+"(DataTime<"+TextBox3.Text+")";
            r = new Regex(@"\/success_pay_(\d*)\/$", RegexOptions.None, TimeSpan.FromMilliseconds(150));
            Regex k = new Regex(@"cart_id\=\d*", RegexOptions.None, TimeSpan.FromMilliseconds(150));
            List<string> cart_id_Agree = new List<string>();
            command = new MySqlCommand("SELECT Cite FROM actions ", conn);
            while (reader.Read())
            {
                r = new Regex(@"\/success_pay_(\d*)\/$", RegexOptions.None, TimeSpan.FromMilliseconds(150));
                m = r.Match(reader[0].ToString());
                if (m.Success)
                {
                    r = new Regex(@"\/success_pay_", RegexOptions.None, TimeSpan.FromMilliseconds(150));
                    boofer = r.Replace(m.Value, string.Empty);
                    r = new Regex(@"\/", RegexOptions.None, TimeSpan.FromMilliseconds(150));
                    cart_id_Agree.Add(r.Replace(boofer, string.Empty));
                }
            }
            temp = 0;
            command = new MySqlCommand("SELECT Cite FROM actions ", conn);
            reader.Close();
            reader = command.ExecuteReader();
            while (reader.Read())
            {
                m = k.Match(reader[0].ToString());
                if (m.Success)
                {
                    r = new Regex(@"cart_id=", RegexOptions.None, TimeSpan.FromMilliseconds(150));
                    boofer = r.Replace(m.Value, string.Empty);
                    if (!cart_id_Agree.Contains(boofer)) {
                        temp++;//количество неоплаченных карзин
                    }
                    else
                    {
                        cart_id_Agree.Add(boofer);
                    }
                }
            }
            Otch1 = "\n1.Количество неоплаченных карзин на момент до "+TextBox3.Text +": "+ temp.ToString()+"\n";
            Report.Text = "\n"+Otch1 + "\n" + Otch2 + "\n" + Otch4;
            conn.Close();
            f.Close();
        }

        protected void Button1_Click(object sender, EventArgs e)
        {

        }
    }
}