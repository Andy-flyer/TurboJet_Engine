#include "EngineData.h"
#include "L_interp.h"


void EngineData::Calc_HP_Compressor(int t, int i, int j) {
	log_file.Log_Info("Model: Start Calculating HP_Compressor for:", t, i, j);

//baseline characteristics of LP-compressor
	//compressor_lp.map[i][0]	compressor_lp.map[i][1]	compressor_lp.map[i][2]	compressor_lp.map[i][3]
	//n1						p_comp_n1				q(l_v)					eff_comp_n1

	nbranches = compressor_lp.CountBranches(0);		//Counting number of branches of the LP-compressor
	npoints = compressor_lp.CountPoints(0);			//Counting number of points of the LP-compressor pressureline


	//Calculation of some LP-compressor characteristics
	Create_LP_PressureLines();
	Calc_n1_relative(t, i, j);
	Calc_p_comp_n1();
	Calc_LP_characteristics();

	//Calculation HP-compressor characteristics
	Create_HP_PressureLines();
	Calc_HP_characteristics();
	Calc_HP_control_function();
	Create_HP_dt_PressureLines();
	Create_HP_WorkLine();
	Calc_HP_WorkLine_characteristics();

}


void EngineData::Calc_LP_Compressor(int t, int i, int j) {
	log_file.Log_Info("Model: Start Calculating LP_Compressor for:", t, i, j);

//baseline characteristics of LP-compressor
	//compressor_lp.map[i][0]	compressor_lp.map[i][1]	compressor_lp.map[i][2]	compressor_lp.map[i][3]
	//n1						p_comp_n1				q(l_v)					eff_comp_n1


	//Calculation LP-compressor characteristics
	Calc_LP_control_function();
	Create_LP_PressureLines_with_HP();
	Create_LP_WorkLine();
	Calc_LP_abs_values();

}
