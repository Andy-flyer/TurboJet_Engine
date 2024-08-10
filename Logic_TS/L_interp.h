#pragma once
#include <string>
#include <iostream>
#include <fstream>

// L_int_1 y = f(x)
class L_int_1
{
public:

	int ncolumns;
	int nrows;
	int headerSize;
	int i, j;

	float map[1000][30];
	float value;
	float cell;
	float x1, x2, y1, y2;

	std::string fileName;
	std::string header;
	std::string str;
	FILE* file;


	float Calc(float x, float* output);

	float Interpolation(float x1, float x2, float y1, float y2, float xInt);
	float Extrapolation(float x1, float x2, float y1, float y2, float xExt);
	void Init(const char* filename);
	void Read();
	void Counter();
	void CountSize();
	void Write_binary(const char* fname);
	void Init_binary(const char* fname);
	void Init_log(const char* fname, FILE* logf);
	void Log_Error(const char* message);
	void Log_Info(const char* message);
	void Log_Info(const char* message, int, int, int);
	void Message(const char* message);
	int CountBranches(int param);
	int CountPoints(int param);

};


// L_int_2 y = f(x,y)
class L_int_2 : public L_int_1
{
public:

	float value1, value2, value3;
	float z1, z2, q11, q12, q21, q22;

	float Calc(float x, float y, float* output);

};


extern L_int_1 compressor_hp;
extern L_int_1 polytropic_coeff;
extern L_int_1 lpcompr;
extern L_int_1 hpcompr;
extern L_int_1 branch_lp[25];
extern L_int_1 branch_hp[25];
extern L_int_1 workpointslp;
extern L_int_1 workpointshp;
extern L_int_1 workpoints_q_lamb_x;
extern L_int_1 workpointslp_abs;
extern L_int_1 compressor_lp_lines[25];
extern L_int_1 compressor_hp_lines[25];
extern L_int_1 compressor_lp_dt;
extern L_int_1 compressor_hp_dt;
extern L_int_1 compressor_lp_p_comp_n1[25];
extern L_int_1 log_file;

extern L_int_2 compressor_lp_t_n1_coeff;
extern L_int_2 compressor_lp;
