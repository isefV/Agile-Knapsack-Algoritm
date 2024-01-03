#include"main.h"

/* ======================================================================
									MAIN APP
   ====================================================================== */

int main(int argc, char* argv[]) {

	LLINT CAPACITY = 1000000, ITEMS = 1000;
	STRING FILEPATH = "test_n_1000_c_1000000_g_10_f_0.3_eps_0.1_s_300.in";
	char* str_format = new char[90];
	PAIR<int, double> result;
	STRING* const PATH = new STRING;
	*PATH = "";

	//PRINT << "\t.: WELLCOME TO KNAPSACK OUR ALGO :.\n\n";
	//if (argc == 1) {
	//	PRINT << "-| Enter The CAPACITY size : ";
	//	GET >> CAPACITY;
	//	PRINT << "-| Enter The ITEM size : ";
	//	GET >> ITEMS;
	//	PRINT << "-| Enter The FILE PATH : ";
	//	GET >> FILEPATH;
	//}
	//else {
	//	CAPACITY = std::atoll(argv[1]);
	//	ITEMS = std::atoll(argv[2]);
	//	FILEPATH = argv[3];
	//}


	time_t now = time(0);
	ctime_s(str_format,90,&now);
	PRINT << "\n\tALGORITHM STARTED AT " << str_format ;
	delete[] str_format;

	LLINT* weight = new LLINT[ITEMS];
	LLINT* value = new LLINT[ITEMS];

	if (!read_data_from_file(FILEPATH, ITEMS, weight , value)) {
		PRINT << "\n!!! ERR : [ Faild To Open File ]\n";
		return 0;
	}
	// @_DEBUG_CODE
	//for (int i = 0; i < ITEMS; i++)
	//	PRINT << weight[i] << ' ' << value[i] << '\n';
	//PRINT << '\n';

	if (sum_of_array(weight, 0, ITEMS) < CAPACITY) {
		PRINT << "\n!!! ERR :  [ Sum of weights is less than the Capacity ]\n";
		return 0;
	}
	else if (exceed_value(weight, 0, ITEMS, CAPACITY) > 0) {
		PRINT << "\n!!! ERR : [ Some weights exceed the Capacity ]\n";
		return 0;
	}
	else 
		sort_arrays_weigth_base(ITEMS,value, weight,true);


	//		# Our Aglorithm #
	//result = Our_Base_Alg_1402_9_13(CAPACITY, ITEMS,weight, value);
	//display_info("Our Algo Base Boolean", result.first, result.second, PATH);

	result = Our_8bit_Alg_1402_10_11_main(CAPACITY, ITEMS, weight, value, PATH);
	display_info("Our Algo 8bit 2", result.first, result.second, PATH);

	return 1;
}