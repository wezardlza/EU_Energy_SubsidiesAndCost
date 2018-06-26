/***********************************************************************************************************************
Author: Ziang Li
Institution: Control Group, UOM

This file declares the math methods of .csv document.
***********************************************************************************************************************/

#pragma once
#ifndef ZAMATH
#define ZAMATH

#include "../Header_Files/ZAMATH_ALIAS.h"
#include <string>  
#include <vector> 
#include <sstream>


namespace Basic_Maths
{
	// Summary: Swap the two varible values with the type of ROW_SZIE etc
	template <typename T> void swap(T & v1, T & v2);

	// Sunnary: Compare whether v1 is larger than v2 
	//	if v1 > v2, return true
	//	if v1 <= v2, return false
	template <typename T> inline bool compare(T & v1, T & v2);

	// Summary: Obtain the maximum value in the vector
	template <typename T> T max(T_ROW<T> & vec);

	// Summary:: Obtain the sizes of the 2-D vector
	template <typename T> T_ROWS_SIZES_VEC<T> rows_sizes_vec(T_TABLE<T> & table);

	// Summary: Obtain the rows_size sequence which can make the vector 'riv' sorted in ascending order
	// Parameters:
	// riv: a vector whose elements must be sequenced in ascending order
	// Return: the rows_size sequence of the original 'riv'
	template <typename T> T_TABLE_INDEXES_VEC<T> ascending(T_ROWS_SIZES_VEC<T> rsv);

	// Summary: Cast the conversion from T to string
	template <typename T> inline std::string string_cast(const T & data);

	// Summary: Cast the conversion from string to T
	template <typename T> T inline num_cast(const std::string & str);
};

/*######################################################################################################################
Struct 'Basic_Maths'
======================================================================================================================*/

template <typename T> bool Basic_Maths::compare(T & v1, T & v2) {
	if (v1 > v2) { return true; }
	else { return false; }
}


template <typename T> void Basic_Maths::swap(T & v1, T & v2) {
	T temp;
	temp = std::move(v1);
	v1 = std::move(v2);
	v2 = std::move(temp);
}


template <typename T> std::string Basic_Maths::string_cast(const T & num) {
	std::ostringstream stream;
	stream.setf(std::ostringstream::fixed);
	stream << num;
	return stream.str();
}

template <typename T> T Basic_Maths::num_cast(const std::string & str) {
	std::istringstream ins(str);
	T num;
	ins >> num;
	return num;
}

// #include "../Source_Files/ZAMATH.cpp"

#endif // !ZAMATH
