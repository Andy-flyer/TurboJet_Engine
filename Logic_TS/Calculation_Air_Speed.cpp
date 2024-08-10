#include "EngineData.h"
#include "InputData.h"
#include "L_interp.h"


void EngineData::Calc_Air_Speed_Data(int t, int i, int j, int k) {
	log_file.Log_Info("Model: Start Calculating Air Speed Data:", t, i, j);

	//Getting absolute values from the LP-compressor array
	n1_relative = workpointslp_abs.map[k][0];
	n2_relative = workpointslp_abs.map[k][5];
	p_comp_n1 = workpointslp_abs.map[k][1];
	q_lamb_v = workpointslp_abs.map[k][2];
	eff_lp_compr = workpointslp_abs.map[k][3];
	p_comp_n2 = workpointslp_abs.map[k][4];
	eff_hp_compr = workpointslp_abs.map[k][7];
	t_turbine_n2_in = workpointslp_abs.map[k][8];
	q_lamb_x = workpointslp_abs.map[k][6];

	slipping = n2_relative / n1_relative;


	//a) calculating the LP-compressor
	//1 calculating thz_n1_out_internal
	outBoardTemperature = (288.15f + dt[t]) - (6.5f * height[i]);
	thz = outBoardTemperature * (1 + ((input.k_const - 1) / 2) * pow(speed[j], 2));
	thz_n1_in = thz;

	thz_n1_out_internal = thz_n1_in * 
		(1 + (((pow(p_comp_n1, (input.k_const - 1) / input.k_const)) - 1) / eff_lp_compr));

	//2 calculating phz_n1_out_internal
	p = 1.01325 * pow((1 - (height[i] / 44.368f)), 5.2532f);
	phz = p * pow((thz / outBoardTemperature), c_1);
	phz_rcvry_coef = input.sigma_confg - 0.033f * speed[j];
	phz_n1_in = phz * phz_rcvry_coef;

	phz_n1_out_internal = phz_n1_in * p_comp_n1;

	//3
	l_n1 = input.c_hc_air_const * (thz_n1_out_internal - thz_n1_in);

	//4
	gv = (m_v_calc * (phz_n1_in * 100000) * fv_calc * q_lamb_v) / sqrt(thz_n1_in);


	//b) calculating the HP-compressor
	//1
	thz_n2_out = thz_n1_out_internal * (1 + (((pow(p_comp_n2, c_2)) - 1) / eff_hp_compr));

	//2
	phz_n1_out = phz_n1_out_internal * phz_rcvry_coef;

	//3
	phz_n2_out = phz_n1_out * p_comp_n2;

	//4
	l_n2 = input.c_hc_air_const * (thz_n2_out - thz_n1_out_internal);
	l_n2_relative = l_n2 / l_n2_calc;

	//5
	q_lamb_k = (gv * sqrt(thz_n2_out)) / (m_v_calc * (phz_n2_out * 100000) * fk_calc);


	//c) calculating the combustion chamber
	//1
	c_heat_cap = 0.9f + 0.0001f * (2 * t_turbine_n2_in + thz_n2_out);

	//2
	q_comb_cham = c_heat_cap * (t_turbine_n2_in - thz_n2_out);

	//3
	gf = q_comb_cham / (input.hu_const * input.eff_cmb_confg);

	//4
	p_turbine_n2_in = phz_n2_out * input.sigma_cmb_confg;

	//5
	Gt = gf * (1 - input.g_cool_confg - input.g_bleed_confg);


	//d) calculating the HP-turbine
	//1
	l_turbine_n2 = l_n2 / 
		((1 + gf) * (1 - input.g_bleed_confg - input.g_cool_confg) * input.eff_mech_confg);

	//2
	pt_turbine_n2 = pow((1 - (l_turbine_n2 /(c_3 * Rf_calc * t_turbine_n2_in * input.eff_turb_hp_confg))), 
		(-input.kf_const / (input.kf_const - 1)));

	//3
	t_turbine_n2_cooled_out = t_turbine_n2_in - (l_turbine_n2) / (c_3 * Rf_calc);

	//4
	cg = 0.9f + 0.0003f * t_turbine_n2_cooled_out;

	//5
	ch = 0.9f + 0.0003f * thz_n2_out;

	//6
	a = cg * ((1 + gf) * (1 - input.g_cool_confg - input.g_bleed_confg) * t_turbine_n2_cooled_out + 
		(ch * input.g_cool_confg * thz_n2_out)) / 
			((1 + gf) * (1 - input.g_cool_confg - input.g_bleed_confg) + input.g_cool_confg);

	//7
	t_yy = (sqrt(0.81f + 0.0012f * a) - 0.9f) / 0.0006f;

	//8
	p_turbine_n2_out = p_turbine_n2_in / pt_turbine_n2;


	//e) calculating the LP-turbine
	//1
	l_turbine_n1 = l_n1 / ((1 + gf) * (1 - input.g_cool_confg - input.g_bleed_confg) + input.g_cool_confg);

	//2
	t_turbine_n2_out = t_turbine_n2_in - (l_turbine_n2) / (c_3 * Rf_calc);

	pt_turbine_n1 = pow(1 - (l_turbine_n1 /
		(c_3 * Rf_calc * t_turbine_n2_out * input.eff_turb_lp_confg)), -c_3);

	//3
	t_turbine_n1_out = t_turbine_n2_out - (l_turbine_n1 / (c_3 * Rf_calc));

	//4
	p_turbine_n1_out = p_turbine_n2_out / pt_turbine_n1;


	//f)  calculating the jet nozzle
	//1
	p_ratio_nozzle = p_turbine_n1_out / p;

	//2
	if (type_of_nozzle == 0)
	{
		c_nozzle_speed = input.f_jn_confg * sqrt((2 * c_3 * Rf_calc * t_turbine_n1_out) *
			(1 - pow(1 / p_ratio_nozzle, (input.kf_const - 1) / input.kf_const)));
	}

	else if (type_of_nozzle == 1)
	{
		c_nozzle_speed = input.f_jn_confg *
			sqrt((2 * input.kf_const * Rf_calc * t_turbine_n1_out) / (input.kf_const + 1));
	}

	//3
	p_static_nozzle = p_turbine_n1_out / p_ratio_cr_calc;

	//4
	lamb_c = input.f_jn_confg;

	y_lamb_c = pow((input.kf_const + 1) / 2, (1 / (input.kf_const - 1))) * 
		lamb_c / (1 - ((input.kf_const - 1) / (input.kf_const + 1)) * pow(lamb_c, 2));

	//5
	fc_ñoeff = sqrt(t_turbine_n1_out) /
		(m_g_calc * (p_static_nozzle * 100000) * y_lamb_c) * 
			((1 + gf) * (1 - input.g_cool_confg - input.g_bleed_confg) + input.g_cool_confg);

	//6
	airSpeed = speed[j] * sqrt(input.k_const * Rf_calc * outBoardTemperature);

	thrust_specific = ((1 + gf) * (1 - input.g_cool_confg - input.g_bleed_confg) + 
		input.g_cool_confg) * c_nozzle_speed - airSpeed + 
			(fc_ñoeff * ((p_static_nozzle * 100000) - (p * 100000)));

	//7
	thrust = thrust_specific * gv;
	thrust_relative = thrust / input.thrust_confg;

	//8
	fuel_flow_specific = 3600 * Gt / thrust_specific;


	//g)  calculating the general characteristics of the engine
	//1
	pgg = p_turbine_n1_out / phz;

	//2
	fuel_flow_hour = fuel_flow_specific * thrust;

	//3
	l_cycle = (l_turbine_n2 * 
		(1 - input.eff_mech_confg)) + (thrust_specific * (thrust_specific + (2 * airSpeed)) / 2);

	//4
	intern_eff = (l_cycle * input.eff_cmb_confg) / (q_comb_cham * 1000);

	//5
	p_comp_sum = p_comp_n1 * p_comp_n2;

}