#include "EngineData.h"
#include "InputData.h"
#include "L_interp.h"


void EngineData::Design_Values(float h, float v) {
	log_file.Log_Info("Model: Start Calculating Design Values.");

	//1
	outBoardTemperature = 288.15f - (6.5f * h);
	thz = outBoardTemperature * (1 + ((input.k_const - 1) / 2) * pow(v, 2));

	//2
	p = 1.01325f * pow((1 - (h / 44.368f)), 5.2532f);
	phz = p * pow((thz / outBoardTemperature), c_1);

	//3a
	thz_n1_in_calc = thz;

	//3b
	phz_n1_in = phz * input.sigma_confg;

	//4
	eff_lp_compr_calc = (pow(input.p_comp_n1_confg, c_2) - 1) /
		(pow(input.p_comp_n1_confg, ((input.k_const - 1) / (input.k_const * input.eff_coeff_n1_confg))) - 1);

	eff_hp_compr_calc = (pow(input.p_comp_n1_confg, c_2) - 1) /
		(pow(input.p_comp_n1_confg, ((input.k_const - 1) / (input.k_const * input.eff_coeff_n2_confg))) - 1);


	polytropic_coeff.Calc(eff_lp_compr_calc, calc_out);
	n1_calc = calc_out[1];

	polytropic_coeff.Calc(eff_hp_compr_calc, calc_out);
	n2_calc = calc_out[1];

	//5
	thz_n1_out_calc = thz_n1_in_calc * pow(input.p_comp_n1_confg, (n1_calc - 1) / n1_calc);

	//5
	phz_n1_out_calc = phz_n1_in * input.p_comp_n1_confg;

	//5
	l_n1_calc = input.c_hc_air_const * (thz_n1_out_calc - thz_n1_in_calc);

	//6
	thz_n2_out_calc = thz_n1_out_calc * pow(input.p_comp_n2_confg, ((n2_calc - 1) / n2_calc));

	//6
	phz_n2_out_calc = phz_n1_out_calc * input.p_comp_n2_confg;

	//6
	l_n2_calc = input.c_hc_air_const * (thz_n2_out_calc - thz_n1_out_calc);

	//7
	p_turbine_n2_in_calc = phz_n2_out_calc * input.sigma_cmb_confg;

	//8a
	c_heat_cap_calc = 0.9f + 0.0001f * (2 * input.tg_confg + thz_n2_out_calc);

	//8a
	q_comb_cham_calc = c_heat_cap_calc * (input.tg_confg - thz_n2_out_calc);

	//8b
	gf_calc = q_comb_cham_calc / (input.hu_const * input.eff_cmb_confg);

	//8c
	l_0 = ((8.f / 3.f * c_f) + (8.f * h_f)) / 0.232f;

	a_sum = 1.f / (l_0 * gf_calc);


	if ((a_sum < 1.) || (a_sum > 7.)) {
		log_file.Log_Error("The working process in the combustion chamber is practically impossible.\nPlease, decrease P1 and P2 air pressire increase ratio of the compressors,\nor T* value of gas temperature before the turbine.");
		return;
	}

	//8d
	Rf_calc = input.r_const * (1 + (1.0862f * gf_calc)) / (1 + gf_calc);

	//9
	if (input.tg_confg < 1270)
		input.g_cool_confg = 0.;

	l_turbine_n2_calc = l_n2_calc / 
		((1 + gf_calc) * (1 - input.g_cool_confg - input.g_bleed_confg) * input.eff_mech_confg);

	//10
	t_turbine_n2_out_calc = input.tg_confg - (l_turbine_n2_calc) / (c_3 * Rf_calc);

	//10
	cg = 0.9f + 0.0003f * t_turbine_n2_out_calc;
	ch = 0.9f + 0.0003f * thz_n2_out_calc;

	//11
	g_relative_turbine_n2_calc = (1 + gf_calc) * (1 - input.g_bleed_confg - input.g_cool_confg);
	
	//11
	a = ((cg * g_relative_turbine_n2_calc * t_turbine_n2_out_calc) + 
		(ch * input.g_cool_confg * thz_n2_out_calc)) /
			(g_relative_turbine_n2_calc + input.g_cool_confg);

	//11
	t_turbine_n2_cooled_out_calc = (sqrt(0.81f + 0.0012f * a) - 0.9f) / 0.0006f;

	//11
	pt_turbine_n2_calc = pow((1 - (l_turbine_n2_calc / 
		((cg * 1000) * input.tg_confg * input.eff_turb_hp_confg))), -c_3);

	//11
	p_turbine_n2_out_calc = p_turbine_n2_in_calc / pt_turbine_n2_calc;

	//12
	l_turbine_n1_calc = l_n1_calc / (g_relative_turbine_n2_calc + input.g_cool_confg);

	//13
	t_turbine_n1_out_calc = t_turbine_n2_cooled_out_calc - (l_turbine_n1_calc / (c_3 * Rf_calc));

	//13
	pt_turbine_n1_calc = pow(1 - (l_turbine_n1_calc / 
		(c_3 * Rf_calc * t_turbine_n2_cooled_out_calc * input.eff_turb_lp_confg)), -c_3);

	//13
	p_turbine_n1_out_calc = p_turbine_n2_out_calc / pt_turbine_n1_calc;

	//14a
	p_ratio_nozzle_calc = p_turbine_n1_out_calc / p;

	p_ratio_cr_calc = pow((input.kf_const + 1) / 2, c_3);

	//14a
	p_static_nozzle_calc = p_turbine_n1_out_calc / p_ratio_cr_calc;


	if (p_static_nozzle_calc == p)// full gas expansion nozzle
	{
		//14b
		c_nozzle_speed_calc = input.f_jn_confg * sqrt((2 * c_3 * Rf_calc * t_turbine_n1_out_calc) *
			(1 - pow(1 / p_ratio_nozzle_calc, (input.kf_const - 1) / input.kf_const)));

		type_of_nozzle = 0;
	}

	else if (p_ratio_nozzle_calc > p_ratio_cr_calc)// convergent nozzle
	{
		p_ratio_nozzle_calc = p_ratio_cr_calc;

		//14b
		c_nozzle_speed_calc = input.f_jn_confg *
			sqrt(2 * input.kf_const / (input.kf_const + 1) * Rf_calc * t_turbine_n1_out_calc);

		type_of_nozzle = 1;
	}

	//15
	m_g_calc = sqrt(input.kf_const /
		Rf_calc * pow(2 / (input.kf_const + 1), (input.kf_const + 1) / (input.kf_const - 1)));

	m_v_calc = sqrt(input.k_const /
		Rf_calc * pow(2 / (input.k_const + 1), (input.k_const + 1) / (input.k_const - 1)));

	//15
	lamb_c = c_nozzle_speed_calc / 
		sqrt((2 * input.kf_const * Rf_calc * t_turbine_n1_out_calc) / (input.kf_const + 1));

	y_lamb_c = pow((input.kf_const + 1) / 2, (1 / (input.kf_const - 1))) * lamb_c /
		(1 - ((input.kf_const - 1) / (input.kf_const + 1)) * pow(lamb_c, 2));

	//15
	fc_ñoeff = ((g_relative_turbine_n2_calc + input.g_cool_confg) * 
		sqrt(t_turbine_n1_out_calc)) / (m_g_calc * (p_static_nozzle_calc * 100000) * y_lamb_c);

	//15
	gv_calc = input.thrust_confg / ((g_relative_turbine_n2_calc + input.g_cool_confg) 
		* c_nozzle_speed_calc + (fc_ñoeff * 100000 * (p_static_nozzle_calc - phz)));

	//16a
	cx_calc = (phz_n1_out_calc - phz_n2_out_calc) / 
		(phz_n1_in - phz_n2_out_calc) * (input.cv_confg - input.ck_confg) + input.ck_confg;

	//17a
	lamb_v_calc = input.cv_confg / 
		sqrt((2 * input.k_const / (input.k_const + 1)) * Rf_calc * thz_n1_in_calc);

	q_lamb_v_calc = pow(((input.k_const + 1) / 2), (1 / (input.k_const - 1))) * lamb_v_calc *
		pow(1 - ((input.k_const - 1) / (input.k_const + 1) * pow(lamb_v_calc, 2)), (1 / (input.k_const - 1)));

	//17b
	lamb_k_calc = input.ck_confg / 
		sqrt((2 * input.k_const / (input.k_const + 1)) * Rf_calc * thz_n2_out_calc);

	q_lamb_k_calc = pow(((input.k_const + 1) / 2), (1 / (input.k_const - 1))) * lamb_k_calc *
		pow(1 - ((input.k_const - 1) / (input.k_const + 1) * pow(lamb_k_calc, 2)), (1 / (input.k_const - 1)));

	//17c
	lamb_x_calc = cx_calc / 
		sqrt((2 * input.k_const / (input.k_const + 1)) * Rf_calc * thz_n1_out_calc);

	q_lamb_x_calc = pow(((input.k_const + 1) / 2), (1 / (input.k_const - 1))) * lamb_x_calc *
		pow(1 - ((input.k_const - 1) / (input.k_const + 1) * pow(lamb_x_calc, 2)), (1 / (input.k_const - 1)));

	//18a
	fv_calc = gv_calc * sqrt(thz_n1_in_calc) / (m_v_calc * (phz_n1_in * 100000) * q_lamb_v_calc);

	//18b
	fk_calc = gv_calc * sqrt(thz_n2_out_calc) / (m_v_calc * (phz_n2_out_calc * 100000) * q_lamb_k_calc);

	//18c
	fx_calc = gv_calc * sqrt(thz_n1_out_calc) / (m_v_calc * (phz_n1_out_calc * 100000) * q_lamb_x_calc);

	//18d
	fc_calc = fc_ñoeff * gv_calc;

}

