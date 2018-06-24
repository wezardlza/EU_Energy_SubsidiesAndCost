/***********************************************************************************************************************
Author: Ziang Li
Institution: Control Group, UOM

This file declares the math methods of .csv document.
***********************************************************************************************************************/

#pragma once
#ifndef ZAMATH
#define ZAMATH

#include <string>  
#include <vector> 

template <typename T> using T_ROW = std::vector<T>;
template <typename T> using T_TABLE = std::vector<T_ROW<T>>;

template <typename T> using T_ROW_INDEX = typename T_ROW<T>::size_type;
template <typename T> using T_ROW_SIZE = typename T_ROW<T>::size_type;
template <typename T> using T_ROWS_SIZES_VEC = std::vector<T_ROW_SIZE<T>>;
template <typename T> using T_CELLS_SIZES_VEC = std::vector<typename T::size_type>;

/*------------------------------------------------------------------------------------------------------------------
These two should be the same for a single ROW object
------------------------------------------------------------------------------------------------------------------*/
template <typename T> using T_ROWS_SIZES_VEC_INDEX = typename T_ROWS_SIZES_VEC<T>::size_type;
template <typename T> using T_TABLE_INDEX = typename T_TABLE<T>::size_type;
/*----------------------------------------------------------------------------------------------------------------*/

template <typename T> using T_TABLE_SIZE = typename T_TABLE<T>::size_type;
template <typename T> using T_TABLE_INDEXES_VEC = std::vector<T_TABLE_INDEX<T>>;
template <typename T> using T_TABLE_INDEXES_VEC_INDEX = typename T_TABLE_INDEXES_VEC<T>::size_type;

struct Basic_Maths
{
	// Summary: Swap the two varible values with the type of ROW_SZIE etc
	template <typename T> void static swap(T & v1, T & v2);

	// Sunnary: Compare whether v1 is larger than v2 
	//	if v1 > v2, return true
	//	if v1 <= v2, return false
	template <typename T> inline static bool compare(T & v1, T & v2);

	// Summary: Obtain the maximum value in the vector
	template <typename T> T static max(T_ROW<T> & vec);

	// Summary:: Obtain the sizes of the 2-D vector
	template <typename T> static T_ROWS_SIZES_VEC<T>
		rows_sizes_vec(T_TABLE<T> & table);

	// Summary: Obtain the rows_size sequence which can make the vector 'riv' sorted in ascending order
	// Parameters:
	// riv: a vector whose elements must be sequenced in ascending order
	// Return: the rows_size sequence of the original 'riv'
	template <typename T> static T_TABLE_INDEXES_VEC<T> ascending(T_ROWS_SIZES_VEC<T> rsv);

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

#endif // !ZAMATH
