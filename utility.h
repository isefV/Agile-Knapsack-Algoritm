#pragma once

/* ======================================================================
								  Header Files
   ====================================================================== */

#include <fstream>
#include <iostream>
#include <string>
#include <string>
#include <utility>
#include <bitset>
#include <chrono>
#include <algorithm>
#include <ctime>

/* ======================================================================
									Macros
====================================================================== */

#define STRING		std::string 
#define FS			std::fstream
#define PRINT		std::cout
#define GET			std::cin
#define CHORNO		std::chrono
#define PAIR		std::pair
#define BITSET		std::bitset
#define LLINT		long long int

#define MOST_BIT	128
#define LESS_BIT	0
#define COUNT_BIT	8

/* ======================================================================
						Definition of Utility Functions
   ====================================================================== */

bool	read_data_from_file(const STRING& file_path,const LLINT& item_size, LLINT* weight_array, LLINT* valua_array);
int		exceed_value(const LLINT* arr, LLINT start, LLINT stop, LLINT& exc_value);
int		find_index_overflow(const LLINT* arr, LLINT start, LLINT stop,const LLINT& cap, bool backward = false);
LLINT	sum_of_array(const LLINT* arr, LLINT start, LLINT stop);
void	sort_arrays_weigth_base(const LLINT& item_size, LLINT* values, LLINT* weights, bool descending = false);
void	display_info(const STRING& name, int& result, double& time, STRING* path);