#pragma once
#include <string.h>


class EngineData {
public:

	// Values of Design characteristics

	float thz_n1_in_calc;											//1. design stagnation temperature at the inlet to the LP-compressor [K]
	float eff_lp_compr_calc;										//2. design adiabatic efficiency of the LP-compressor
	float eff_hp_compr_calc;										//3. design adiabatic efficiency of the HP-compressor
	float n1_calc;													//4. the polytropic index of the LP-compressor
	float n2_calc;													//5. the polytropic index of the HP-compressor
	float l_n1_calc;												//6. design specific work of compression at the LP-compressor [J\kg]
	float thz_n1_out_calc;											//7. design stagnation temperature at the outlet of the LP-compressor [K]
	float phz_n1_out_calc;											//8. design total air pressure at the outlet of the LP-compressor [N\m^2]
	float l_n2_calc;												//9. design specific work of compression at the HP-compressor [J\kg]
	float thz_n2_out_calc;											//10. design stagnation temperature at the outlet of the HP-compressor [K]
	float phz_n2_out_calc;											//11. design total air pressure at the outlet of the HP-compressor [N\m^2]
	float p_turbine_n2_in_calc;										//12. design total gas pressure at the inlet of the HP-turbine [N\m^2]
	float c_heat_cap_calc;											//13. design value of supplied average heat capacity in the combustion chamber [J*(10^3)\kg*K]
	float q_comb_cham_calc;											//14. design value of specific amount of heat supplied to the air in the combustion chamber [J*(10^3)\kg]
	float gf_calc;													//15. design air to fuel ratio in the combustion chamber
	float l_0;														//16. value of air mass
	float a_sum;													//17. the coefficient of excess air
	float Rf_calc;													//18. gas constant of dry air
	float l_turbine_n2_calc;										//19. design value of specific work of the gas expansion at the HP-turbine [J\kg]
	float t_turbine_n2_out_calc;									//20. design value of gas temperature after the HP-turbine without cooling [K]
	float cg;														//21. average heat capacity of gas in T*y temperature range [ÍJ/kg*K]
	float ch;														//22. average heat capacity of gas in T*k temperature range [ÍJ/kg*K]
	float g_relative_turbine_n2_calc;								//23. design value of relative change of the gas flow at the HP-turbine
	float a;														//24. coefficient for cmix calculation
	float t_yy;														//25. value of gas temperature at the outlet of the cooled turbine [K]
	float cmix;														//26. average heat capacity of the mix of air and gas and cooled air
	float t_turbine_n2_cooled_out_calc;								//27. design value of gas temperature mixed with cooled air after the HP-turbine [K]
	float pt_turbine_n2_calc;										//28. design ratio of gas expansion at the HP-turbine
	float p_turbine_n2_out_calc;									//29. design total gas pressure after the HP-turbine [N\m^2]
	float l_turbine_n1_calc;										//30. design value of specific work of the gas expansion at the LP-turbine [J\kg]
	float t_turbine_n1_out_calc;									//31. design value of gas temperature after the LP-turbine [K]
	float pt_turbine_n1_calc;										//32. design ratio of gas expansion at the LP-turbine
	float p_turbine_n1_out_calc;									//33. design total gas pressure after the LP-turbine [N\m^2]
	float p_ratio_nozzle_calc;										//34. design ratio of gas pressure decrease in the nozzle
	float p_ratio_cr_calc;											//35. design critical ratio of gas pressure decrease in the nozzle
	float p_static_nozzle_calc;										//36. design static gas pressure at the nozzle [N\m^2]
	bool type_of_nozzle;											//37. the type of jet-nozzle (1 - convergent nozzle, 0 - full gas expansion nozzle)
	float c_nozzle_speed_calc;										//38. design rate of gas speed from the nozzle without nom expansion [m\sec] 
	float m_g_calc;													//39. coefficient depending on adiabatic constant for combustion products and on gas constant of dry air [sqrt(kg*K/J)]
	float m_v_calc;													//40. coefficient depending on adiabatic constant for combustion products and on adiabatic constant for dry air [sqrt(kg*K/J)]
	float lamb_c;													//41. design relative gas speed at the nozzle
	float y_lamb_c;													//42. design gasodynamic function of the gas speed at the nozzle
	float fc_Òoeff;													//43. coefficient for air flow comsuption calculation
	float gv_calc;													//44. design air flow comsuption of the engine [kg\sec]
	float lamb_v_calc;												//45. design relative air flow speed at the inlet of the LP-compressor
	float q_lamb_v_calc;											//46. design relative air flow density at the inlet of the LP-compressor
	float lamb_k_calc;												//47. design relative air flow speed at the outlet of the HP-compressor
	float q_lamb_k_calc;											//48. design relative air flow density at the outlet of the HP-compressor
	float cx_calc;													//49. design axial velocity in gas air duct reference section at the outlet of the HP-compressor
	float lamb_x_calc;												//50. design relative air flow speed at the inlet of the HP-compressor
	float q_lamb_x_calc;											//51. design relative air flow density at the inlet of the HP-compressor
	float fv_calc;													//52. design air-gas flow area at the inlet of the LP-compressor [m^2]
	float fk_calc;													//53. design air-gas flow area at the outlet of the HP-compressor [m^2]
	float fx_calc;													//54. design air-gas flow area at the inlet of the HP-compressor [m^2]
	float fc_calc;													//55. design air-gas flow area at the nozzle [m^2]

