using System;
using System.Windows.Forms;

namespace TurboJet_Engine
{
    public partial class Form_Selection : Form
    {
        int selection = 0;

        public Form_Selection()
        {
            InitializeComponent();
        }

        private void RadioButton2_CheckedChanged(object sender, EventArgs e)
        {

            RadioButton radioButton = (RadioButton)sender;

            if (radioButton.Checked == true)
            {
                selection = 2;
            }

            else
            {
                selection = 0;
            }

        }

        private void Btn_Select_Click(object sender, EventArgs e)
        {
            if (selection > 0)
            {
                Form_TwinShaft_File form_TwinShaft_File = new Form_TwinShaft_File(selection);
                form_TwinShaft_File.Show();

                Hide();
            }

            else
            {
                MessageBox.Show("Please, select a type of engine!",
                    "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

        }

        private void Form_Selection_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }

    }
}
