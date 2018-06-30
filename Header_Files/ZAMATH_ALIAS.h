/***********************************************************************************************************************
Author: Ziang Li
Institution: Control Group, UOM

This file defines the template class aliases.
***********************************************************************************************************************/
#pragma once
#ifndef __ZAMATH_ALIAS__
#define __ZAMATH_ALIAS__

#include <vector>

template <typename T> using T_ROW = std::vector<T>;
template <typename T> using T_TABLE = std::vector<T_ROW<T>>;

template <typename T> using T_ROW_INDEX = typename T_ROW<T>::size_type;
template <typename T> using T_ROW_SIZE = typename T_ROW<T>::size_type;
template <typename T> using T_ROWS_INDEXES_VEC = std::vector<T_ROW_INDEX<T>>;
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

#endif // !__ZAMATH_ALIAS__
