#include "L_interp.h"
#include <windows.h>

// L_int_1 y = f(x)
float L_int_1::Calc(float x, float* output) {

	if ((x >= map[0][0]) && (x <= map[nrows-1][0])) {
		for (int i = 0, j = 0; i < nrows; i++) {

			if (x == map[i][j])
			{
				for (int j = 0; j < ncolumns; j++) {
					output[j] = map[i][j];
				}
				return *output;
			}

			else if (x < map[i][j]) {
				output[j] = x;

				x1 = map[i - 1][j];
				x2 = map[i][j];

				for (int j = 1; j < ncolumns; j++) {
					y1 = map[i-1][j];
					y2 = map[i][j];
					value = Interpolation(x1, x2, y1, y2, x);
					output[j] = value;
				}
				return *output;
			}
		}
	}

	else {
		output[0] = x;

		x1 = map[0][0];
		x2 = map[nrows-1][0];

		for (int j = 1; j < ncolumns; j++) {
			y1 = map[0][j];
			y2 = map[nrows-1][j];
			value = Extrapolation(x1, x2, y1, y2, x);
			output[j] = value;
		}
	}
	return *output;

}


float L_int_1::Interpolation(float x1, float x2, float y1, float y2, float xInt) {
	return y1 + (y2 - y1) / (x2 - x1) * (xInt - x1);
}


float L_int_1::Extrapolation(float x1, float x2, float y1, float y2, float xExt) {
	return y1 + (xExt - x1) / (x2 - x1) * (y2 - y1);
}


void L_int_1::Init(const char* fname) {
	fileName = fname;
	Read();
}


void L_int_1::Read() {
	std::ifstream File(fileName);

	Counter();

	if (File.is_open()) {
		std::getline(File, header);

		for (int i = 0; i < nrows; i++) {
			for (int j = 0; j < ncolumns; j++) {
				File >> cell;
				map[i][j] = cell;
			}
		}

		File.close();
	}

}


void L_int_1::Write_binary(const char* fname) {
	std::ofstream ofs(fname, std::ios::out | std::ios::binary);

	if (ofs.is_open()) {
		ofs.write((char*)&map, sizeof(map));
	}
	ofs.close();

}


void L_int_1::Init_binary(const char* fname) {
	std::ifstream ifs(fname, std::ios::in | std::ios::binary);

	if (ifs.is_open()) {
		ifs.read((char*)&map, sizeof(map));
	}
	ifs.close();

	CountSize();

}


void L_int_1::Init_log(const char* fname, FILE* logf) {
	fileName = fname;
	file = logf;
}


void L_int_1::Log_Error(const char* message) {
	HWND hwnd = GetDesktopWindow();

	SYSTEMTIME tm;
	GetLocalTime(&tm);

	fprintf_s(file, "%02d.%02d.%02d %02d:%02d:%02d.%03d\t", tm.wDay,
		tm.wMonth, tm.wYear - 2000, tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds);

	fprintf_s(file, "%s\n", message);

	MessageBoxA(hwnd, message, "Error", MB_OK | MB_ICONERROR);
}


void L_int_1::Log_Info(const char* message) {
	SYSTEMTIME tm;
	GetLocalTime(&tm);

	fprintf_s(file, "%02d.%02d.%02d %02d:%02d:%02d.%03d\t", tm.wDay,
		tm.wMonth, tm.wYear - 2000, tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds);

	fprintf_s(file, "%s\n", message);
}


void L_int_1::Log_Info(const char* message, int t, int i, int j) {
	SYSTEMTIME tm;
	GetLocalTime(&tm);

	fprintf_s(file, "%02d.%02d.%02d %02d:%02d:%02d.%03d\t", tm.wDay,
		tm.wMonth, tm.wYear - 2000, tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds);

	fprintf_s(file, "%s %02d dt %02d Km %02d M\n", message, t, i, j);
}


void L_int_1::Message(const char* message) {
	HWND hwnd = GetDesktopWindow();

	MessageBoxA(hwnd, message, "Error", MB_OK | MB_ICONERROR);
}


