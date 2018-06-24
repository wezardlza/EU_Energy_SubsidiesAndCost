/***********************************************************************************************************************
Author: Ziang Li
Institution: Control Group, UOM

This file defines the saving and reading methods of .csv document.
***********************************************************************************************************************/

#include <iostream>  
#include <fstream>  
#include <sstream>  
#include <string>  
#include <vector>  

typedef std::string                                  CELL;
typedef std::vector<CELL>                            ROW;
typedef std::vector<ROW>                             TABLE;


typedef ROW::size_type                               ROW_INDEX;
typedef ROW::size_type                               ROW_SIZE;
typedef std::vector<ROW_SIZE>                        ROWS_SIZES_VEC;
typedef std::vector<CELL::size_type>                 CELLS_SIZES_VEC;

// These two should be the same for a single ROW object
typedef ROWS_SIZES_VEC::size_type                    ROWS_SIZES_VEC_INDEX;
typedef TABLE::size_type                             TABLE_INDEX;

typedef TABLE::size_type                             TABLE_SIZE;
typedef std::vector <TABLE_INDEX>                    TABLE_INDEXES_VEC;
typedef TABLE_INDEXES_VEC::size_type                 TABLE_INDEXES_VEC_INDEX;

// Open the input file and form a table of the data
class Read_CSV_File
{
public:
	Read_CSV_File(const std::string & file_address);
	~Read_CSV_File();

	// Summary: Trim the string 
	static void Trim(std::string &);
	
	// Summary: Initialize 'table' and 'tiv'
	void table_init();

	// Summary: Print the table
	void print_table();

protected:

	// a input file stream based on the input .csv file 
	std::ifstream infile;

	// a table based on the input .csv file
	// a template has the original .csv file as
		// 333,22,1,4444,666666,55555
		// 22, 1, 333, 55555, 22, 4444, 333
		// 1, 333, 4444, 22, 66666
		// 333, 22, 1
		// 333, 4444, 1, 22, 55555
		// 22, 7777777, 55555, 333
		// 999999999, 55555, 1, 22, 333
		// 22, 333
	TABLE table;

	// table indexes of each row sequenced by the row sizes in the asceding order
	TABLE_INDEXES_VEC tiv; // {7, 3, 5, 2, 4, 6, 0, 1}

	// sizes of each ROW in original 'table'	
	ROWS_SIZES_VEC rsv; // {6, 7, 5, 3, 5, 4, 5, 2}	

private:
	static std::size_t count;
};

std::size_t Read_CSV_File::count(0);

struct Basic_Maths
{
	// Sunnary: Compare whether v1 is larger than v2 
	//	if v1 > v2, return true
	//	if v1 <= v2, return false
	template <typename T> inline static bool compare(T & v1, T & v2);

	// Summary: Swap the two varible values with the type of ROW_SZIE etc
	template <typename T> void static swap(T & v1, T & v2);

	// Summary: Obtain the maximum value in the vector
	template <typename T> T static max(std::vector<T> & vec);

	// Summary:: Obtain the sizes of the 2-D vector
	template <typename T> static std::vector<typename std::vector<T>::size_type>
		rows_sizes_vec(std::vector<std::vector<T>> & table);

	// Summary: Obtain the rows_size sequence which can make the vector 'riv' sorted in ascending order
	// Parameters:
	// riv: a vector whose elements must be sequenced in ascending order
	// Return: the rows_size sequence of the original 'riv'
	static TABLE_INDEXES_VEC ascending(ROWS_SIZES_VEC rsv);

};

// Summary: trim the string 
void Read_CSV_File::Trim(std::string & str)
{
	//str.find_first_not_of(" \t\r\n"),在字符串str中从索引0开始，返回首次不匹配"\t\r\n"的位置  
	str.erase(0, str.find_first_not_of(" \t\r\n"));
	str.erase(str.find_last_not_of(" \t\r\n") + 1);
}

// Sunnary: Compare whether v1 is larger than v2 
//	if v1 > v2, return true
//	if v1 <= v2, return false
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

