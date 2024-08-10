using System;
using System.Globalization;
using System.Windows.Forms;

namespace TurboJet_Engine
{
    public partial class Form_Const : Form
    {
        InputData inp;

        public Form_Const(InputData input)
        {
            InitializeComponent();
            inp = input;
        }

        private void PushData()
        {
            inp.k_const = float.Parse(textBox1.Text, CultureInfo.InvariantCulture);
            inp.t_const = float.Parse(textBox2.Text, CultureInfo.InvariantCulture);
            inp.hu_const = float.Parse(textBox3.Text, CultureInfo.InvariantCulture);
            inp.c_hc_air_const = float.Parse(textBox4.Text, CultureInfo.InvariantCulture);
            inp.kf_const = float.Parse(textBox5.Text, CultureInfo.InvariantCulture);
            inp.r_const = float.Parse(textBox6.Text, CultureInfo.InvariantCulture);
        }

        private void Btn_Set_Click(object sender, EventArgs e)
        {
            PushData();
            Hide();
        }

        private void Form_Const_FormClosed(object sender, FormClosedEventArgs e)
        {
            Hide();
        }

    }
}