	// Values of AirSpeed characteristics

	float outBoardTemperature;										//1. outboard temperature [K]
	float p;														//2. outboard air pressure [N\m^2]
	float thz;														//3. stagnation temperature at the inlet to the engine [K]
	float phz;														//4. stagnation air pressure at the inlet to the engine [N\m^2]
	float thz_n1_in;												//5. stagnation temperature at the inlet to the LP-compressor [K]
	float phz_rcvry_coef;											//6. coefficient of air pressure recovery at the inlet of the engine
	float phz_n1_in;												//7. value of total air pressure at the inlet to the LP-compressor [N\m^2]
	float alfaTLA;													//8. value of engine (TLA) throttle leveler position [deg]
	float n2_relative;												//9. value of relative change at specified rotation speed of the HP-compressor
	float n1_relative;												//10. value of relative change at specified rotation speed of the LP-compressor
	float p_comp_n2;												//11. value of air pressure increase ratio at the HP-compressor
	float p_comp_n1;												//12. value of air pressure increase ratio at the LP-compressor
	float thz_n1_out;												//13. stagnation temperature at the outlet of the LP-compressor [K]
	float thz_n2_out;												//14. stagnation temperature at the outlet of the HP-compressor [K]
	float phz_n1_out;												//15. total air pressure at the outlet of the LP-compressor [N\m^2]
	float phz_n2_out;												//16. total air pressure at the outlet of the HP-compressor [N\m^2]
	float l_n1;														//17. specific work of compression at the LP-compressor [J\kg]
	float l_n2;														//18. specific work of compression at the HP-compressor [J\kg]
	float l_n2_relative;											//19. value of relative change at work of compression at the HP-compressor
	float t_turbine_n2_in;											//20. value of gas temperature before the HP-turbine [K]
	float gv;														//21. air flow comsuption of the engine [kg\sec]
	float c_heat_cap;												//22. value of supplied average heat capacity in the combustion chamber [J*(10^3)\kg*K]
	float q_comb_cham;												//23. value of specific amount of heat supplied to the air in the combustion chamber [J*(10^3)\kg]
	float gf;														//24. air to fuel ratio in the combustion chamber
	float g_relative_turbine_n2;									//25. value of relative change of the gas flow at the HP-turbine
	float l_turbine_n2;												//26. value of specific work of the gas expansion at the HP-turbine [J\kg]
	float p_turbine_n2_in;											//27. total gas pressure at the inlet of the HP-turbine [N\m^2]
	float pt_turbine_n2;											//28. ratio of gas expansion at the HP-turbine
	float t_turbine_n2_out;											//29. value of gas temperature after the HP-turbine without cooling [K]
	float t_turbine_n2_cooled_out;									//30. value of gas temperature mixed with cooled air after the HP-turbine [K]
	float p_turbine_n2_out;											//31. total gas pressure after the HP-turbine [N\m^2]
	float l_turbine_n1;												//32. value of specific work of the gas expansion at the LP-turbine [J\kg]
	float pt_turbine_n1;											//33. ratio of gas expansion at the LP-turbine
	float t_turbine_n1_out;											//34. value of gas temperature after the LP-turbine	[K]
	float p_turbine_n1_out;											//35. total gas pressure after the LP-turbine [N\m^2]
	float p_ratio_nozzle;											//36. ratio of gas pressure decrease in the nozzle
	float c_nozzle_speed;											//37. the rate of gas speed from the nozzle without nom expansion [m\sec] 
	float p_static_nozzle;											//38. static gas pressure at the nozzle [N\m^2]
	float airSpeed;													//39. air speed of the aircraft [m\sec]
	float thrust;													//40. thrust of the engine [N]
	float thrust_specific;											//41. specific thrust of the engine [N*sec\kg]
	float fuel_flow_specific;										//42. specific fuel consumption of the engine [kg\N*hour]
	float fuel_flow_hour;											//43. value of fuel consumption in hour [kg\hour]
	float l_cycle;													//44. engine cycle work [J\kg]
	float intern_eff;												//45. internal efficiency of the engine 
	float q_lamb_v;													//46. relative air flow density at the inlet of the LP-compressor
	float eff_lp_compr;												//47. adiabatic efficiency of the LP-compressor
	float eff_hp_compr;												//48. adiabatic efficiency of the HP-compressor
	float slipping;													//49. value of slipping	between the LP-compressor and the HP-compressor			
	float q_lamb_x;													//50. relative air flow density at the inlet of the HP-compressor
	float thz_n1_out_internal;										//51. stagnation temperature between the outlet of the LP-compressor and the inlet of the HP-compressor [K]
	float phz_n1_out_internal;										//52. stagnation air pressure between the outlet of the LP-compressor and the inlet of the HP-compressor [N\m^2]
	float q_lamb_k;													//53. relative air flow density at the outlet of the HP-compressor
	float pgg;														//54. value of air pressure increase ratio at the gas generator
	float p_comp_sum;												//55. summary air pressure increase ratio of the engine
	float thrust_relative;											//56. value of relative thrust of the engine
	float Gt;														//57. specific fuel consumption with bleed operation

