using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Threading;

namespace Moving
{
    class Ball
    {
        
        int x, y;
        int n, m;
        int dx, dy;
        int i, j;
        bool running;
     

        public bool Running
        {
            get { return running; }
            set { running = value; }
        }
        Color col;
        Brush brush;
        Thread th;

        public Thread Th
        {
            get { return th; }
            set { th = value; }
        }
        Form1 fr;
        Random rand = new Random();
        public Ball(Form1 fr)
        {
            this.fr = fr;
            x = rand.Next(1, fr.Width);
            y = rand.Next(1, fr.Height);
            Thread.Sleep(5);
            n = rand.Next(30,50);
            m = rand.Next(30, 50);
            dx = rand.Next(-5, 5);
            dy = rand.Next(-5,5);
            col = Color.FromArgb(255, rand.Next(255), rand.Next(255), rand.Next(255));
            brush = new SolidBrush(col);
            running = false;
            
            i = 0;
            j = 0;
            th = new Thread(new ThreadStart(Run));
            //th.Start();
            
        }

        public void Paint(Graphics g)
        {
            g.FillEllipse(brush, x, y, m, n);
       
        }

        public void Run()
        {
            for (; ; )
            {
                Thread.Sleep(20);
                if (!running) continue;
                Move();
                fr.Invalidate();
            }
        }

        public void Move()
        {
            if (x+m > fr.Width)
            {
                dx = -Math.Abs(dx);
                
            }
            if (y+n+2 > fr.Height)
            {
                dy = -Math.Abs(dy);
            }
            if (x < 0)
            {
                dx = Math.Abs(dx);
            }
            if (y < 0)
            {
                dy = Math.Abs(dy);
            }
            x += dx;
            y += dy;
        }

        public void Sss()
        {
            if(!th.IsAlive)
                th.Start();
                
            running = true;
            
        }

        public void Stop()
        {
            running = false;
        }

  
    }
}
