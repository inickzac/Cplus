using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing;

namespace ipr1
{
    
    public  class line : Ifigure
    {
        PictureBox pictureBox;
        Color tipeColor=Color.Black;

        public  line(PictureBox picture)
        {
            pictureBox = picture;
        }

        public  void draw()
        {
            Bitmap bmp = new Bitmap(pictureBox.Width, pictureBox.Height);
            Graphics graph = Graphics.FromImage(bmp);
            Pen pen = new Pen(tipeColor);
            graph.DrawLine(pen, 10, 50, 150, 200);
            pictureBox.Image = bmp;
        }

      public  void ChangeColor()
        {
            Random rnb = new Random();
            tipeColor= Color.FromArgb(rnb.Next(256), rnb.Next(256), rnb.Next(256));
        }

    }

    public class brokenLine:Ifigure
    {
        PictureBox pictureBox;
        Color tipeColor = Color.Black;

        public brokenLine(PictureBox picture)
        {
            pictureBox = picture;
        }

        public void ChangeColor()
        {
            Random rnb = new Random();
            tipeColor = Color.FromArgb(rnb.Next(256), rnb.Next(256), rnb.Next(256));
        }

        public void draw()
        {
            Bitmap bmp = new Bitmap(pictureBox.Width, pictureBox.Height);
            Graphics graph = Graphics.FromImage(bmp);
            Pen pen = new Pen(tipeColor);
            graph.DrawLine(pen, 10, 50, 100, 110);
            graph.DrawLine(pen, 100, 110, 300, 400);
            pictureBox.Image = bmp;
        }
    }

    public class rectangle:Ifigure
    {
        PictureBox pictureBox;
        Color tipeColor = Color.Black;

        public rectangle(PictureBox picture)
        {
            pictureBox = picture;
        }

        public void draw()
        {
            Bitmap bmp = new Bitmap(pictureBox.Width, pictureBox.Height);
            Graphics graph = Graphics.FromImage(bmp);
            Pen pen = new Pen(tipeColor);
            Rectangle rect = new Rectangle(1, 2, 175, 205);
            graph.DrawRectangle(pen, rect);
            pictureBox.Image = bmp;
        }

        public void ChangeColor()
        {
            Random rnb = new Random();
            tipeColor = Color.FromArgb(rnb.Next(256), rnb.Next(256), rnb.Next(256));
        }
    }

    public class elias : Ifigure
    {
        PictureBox pictureBox;
        Color tipeColor = Color.Black;

        public elias(PictureBox picture)
        {
            pictureBox = picture;
        }

        public void draw()
        {
            Bitmap bmp = new Bitmap(pictureBox.Width, pictureBox.Height);
            Graphics graph = Graphics.FromImage(bmp);
            Pen pen = new Pen(tipeColor);
            Rectangle rect = new Rectangle(1, 2, 175, 205);
            graph.DrawEllipse(pen,rect);
            pictureBox.Image = bmp;
        }


        public void ChangeColor()
        {
            Random rnb = new Random();
            tipeColor = Color.FromArgb(rnb.Next(256), rnb.Next(256), rnb.Next(256));
        }
    }

    public class poligons : Ifigure
    {
        PictureBox pictureBox;
        Color tipeColor = Color.Black;

        public poligons(PictureBox picture)
        {
            pictureBox = picture;
        }

        public void draw()
        {
            Bitmap bmp = new Bitmap(pictureBox.Width, pictureBox.Height);
            Graphics graph = Graphics.FromImage(bmp);
            Pen pen = new Pen(tipeColor);
            System.Drawing.Point[] p = new System.Drawing.Point[6];
            p[0].X = 0;
            p[0].Y = 0;
            p[1].X = 53;
            p[1].Y = 111;
            p[2].X = 114;
            p[2].Y = 86;
            p[3].X = 34;
            p[3].Y = 34;
            p[4].X = 165;
            p[4].Y = 7;
            graph.DrawPolygon(pen, p);
            pictureBox.Image = bmp;
        }


        public void ChangeColor()
        {
            Random rnb = new Random();
            tipeColor = Color.FromArgb(rnb.Next(256), rnb.Next(256), rnb.Next(256));
        }
    }

    public interface Ifigure
    {
        void draw();

        void ChangeColor();
      
    }

  


}