	// AirSpeed calculating points

	float height[151];												//1. calculating points of the height [km]
	float speed[11];												//2. calculating points of the speed
	float dt[30];													//3. calculating points of the temperature

	// Coefficients for calculation

	float c_1;														//1. (input.k_const / (input.k_const - 1)) = 3.5
	float c_2;														//2. ((input.k_const - 1) / input.k_const) = 0.2857142857
	float c_3;														//3. (input.kf_const / (input.kf_const - 1)) = 4.0303030303
	float c_f;														//4. coefficient of carbon mass fraction for the fuel = 0.85
	float h_f;														//5. coefficient of hydrogen mass fraction for the fuel = 0.15

	// Variables for calculation

	int nbranches;													//1. number of pressure lines of the compressor
	int npoints;													//2. number of points of the pressure line
	float coeff_10;													//3. temperature coefficient of air pressure increase ratio at the LP-compressor
	float t_n1_coeff;												//4. coefficient depending on stagnation temperature at the inlet to the LP-compressor and on engine LP-compressor rotation speed
	float thz_n2_in[200];											//5. stagnation temperature at the inlet to the HP-compressor with calculated temperature coefficient [K]
	float n2_specific[200];											//6. specific value of the HP-compressor relative speed
	float calc_out[30];												//7. output array for calculation


	EngineData() {
		memset(this, 0, sizeof(EngineData));
	}

	//Calculation of design values
	void Design_Values(float, float);

	//Calculation of HP-compressor workline
	void Calc_HP_Compressor(int, int, int);
	void Create_LP_PressureLines();
	void Calc_n1_relative(int, int, int);
	void Calc_p_comp_n1();
	void Calc_LP_characteristics();
	void Create_HP_PressureLines();
	void Calc_HP_characteristics();
	void Calc_HP_control_function();
	void Create_HP_dt_PressureLines();
	void Create_HP_WorkLine();
	void Calc_HP_WorkLine_characteristics();

	//Calculation of LP-compressor workline
	void Calc_LP_Compressor(int, int, int);
	void Calc_LP_control_function();
	void Create_LP_PressureLines_with_HP();
	void Create_LP_WorkLine();
	void Calc_LP_abs_values();

	//Calculation of AirSpeed Data
	void Calc_Air_Speed_Data(int, int, int, int);
};

extern EngineData eng;


void Run();
