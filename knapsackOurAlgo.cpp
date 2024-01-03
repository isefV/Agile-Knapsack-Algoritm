#include"knapsackOurAlgo.h"

/* ======================================================================
					Implementation of Algorithm Functions
   ====================================================================== */

PAIR<int, double> Our_Base_Alg_1402_9_13(const LLINT& _cap, const LLINT& _items, LLINT* weight, LLINT* value) {
	auto start_time = CHORNO::high_resolution_clock::now();

	//int state_plus = 0;
	int state_minus = 0;
	int max_state = 0;
	int valua_state_plus = 0;

	const LLINT cap = _cap + 1;
	int* state_value = new int[cap]();
	bool* flag = new bool[cap]();

	flag[_cap] = true;

	for (int step = 0; step < _items; step++) {
		for (int state = weight[step]; state < cap; state++) {
			if (flag[state]) {
				valua_state_plus = state_value[state] + value[step];
				state_minus = state - weight[step];
				if (valua_state_plus > state_value[state_minus]) {
					flag[state_minus] = true;
					state_value[state_minus] = valua_state_plus;
				}
			}
		}
	}

	auto end_time = CHORNO::high_resolution_clock::now();
	CHORNO::duration<double> duration = end_time - start_time;
	int max_val = *std::max_element(state_value, state_value + cap);

	delete[] state_value;
	delete[] flag;

	return std::make_pair(max_val, duration.count());
}

PAIR<int, double> Our_BaseG_Alg_1402_10_12(const LLINT& _cap, const LLINT& _items, LLINT* weight, LLINT* value) {
	auto start_time = CHORNO::high_resolution_clock::now();

	// Algorithm Variables
	int state = 0,
		aja_state_inducing_value = 0,
		cap = _cap + 1;
	int* state_value = new int[cap]();
	bool* flag = new bool[cap]();

	// Algorithm Controller Variables
	int bkwd_cap_ovflo_index = find_index_overflow(weight, 0, _items, _cap,true) + 1;
	LLINT bkwd_wght_sum = sum_of_array(weight, bkwd_cap_ovflo_index, _items);
	LLINT aja_ceil = _cap;
	LLINT current_ceil;

	// Algorithm Starter Point
	flag[_cap] = true;

	// Algorithm Formula
	for (int step = 0; step < _items; step++) {
		for (int aja_state = weight[step]; aja_state < aja_ceil + 1; aja_state++) {
			if (flag[aja_state]) {
				state = aja_state - weight[step];
				aja_state_inducing_value = state_value[aja_state] + value[step];
				if (aja_state_inducing_value > state_value[state]) {
					flag[state] = true;
					state_value[state] = aja_state_inducing_value;
				}
			}
		}

		if (step > bkwd_cap_ovflo_index) {
			bkwd_wght_sum -= weight[step];
			current_ceil = bkwd_wght_sum - 1;
			for (int state = aja_ceil; state > current_ceil && current_ceil >= 0; state--) {
				flag[state] = false;
			}
			aja_ceil = current_ceil;
		}
	}

	auto end_time = CHORNO::high_resolution_clock::now();
	CHORNO::duration<double> duration = end_time - start_time;

	// Find The Opt Value and index of it
	int max_val = *std::max_element(state_value, state_value + aja_ceil);

	delete[] state_value;
	delete[] flag;

	return std::make_pair(max_val, duration.count());
}

