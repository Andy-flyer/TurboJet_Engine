#include <stdio.h>
#include "EngineData.h"
#include "InputData.h"
#include "L_interp.h"


EngineData eng;

L_int_1 compressor_hp;
L_int_1 polytropic_coeff;
L_int_1 lpcompr;
L_int_1 hpcompr;
L_int_1 branch_lp[25];
L_int_1 branch_hp[25];
L_int_1 workpointslp;
L_int_1 workpointshp;
L_int_1 workpoints_q_lamb_x;
L_int_1 workpointslp_abs;
L_int_1 compressor_lp_lines[25];
L_int_1 compressor_hp_lines[25];
L_int_1 compressor_lp_dt;
L_int_1 compressor_hp_dt;
L_int_1 compressor_lp_p_comp_n1[25];
L_int_1 log_file;

L_int_2 compressor_lp_t_n1_coeff;
L_int_2 compressor_lp;

FILE* logfile;

FILE* in1;
FILE* in2;
FILE* in3;
FILE* in4;

FILE* table_in1;
FILE* table_in2;

FILE* fuel_out;


#define FILE_LOG "..\\..\\Logic_TS\\logfile\\log.txt"

#define FILE_1 "..\\..\\Logic_TS\\data\\polytropic_coeff.txt"
#define FILE_2 "..\\..\\Logic_TS\\data\\p_comp_n1_t_coeff.txt"

#define FILE_TABLE_1 "..\\..\\Logic_TS\\data\\polytropic_coeff.dat"
#define FILE_TABLE_2 "..\\..\\Logic_TS\\data\\p_comp_n1_t_coeff.dat"


static float outf[60];


void Init() {

	//Initializing LogFile
	errno_t err_log;
	err_log = fopen_s(&logfile, FILE_LOG, "a");

	if (err_log == 0)
	{
		log_file.Init_log(FILE_LOG, logfile);
		log_file.Log_Info("The file log.txt was opened.");
	}

	else
	{
		log_file.Message("The file log.txt was not opened");
	}

	//Initializing EngData Files
	errno_t err_in1, err_in2, err_in3, err_in4, err_table1, err_table2;

	err_in1 = fopen_s(&in1, FILE_1, "r");
	err_in2 = fopen_s(&in2, FILE_2, "r");
	err_in3 = fopen_s(&in3, input.filePathLP, "r");
	err_in4 = fopen_s(&in4, input.filePathHP, "r");

	err_table1 = fopen_s(&table_in1, FILE_TABLE_1, "r");
	err_table2 = fopen_s(&table_in2, FILE_TABLE_2, "r");

	if (err_in1 == 0)
	{

		if (err_table1 == 0) {
			log_file.Log_Info("The file polytropic_coeff.dat was opened.");
			polytropic_coeff.Init_binary(FILE_TABLE_1);
		}

		else {
			polytropic_coeff.Init(FILE_1);
			polytropic_coeff.Write_binary(FILE_TABLE_1);
		}

	}
	else
	{
		if (err_table1 == 0) {
			log_file.Log_Info("The file polytropic_coeff.dat was opened.");
			polytropic_coeff.Init_binary(FILE_TABLE_1);
		}

		else {
			log_file.Log_Error("The file polytropic_coeff.dat was not opened");
			return;
		}

	}

	if (err_in2 == 0)
	{

		if (err_table2 == 0) {
			log_file.Log_Info("The file p_comp_n1_t_coeff.dat was opened.");
			compressor_lp_t_n1_coeff.Init_binary(FILE_TABLE_2);
		}

		else {
			compressor_lp_t_n1_coeff.Init(FILE_2);
			compressor_lp_t_n1_coeff.Write_binary(FILE_TABLE_2);
		}

	}
	else
	{
		if (err_table2 == 0) {
			log_file.Log_Info("The file p_comp_n1_t_coeff.dat was opened.");
			compressor_lp_t_n1_coeff.Init_binary(FILE_TABLE_2);
		}

		else {
			log_file.Log_Error("The file p_comp_n1_t_coeff.dat was not opened");
			return;
		}

	}

	if (err_in3 == 0)
	{
		log_file.Log_Info("The file with LP-compressor data was opened.");
		compressor_lp.Init(input.filePathLP);
	}
	else
	{
		log_file.Log_Error("The file with LP-compressor data was not opened");
		return;
	}

	if (err_in4 == 0)
	{
		log_file.Log_Info("The file with HP-compressor data was opened.");
		compressor_hp.Init(input.filePathHP);
	}
	else
	{
		log_file.Log_Error("The file with HP-compressor data was not opened");
		return;
	}

	//Initializing Results Files
	errno_t err_out1;
	err_out1 = fopen_s(&fuel_out, input.filePathResult, "w");

	if (err_out1 == 0)
	{
		log_file.Log_Info("The file with results was opened.");
	}
	else
	{
		log_file.Log_Error("The result file was not opened");
	}

}


