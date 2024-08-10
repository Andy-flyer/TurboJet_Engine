#pragma once

class InputData{
public:

	// Constants
	float k_const;					//1. adiabatic constant for dry air
	float t_const;					//2. value of the temperature of standart atmosphere [K]
	float hu_const;					//3. value of the fuel heat capacity [kJ/kg]
	float c_hc_air_const;			//4. specific heat capacity of the air at constant pressure [J/kg*K]
	float kf_const;					//5. adiabatic constant for combustion products
	float r_const;					//6. gas constant of dry air [J/kg*K]
	
	// Engine configuration
	float sigma_confg;				//7. coefficient of air pressure recovery at the inlet of the engine
	float p_comp_n1_confg;			//8. value of air pressire increase ratio at the LP-compressor
	float p_comp_n2_confg;			//9. value of air pressire increase ratio at the HP-compressor
	float tg_confg;					//10. value of gas temperature before the turbine [K]
	float eff_cmb_confg;			//11. efficiency in the combustion chamber
	float g_bleed_confg;			//12. value of relative air flow comsuption of the engine
	float g_cool_confg;				//13. value of relative air flow comsuption for the turbine cooling
	float eff_mech_confg;			//14. coefficient of power consumption for the auxiliary units drive
	float sigma_cmb_confg;			//15. coefficient of air pressure recovery at the combustion chamber
	float eff_turb_hp_confg;		//16. adiabatic efficiency of the HP-turbine stage
	float eff_turb_lp_confg;		//17. adiabatic efficiency of the LP-turbine stage
	float f_jn_confg;				//18. speed coefficinet of gas outflow from the nozzle
	float thrust_confg;				//19. value of the engine thrust [N]
	float cv_confg;					//20. axial velocity in gas air duct reference section at the inlet of the LP-compressor [m/s]
	float ck_confg;					//21. axial velocity in gas air duct reference section at the inlet of the HP-compressor [m/s]
	float eff_coeff_n1_confg;		//22. polytropic efficiency of the axial LP-compressor stage
	float eff_coeff_n2_confg;		//23. polytropic efficiency of the axial HP-compressor stage

	// AirSpeed points
	float min_height;				//1. Minimum point of the height [km]
	float numb_of_height;			//2. Number of points of the height [km]
	float max_height;				//3. Maximum point of the height [km]

	float min_speed;				//1. Minimum point of the speed
	float numb_of_speed;			//2. Number of points of the speed
	float max_speed;				//3. Maximum point of the speed

	float min_temperature;			//1. Minimum point of the temperature
	float numb_of_temperature;		//2. Number of points of the temperature
	float max_temperature;			//3. Maximum point of the temperature

	// File paths
	const char *filePathLP;			//1. FilePath of LP-compressor characteristics
	const char *filePathHP;			//2. FilePath of HP-compressor characteristics
	const char* filePathResult;		//3. FilePath for results save


	void Load(InputData*);
	void Set_AirData_Step(InputData*);
	void Set_Coefficients(InputData*);

};

extern InputData input;