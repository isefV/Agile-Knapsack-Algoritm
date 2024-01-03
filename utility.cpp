#include"utility.h"

/* ======================================================================
					Implementation of Utility Functions
   ====================================================================== */

bool read_data_from_file(const STRING& file_path, const LLINT& item_size, LLINT* weight_arr, LLINT* valua_arr) {
	FS file;
	file.open(file_path, std::ios::in);
	if (!file.is_open())
		return false;
	int index = 0;
	STRING line;
	std::getline(file, line);
	while (std::getline(file, line)) {
		unsigned int token_number = 0;
		int character = 0;
		STRING token = "";
		line += " \n";
		while (line[character] != '\n') {
			if (line[character] == ' ') {
				switch (token_number)
				{
				case 1:
					valua_arr[index] = std::atoll(&token[0]);
					break;
				case 2:
					weight_arr[index] = std::atoll(&token[0]);
					index++;
					break;
				default:
					if (item_size == std::atoll(&token[0]))
						return true;
					break;
				}

				token = "";
				token_number++;
			}
			token += line[character];
			character++;
		}
	}
	file.close();
	return true;
}

int find_index_overflow(const LLINT* arr, LLINT start, LLINT stop,const LLINT& cap,bool backward) {
	if (backward) {
		int total = 0;
		int index = stop - 1;
		while (index >= start && total < cap) {
			total += arr[index--];
			//index--;
		}
		return index;
	}
	int total = cap;
	int index = start;
	while (index < stop && total >= 0) {
		total -= arr[index++];
		//index--;
	}
	return index;

}

LLINT sum_of_array(const LLINT* array, LLINT start, LLINT stop) {
	LLINT total = 0;
	for (int index = start; index < stop; index++)
		total += array[index];
	return total;
}

int exceed_value(const LLINT* arr, LLINT start, LLINT stop, LLINT& exc_value) {
	int index = 0, diff = 0;
	while (index <= stop) {
		diff = arr[index] - exc_value;
		if (diff > 0) {
			return diff;
			break;
		}
		index++;
	}
	return -1;
}

void sort_arrays_weigth_base(const LLINT& item_size, LLINT* values, LLINT* weights,bool descending) {
	PAIR<int, int>* pairs = new PAIR<int, int>[item_size];

	for (int i = 0; i < item_size; ++i)
		pairs[i] = std::make_pair(weights[i], values[i]);

	std::sort(pairs, pairs + item_size);

	if (descending) {
		LLINT size = item_size - 1;
		for (int i = 0; i < item_size; i++) {
			weights[i] = pairs[size - i].first;
			values[i] = pairs[size - i].second;
		}
	}
	else {
		for (int i = 0; i < item_size; i++) {
			weights[i] = pairs[i].first;
			values[i] = pairs[i].second;
		}
	}

	delete[] pairs;
}

void display_info(const STRING& name, int& result, double& time, STRING* path) {
	PRINT << "\n-|" << name << "\n\t|- Value : " << result << "\n\t|- Time Excute : " << time << " sec\n";
	if ((*path) != "")
		PRINT << "\t|- Opt Path : \n" << *path << "\n\n";
	*path = "";
}