void L_int_1::Counter() {
	std::ifstream File(fileName);
	ncolumns = nrows = 0;

	if (File.is_open()) {

		std::getline(File, header);
		headerSize = header.length();

		for (int i = 0; i < headerSize; i++) {
			if (header[i] == '\t') {
				ncolumns++;
				i++;
			}
		}
		ncolumns++;

	}

	if (File.is_open()) {
		while (!File.eof())
		{
			std::getline(File, str);

			if (str != "")
				nrows++;
		}
	}

	File.close();

}


void L_int_1::CountSize() {
	i = j = 0;
	nrows = ncolumns = 0;

	while (map[i][0] != 0.) {
		nrows++;
		i++;
	}

	while (map[0][j] != 0.) {
		ncolumns++;
		j++;
	}

}


int L_int_1::CountBranches(int param) {
	int nbranches = 1;

	value = map[0][param];

	for (int i = 0; i < nrows; i++) {

		if (map[i][param] != value)
		{
			value = map[i][param];
			nbranches++;
		}
	}

	return nbranches;

}


int L_int_1::CountPoints(int param) {
	int npoints = 0;

	i = 0;

	value = map[0][param];

	while (value == map[i][param]) {
		i++;
		npoints++;
	}

	return npoints;

}


// L_int_2 y = f(x,y)
float L_int_2::Calc(float x, float y, float* output) {

	if (((x >= map[0][0]) && (x <= map[nrows-1][0])) && ((y >= map[0][1]) && (y <= map[nrows-1][1]))) {
		for (int i = 0, j = 0; i < nrows; i++) {

			if (x == map[i][j] || y == map[i][j + 1]) {
				if (x == map[i][j] && y == map[i][j+1]) {
					for (int j = 0; j < ncolumns; j++) {
						output[j] = map[i][j];
					}
					return *output;
				}

				else if (x == map[i][j] && y < map[i][j+1]) {
					output[j] = map[i][j];

					x1 = x2 = map[i][j];
					y1 = map[i-1][j+1];
					y2 = map[i][j+1];

					for (int j = 2; j < ncolumns; j++) {
						z1 = map[i - 1][j];
						z2 = map[i][j];

						value = Interpolation(y1, y2, z1, z2, y);

						output[j] = value;
					}
					return *output;
				}
			}

			if (x < map[i][j] && y < map[i][j+1]) {
				output[j] = x;

				x2 = map[i][j];
				q21 = map[i-1][j+2];
				q22 = map[i][j+2];

				for (int i = nrows - 1, j = 0; i >= 0; i--) {

					if (x >= map[i][j] && y >= map[i][j+1])
					{
						x1 = map[i][j];

						y1 = map[i][j+1];
						y2 = map[i+1][j+1];

						if (y == map[i][j+1]) {
							for (int j = 2; j < ncolumns; j++) {
								q11 = map[i][j];
								q12 = map[i+1][j];

								value1 = Interpolation(x1, x2, q11, q21, x);
								value2 = Interpolation(x1, x2, q12, q22, x);
								value3 = Interpolation(y1, y2, value1, value2, y);

								output[j] = value3;

								return *output;
							}
						}

						else {
							for (int j = 2; j < ncolumns; j++) {
								q11 = map[i][j];
								q12 = map[i+1][j];

								value1 = Interpolation(x1, x2, q22, q21, x);
								value2 = Interpolation(x1, x2, q12, q11, x);
								value3 = Interpolation(y1, y2, value1, value2, y);

								output[j] = value3;
							}
							return *output;
						}
					}
				}
			}
		}
	}

	else {
		output[0] = x;

		x1 = map[0][0];
		x2 = map[nrows-1][0];

		y1 = map[0][1];
		y2 = map[nrows-1][1];

		for (int j = 2; j < ncolumns; j++) {
			q11 = map[0][j];
			q12 = map[nrows-1][j];

			value1 = Extrapolation(x1, x2, q22, q21, x);
			value2 = Extrapolation(x1, x2, q12, q11, x);
			value3 = Extrapolation(y1, y2, value1, value2, y);

			output[j] = value3;

		}
		return *output;

	}

	return *output;

}

