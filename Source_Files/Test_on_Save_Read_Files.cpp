/***********************************************************************************************************************
Author: Ziang Li
Institution: Control Group, UOM

This file tests the reading and saving functions.
***********************************************************************************************************************/

#include "../Header_Files/SRF.h"

int main()
{
	Read_CSV_File csv("../Data_Files/TEST_1_LCOE.csv");
	csv.print_table();
	system("pause");
}