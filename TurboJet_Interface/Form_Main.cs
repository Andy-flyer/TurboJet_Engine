using System;
using System.Windows.Forms;

namespace TurboJet_Engine
{
    public partial class Form_Main : Form
    {
        string version = "";

        public Form_Main()
        {
            InitializeComponent();

            version = System.Windows.Forms.Application.ProductVersion;

            Show_Version_Info();
        }

        private void Show_Version_Info()
        {
            label2.Text += version;
        }

        private void Btn_Start_Click(object sender, EventArgs e)
        {
            Form_Selection form_Selection = new Form_Selection();
            form_Selection.Show();

            Hide();
        }

        private void Form_Main_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }

    }
}
