#include "EngineData.h"
#include "InputData.h"

extern "C" {

	_declspec(dllexport) int Start(InputData* inp) {

		input.Load(inp);							//Importing input class
		input.Set_AirData_Step(inp);				//Setting AirSpeed Data
		input.Set_Coefficients(inp);				//Setting Coefficients

		Run();

		return 1;
	}
}