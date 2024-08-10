#include "EngineData.h"
#include "InputData.h"
#include "L_interp.h"


void EngineData::Create_LP_PressureLines() {
	log_file.Log_Info("Model: Creating LP Pressure Lines");

	//compressor_lp_lines[n].map[i][0]	compressor_lp_lines[n].map[i][1]	compressor_lp_lines[n].map[i][2]	compressor_lp_lines[n].map[i][3]
	//n1								p_comp_n1							q(l_v)								eff_comp_n1

	for (int i = 0, m = 0; i < nbranches; i++) {
		for (int n = 0; n < npoints; n++)
		{
			for (int j = 0; j < compressor_lp.ncolumns; j++)
			{
				compressor_lp_lines[n].map[i][j] = compressor_lp.map[m][j];		// Transform the array with LP-compressor characteristics to pressurelines
			}
			m++;
		}
	}

	for (int n = 0; n < npoints; n++) {
		compressor_lp_lines[n].CountSize();
	}

}


void EngineData::Calc_n1_relative(int t, int i, int j) {
	log_file.Log_Info("Model: Calculating N1 relative");

	outBoardTemperature = (288.15f + dt[t]) - (6.5f * height[i]);
	thz = outBoardTemperature * (1 + ((input.k_const - 1) / 2) * pow(speed[j], 2));
	thz_n1_in = thz;

	n1_relative = sqrt(thz_n1_in_calc / thz_n1_in);

}


void EngineData::Calc_p_comp_n1() {
	log_file.Log_Info("Model: Calculating p_comp_n1");

	//compressor_lp_dt.map[i][0]	compressor_lp_dt.map[i][1]	compressor_lp_dt.map[i][2]	compressor_lp_dt.map[i][3]
	//n1							p_comp_n1					q(lamb_v)					eff_lp_compr

	//Calculating p_comp_n1 with temperature coefficient
	for (int i = 0, n = 0; i < compressor_lp.nrows; i++) {
		compressor_lp_dt.map[i][0] = compressor_lp.map[i][0] * n1_relative;		//n_1_relative
		compressor_lp_lines[n].Calc(compressor_lp_dt.map[i][0], calc_out);

		compressor_lp_dt.map[i][1] = calc_out[1];								//p_comp_n1 = f(n1)

		coeff_10 = thz * (pow(compressor_lp_dt.map[i][1], ((input.k_const - 1) / input.k_const)) - 1);
		compressor_lp_t_n1_coeff.Calc(compressor_lp.map[i][0], thz, calc_out);

		t_n1_coeff = calc_out[2];												//t_n1_coeff = f(n1_rel, thz)

		//p_comp_n1 with temperature coefficient
		compressor_lp_dt.map[i][1] = pow(1 + (coeff_10 * t_n1_coeff / thz), (input.k_const / (input.k_const - 1)));
																				//p_comp_n1 = f(n1_rel, thz)
		n++;
		if (n == npoints) {
			n = 0;
		}
	}

	compressor_lp_dt.CountSize();


}


void EngineData::Calc_LP_characteristics() {
	log_file.Log_Info("Model: Calculating LP characteristics");

	//compressor_lp_p_comp_n1[n].map[i][0]	compressor_lp_p_comp_n1[n].map[i][1]	compressor_lp_p_comp_n1[n].map[i][2]	compressor_lp_p_comp_n1[n].map[i][3]
	//p_comp_n1								q(lamb_v)								eff_lp_compr							n1

	//Creating the new map with p_comp_n1 main value
	for (int i = 0, m = 0; i < nbranches; i++) {
		for (int n = 0; n < npoints; n++)
		{
			compressor_lp_p_comp_n1[n].map[i][0] = compressor_lp.map[m][1];			//p_comp_n1
			compressor_lp_p_comp_n1[n].map[i][1] = compressor_lp.map[m][2];			//q(lamb_v)
			compressor_lp_p_comp_n1[n].map[i][2] = compressor_lp.map[m][3];			//eff_lp_compr

			m++;
		}
	}

	for (int n = 0; n < npoints; n++) {
		compressor_lp_p_comp_n1[n].CountSize();
	}


	//Calculating q(lamb_v) and eff_lp_compr
	for (int i = 0, n = 0; i < compressor_lp.nrows; i++) {
		compressor_lp_p_comp_n1[n].Calc(compressor_lp_dt.map[i][1], calc_out);

		compressor_lp_dt.map[i][2] = calc_out[1];								//q(lamb_v) = f(p_comp_n1)
		compressor_lp_dt.map[i][3] = calc_out[2];								//eff_lp_compr = f(p_comp_n1)

		n++;
		if (n == npoints) {
			n = 0;
		}
	}


	compressor_lp_dt.CountSize();


	//Calculating thz_n2_in for HP-compressor calculation
	for (int i = 0; i < compressor_lp.nrows; i++) {
		thz_n2_in[i] = thz_n1_in * pow(compressor_lp_dt.map[i][1], (n1_calc - 1) / n1_calc);
	}

}