void Run() {

	Init();

	eng.Design_Values(0., 0.);	//Calculating design values of engine characteristics


	//Header in result file
	fprintf_s(fuel_out, "%s\t"	"%s\t"	"%s\t"	"%s\t"		"%s\t"			"%s\t"				"%s\t"		"%s\t"		"%s\t"	"%s\t"			"%s\t"		"%s\t"	"%s\t"		"%s\t"		"%s\t"				"%s\t"				"%s\t"	"%s\t"			"%s\t"			"%s\t"	"%s\t"			"%s\t"		"%s\t"			"%s\t"			"%s\t"  "%s\t"				"%s\t"			"%s\t"				"%s\t"						"%s\t"			"%s\t"				"%s\t"				"%s\t"				"%s\t"				"%s\t"				"%s\t"				"%s\t"				"%s\t"	"%s\t"				"%s\t"		"%s\t"			"%s\n",
						"H",	"M",	"dt",	"n2_rel",	"p_comp_n1",	"t_turbine_n2_in",	"q_lamb_v", "eff_lp",	"gv",	"p_comp_n2",	"n1_rel",	"slip", "eff_hp",	"q_lamb_x", "thz_n1_out_inter",	"phz_n1_out_inter",	"l_n1", "thz_n2_out",	"phz_n2_out",	"l_n2", "phz_n1_out",	"q_lamb_k", "c_heat_cap",	"q_comb_cham",	"gf",	"p_turbine_n2_in",	"l_turbine_n2", "p_turbine_n2_out", "t_turbine_n2_cooled_out",	"l_turbine_n1", "p_turbine_n1_out", "t_turbine_n1_out", "p_ratio_nozzle",	"c_nozzle_speed",	"thrust_specific",	"thrust_relative",	"fuel_flow_spec",	"p_gg", "fuel_flow_hour",	"l_cycle",	"intern_eff",	"p_comp_sum");

	for (int t = 0; t < input.numb_of_temperature; t++) {	//iteration by temperature
		for (int i = 0; i < input.numb_of_height; i++) {	//iteration by height
			for (int j = 0; j < input.numb_of_speed; j++) {	//iteration by speed

				eng.Calc_HP_Compressor(t, i, j);				//calculation of the HP-compressor
				eng.Calc_LP_Compressor(t, i, j);				//calculation of the LP-compressor

				for (int k = 0; k < workpointslp_abs.nrows; k++) {
					eng.Calc_Air_Speed_Data(t, i, j, k);		//calculation of AirSpeed data

					outf[0] = eng.height[i];
					outf[1] = eng.speed[j];
					outf[2] = eng.dt[t];
					outf[3] = eng.n2_relative;
					outf[4] = eng.p_comp_n1;
					outf[5] = eng.t_turbine_n2_in;
					outf[6] = eng.q_lamb_v;
					outf[7] = eng.eff_lp_compr;
					outf[8] = eng.gv;
					outf[9] = eng.p_comp_n2;
					outf[10] = eng.n1_relative;
					outf[11] = eng.slipping;
					outf[12] = eng.eff_hp_compr;
					outf[13] = eng.q_lamb_x;
					outf[14] = eng.thz_n1_out_internal;
					outf[15] = eng.phz_n1_out_internal;
					outf[16] = eng.l_n1;
					outf[17] = eng.thz_n2_out;
					outf[18] = eng.phz_n2_out;
					outf[19] = eng.l_n2;
					outf[20] = eng.phz_n1_out;
					outf[21] = eng.q_lamb_k;
					outf[22] = eng.c_heat_cap;
					outf[23] = eng.q_comb_cham;
					outf[24] = eng.gf;
					outf[25] = eng.p_turbine_n2_in;
					outf[26] = eng.l_turbine_n2;
					outf[27] = eng.p_turbine_n2_out;
					outf[28] = eng.t_turbine_n2_cooled_out;
					outf[29] = eng.l_turbine_n1;
					outf[30] = eng.p_turbine_n1_out;
					outf[31] = eng.t_turbine_n1_out;
					outf[32] = eng.p_ratio_nozzle;
					outf[33] = eng.c_nozzle_speed;
					outf[34] = eng.thrust_specific;
					outf[35] = eng.thrust_relative;
					outf[36] = eng.fuel_flow_specific;
					outf[37] = eng.pgg;
					outf[38] = eng.fuel_flow_hour;
					outf[39] = eng.l_cycle;
					outf[40] = eng.intern_eff;
					outf[41] = eng.p_comp_sum;


					//					"H",		"M",		"dt",		"n2_rel",	"p_comp_n1",	"t_turbine_n2_in",	"q_lamb_v", "eff_lp",	"gv",		"p_comp_n2",	"n1_rel", "slip",	"eff_hp", "q_lamb_x",	"thz_n1_out_inter",	"phz_n1_out_inter",	"l_n1",		"thz_n2_out",	"phz_n2_out",	"l_n2",		"phz_n1_out",	"q_lamb_k", "c_heat_cap",	"q_comb_cham",	"gf",		"p_turbine_n2_in",	"l_turbine_n2",	"p_turbine_n2_out", "t_turbine_n2_cooled_out", "l_turbine_n1", "p_turbine_n1_out", "t_turbine_n1_out",	"p_ratio_nozzle",	"c_nozzle_speed",	"thrust_specific",	"thrust_relative",	"fuel_flow_spec",	"p_gg",		"fuel_flow_hour",	"l_cycle",	"intern_eff",	"p_comp_sum"
					fprintf_s(fuel_out, "%2.1f\t"	"%1.1f\t"	"%3.0f\t"	"%1.3f\t"	"%2.2f\t"		"%4.1f\t"			"%1.4f\t"	"%1.3f\t"	"%3.1f\t"	"%2.3f\t"		"%1.2f\t" "%1.3f\t" "%1.3f\t" "%1.4f\t"		"%3.1f\t"			"%2.4f\t"			"%7.0f\t"	"%4.1f\t"		"%2.4f\t"		"%7.0f\t"	"%2.4f\t"		"%1.3f\t"	"%1.4f\t"		"%4.3f\t"		"%0.5f\t"	"%2.4f\t"			"%7.0f\t"		"%2.4f\t"			"%4.1f\t"					"%7.0f\t"		"%1.4f\t"			"%4.1f\t"			"%2.3f\t"			"%4.1f\t"			"%4.1f\t"			"%3.3f\t"			"%1.4f\t"			"%1.3f\t"	"%4.0f\t"			"%7.0f\t"	"%0.3f\t"		"%3.2f\n",
										outf[0],	outf[1],	outf[2],	outf[3],	outf[4],		outf[5],			outf[6],	outf[7],	outf[8],	outf[9],		outf[10], outf[11], outf[12], outf[13],		outf[14],			outf[15],			outf[16],	outf[17],		outf[18],		outf[19],	outf[20],		outf[21],	outf[22],		outf[23],		outf[24],	outf[25],			outf[26],		outf[27],			outf[28],					outf[29],		outf[30],			outf[31],			outf[32],			outf[33],			outf[34],			outf[35],			outf[36],			outf[37],	outf[38],			outf[39],	outf[40],		outf[41]);
				}
			}
		}
	}

	log_file.Log_Info("Model: Stop calcultating.");
	log_file.Log_Info("Stop");

	_fcloseall();

}