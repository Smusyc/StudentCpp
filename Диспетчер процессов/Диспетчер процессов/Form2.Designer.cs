namespace Диспетчер_процессов
{
    partial class Form2
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.ID = new System.Windows.Forms.TextBox();
            this.CP = new System.Windows.Forms.TextBox();
            this.Memory = new System.Windows.Forms.TextBox();
            this.System_Time_H = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.System_Time_M = new System.Windows.Forms.TextBox();
            this.System_Time_S = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 24);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(90, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Идентификатор:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 52);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(86, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "Выделение ЦП:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(13, 81);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(107, 13);
            this.label3.TabIndex = 2;
            this.label3.Text = "Выделение памяти:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 112);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(155, 13);
            this.label4.TabIndex = 3;
            this.label4.Text = "Время появления в системе:";
            // 
            // ID
            // 
            this.ID.Location = new System.Drawing.Point(173, 21);
            this.ID.Name = "ID";
            this.ID.Size = new System.Drawing.Size(100, 20);
            this.ID.TabIndex = 12;
            this.ID.TextChanged += new System.EventHandler(this.ID_TextChanged);
            // 
            // CP
            // 
            this.CP.Location = new System.Drawing.Point(173, 49);
            this.CP.Name = "CP";
            this.CP.Size = new System.Drawing.Size(100, 20);
            this.CP.TabIndex = 11;
            this.CP.TextChanged += new System.EventHandler(this.CP_TextChanged);
            // 
            // Memory
            // 
            this.Memory.Location = new System.Drawing.Point(173, 78);
            this.Memory.Name = "Memory";
            this.Memory.Size = new System.Drawing.Size(100, 20);
            this.Memory.TabIndex = 10;
            this.Memory.TextChanged += new System.EventHandler(this.Memory_TextChanged);
            // 
            // System_Time_H
            // 
            this.System_Time_H.Location = new System.Drawing.Point(173, 109);
            this.System_Time_H.Name = "System_Time_H";
            this.System_Time_H.Size = new System.Drawing.Size(30, 20);
            this.System_Time_H.TabIndex = 9;
            this.System_Time_H.TextChanged += new System.EventHandler(this.System_Time_TextChanged);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(299, 61);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 0;
            this.button1.Text = "Создать";
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // System_Time_M
            // 
            this.System_Time_M.Location = new System.Drawing.Point(217, 109);
            this.System_Time_M.Name = "System_Time_M";
            this.System_Time_M.Size = new System.Drawing.Size(30, 20);
            this.System_Time_M.TabIndex = 13;
            // 
            // System_Time_S
            // 
            this.System_Time_S.Location = new System.Drawing.Point(263, 109);
            this.System_Time_S.Name = "System_Time_S";
            this.System_Time_S.Size = new System.Drawing.Size(30, 20);
            this.System_Time_S.TabIndex = 14;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label5.Location = new System.Drawing.Point(204, 110);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(12, 16);
            this.label5.TabIndex = 15;
            this.label5.Text = ":";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label6.Location = new System.Drawing.Point(247, 107);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(14, 20);
            this.label6.TabIndex = 16;
            this.label6.Text = ":";
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(399, 152);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.System_Time_S);
            this.Controls.Add(this.System_Time_M);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.System_Time_H);
            this.Controls.Add(this.Memory);
            this.Controls.Add(this.CP);
            this.Controls.Add(this.ID);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "Form2";
            this.Text = "Form2";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox ID;
        private System.Windows.Forms.TextBox CP;
        private System.Windows.Forms.TextBox Memory;
        private System.Windows.Forms.TextBox System_Time_H;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox System_Time_M;
        private System.Windows.Forms.TextBox System_Time_S;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
    }
}