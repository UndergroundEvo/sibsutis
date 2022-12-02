using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;

namespace Moving
{
    public partial class Form1 : Form
    {
        Ball[] ball;
        int n;
       

        public Form1()
        {
            
            InitializeComponent();
            n = 100;
            ball = new Ball[n];
            for (int i = 0; i < n; i++)
            {
                ball[i] = new Ball(this);
            }

           

        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            
            for (int i = 0; i < ball.Length; i++)
            {
                
                ball[i].Paint(g);
            }
            
           
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            for (int i = 0; i < n; i++)
            {
                ball[i].Th.Abort();
            }
            //ball.Th.Abort();
            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            
            for (int i = 0; i < n; i++)
            {
                ball[i].Sss();  
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < n; i++)
            {
                ball[i].Stop();
            }
        }

   



    }
}
