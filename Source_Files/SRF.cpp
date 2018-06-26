/***********************************************************************************************************************
Author: Ziang Li
Institution: Control Group, UOM

This file defines the saving and reading methods of .csv document.
***********************************************************************************************************************/
 
#include "../Header_Files/SRF.h"
#include <io.h>


/*######################################################################################################################
Class 'Read_CSV_File'
======================================================================================================================*/

// Constructors
Read_CSV_File::Read_CSV_File(const std::string & file_address) : infile(file_address) {
	if (!infile) { std::cerr << "Error: unable to open the input file." << std::endl; }
	// initialize table, rsv and tiv
	table_init();
	rsv = Basic_Maths::rows_sizes_vec(table);
	tiv = Basic_Maths::ascending<CELL>(rsv);
	++count;
}

Read_CSV_File::~Read_CSV_File() {
	--count;
}

// Static function
void Read_CSV_File::Trim(std::string & str)
{
	//str.find_first_not_of(" \t\r\n"),在字符串str中从索引0开始，返回首次不匹配"\t\r\n"的位置  
	str.erase(0, str.find_first_not_of(" \t\r\n"));
	str.erase(str.find_last_not_of(" \t\r\n") + 1);
}

// Meember fucntions
void Read_CSV_File::table_init() {

	// declare a string for the storage of one row of data in 'infile' read from .csv file
	std::string line;	
	// define a input string-based stream (ins) from line
	std::istringstream ins;

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

		ins.clear();
		ins.str(line);

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

std::size_t Read_CSV_File::count(0);


/*######################################################################################################################
Class 'Save_CSV_File'
======================================================================================================================*/
// Constructors
Save_CSV_File::Save_CSV_File(const std::string & file_address) { ++count; }
Save_CSV_File::~Save_CSV_File() { --count; }

// Member functions
bool Save_CSV_File::open_file_check(const std::string & file_address) {
	bool b(_access(file_address.c_str(), 0) != -1);
	if (b) {
		std::cout << "Warning: The file " << file_address << " is overwritten." << std::endl;
	}
	else {
		std::cout << "The file " << file_address << " is created." << std::endl;
	}
	return b;
}

void Save_CSV_File::_save_row(ROW & row) {
	ROW_SIZE n(row.size() - 1);
	for (ROW_INDEX i = 0; i < n; ++i) {
		outfile << row[i]<< ",";
	}
	outfile << row[n] << std::endl;
}

void Save_CSV_File::save_row(ROW & row, const std::string & file_address) {
	outfile.close();
	outfile.clear();
	if (Save_CSV_File::open_file_check(file_address));
	outfile.open(file_address.c_str(), std::fstream::out);
	Save_CSV_File::_save_row(row);
}

void Save_CSV_File::save_table(TABLE table, const std::string & file_address) {
	outfile.close();
	outfile.clear();
	Save_CSV_File::open_file_check(file_address);
	outfile.open(file_address.c_str(), std::fstream::out);
	TABLE_SIZE n(table.size());
	for (TABLE_INDEX i = 0; i != n; ++i) {
		Save_CSV_File::_save_row(table[i]);
	}

}


std::size_t Save_CSV_File::count(0);