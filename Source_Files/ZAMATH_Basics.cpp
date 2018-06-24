/***********************************************************************************************************************
Author: Ziang Li
Institution: Control Group, UOM

This file defines the saving and reading methods of .csv document.
***********************************************************************************************************************/

#include "../Header_Files/ZAMATH.h"

template <typename T> T Basic_Maths::max(T_ROW<T> & vec) {
	T *m = &vec[0];
	for (T_ROW_INDEX<T> i = 1; i != vec.size(); ++i) {
		if (compare(vec[i], *m)) {
			m = &vec[i];
		}
	}
	return *m;
}

template <typename T> T_ROWS_SIZES_VEC<T>
	Basic_Maths::rows_sizes_vec(T_TABLE<T> & table) {
		T_ROWS_SIZES_VEC<T> rsv;
		for (T_TABLE_INDEX<T> i = 0; i != table.size(); ++i) {
			rsv.push_back(std::move(table[i].size()));
		}
		return rsv;
	}

template <typename T>
T_TABLE_INDEXES_VEC<T> Basic_Maths::ascending(T_ROWS_SIZES_VEC<T> rsv) {
	T_ROWS_SIZES_VEC_INDEX<T> i(0), j(0);
	T_TABLE_INDEXES_VEC<T> tiv_x;
	const T_TABLE_SIZE<T> & ts = rsv.size();
	for (T_TABLE_INDEX<T> k = 0; k != ts; ++k) { tiv_x.push_back(k); }

	while (j != rsv.size()) {
		i = 0;
		while (i != rsv.size() - j - 1) {
			if (Basic_Maths::compare(rsv[i], rsv[i + 1])) {
				Basic_Maths::swap(rsv[i], rsv[i + 1]);
				Basic_Maths::swap(tiv_x[i], tiv_x[i + 1]);
			}
			++i;
		}
		++j;
	}
	return tiv_x;
}
