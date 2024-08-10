using System;
using System.Diagnostics;
using System.Threading;
using System.Windows.Forms;

namespace TurboJet_Engine
{
    public partial class Form_TwinShaft_Config : Form
    {
        InputData inp;
        int selection = 0;
        int result = 0;

        public Form_TwinShaft_Config(InputData input, int sel)
        {

            InitializeComponent();

            inp = input;
            selection = sel;

            if (Properties.Settings.Default.demo == true)
            {
                numericUpDown1.Value = (decimal)(0.99);
                numericUpDown2.Value = (decimal)(3.873);
                numericUpDown3.Value = (decimal)(3.873);
                numericUpDown4.Value = 1370;
                numericUpDown5.Value = (decimal)(0.985);
                numericUpDown6.Value = (decimal)(0.015);
                numericUpDown7.Value = (decimal)(0.04);
                numericUpDown8.Value = (decimal)(0.995);
                numericUpDown9.Value = (decimal)(0.955);
                numericUpDown10.Value = (decimal)(0.91);
                numericUpDown11.Value = (decimal)(0.92);
                numericUpDown12.Value = (decimal)(0.98);
                numericUpDown13.Value = 100;
                numericUpDown14.Value = 160;
                numericUpDown15.Value = 100;
                numericUpDown16.Value = (decimal)(0.9);
                numericUpDown17.Value = (decimal)(0.9);
            }

        }

        private void Thread1()
        {

            if (selection == 2)
            {
                PushData();
                result = Program.TwinShaftEng(inp);
            }

            groupBox1.Invoke((MethodInvoker)(() => groupBox1.Enabled = true));

            if (result == 1)
                label39.Invoke((MethodInvoker)(() => label39.Text = "Completed!"));

            else if (result == 0)
                label39.Invoke((MethodInvoker)(() => label39.Text = "Error!"));

            Process.Start(inp.filePathResult);

        }

        private void Thread2()
        {

            while (result == 0)
            {
                progressBar1.Invoke((MethodInvoker)(() => progressBar1.Value++));

                if (progressBar1.Value == progressBar1.Maximum)
                {
                    progressBar1.Invoke((MethodInvoker)(() => progressBar1.Value = progressBar1.Minimum));
                }

                Thread.Sleep(30);
            }

            progressBar1.Invoke((MethodInvoker)(() => progressBar1.Value = progressBar1.Minimum));

            progressBar1.Invoke((MethodInvoker)(() => progressBar1.Visible = false));
       
        }

        private void PushData()
        {
            inp.sigma_confg = float.Parse(numericUpDown1.Text);
            inp.p_comp_n1_confg = float.Parse(numericUpDown2.Text);
            inp.pk_n2_confg = float.Parse(numericUpDown3.Text);
            inp.tg_confg = float.Parse(numericUpDown4.Text);
            inp.eff_cmb_confg = float.Parse(numericUpDown5.Text);
            inp.g_bleed_confg = float.Parse(numericUpDown6.Text);
            inp.g_cool_confg = float.Parse(numericUpDown7.Text);
            inp.eff_mech_confg = float.Parse(numericUpDown8.Text);
            inp.sigma_cmb_confg = float.Parse(numericUpDown9.Text);
            inp.eff_turb_hp_confg = float.Parse(numericUpDown10.Text);
            inp.eff_turb_lp_confg = float.Parse(numericUpDown11.Text);
            inp.f_jn_confg = float.Parse(numericUpDown12.Text);
            inp.thrust_confg = float.Parse(numericUpDown13.Text);
            inp.cv_confg = float.Parse(numericUpDown14.Text);
            inp.ck_confg = float.Parse(numericUpDown15.Text);
            inp.eff_coeff_n1_confg = float.Parse(numericUpDown16.Text);
            inp.eff_coeff_n2_confg = float.Parse(numericUpDown17.Text);
        }

        private void PathToSafe()
        {
            SaveFileDialog sfd = new SaveFileDialog();

            sfd.FileName = "result.txt";
            sfd.DefaultExt = ".txt";
            sfd.Filter = "Text File. Format of File:  .txt|*.txt";

            if (sfd.ShowDialog() == DialogResult.OK)
            {
                inp.filePathResult = sfd.FileName;
            }
        }

        private void Btn_atmos_cond_Click(object sender, EventArgs e)
        {

            Form_Atmospheric_Cond form_Atmospheric_Cond = new Form_Atmospheric_Cond(inp);
            form_Atmospheric_Cond.ShowDialog();

            btn_const.Enabled = true;

        }

        private void Btn_const_Click(object sender, EventArgs e)
        {

            Form_Const form_Const = new Form_Const(inp);
            form_Const.ShowDialog();

            btn_Calc.Enabled = true;

        }

        private void Btn_Calc_Click(object sender, EventArgs e)
        {

            PathToSafe();

            if (inp.filePathResult != null)
            {
                groupBox1.Enabled = false;

                label39.Text = "Calculating...";
                label39.Visible = true;
                progressBar1.Visible = true;

                Thread thread1 = new Thread(new ThreadStart(Thread1));
                thread1.Start();

                Thread thread2 = new Thread(new ThreadStart(Thread2));
                thread2.Start();

                result = 0;
            }

            else
            {
                MessageBox.Show("Please, select result file for save!",
                    "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

        }

        private void Form_TwinShaft_Config_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }

    }
}
