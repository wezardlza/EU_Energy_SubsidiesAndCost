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

class File_Address 
{
public:
	// Summary: Construct an address to store the file
	// name: name of the file 
	File_Address(const std::string & file_name);
	~File_Address();

	// directory of the succeeding files, default is "./" 
	static std::string directory;

	// format of the succeeding files, default is ".csv"  
	static std::string format;

	// name of the file 
	std::string file_name;
	
	// Summary: Address of the file 
	const std::string file_address() const;
	
	// Summary: Check if the file already exists.
	// This method is called when a file is about to be written.
	static bool is_file_acessible(const std::string & file_address);

private:
	static std::size_t count;
};


class File_Stream 
{
public:
	// Summary: Construct an address to store the file
	// file_name: name of the file
	// directory: directory of the succeeding files, default is "./" 
	// format: format of the succeeding files, default is ".csv" 
	// file_mode: file mode of the succeeding files, default is "std::ios_base::in"
	File_Stream(const std::string & file_name, const std::string & directory, const std::string & format, 
		const std::ios_base::openmode & file_mode);

	~File_Stream();

	static std::ios_base::openmode file_mode;
	
	// Summary: Change the name, directory, format, or open mode of the file
	void change_file_attributes(const std::string & file_name, const std::string & directory, 
		const std::string & format, const std::ios_base::openmode & file_mode);

	// Summary: Change the name, directory, or format of the file
	void change_file_attributes(const std::string & file_name, const std::string & directory,
		const std::string & format);

	// Summary: Change the openmode of the file
	void change_file_attributes(const std::ios_base::openmode & file_mode);

	// Summary: Change the name of the file
	void change_file_attributes(const std::string & file_name);

	// Summary :Get the name of the open file
	inline const std::string & get_file_name() const;

	// Summary: Get the address of the open file
	inline const std::string & get_file_address() const;

	// file stream
	std::fstream file;
	
private:
	// Summary: Retrun stream
	std::fstream & file_stream();

	// file name
	std::string file_name;

	// file address
	std::string file_address;

	static std::size_t count;
};


class Read_File
{
public:

	Read_File(std::istream & infile);
	~Read_File();

	// Summary: Trim the string 
	static void Trim(std::string &);

	// Summary: Initialize 'table' and 'tiv'
	void table_init();

	// Summary: Print the table
	void print_table();

	// Summary: Obtain the TABLE object
	const TABLE & get_table() const;

	// Summary: If the line is started by '#', skip to the next line of the istream
	static void is_sharp_sign(std::istream infile);

	// Summary: Assign the Read_File object a new input stream pointer member
	std::istream * new_infile(std::istream & new_istream);

	// a input file stream based on the input .csv file 
	std::istream * infile;

protected:

	// a table based on the input .csv file
	TABLE table;

	// table indexes of each row sequenced by the row sizes in the asceding order
	TABLE_INDEXES_VEC tiv; // {7, 3, 5, 2, 4, 6, 0, 1}

	// sizes of each ROW in original 'table'	
	ROWS_SIZES_VEC rsv; // {6, 7, 5, 3, 5, 4, 5, 2}	

private:
	static std::size_t count;
};


class Save_File 
{
	// Summary: Write the ROW in the open file
	friend std::ostream & operator<<(Save_File & log, const ROW & row);
	
	// Summary: Write the ROW in the open file
	friend std::ostream & operator<<(Save_File & log, const TABLE & table);

public:
	Save_File(std::ostream & outfile);
	~Save_File();

	// Summary: Assign the Save_File object a new output stream pointer member
		std::ostream * new_outfile(std::ostream & new_ostream);

	std::ostream * outfile;
	
private:
	static std::size_t count;

};


/* Inline functions */

inline const std::string & File_Stream::get_file_name() const { return file_name; }

inline const std::string & File_Stream::get_file_address() const { return file_address; }


/*######################################################################################################################
Constant values
======================================================================================================================*/

namespace CONST_LABEL {
	extern const std::string INFO;
	extern const std::string WARN;
	extern const std::string ERRO;
};


#endif // !SRF