using System.Runtime.InteropServices;

namespace TurboJet_Engine
{
    [StructLayout(LayoutKind.Sequential)]
    public class InputData
    {

        // Constants
        public float k_const;                   //1. adiabatic constant for dry air
        public float t_const;                   //2. value of the temperature of standart atmosphere [K]
        public float hu_const;                  //3. value of the fuel heat capacity [kJ/kg]
        public float c_hc_air_const;            //4. specific heat capacity of the air at constant pressure [J/kg*K]
        public float kf_const;                  //5. adiabatic constant for combustion products
        public float r_const;                   //6. gas constant of dry air [J/kg*K]

        // Engine configuration
        public float sigma_confg;               //7. coefficient of air pressure recovery at the inlet of the engine
        public float p_comp_n1_confg;           //8. value of air pressire increase ratio at the LP-compressor
        public float pk_n2_confg;               //9. value of air pressire increase ratio at the HP-compressor
        public float tg_confg;                  //10. value of gas temperature before the turbine [K]
        public float eff_cmb_confg;             //11. efficiency in the combustion chamber
        public float g_bleed_confg;             //12. value of relative air flow comsuption of the engine
        public float g_cool_confg;              //13. value of relative air flow comsuption for the turbine cooling
        public float eff_mech_confg;            //14. coefficient of power consumption for the auxiliary units drive
        public float sigma_cmb_confg;           //15. coefficient of air pressure recovery at the combustion chamber
        public float eff_turb_hp_confg;         //16. adiabatic efficiency of the HP-turbine stage
        public float eff_turb_lp_confg;         //17. adiabatic efficiency of the LP-turbine stage
        public float f_jn_confg;                //18. speed coefficinet of gas outflow from the nozzle
        public float thrust_confg;              //19. value of the engine thrust [kN]
        public float cv_confg;                  //20. axial velocity in gas air duct reference section at the inlet of the LP-compressor [m/s]
        public float ck_confg;                  //21. axial velocity in gas air duct reference section at the inlet of the HP-compressor [m/s]
        public float eff_coeff_n1_confg;        //22. polytropic efficiency of the axial LP-compressor stage
        public float eff_coeff_n2_confg;        //23. polytropic efficiency of the axial HP-compressor stage


        // AirSpeed points
        public float min_height;                //1. Minimum point of the height [km]
        public float numb_of_height;            //2. Number of points of the height [km]
        public float max_height;                //3. Maximum point of the height [km]

        public float min_speed;                 //1. Minimum point of the speed
        public float numb_of_speed;             //2. Number of points of the speed
        public float max_speed;                 //3. Maximum point of the speed

        public float min_temperature;           //1. Minimum point of the temperature
        public float numb_of_temperature;       //2. Number of points of the temperature
        public float max_temperature;           //3. Maximum point of the temperature


        // File paths
        public string filePathLP;               //1. FilePath of LP-compressor characteristics
        public string filePathHP;               //2. FilePath of HP-compressor characteristics
        public string filePathResult;           //3. FilePath for results save

    }
}