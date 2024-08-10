using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace TurboJet_Engine
{
    internal static class Program
    {
        private const string dllPath = @"\..\..\Logic_TS\bin\Logic_TS.dll";

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern int Start(InputData input);

        /// <summary>
        /// Main enter point of application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form_Main());
        }

       public static int TwinShaftEng(InputData inp)
        {
            int output = 0;

            output = Start(inp);

            if (output == 0)
            {
                MessageBox.Show("Error of running Logic_TS.dll", 
                    "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);

                Application.Exit();
            }

            return output;

        }

    }
}
