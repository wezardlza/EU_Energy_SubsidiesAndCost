/***********************************************************************************************************************
Author: Ziang Li
Institution: Control Group, UOM

	This file declares the saving and reading methods of .csv document.
***********************************************************************************************************************/
#pragma once
#ifndef SRF
#define SRF

#include "../Header_Files/ZAMATH.h"

#include <iostream>  
#include <fstream>  
#include <sstream>  
#include <string>  
#include <vector> 

typedef std::string                                  CELL;
typedef T_ROW<CELL>                                  ROW;
typedef T_TABLE<CELL>							     TABLE;


typedef T_ROW_INDEX<CELL>                            ROW_INDEX;
typedef T_ROW_SIZE<CELL>                             ROW_SIZE;
typedef T_ROWS_SIZES_VEC<CELL>                       ROWS_SIZES_VEC;
typedef T_CELLS_SIZES_VEC<CELL>                      CELLS_SIZES_VEC;

/*----------------------------------------------------------------------------------------------------------------------
These two should be the same for a single ROW object 
----------------------------------------------------------------------------------------------------------------------*/
typedef T_ROWS_SIZES_VEC_INDEX<CELL>                 ROWS_SIZES_VEC_INDEX;
typedef T_TABLE_INDEX<CELL>                          TABLE_INDEX;
/*--------------------------------------------------------------------------------------------------------------------*/

typedef T_TABLE_SIZE<CELL>                           TABLE_SIZE;
typedef T_TABLE_INDEXES_VEC<CELL>                    TABLE_INDEXES_VEC;
typedef T_TABLE_INDEXES_VEC_INDEX<CELL>              TABLE_INDEXES_VEC_INDEX;

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

#endif // !SRF