template <typename T> T Basic_Maths::max(std::vector<T> & vec) {
	T *m = & vec[0];
	for (typename std::vector<T>::size_type i = 1; i != vec.size(); ++i) {
		if (compare(vec[i], *m)) {
			m = & vec[i];
		}
	}
	return *m;
}

template <typename T> std::vector<typename std::vector<T>::size_type>
	Basic_Maths::rows_sizes_vec(std::vector<std::vector<T>> & table) {
		std::vector<typename std::vector<T>::size_type> rsv;
		for (typename std::vector<std::vector<T>>::size_type i = 0; i != table.size(); ++i) {
			rsv.push_back(std::move(table[i].size()));
		}
		return rsv;
	}

TABLE_INDEXES_VEC Basic_Maths::ascending(ROWS_SIZES_VEC rsv) {
	
	ROWS_SIZES_VEC_INDEX i(0), j(0);
	TABLE_INDEXES_VEC tiv_x;
	const TABLE_SIZE & ts(rsv.size());
		
	for (TABLE_INDEX k = 0; k != ts; ++k) { tiv_x.push_back(k); }
	
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

Read_CSV_File::Read_CSV_File(const std::string & file_address) : infile(file_address) {
	if (!infile) { std::cerr << "error: unable to open the input file." << std::endl; }
	// initialize table, rsv and tiv
	table_init();
	rsv = Basic_Maths::rows_sizes_vec(table);
	tiv = Basic_Maths::ascending(rsv);
	++count;
}

Read_CSV_File::~Read_CSV_File() {
	--count;
}

void Read_CSV_File::table_init() {

	// declare a string for the storage of one row of data in 'infile' read from .csv file
	std::string line;	

	while (std::getline(infile, line))
	{
		// A template has the original .csv file as
		/* 333,22,1,4444,666666,55555 */
		/* 22, 1, 333, 55555, 22, 4444, 333 */
		/* 1, 333, 4444, 22, 66666 */
		/* 333, 22, 1 */
		/* 333, 4444, 1, 22, 55555 */
		/* 22, 7777777, 55555, 333 */
		/* 999999999, 55555, 1, 22, 333 */
		/* 22, 333 */

		// define a input string-based stream (ins) from line
		std::istringstream ins(line);

		ROW row;
		CELL cell;

		// execute the block when meeting "," in 'ins'; 
		// leave the block when meeting EOF in 'ins';
		// each execution also assigns 'cell' with the string stored in 'ins' seperated by ","
		while (std::getline(ins, cell, ',')) {
			Trim(cell);
			// move 'cell' to a slot in'row'
			row.push_back(std::move(cell));
		}
		table.push_back(std::move(row));
	}
}

void Read_CSV_File::print_table() {
	// loop the column 
	TABLE_INDEXES_VEC_INDEX m(0); // index for 'tiv'
	ROW_INDEX k(0);
	CELLS_SIZES_VEC cs_vec;
	while (m != tiv.size()) {

		ROWS_SIZES_VEC_INDEX & q(tiv[m]);
		while (k != rsv[q]) {

			// loop the row
			CELL::size_type cs(0);
			TABLE_INDEXES_VEC_INDEX n(m);
			while (n != tiv.size()) {
				const CELL::size_type & cs_temp = table[tiv[n]][k].size();
				if (cs < cs_temp) { cs = std::move(cs_temp); }
				++n;
			}
			cs_vec.push_back(std::move(cs));
			++k;
		}
		++m;
	}

	std::cout.setf(std::ios::left);
	CELL::size_type x(Basic_Maths::max<CELL::size_type>(cs_vec));
	for (TABLE_INDEX i = 0; i != table.size(); ++i) {
		for (ROW_INDEX j = 0; j != table[i].size(); j++) {

			std::cout.width(cs_vec[j]);
			// std::cout.width(x);

			std::cout << table[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

int main()
{
	Read_CSV_File csv("../Data_Files/TEST_1_LCOE.csv");  
	csv.print_table();

	system("pause");
}