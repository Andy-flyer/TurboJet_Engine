#include "EngineData.h"
#include "InputData.h"
#include "L_interp.h"


void EngineData::Calc_LP_control_function() {
	log_file.Log_Info("Model: Calculating LP control function");

	//lpcompr.map[i][0]	lpcompr.map[i][1]	lpcompr.map[i][2]	lpcompr.map[i][3]	lpcompr.map[i][4]		lpcompr.map[i][5]	lpcompr.map[i][6]	lpcompr.map[i][7]
	//D_n1_relative		n_1_relative		p_comp_n1_relative	q_lamb_v_relative	eff_lp_compr_relative	p_comp_n2_relative	n2_relative			q_lamb_x_relative


	for (int i = 0; i < compressor_lp.nrows; i++) {
		//Creating the new map with D_n1_relative main value

		lpcompr.map[i][1] = compressor_lp_dt.map[i][0];							// n_1_relative
		lpcompr.map[i][2] = compressor_lp_dt.map[i][1] / input.p_comp_n1_confg;	// p_comp_n1_relative
		lpcompr.map[i][3] = compressor_lp_dt.map[i][2] / q_lamb_v_calc;			// q_lamb_v_relative
		lpcompr.map[i][4] = compressor_lp_dt.map[i][3] / eff_lp_compr_calc;		// eff_lp_compr_relative

		//Calculating q_lamb_x_relative
		lpcompr.map[i][7] = lpcompr.map[i][3] / lpcompr.map[i][2] *	
			sqrt((1 + ((pow(lpcompr.map[i][2] * input.p_comp_n1_confg, (input.k_const - 1) / input.k_const) - 1) /
				(eff_lp_compr_calc * lpcompr.map[i][4]))) /
				(1 + ((pow(input.p_comp_n1_confg, (input.k_const - 1) / input.k_const) - 1) /
					(eff_lp_compr_calc))));
																				//q_lamb_x_relative
	}

	//Calculating p_comp_n2_relative and n2_relative
	for (int i = 0; i < compressor_lp.nrows; i++) {
		workpoints_q_lamb_x.Calc(lpcompr.map[i][7], calc_out);
		lpcompr.map[i][5] = calc_out[1];										// p_comp_n2_relative = f(q_lamb_x_relative)
		lpcompr.map[i][6] = calc_out[2];										// n2_relative = f(q_lamb_x_relative)
	}

	//Calculating D_n1_relative
	for (int i = 0; i < compressor_lp.nrows; i++) {
		lpcompr.map[i][0] = lpcompr.map[i][2] * lpcompr.map[i][5] / lpcompr.map[i][3] * sqrt(lpcompr.map[i][4]) *
			sqrt((pow(input.p_comp_n1_confg, ((input.k_const - 1) / input.k_const)) - 1) /
				(pow(lpcompr.map[i][2] * input.p_comp_n1_confg, ((input.k_const - 1) / input.k_const)) - 1));
																				// D_n1_relative
	}

	lpcompr.CountSize();

}


void EngineData::Create_LP_PressureLines_with_HP() {
	log_file.Log_Info("Model: Creating LP Pressure Lines with HP data");

	//branch_lp[n].map[i][0]	branch_lp[n].map[i][1]	branch_lp[n].map[i][2]	branch_lp[n].map[i][3]	branch_lp[n].map[i][4]	branch_lp[n].map[i][5]	branch_lp[n].map[i][6]	branch_lp[n].map[i][7]
	//D_n1_relative				n_1_relative			p_comp_n1_relative		q_lamb_v_relative		eff_lp_compr_relative	p_comp_n2_relative		n2_relative				q_lamb_x_relative

	nbranches = lpcompr.CountBranches(1);

	for (int n = 0, m = 0; n < nbranches; n++) {
		npoints = lpcompr.CountPoints(1);

		for (int i = 0; i < npoints; i++)
		{
			for (int j = 0; j < lpcompr.ncolumns; j++)
			{
				branch_lp[n].map[npoints - i - 1][j] = lpcompr.map[m][j];		// Transform the array with calculated LP-compressor and HP-compressor characteristics to pressurelines
			}
			m++;
		}
	}

	for (int n = 0; n < nbranches; n++)
	{
		branch_lp[n].CountSize();
	}

}


