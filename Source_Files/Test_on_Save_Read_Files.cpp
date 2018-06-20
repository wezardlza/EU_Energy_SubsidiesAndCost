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

typedef std::vector<std::vector<std::string>>  TABLE;
typedef std::vector<std::string>  ROW;
typedef std::vector<ROW::size_type> ROWS_SIZE;
typedef std::vector<ROWS_SIZE::size_type> ROWS_SIZE_INDEXES;

//删除字符串中空格，制表符tab等无效字符  
void Trim(std::string & str)
{
	//str.find_first_not_of(" \t\r\n"),在字符串str中从索引0开始，返回首次不匹配"\t\r\n"的位置  
	str.erase(0, str.find_first_not_of(" \t\r\n"));
	str.erase(str.find_last_not_of(" \t\r\n") + 1);
}

// Sunnary: Compare whether v1 is larger than v2 
//	if v1 > v2, return true
//	if v1 <= v2, return false
inline bool compare(ROW::size_type & v1, ROW::size_type & v2) {
	if (v1 > v2) { return true; }
	else { return false; }
}

// Summary: Swap the two varible values
bool swap(ROW::size_type & v1, ROW::size_type & v2) {
	ROW::size_type temp;
	temp = std::move(v1);
	v1 = std::move(v2);
	v2 = std::move(temp);
}

// Summary: Obtain the index sequence which can make the vector 'vec' sorted in ascending order
// Parameters:
// vec: a vector whose elements must be sequenced in ascending order
// Return: the index sequence of the original 'vec'
ROWS_SIZE ascending(ROWS_SIZE vec) {
	
	ROWS_SIZE::size_type i(0), j(0);
	ROWS_SIZE index;
	
	for (/*initialized*/; i != vec.size(); ++i) { index.push_back(i); }
	
	while (j != vec.size()) {
		i = j;
		while (i != vec.size()) {
			if (compare(vec[i], vec[i + 1])) {
				swap(vec[i], vec[i + 1]);
				swap(index[i], index[i + 1]);
			}
			++i;
		}
		++j;
	}
	return index;
}

int main()
{
	// open the input file
	std::ifstream infile("../Data_Files/TEST_1_LCOE.csv");  
	if (!infile) { std::cerr << "error: unable to open the input file." << std::endl; }

	// declare a string for the storage of a temp line in 'infile'
	std::string line;

	// declare a table to store the data in 'infile' 
	std::vector<std::vector<std::string>> table;

	// define the index of the current row
	TABLE::size_type row_index(0);

	// declare an index vector 'rows_size' which stores the number of columns of each 'row' of 'table'
	ROWS_SIZE rows_size;
	ROWS_SIZE::size_type rows_size_index(0);

	// execute the block when meeting '\n' in 'infile';
	// leave the block when meeting EOF in 'infile'
	// each execution also assigns 'line' with the string stored in 'infile' seperated by "\n"
	while (std::getline(infile, line))   
	{

		// define a input string-based stream (ins) from line
		std::istringstream ins(line);  

		std::vector<std::string> row;
		std::string cell;
		
		// execute the block when meeting "," in 'ins'; 
		// leave the block when meeting EOF in 'ins';
		// each execution also assigns 'cell' with the string stored in 'ins' seperated by ","
		while (std::getline(ins, cell, ','))   
		{
			Trim(cell);
			// move 'cell' to a slot in'row'
			row.push_back(std::move(cell));  
		}
		table.push_back(std::move(row));
		rows_size.push_back(table[row_index].size());
		++row_index;		
	}
	rows_size = ascending(rows_size);

	for (TABLE::size_type r = 0; r != table.size(); ++r) {
		for (; rows_size_index != rows_size.size(); ++rows_size_index) {

		}
	}
	for (std::vector<std::string>::size_type i_c = 0; i_c != iter_r->end(); ++iter_c) {
		for (std::vector<std::vector<std::string>>::iterator iter_r = table.begin(); iter_r != table.end(); ++iter_r) {

		}
	}
	system("pause");
}