void EngineData::Create_HP_PressureLines() {
	log_file.Log_Info("Model: Creating HP Pressure Lines");

	//compressor_hp.map[i][0]	compressor_hp.map[i][1]	compressor_hp.map[i][2]	compressor_hp.map[i][3]
	//n2						p_comp_n2				q(l_x)					eff_comp_n2

	nbranches = compressor_hp.CountBranches(0);
	npoints = compressor_hp.CountPoints(0);



	//compressor_hp_lines[n].map[i][0]	compressor_hp_lines[n].map[i][1]	compressor_hp_lines[n].map[i][2]	compressor_hp_lines[n].map[i][3]
	//n2								p_comp_n2							q(l_x)								eff_comp_n2

	for (int i = 0, m = 0; i < nbranches; i++) {
		for (int n = 0; n < npoints; n++)
		{
			for (int j = 0; j < compressor_hp.ncolumns; j++)
			{
				compressor_hp_lines[n].map[i][j] = compressor_hp.map[m][j];		// Transform the array with HP-compressor characteristics to pressurelines
			}
			m++;
		}
	}

	for (int n = 0; n < npoints; n++) {
		compressor_hp_lines[n].CountSize();
	}

}


void EngineData::Calc_HP_characteristics() {
	log_file.Log_Info("Model: Calculating HP characteristics");

	//compressor_hp_dt.map[i][0]	compressor_hp_dt.map[i][1]	compressor_hp_dt.map[i][2]	compressor_hp_dt.map[i][3]
	//n_2_relative					p_comp_n2					q_lamb_x					eff_hp_compr

	for (int i = 0, n = 0; i < compressor_hp.nrows; i++) {
		n2_specific[i] = sqrt(thz_n1_out_calc / thz_n2_in[i]);
		compressor_hp_dt.map[i][0] = compressor_hp.map[i][0] * n2_specific[i];	// n_2_relative

		compressor_hp_lines[n].Calc(compressor_hp_dt.map[i][0], calc_out);

		compressor_hp_dt.map[i][1] = calc_out[1];								//p_comp_n2 = f(n_2_relative)
		compressor_hp_dt.map[i][2] = calc_out[2];								//q_lamb_x = f(n_2_relative)
		compressor_hp_dt.map[i][3] = calc_out[3];								//eff_hp_compr = f(n_2_relative)

		n++;
		if (n == npoints) {
			n = 0;
		}
	}

	compressor_hp_dt.CountSize();

}


