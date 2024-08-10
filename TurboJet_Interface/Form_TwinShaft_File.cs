using System;
using System.IO;
using System.Windows.Forms;

namespace TurboJet_Engine
{
    public partial class Form_TwinShaft_File : Form
    {
        InputData input = new InputData();
        string path1, path2 = "";
        int selection = 0;

        public Form_TwinShaft_File(int sel)
        {
            InitializeComponent();

            selection = sel;
        }

        private void Btn_1_sel_Click(object sender, EventArgs e)
        {

            OpenFileDialog ofd_1 = new OpenFileDialog();

            DirectoryInfo directoryInfo1 = new DirectoryInfo(Directory.GetCurrentDirectory()).Parent.Parent;
            path1 = directoryInfo1.FullName.ToString() + "\\Logic_TS\\compressor_data";

            ofd_1.InitialDirectory = path1;
            ofd_1.FileName = "low_press.txt";
            ofd_1.DefaultExt = ".txt";
            ofd_1.Filter = "Text File. Format of File:  .txt|*.txt";

             if (ofd_1.ShowDialog() == DialogResult.OK)
             {
                 input.filePathLP = ofd_1.FileName;
             }

            if (input.filePathLP == null)
            {
                MessageBox.Show("LP-compressor data file was not selected.",
                    "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            textBox1.Text = input.filePathLP;

        }

        private void Btn_2_sel_Click(object sender, EventArgs e)
        {

            OpenFileDialog ofd_2 = new OpenFileDialog();

            DirectoryInfo directoryInfo2 = new DirectoryInfo(Directory.GetCurrentDirectory()).Parent.Parent;
            path2 = directoryInfo2.FullName.ToString() + "\\Logic_TS\\compressor_data";

            ofd_2.InitialDirectory = path2;
            ofd_2.FileName = "high_press.txt";
            ofd_2.DefaultExt = ".txt";
            ofd_2.Filter = "Text File. Format of File:  .txt|*.txt";

            if (ofd_2.ShowDialog() == DialogResult.OK)
            {
                input.filePathHP = ofd_2.FileName;
            }

            if (input.filePathHP == null)
            {
                MessageBox.Show("HP-compressor data file was not selected.",
                    "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            textBox2.Text = input.filePathHP;

        }

        private void Btn_Continue_Click(object sender, EventArgs e)
        {
            if ((input.filePathLP != null) && (input.filePathHP != null))
            {
                Form_TwinShaft_Config form_TwinShaft_Config = new Form_TwinShaft_Config(input, selection);
                form_TwinShaft_Config.Show();

                Hide();
            }

            else 
            {
                    MessageBox.Show("LP-compressor or HP-compressor data file was not selected.",
                        "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

        }

        private void Btn_Exit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void Form_TwinShaft_File_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }

    }
}