PAIR<int, double> Our_8bit_Alg_1402_10_11_main(const LLINT& _cap, const LLINT& _items, LLINT* weight, LLINT* value, STRING* path) {
	auto start_time = CHORNO::high_resolution_clock::now();

	// Algorithm Variables
	int state = 0,
		aja_state_inducing_value = 0,
		cap = _cap + 1;
	int* state_value = new int[cap]();
	bool* flag = new bool[cap]();
	const int size = (_items / 8);

	// Algorithm Find Opt Path Variables
	unsigned char** pathes = new unsigned char* [cap];

	// Algorithm Controller Variables
	unsigned char bit_shifter = MOST_BIT;	// 1000 0000
	int step_bit_counter = 0;
	int bkwd_cap_ovflo_index = find_index_overflow(weight, 0, _items, _cap,true) + 1;
	LLINT bkwd_wght_sum = sum_of_array(weight, bkwd_cap_ovflo_index, _items);
	LLINT aja_ceil = _cap;
	//LLINT current_ceil;

	// Initilize Variables
	for (int index = 0; index < cap; index++) {
		unsigned char* temp = new unsigned char[size];
		std::memset(temp, LESS_BIT, size);
		pathes[index] = temp;
	}

	// Algorithm Starter Point
	flag[_cap] = true;

	// Algorithm Formula
	for (int step = 0; step < _items; step++) {
		for (int aja_state = weight[step]; aja_state < aja_ceil + 1; aja_state++) {
			if (flag[aja_state]) {
				state = aja_state - weight[step];
				aja_state_inducing_value = state_value[aja_state] + value[step];
				if (aja_state_inducing_value > state_value[state]) {
					flag[state] = true;
					state_value[state] = aja_state_inducing_value;
					memcpy(pathes[state], pathes[aja_state], size);
					pathes[state][step_bit_counter] |= bit_shifter;
				}
			}
		}

		// Update Item Number by Shift Binary like: 1000 0000 >> 0100 000
		bit_shifter >>= 1;

		// Control Shift underflow
		if (bit_shifter == LESS_BIT) {
			bit_shifter = MOST_BIT;
			step_bit_counter++;
		}

		if (step > bkwd_cap_ovflo_index) {
			bkwd_wght_sum -= weight[step];
			//current_ceil = bkwd_wght_sum - 1;
			for (int state = aja_ceil; state >= bkwd_wght_sum && bkwd_wght_sum >= 1; state--) {
				flag[state] = false;
				delete pathes[state];
			}
			aja_ceil = bkwd_wght_sum - 1;
		}
	}

	auto end_time = CHORNO::high_resolution_clock::now();
	CHORNO::duration<double> duration = end_time - start_time;

	// Find The Opt Value and index of it
	int max_val = *std::max_element(state_value, state_value + aja_ceil);
	int opt_index = -1;
	for (int index = 0; index < aja_ceil; ++index) {
		if (state_value[index] == max_val) {
			opt_index = index;
			break;
		}
	}

	// Find The Opt Path Over Shift to right byte by byte
	int step = 1;
	int byte;
	for (int i = 0; i < size; i++) {
		if (pathes[opt_index][i] == LESS_BIT) {
			step += COUNT_BIT;
			continue;
		}
		byte = int(pathes[opt_index][i]);
		bit_shifter = MOST_BIT;
		while (bit_shifter) {
			if (bit_shifter & byte)
				*path += std::to_string(step) + ' ';
			bit_shifter >>= 1;
			step++;
		}
	}

	// Free Memory
	delete[] state_value;
	delete[] flag;
	for (int index = 0; index < aja_ceil; index++)
		delete pathes[index];

	return std::make_pair(max_val, duration.count());
}

