▀▀█▀▀ █──█ █▀▀█ █▀▀▄ █▀▀█ ───░█ █▀▀ ▀▀█▀▀ 　 ░█▀▀▀ █▀▀▄ █▀▀▀ ─▀─ █▀▀▄ █▀▀ 
─░█── █──█ █▄▄▀ █▀▀▄ █──█ ─▄─░█ █▀▀ ──█── 　 ░█▀▀▀ █──█ █─▀█ ▀█▀ █──█ █▀▀ 
─░█── ─▀▀▀ ▀─▀▀ ▀▀▀─ ▀▀▀▀ ░█▄▄█ ▀▀▀ ──▀── 　 ░█▄▄▄ ▀──▀ ▀▀▀▀ ▀▀▀ ▀──▀ ▀▀▀


README
	TurboJet Engine is a program for calculating the altitude-speed and throttle characteristics of turbojet engines on any engine operating modes with a reduced amount of data input.
	The program provides a wide temperature range with large deviation from Standart Atmosphere. The result of the program calculation is a large array of data with a large number of the altitude-speed and throttle engine characteristics.
	In demo mode, the program provides calculations only for a twin-shaft turbojet engine.

INSTALLATION
	The program does not require any pre installations, and can operate on Windows 7, 10, 11 operation systems. The size of the program with source code on disk is 17 MB, without source code is 13.2 MB.

OPERATING INSTRUCTIONS
	To calculate the altitude-speed and throttle characteristics, you must perform the following steps:
	1. Launch the program using the "TurboJet_Engine.exe" program located in the installed directory ...\TurboJet_Engine\TurboJet_Interface\bin\TurboJet_Engine.exe.
	2. After starting the program, click the "START" button on the first form of the application.
	3. In the next step, select the type of engine required for the calculation (in demo-mode of the program, only a two-shaft turbojet engine is available). After selection, click the "SELECT" button.
	4. On the third application form, select the paths to compressors characteristics location:
		- Select the path to the location of the .txt-file with the characteristics of the low pressure compressor.
		- Select the path to the location of the .txt-file with the characteristics of the high pressure compressor.

	(!) In demo mode, by default, the program has the default compressor characteristics low-pressure.txt and high-pressure.txt in the program directory path \TurboJet_Engine\Logic_TS\compressor_data

	(!) .txt-files with compressors characteristics must be in a strict format (Please, see .txt file format at the bottom of this section).
	After selection, click the "CONTINUE" button.

	5. In the next step, enter the engine characteristics for calculation. 
		- The first controlbox shows the names of engine characteristics. 
		- The second controlbox contains data of the minimum and maximum ranges of the concrete characteristic.
		- The third controlbox purposed for entering of engine characteristics.
	(!) In demo mode, by default, characteristics are already inserted into this form.

	6. In the next step, click the "Atmospheric conditions" button to enter the airspeed ranges for calculation.
		- The first controlbox shows the names of airspeed characteristics. 
		- The second controlbox contains data of the minimum and maximum ranges of the concrete characteristic.
		- The third controlbox purposed for entering of airspeed range.
	(!) In demo mode, by default, this ranges are already inserted into this form.
	After the inserting of this data, click the "Set" button.

	7. In the next step, click on the "Constants" button to enter the values of the constants for the calculation.
	(!) In demo mode, by default, constants for calculation are already inserted into this form.

	After the inserting of this data, click the "Set" button.

	8. After completing all of the above steps, click the "Calculate" button. It is necessary to select a directory to save the results of calculating altitude-speed and throttle characteristics. The program only supports .txt file format for saving.

	9. The program will take some time for calculation. After the calculation is completed, the label "Completed!" will appear in the lower right corner of the form, and a catalog will open with the saved result of calculating the altitude-speed and throttle characteristics.

	10. To see the calculation result, open the .txt file in the directory that opens after calculation.
	(!) For a description of the abbreviations of characteristics in the output file with the results, see at the file OUTPUT_LIST.TXT file located in the parent directory of the program.
	
	The program able to calculate the altitude-speed and throttle characteristics with the edited engine and airspeed characteristics again without closing the program.

	11. After the finish of program usage, close the program.


	(!) FILE FORMAT WITH COMPRESSORS CHARACTERISTICS

	By default, the files with compressor characteristics located in the program directory path \TurboJet_Engine\Logic_TS\compressor_data

	The compressor characteristics should contain the compressor pressure lines with the same fixed number of points on every line.
	
	The file must be only in .txt format, and contain the following data:
	- The first column (n_comp) should  contain engine speed of the pressure line.
	- The second column (P_comp) should contain the value of the air pressure increase ratio at the compressor.
	- The third column (q_l) should contain the relative air flow density at the compressor inlet.
	- The fourth column (eff_comp) should contain the adiabatic efficiency of the compressor.

	The data in the compressor data file should be arranged in increasing order, sorted first by engine speed (n_comp), and second by air pressure increase ratio (P_comp).
	Data must be specified without empty strings between pressure lines and without empty cells between the columns.

FILE MANIFEST
	OUTPUT_LIST.TXT - list, with a description of the abbreviations of characteristics in the output file with the results

LIST OF KNOWN BUGS
	1. Some problems, with correct calculation of the value of air pressure increase ratio at the LP-compressor.
	2. The results are calculated only with air bleed and anti-ice system running.
	3. Some problems with form hiding.
