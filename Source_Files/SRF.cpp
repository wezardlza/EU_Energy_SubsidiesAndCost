/***********************************************************************************************************************
Author: Ziang Li
Institution: Control Group, UOM

This file defines the saving and reading methods of .csv document.
***********************************************************************************************************************/
 
#include "../Header_Files/SRF.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <direct.h> 
#include <io.h> 
#include <xiosbase>
#include <stdexcept>


/*######################################################################################################################
Class 'File_Adress'
======================================================================================================================*/
/* Constructors */

File_Address::File_Address(const std::string & file_name) : file_name(file_name) { ++count; }

File_Address::~File_Address() { --count; }

/* Member functions */

const std::string File_Address::file_address() const {
	struct _stat fileStat;
	if ((_stat(directory.c_str(), & fileStat) == 0) && (fileStat.st_mode & _S_IFDIR))
	{
		std::cout << "The directory: \"" << directory << "\" already exists." << std::endl;;
	}
	else
	{
		int i = _mkdir(directory.c_str());
		if (i = 1) {
			std::cout << "The directory: \"" << directory << "\" is created." << std::endl;
		}
		else
		{
			throw std::runtime_error("Error: Fail to create the directory: \""  + directory + "\" is created.");
		}
	}
	return directory + file_name + "." + format;	
}

bool File_Address::is_file_acessible(const std::string & file_address) {
	bool b(_access(file_address.c_str(), 0) != -1);
	if (b) {
		std::cout << "Warning: The file: \"" << file_address << "\" is overwritten." << std::endl;
	}
	else {
		std::cout << "The file: \"" << file_address << "\" is created." << std::endl;
	}
	return b;
}


std::size_t File_Address::count(0);
std::string File_Address::directory("./");
std::string File_Address::format("csv");

/*######################################################################################################################
Class 'File_Stream'
======================================================================================================================*/
/* Constructors */

File_Stream::File_Stream(const std::string & file_name_, const std::string & directory, const std::string & format,
	const std::ios_base::openmode & file_mode) : file_name (file_name_) {
	File_Address::directory = directory;
	File_Address::format = format;
	File_Stream::file_mode = file_mode;
	File_Address fa(file_name);
	file_address = fa.file_address();
	file_stream();
}

/* Member functions */

std::fstream & File_Stream::file_stream() {
	if (file_mode == std::ios_base::in
		|| file_mode == (std::ios_base::in | std::ios_base::out)
		|| file_mode == (std::ios_base::in | std::ios_base::out | std::ios_base::trunc))
	{
		file.close();
		file.clear();
	}
	else if (file_mode == std::ios_base::out
		|| file_mode == (std::ios_base::out | std::ios_base::app)
		|| file_mode == (std::ios_base::out | std::ios_base::trunc))
	{
		file.close();
		file.clear();
		File_Address::is_file_acessible(file_address);
	}
	else
	{
		throw std::runtime_error("Error: Fail to recognize the open mode of the file.");
	}
	file.open(file_address, file_mode);
	if (!file) { std::cerr << "Error: Unable to open the file \"" << file_address << "/\"." << std::endl; }
	return file;
}

void File_Stream::change_file_attributes(const std::string & file_name_, const std::string & directory,
	const std::string & format, const std::ios_base::openmode & file_mode) {
	File_Address::directory = directory;
	File_Address::format = format;
	File_Stream::file_mode = file_mode;
	file_name = file_name_;
	File_Address fa(file_name);
	file_address = fa.file_address();
	file_stream();
}
void File_Stream::change_file_attributes(const std::string & file_name_, const std::string & directory,
	const std::string & format) {
	File_Address::directory = directory;
	File_Address::format = format;
	file_name = file_name_;
	File_Address fa(file_name);
	file_address = fa.file_address();
	file_stream();
}

void File_Stream::change_file_attributes(const std::ios_base::openmode & file_mode) {
	File_Stream::file_mode = file_mode;
	File_Address fa(file_name);
	file_address = fa.file_address();
	file_stream();
}

void File_Stream::change_file_attributes(const std::string & file_name_) {
	file_name = file_name_;
	File_Address fa(file_name);
	file_address = fa.file_address();
	file_stream();
}

std::size_t File_Stream::count(0);

std::ios_base::openmode File_Stream::file_mode(std::ios_base::in);


/*######################################################################################################################
Class 'Read_File'
======================================================================================================================*/
/* Constructors */

Read_File::Read_File(std::istream & infile) : infile(& infile) { ++count; }

Read_File::~Read_File() { count; }

/* Static function */

void Read_File::Trim(std::string & str)
{
	//str.find_first_not_of(" \t\r\n"),在字符串str中从索引0开始，返回首次不匹配"\t\r\n"的位置  
	str.erase(0, str.find_first_not_of(" \t\r\n"));
	str.erase(str.find_last_not_of(" \t\r\n") + 1);
}

/* Meember fucntions */

void Read_File::table_init() {

	// declare a string for the storage of one row of data in 'infile' read from .csv file
	std::string line;	
	// define a input string-based stream (ins) from line
	std::istringstream ins;

	while (std::getline(*infile, line))
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

void Read_File::print_table() {

	// sizes of each ROW in original 'table'	
	rsv = Basic_Maths::rows_sizes_vec(table);

	// table indexes of each row sequenced by the row sizes in the asceding order
	tiv = Basic_Maths::ascending<CELL>(rsv);
	
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

std::size_t Read_File::count(0);


/*######################################################################################################################
Class 'Save_File'
======================================================================================================================*/
// Friends
std::ostream & operator<<(Save_File & log, const ROW & row) {
	const ROW_SIZE & n = row.size() - 1;
	for (ROW_INDEX i = 0; i != n; ++i) {
		*log.outfile << row[i] << ", ";
	}
	*log.outfile << row[n];
	return *log.outfile;
}

std::ostream & operator<<(Save_File & log, const TABLE & table) {
	const TABLE_SIZE & n = table.size() - 1;
	for (TABLE_INDEX i = 0; i != n; ++i) {
		log << table[i] << std::endl;
	}
	log << table[n];
	return *log.outfile;
}
// Constructors
Save_File::Save_File(std::ostream & outfile) : outfile(&outfile) { ++count; }

Save_File::~Save_File() { --count; }

std::size_t Save_File::count(0);