PAIR<int, double> Our_8bitMountain_Alg_1402_10_12_test(const LLINT& _cap, const LLINT& _items, LLINT* weight, LLINT* value, STRING* path) {
	auto start_time = CHORNO::high_resolution_clock::now();

	// Algorithm Variables
	int state = 0,
		aja_state_inducing_value = 0,
		cap = _cap + 1;
	int* state_value = new int[cap]();
	bool* flag = new bool[cap]();
	const int size = (_items / 8);

	// Algorithm Find Opt Path Variables
	unsigned char** pathes = new unsigned char* [cap];

	// Algorithm Controller Variables
	unsigned char bit_shifter = MOST_BIT;	// 1000 0000
	int step_bit_counter = 0;
	int bkwd_cap_ovflo_index = find_index_overflow(weight, 0, _items, _cap,true) + 1;
	LLINT bkwd_wght_sum = sum_of_array(weight, bkwd_cap_ovflo_index, _items);
	LLINT aja_ceil = _cap;

	sort_arrays_weigth_base(bkwd_cap_ovflo_index, value, weight, false);

	// @_DEBUG_CODE
	//for (int i = 0; i < _items; i++)
	//	PRINT << weight[i] << ' ' << value[i] << '\n';
	//PRINT << '\n';
	int p = 0;

	// Initilize Variables
	for (int index = 0; index < cap; index++) {
		unsigned char* temp = new unsigned char[size];
		std::memset(temp, LESS_BIT, size);
		pathes[index] = temp;
	}

	// Algorithm Starter Point
	flag[_cap] = true;

	// Algorithm Formula
	for (int step = 0; step < _items; step++) {
		for (int aja_state = weight[step]; aja_state < aja_ceil + 1; aja_state++) {
			if (flag[aja_state]) {
				state = aja_state - weight[step];
				aja_state_inducing_value = state_value[aja_state] + value[step];
				if (aja_state_inducing_value > state_value[state]) {
					flag[state] = true;
					state_value[state] = aja_state_inducing_value;
					memcpy(pathes[state], pathes[aja_state], size);
					pathes[state][step_bit_counter] |= bit_shifter;
				}
			}
		}

		// Update Item Number by Shift Binary like: 1000 0000 >> 0100 000
		bit_shifter >>= 1;

		// Control Shift underflow
		if (bit_shifter == LESS_BIT) {
			bit_shifter = MOST_BIT;
			step_bit_counter++;
		}

		if (step > bkwd_cap_ovflo_index) {
			bkwd_wght_sum -= weight[step];
			for (int state = aja_ceil; state >= bkwd_wght_sum && bkwd_wght_sum >= 1; state--) {
				flag[state] = false;
				delete pathes[state];
			}
			aja_ceil = bkwd_wght_sum - 1;
		}
	}

	auto end_time = CHORNO::high_resolution_clock::now();
	CHORNO::duration<double> duration = end_time - start_time;

	// Find The Opt Value and index of it
	int max_val = *std::max_element(state_value, state_value + aja_ceil);
	int opt_index = -1;
	for (int index = 0; index < aja_ceil; ++index) {
		if (state_value[index] == max_val) {
			opt_index = index;
			break;
		}
	}

	// Find The Opt Path Over Shift to right byte by byte
	int step = 1;
	int byte;
	for (int i = 0; i < size; i++) {
		if (pathes[opt_index][i] == LESS_BIT) {
			step += COUNT_BIT;
			continue;
		}
		byte = int(pathes[opt_index][i]);
		bit_shifter = MOST_BIT;
		while (bit_shifter) {
			if (bit_shifter & byte)
				*path += std::to_string(step) + ' ';
			bit_shifter >>= 1;
			step++;
		}
	}

	// Free Memory
	delete[] state_value;
	delete[] flag;
	for (int index = 0; index < aja_ceil; index++)
		delete pathes[index];

	return std::make_pair(max_val, duration.count());
}

