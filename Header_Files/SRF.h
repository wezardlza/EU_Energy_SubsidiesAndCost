/***********************************************************************************************************************
Author: Ziang Li
Institution: Control Group, UOM

	This file declares the saving and reading methods of .csv document.
***********************************************************************************************************************/
#pragma once
#ifndef SRF
#define SRF

#include "../Header_Files/ZAMATH.h"
#include "../Header_Files/SRF_ALIAS.h"

#include <iostream>  
#include <fstream>  
#include <sstream>  
#include <string>  
#include <vector> 

class File_Address {
public:
	File_Address(const std::string & name);
	~File_Address();

	static std::string directory;
	static std::string format;
	std::string name;
	std::string file_address();

private:
	static std::size_t count;
};

// Open the input file and form a table of the data
class Read_File
{
public:

	Read_File(const std::string & file_name, const std::string & directory, const std::string & format = "csv");
	Read_File(const std::string & file_name);
	~Read_File();

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


class Save_File : public std::ofstream
{
public:

	Save_File(const std::string & file_address);
	~Save_File();

	// Summary: Check if the file already exists
	static bool open_file_check(const std::string & file_address);

	// Summary: Record the record in a row
	void save_row(ROW & row, const std::string & file_address);

	// Summary£º Record the records in the table
	void save_table(TABLE table, const std::string & file_address);


protected:

	// Summary: Record the record in a row
	void _save_row(ROW & row);

private:
	static std::size_t count;

};


#endif // !SRF