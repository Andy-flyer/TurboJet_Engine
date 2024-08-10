#include "InputData.h"
#include "EngineData.h"
#include "math.h"

InputData input;

void InputData::Load(InputData* inp) {
	//Constant
	k_const	= inp->k_const;
	t_const = inp->t_const;
	hu_const = inp->hu_const;
	c_hc_air_const = inp->c_hc_air_const;
	kf_const = inp->kf_const;
	r_const = inp->r_const;

	//Configuration values
	sigma_confg	= inp->sigma_confg;
	p_comp_n1_confg = inp->p_comp_n1_confg;
	p_comp_n2_confg = inp->p_comp_n2_confg;
	tg_confg = inp->tg_confg;
	eff_cmb_confg = inp->eff_cmb_confg;
	g_bleed_confg = inp->g_bleed_confg;
	g_cool_confg = inp->g_cool_confg;
	eff_mech_confg = inp->eff_mech_confg;
	sigma_cmb_confg = inp->sigma_cmb_confg;
	eff_turb_hp_confg = inp->eff_turb_hp_confg;
	eff_turb_lp_confg = inp->eff_turb_lp_confg;
	f_jn_confg = inp->f_jn_confg;
	thrust_confg = inp->thrust_confg * 1000;
	cv_confg = inp->cv_confg;
	ck_confg = inp->ck_confg;
	eff_coeff_n1_confg = inp->eff_coeff_n1_confg;
	eff_coeff_n2_confg = inp->eff_coeff_n2_confg;

	//Height
	min_height = inp->min_height;
	numb_of_height = inp->numb_of_height;
	max_height = inp->max_height;

	//Speed
	min_speed = inp->min_speed;
	numb_of_speed = inp->numb_of_speed;
	max_speed = inp->max_speed;

	//Temperature
	min_temperature	= inp->min_temperature;
	numb_of_temperature	= inp->numb_of_temperature;
	max_temperature	= inp->max_temperature;

	//FilePaths
	filePathLP = inp->filePathLP;
	filePathHP = inp->filePathHP;
	filePathResult = inp->filePathResult;
}


void InputData::Set_AirData_Step(InputData* inp) {
	float interval, step = 0.;

	//Calculating the interval, minimun and maximum value of the height
	interval = step = input.max_height / (input.numb_of_height - 1);

	eng.height[0] = input.min_height;

	for (int i = 1; i < input.numb_of_height; i++) {
		eng.height[i] = interval;
		interval += step;
	}

	//Calculating the interval, minimun and maximum value of the speed
	interval = step = input.max_speed / (input.numb_of_speed - 1);

	eng.speed[0] = input.min_speed;

	for (int i = 1; i < input.numb_of_speed; i++) {
		eng.speed[i] = interval;
		interval += step;
	}

	//Calculating the interval, minimun and maximum value of the temperature
	interval = step = (input.max_temperature + fabs(input.min_temperature)) / (input.numb_of_temperature - 1);

	eng.dt[0] = input.min_temperature;

	for (int i = 1; i < input.numb_of_temperature; i++) {
		eng.dt[i] = input.min_temperature + interval;
		interval += step;
	}

}


void InputData::Set_Coefficients(InputData* inp) {

	eng.c_1 = (input.k_const / (input.k_const - 1));	// = 3.5
	eng.c_2 = ((input.k_const - 1) / input.k_const);	// = 0.2857142857
	eng.c_3 = (input.kf_const / (input.kf_const - 1));	// = 4.0303030303

	eng.c_f = 0.85f;									// = 0.85
	eng.h_f = 0.15f;									// = 0.15

}