PAIR<int, double> Our_8bitMountain2_Alg_1402_10_12_test(const LLINT& _cap, const LLINT& _items, LLINT* weight, LLINT* value, STRING* path) {
	auto start_time = CHORNO::high_resolution_clock::now();

	// Algorithm Variables
	int state = 0,
		aja_state_inducing_value = 0,
		cap = _cap + 1;
	int* state_value = new int[cap]();
	bool* flag = new bool[cap]();
	const int size = (_items / 8);

	// Algorithm Find Opt Path Variables
	unsigned char** pathes = new unsigned char* [cap];

	// Algorithm Controller Variables
	unsigned char bit_shifter = MOST_BIT;	// 1000 0000
	int step_bit_counter = 0;
	int bkwd_cap_ovflo_index = find_index_overflow(weight, 0, _items, _cap , true) + 1;
	int frwd_cap_ovflo_index = find_index_overflow(weight, 0, _items, _cap , false);
	int cap_ovflo_index = std::min(bkwd_cap_ovflo_index, frwd_cap_ovflo_index);

	LLINT bkwd_wght_sum = sum_of_array(weight, bkwd_cap_ovflo_index, _items);
	LLINT aja_ceil = _cap;
	LLINT aja_floor = _cap;
	LLINT aja_floor_temp;

	LLINT ZERO = 0;

	sort_arrays_weigth_base(bkwd_cap_ovflo_index, value, weight, false);

	// Initilize Variables
	for (int index = 0; index < cap; index++) {
		unsigned char* temp = new unsigned char[size];
		std::memset(temp, LESS_BIT, size);
		pathes[index] = temp;
	}

	// Algorithm Starter Point
	flag[_cap] = true;

	// Algorithm Formula
	for (int step = 0; step < cap_ovflo_index; step++) {
		for (int aja_state = aja_floor; aja_state <= aja_ceil; aja_state++) {
			if (flag[aja_state]) {
				state = aja_state - weight[step];
				//if (state > 0) {
				aja_state_inducing_value = state_value[aja_state] + value[step];
				if (aja_state_inducing_value > state_value[state]) {
					flag[state] = true;
					state_value[state] = aja_state_inducing_value;
					memcpy(pathes[state], pathes[aja_state], size);
					pathes[state][step_bit_counter] |= bit_shifter;
				}
				//}
			}
		}

		// Update Item Number by Shift Binary like: 1000 0000 >> 0100 000
		bit_shifter >>= 1;

		// Control Shift underflow
		if (bit_shifter == LESS_BIT) {
			bit_shifter = MOST_BIT;
			step_bit_counter++;
		}


		aja_floor_temp =  aja_floor - weight[step] ;
		auto minfloor = weight[cap_ovflo_index] > weight[step] ? weight[step] : weight[cap_ovflo_index];
		if (aja_floor_temp >= minfloor)
			aja_floor = aja_floor_temp;
			//aja_floor = aja_floor_temp  > 0 ? aja_floor_temp :0 ;
			//aja_floor = std::max(ZERO, aja_floor_temp);
		

	}

	for (int step = cap_ovflo_index; step < _items; step++) {
		for (int aja_state = weight[step]; aja_state <= aja_ceil; aja_state++) {
			if (flag[aja_state]) {
				state = aja_state - weight[step];
				aja_state_inducing_value = state_value[aja_state] + value[step];
				if (aja_state_inducing_value > state_value[state]) {
					flag[state] = true;
					state_value[state] = aja_state_inducing_value;
					memcpy(pathes[state], pathes[aja_state], size);
					pathes[state][step_bit_counter] |= bit_shifter;
				}
			}
		}

		// Update Item Number by Shift Binary like: 1000 0000 >> 0100 000
		bit_shifter >>= 1;

		// Control Shift underflow
		if (bit_shifter == LESS_BIT) {
			bit_shifter = MOST_BIT;
			step_bit_counter++;
		}

		if (step > bkwd_cap_ovflo_index) {
			bkwd_wght_sum -= weight[step];
			for (int state = aja_ceil; state >= bkwd_wght_sum && bkwd_wght_sum >= 1; state--) {
				flag[state] = false;
				delete pathes[state];
			}
			aja_ceil = bkwd_wght_sum - 1;
		}
	}

	auto end_time = CHORNO::high_resolution_clock::now();
	CHORNO::duration<double> duration = end_time - start_time;

	// Find The Opt Value and index of it
	int max_val = *std::max_element(state_value, state_value + aja_ceil);
	int opt_index = -1;
	for (int index = 0; index < aja_ceil; ++index) {
		if (state_value[index] == max_val) {
			opt_index = index;
			break;
		}
	}

	// Find The Opt Path Over Shift to right byte by byte
	int step = 1;
	int byte;
	for (int i = 0; i < size; i++) {
		if (pathes[opt_index][i] == LESS_BIT) {
			step += COUNT_BIT;
			continue;
		}
		byte = int(pathes[opt_index][i]);
		bit_shifter = MOST_BIT;
		while (bit_shifter) {
			if (bit_shifter & byte)
				*path += std::to_string(step) + ' ';
			bit_shifter >>= 1;
			step++;
		}
	}

	// Free Memory
	delete[] state_value;
	delete[] flag;
	for (int index = 0; index < aja_ceil; index++)
		delete pathes[index];

	return std::make_pair(max_val, duration.count());
}
