using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ipr1
{
    public partial class Form1 : Form
    {
        int change; 
        List<Ifigure> figursList = new List<Ifigure>();

        public Form1()
        {
            InitializeComponent();
            
            line lin = new line(pictureBox1);
            figursList.Add(lin);
            brokenLine brline = new brokenLine(pictureBox1);
            figursList.Add(brline);
            rectangle rect = new rectangle(pictureBox1);
            figursList.Add(rect);
            elias el= new elias(pictureBox1);
            figursList.Add(el);
            poligons pol = new poligons(pictureBox1);
            figursList.Add(pol);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            figursList[change].draw();
        }

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
           


        }


        private void button2_Click(object sender, EventArgs e)
        {
            figursList[change].ChangeColor();
            figursList[change].draw();
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            change = comboBox1.SelectedIndex;
        }
    }
}
 