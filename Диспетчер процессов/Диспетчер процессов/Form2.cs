using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Диспетчер_процессов
{
    public partial class Form2 : Form
    {
        public Form1 outer;
        public Form2(Form1 f)
        {
            InitializeComponent();
            outer = f;
        }
    
        private void ID_TextChanged(object sender, EventArgs e)
        {

        }

        private void CP_TextChanged(object sender, EventArgs e)
        {

        }

        private void Memory_TextChanged(object sender, EventArgs e)
        {

        }

        private void System_Time_TextChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            Process_new adding = new Process_new(ID.Text, CP.Text, Memory.Text, System_Time_H.Text, System_Time_M.Text, System_Time_S.Text);
            if (!outer.proc.Contains(adding))
                outer.proc.Add(adding);
            outer.SJF();
            this.Close();
        }
    }



}
