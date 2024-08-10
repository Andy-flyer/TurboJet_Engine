using System;
using System.Windows.Forms;

namespace TurboJet_Engine
{
    public partial class Form_Atmospheric_Cond : Form
    {
        InputData inp;

        public Form_Atmospheric_Cond(InputData input)
        {
            InitializeComponent();
            inp = input;
        }

        private void PushData()
        {
            inp.min_height = float.Parse(numericUpDown1.Text);
            inp.numb_of_height = float.Parse(numericUpDown2.Text);
            inp.max_height = float.Parse(numericUpDown3.Text);

            inp.min_speed = float.Parse(numericUpDown4.Text);
            inp.numb_of_speed = float.Parse(numericUpDown5.Text);
            inp.max_speed = float.Parse(numericUpDown6.Text);

            inp.min_temperature = float.Parse(numericUpDown7.Text);
            inp.numb_of_temperature = float.Parse(numericUpDown8.Text);
            inp.max_temperature = float.Parse(numericUpDown9.Text);
        }

        private void Btn_Set_Click(object sender, EventArgs e)
        {
            PushData();
            Hide();
        }

        private void Form_Atmospheric_Cond_FormClosed(object sender, FormClosedEventArgs e)
        {
            Hide();
        }

    }
}