void EngineData::Calc_HP_control_function() {
	log_file.Log_Info("Model: Calculating HP control function");

	//hpcompr.map[i][0]	hpcompr.map[i][1]	hpcompr.map[i][2]	hpcompr.map[i][3]	hpcompr.map[i][4]		hpcompr.map[i][5]
	//D_n2_relative		n_2_relative		p_comp_n2_relative	q_lamb_x_relative	eff_hp_compr_relative	t_turbine_n2_in_relative

	for (int i = 0; i < compressor_hp.nrows; i++) {
		//Creating the new map with D_n2_relative main value

		hpcompr.map[i][1] = compressor_hp_dt.map[i][0];							// n_2_relative
		hpcompr.map[i][2] = compressor_hp_dt.map[i][1] / input.p_comp_n2_confg;	// p_comp_n2_relative
		hpcompr.map[i][3] = compressor_hp_dt.map[i][2] / q_lamb_x_calc;			// q_lamb_x_relative
		hpcompr.map[i][4] = compressor_hp_dt.map[i][3] / eff_hp_compr_calc;		// eff_hp_compr_relative


		hpcompr.map[i][0] = hpcompr.map[i][2] / hpcompr.map[i][3] * sqrt(hpcompr.map[i][4]) *
			sqrt((pow(input.p_comp_n2_confg, ((input.k_const - 1) / input.k_const)) - 1) /
				(pow(hpcompr.map[i][2] * input.p_comp_n2_confg, ((input.k_const - 1) / input.k_const)) - 1));
																				// D_n2_relative

		hpcompr.map[i][5] = (pow(hpcompr.map[i][2] * input.p_comp_n2_confg, ((input.k_const - 1) / input.k_const)) - 1) /
			(pow(input.p_comp_n2_confg, ((input.k_const - 1) / input.k_const)) - 1) * (1 / hpcompr.map[i][4]);
																				// t_turbine_n2_in_relative
	}

	hpcompr.CountSize();

}


void EngineData::Create_HP_dt_PressureLines() {
	log_file.Log_Info("Model: Creating HP dt_Pressure Lines");

	//branch_hp[n].map[i][0]	branch_hp[n].map[i][1]	branch_hp[n].map[i][2]	branch_hp[n].map[i][3]	branch_hp[n].map[i][4]		branch_hp[n].map[i][5]
	//D_n2_relative				n_2_relative			p_comp_n2_relative		q_lamb_x_relative		eff_hp_compr_relative		t_turbine_n2_in_relative

	nbranches = compressor_hp.CountBranches(0);

	//Transform the array with calculated LP-compressor characteristics to pressurelines
	for (int n = 0, m = 0; n < nbranches; n++) {
		npoints = compressor_hp.CountPoints(0);

		for (int i = 0; i < npoints; i++)
		{
			for (int j = 0; j < hpcompr.ncolumns; j++)
			{
				branch_hp[n].map[i][j] = hpcompr.map[m][j];
			}
			m++;
		}
	}

	for (int n = 0; n < nbranches; n++)
	{
		branch_hp[n].CountSize();
	}

}


void EngineData::Create_HP_WorkLine() {
	log_file.Log_Info("Model: Creating HP Workline");

	//workpointshp.map[i][0]	workpointshp.map[i][1]	workpointshp.map[i][2]	workpointshp.map[i][3]	workpointshp.map[i][4]		workpointshp.map[i][5]
	//n_2_relative				p_comp_n2_relative		q_lamb_x_relative		eff_hp_compr_relative	t_turbine_n2_in_relative	del_Ky_n2

	//Creating the workline of the HP-compressor
	for (int n = 0; n < nbranches; n++) {
		branch_hp[n].Calc(1., calc_out);	//D_n2_relative = 1

		for (int j = 1; j < branch_hp[n].ncolumns; j++)
			workpointshp.map[n][j - 1] = calc_out[j];
	}


	for (int i = 0; i < nbranches; i++) {
		workpointshp.map[i][5] = (((branch_hp[i].map[npoints - 1][2] / branch_hp[i].map[npoints - 1][3]) /
			(workpointshp.map[i][1] / workpointshp.map[i][2])) - 1.) * 100;
																				//del_Ky_n2
	}

	workpointshp.CountSize();

}


void EngineData::Calc_HP_WorkLine_characteristics() {
	log_file.Log_Info("Model: Calculating HP WorkLine characteristics");

	//workpoints_q_lamb_x.map[i][0]	workpoints_q_lamb_x.map[i][1]	workpoints_q_lamb_x.map[i][2]
	//q_lamb_x_relative				p_comp_n2_relative				n_2_relative

	//Creating the new map with D_n2_relative main value for LP-compressor calculation
	for (int i = 0; i < nbranches; i++) {
		workpoints_q_lamb_x.map[i][0] = workpointshp.map[i][2];					//q_lamb_x_relative
		workpoints_q_lamb_x.map[i][1] = workpointshp.map[i][1];					//p_comp_n2_relative
		workpoints_q_lamb_x.map[i][2] = workpointshp.map[i][0];					//n_2_relative
	}

	workpoints_q_lamb_x.CountSize();

}
