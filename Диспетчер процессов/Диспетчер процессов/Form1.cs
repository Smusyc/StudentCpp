using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;



namespace Диспетчер_процессов
{
    public partial class Form1 : Form
    {
        public List<Process_new> proc = new List<Process_new>();
        Boolean flag=false;
        public Form1()
        {
            InitializeComponent();
        }

        public void SJF()
        {
            List_processes.Items.Clear();
            if (flag)
            {
                IEnumerable<Process_new> query = from elem in proc
                                                 orderby elem.CP
                                                 select elem;
                foreach (Process_new elem_add in query)
                    List_processes.Items.Add($"{elem_add.ID} || {elem_add.date1} || {elem_add.CP} || {elem_add.time_work} || ");
            }
            else
            {
                IEnumerable<Process_new> query = from elem in proc
                                                 orderby ((elem.CP)+ elem.date1.Second)
                                                 select elem;
                foreach (Process_new elem_add in query)
                    List_processes.Items.Add($"{elem_add.ID} || {elem_add.date1} || {elem_add.CP} || {elem_add.time_work} || ");
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            flag = false;
            SJF();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            Form2 newForm = new Form2(this);
            newForm.Show();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            flag = true;
            SJF();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            List_processes.Items.Remove(List_processes.SelectedItem);
        }

        private void List_processes_MouseClick(object sender, MouseEventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            proc.Remove(proc.Find(x=>x.ID.Contains($"{(new Regex(@"^(\w*)|")).Match(List_processes.SelectedItem.ToString())}")));
            Form2 newForm = new Form2(this);
            newForm.Show();
        }
    }
    public class Process_new
    {
        public string ID;
        public DateTime date1;
        public int CP;
        public int time_work;
        public Process_new(string a, string b, string c, string d, string i, string f)
        {
            ID = a;
            date1 = new DateTime(2015, 7, 20, (int.Parse(d)), (int.Parse(i)), (int.Parse(f)));
            CP = int.Parse(b);
            time_work = int.Parse(c);
        }
    }
   
    

    
}