void EngineData::Create_LP_WorkLine() {
	log_file.Log_Info("Model: Creating LP Workline");

	//workpointslp.map[i][0]	workpointslp.map[i][1]	workpointslp.map[i][2]	workpointslp.map[i][3]	workpointslp.map[i][4]	workpointslp.map[i][5]	workpointslp.map[i][6]	workpointslp.map[i][7]	workpointslp.map[i][8]		workpointslp.map[i][9]
	//n_1_relative				p_comp_n1_relative		q_lamb_v_relative		eff_lp_compr_relative	p_comp_n2_relative			n2_relative			q_lamb_x_relative		eff_hp_compr_relative	t_turbine_n2_in_relative	del_Ky_n1

	//Creating the workline of the LP-compressor

	for (int n = 0; n < nbranches; n++) {
		branch_lp[n].Calc(1., calc_out);	//D_n1_relative = 1

		for (int j = 1; j < branch_lp[n].ncolumns; j++)
			workpointslp.map[n][j - 1] = calc_out[j];
	}

	for (int i = 0; i < nbranches; i++) {
		workpointshp.Calc(workpointslp.map[i][5], calc_out);
		workpointslp.map[i][6] = calc_out[2];									//q_lamb_x_relative = f(n2_relative)
		workpointslp.map[i][7] = calc_out[3];									//eff_hp_compr_relative = f(n2_relative)
		workpointslp.map[i][8] = calc_out[4];									//t_turbine_n2_in_relative = f(n2_relative)
	}

	for (int i = 0; i < nbranches; i++) {
		workpointslp.map[i][9] = (((workpointslp.map[i][3] / workpointslp.map[i][2]) /
			(workpointslp.map[i][1] / workpointslp.map[i][2])) - 1.) * 100;
																				//del_Ky_n1
	}

	workpointslp.CountSize();

}


void EngineData::Calc_LP_abs_values() {
	log_file.Log_Info("Model: Calculating LP absolute values");

	//workpointslp_abs.map[i][0]	workpointslp_abs.map[i][1]	workpointslp_abs.map[i][2]	workpointslp_abs.map[i][3]	workpointslp_abs.map[i][4]	workpointslp_abs.map[i][5]	workpointslp_abs.map[i][6]	workpointslp_abs.map[i][7]	workpointslp_abs.map[i][8]	workpointslp_abs.map[i][9]
	//n_1_relative					p_comp_n1					q_lamb_v					eff_lp_compr				p_comp_n2					n2_relative					q_lamb_x					eff_hp_compr				t_turbine_n2_in				del_Ky_n1

	//Creating the new array with the absolute values
	for (int i = 0; i < workpointslp.nrows; i++) {
		workpointslp_abs.map[i][0] = workpointslp.map[i][0];						//n_1_relative
		workpointslp_abs.map[i][1] = workpointslp.map[i][1] * input.p_comp_n1_confg;//p_comp_n1
		workpointslp_abs.map[i][2] = workpointslp.map[i][2] * q_lamb_v_calc;		//q_lamb_v
		workpointslp_abs.map[i][3] = workpointslp.map[i][3] * eff_lp_compr_calc;	//eff_lp_compr
		workpointslp_abs.map[i][4] = workpointslp.map[i][4] * input.p_comp_n2_confg;//p_comp_n2
		workpointslp_abs.map[i][5] = workpointslp.map[i][5];						//n2_relative
		workpointslp_abs.map[i][6] = workpointslp.map[i][6] * q_lamb_x_calc;		//q_lamb_x
		workpointslp_abs.map[i][7] = workpointslp.map[i][7] * eff_hp_compr_calc;	//eff_hp_compr
		workpointslp_abs.map[i][8] = workpointslp.map[i][8] * input.tg_confg;		//t_turbine_n2_out
		workpointslp_abs.map[i][9] = workpointslp.map[i][9];						//del_Ky_n1
	}

	workpointslp_abs.CountSize();

}