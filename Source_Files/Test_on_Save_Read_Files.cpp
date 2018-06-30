/***********************************************************************************************************************
Author: Ziang Li
Institution: Control Group, UOM

This file tests the reading and saving functions.
***********************************************************************************************************************/

#include "../Header_Files/SRF.h"
#include "../Header_Files/EUSAC.h"

namespace escn = eu_subsidies_and_cost;

int main()
{

	// Set the cammand window size
	// system("mode con cols=170 lines=45  ");

	// Default investment plant specifications
	extern escn::Physical_Quantity C0;
	extern escn::Physical_Quantity LB0;
	extern escn::Physical_Quantity LT0;
	extern escn::Physical_Quantity FOM0;
	extern escn::Physical_Quantity VOM0;
	extern escn::Physical_Quantity P_E0;
	extern escn::Physical_Quantity P_H0;
	extern escn::Physical_Quantity FC0;
	extern escn::Physical_Quantity REV0;
	extern escn::Physical_Quantity dv0;
	extern escn::Physical_Quantity FLH_E0;
	extern escn::Physical_Quantity FLH_H0;
	extern escn::Coefficient d0;
	extern escn::Coefficient r0;
	extern escn::Coefficient i0;
	extern escn::Coefficient etaE0;
	extern escn::Coefficient etaH0;
	extern escn::Physical_Quantity EP0;
	extern escn::Physical_Quantity HP0;


/***********************************************************************************************************************
	TEST ON SAVING DEFAULT PLANT SPECIFICATIONS
***********************************************************************************************************************/

	// Construct default investments
	escn::LCOH plantA;
	escn::LCOE plantB;
	escn::LCOH_CHP plantC;
	escn::LCOE_CHP plantD;


	/*##################################################################################################################
	Test on LCOH object 
	==================================================================================================================*/
	// test on output file stream
	std::cout << "=============================================================================\n" 
		<< "Test on output file stream for LCOH Plant\n" 
		<<"-----------------------------------------------------------------------------" << std::endl;
	File_Stream A_file_strm("LCOH_origin", "../Data_Files/TEST_on_Save_Read_Files/", "csv", std::iostream::out);
	Save_File A_file_saving(A_file_strm.file);
	A_file_saving << plantA << std::endl;
	
	// test on standard output stream
	std::cout << "=============================================================================\n"
		<< "Test on standard output stream for LCOH Plant\n"
		<< "-----------------------------------------------------------------------------" << std::endl;
	A_file_saving.new_outfile(std::cout);
	A_file_saving << plantA << std::endl;
	

	/*################################################################################################################## 
	Test on LCOE object
	==================================================================================================================*/
	// test on output file stream
	std::cout << "=============================================================================\n"
		<< "Test on output file stream for LCOE Plant\n"
		<< "-----------------------------------------------------------------------------" << std::endl;
	File_Stream B_file_strm("LCOE_origin", "../Data_Files/TEST_on_Save_Read_Files/", "csv", std::iostream::out);
	Save_File B_file_saving(B_file_strm.file);
	B_file_saving << plantB << std::endl;

	// test on standard output stream
	std::cout << "=============================================================================\n"
		<< "Test on standard output stream for LCOE Plant\n"
		<< "-----------------------------------------------------------------------------" << std::endl;
	B_file_saving.new_outfile(std::cout);
	B_file_saving << plantB << std::endl;


	/*##################################################################################################################
	Test on LCOH_CHP object
	==================================================================================================================*/
	// test on output file stream
	std::cout << "=============================================================================\n"
		<< "Test on output file stream for LCOH_CHP Plant\n"
		<< "-----------------------------------------------------------------------------" << std::endl;
	File_Stream C_file_strm("LCOH_CHP_origin", "../Data_Files/TEST_on_Save_Read_Files/", "csv", std::iostream::out);
	Save_File C_file_saving(C_file_strm.file);
	C_file_saving << plantC << std::endl;

	// test on standard output stream
	std::cout << "=============================================================================\n"
		<< "Test on standard output stream for LCOH_CHP Plant\n"
		<< "-----------------------------------------------------------------------------" << std::endl;
	C_file_saving.new_outfile(std::cout);
	C_file_saving << plantC << std::endl;


	/*##################################################################################################################
	Test on LCOE_CHP object
	==================================================================================================================*/
	// test on output file stream
	std::cout << "=============================================================================\n"
		<< "Test on output file stream for LCOE_CHP Plant\n"
		<< "-----------------------------------------------------------------------------" << std::endl;
	File_Stream D_file_strm("LCOE_CHP_origin", "../Data_Files/TEST_on_Save_Read_Files/", "csv", std::iostream::out);
	Save_File D_file_saving(D_file_strm.file);
	D_file_saving << plantD << std::endl;

	// test on standard output stream
	std::cout << "=============================================================================\n"
		<< "Test on standard output stream for LCOE_CHP Plant\n"
		<< "-----------------------------------------------------------------------------" << std::endl;
	D_file_saving.new_outfile(std::cout);
	D_file_saving << plantD << std::endl;

/***********************************************************************************************************************
TEST ON SAVING MODIFIED PLANT SPECIFICATIONS
***********************************************************************************************************************/
	
	// Original investment plant specifications
	plantA.LT.change_magnitude(30.0);
	plantB.change_FLH_E(6000.0);
	plantC.change_EP(0.035);
	plantD.change_HP(2.0);


	/*##################################################################################################################
	Test on LCOH object
	==================================================================================================================*/
	// test on output file stream
	std::cout << "=============================================================================\n"
		<< "Test on output file stream for LCOH Plant\n"
		<< "-----------------------------------------------------------------------------" << std::endl;
	A_file_strm.change_file_attributes("LCOH");
	A_file_saving.new_outfile(A_file_strm.file);
	A_file_saving << plantA << std::endl;

	// test on standard output stream
	std::cout << "=============================================================================\n"
		<< "Test on standard output stream for LCOH Plant\n"
		<< "-----------------------------------------------------------------------------" << std::endl;
	A_file_saving.new_outfile(std::cout);
	A_file_saving << plantA << std::endl;


	/*##################################################################################################################
	Test on LCOE object
	==================================================================================================================*/
	// test on output file stream
	std::cout << "=============================================================================\n"
		<< "Test on output file stream for LCOE Plant\n"
		<< "-----------------------------------------------------------------------------" << std::endl;
	B_file_strm.change_file_attributes("LCOE", "../Data_Files/TEST_on_Save_Read_Files/", "csv");
	B_file_saving.new_outfile(B_file_strm.file);
	B_file_saving << plantB << std::endl;

	// test on standard output stream
	std::cout << "=============================================================================\n"
		<< "Test on standard output stream for LCOE Plant\n"
		<< "-----------------------------------------------------------------------------" << std::endl;
	B_file_saving.new_outfile(std::cout);
	B_file_saving << plantB << std::endl;


	/*##################################################################################################################
	Test on LCOH_CHP object
	==================================================================================================================*/
	// test on output file stream
	std::cout << "=============================================================================\n"
		<< "Test on output file stream for LCOH_CHP Plant\n"
		<< "-----------------------------------------------------------------------------" << std::endl;
	C_file_strm.change_file_attributes("LCOH_CHP");
	C_file_saving.new_outfile(C_file_strm.file);
	C_file_saving << plantC << std::endl;

	// test on standard output stream
	std::cout << "=============================================================================\n"
		<< "Test on standard output stream for LCOH_CHP Plant\n"
		<< "-----------------------------------------------------------------------------" << std::endl;
	C_file_saving.new_outfile(std::cout);
	C_file_saving << plantC << std::endl;


	/*##################################################################################################################
	Test on LCOE_CHP object
	==================================================================================================================*/
	// test on output file stream
	std::cout << "=============================================================================\n"
		<< "Test on output file stream for LCOE_CHP Plant\n"
		<< "-----------------------------------------------------------------------------" << std::endl;
	D_file_strm.change_file_attributes("LCOE_CHP");
	D_file_saving.new_outfile(D_file_strm.file);
	D_file_saving << plantD << std::endl;

	// test on standard output stream
	std::cout << "=============================================================================\n"
		<< "Test on standard output stream for LCOE_CHP Plant\n"
		<< "-----------------------------------------------------------------------------" << std::endl;
	D_file_saving.new_outfile(std::cout);
	D_file_saving << plantD << std::endl;


/***********************************************************************************************************************
TEST ON READING DEFAULT PLANT SPECIFICATIONS
***********************************************************************************************************************/


	/*##################################################################################################################
	Test on LCOH object
	==================================================================================================================*/
	std::cout << "=============================================================================\n"
		<< "Test on reading file for LCOH Plant from file LCOH_origin.csv\n"
		<< "-----------------------------------------------------------------------------" << std::endl;
	A_file_strm.change_file_attributes("LCOH_origin", "../Data_Files/TEST_on_Save_Read_Files/", 
		"csv", std::ifstream::in);
	Read_File A_file_reading(A_file_strm.file);
	A_file_reading >> plantA;

	std::cout << "-----------------------------------------------------------------------------\n"
		<< "Check specifications for LCOH Plant from file LCOH_origin.csv\n" 
		<< "-----------------------------------------------------------------------------" << std::endl;
	A_file_saving.new_outfile(std::cout);
	A_file_saving << plantA << std::endl;


	/*##################################################################################################################
	Test on LCOE object
	==================================================================================================================*/
	std::cout << "=============================================================================\n"
		<< "Test on reading file for LCOE Plant from file LCOE_origin.csv\n"
		<< "-----------------------------------------------------------------------------" << std::endl;
	B_file_strm.change_file_attributes("LCOE_origin", "../Data_Files/TEST_on_Save_Read_Files/",
		"csv", std::ifstream::in);
	Read_File B_file_reading(B_file_strm.file);
	B_file_reading >> plantB;

	std::cout << "-----------------------------------------------------------------------------\n"
		<< "Check specifications for LCOE Plant from file LCOE_origin.csv\n" 
		<< "-----------------------------------------------------------------------------" << std::endl;
	B_file_saving.new_outfile(std::cout);
	B_file_saving << plantB << std::endl;


	/*##################################################################################################################
	Test on LCOH_CHP object
	==================================================================================================================*/
	std::cout << "=============================================================================\n"
		<< "Test on reading file for LCOH_CHP Plant from file LCOH_CHP_origin.csv\n"
		<< "-----------------------------------------------------------------------------" << std::endl;
	C_file_strm.change_file_attributes("LCOH_CHP_origin", "../Data_Files/TEST_on_Save_Read_Files/",
		"csv", std::ifstream::in);
	Read_File C_file_reading(C_file_strm.file);
	C_file_reading >> plantC;

	std::cout << "-----------------------------------------------------------------------------\n"
		<< "Check specifications for LCOH_CHP Plant from file LCOH_CHP_origin.csv\n"
		<< "-----------------------------------------------------------------------------" << std::endl;
	C_file_saving.new_outfile(std::cout);
	C_file_saving << plantC << std::endl;


	/*##################################################################################################################
	Test on LCOE_CHP object
	==================================================================================================================*/
	std::cout << "=============================================================================\n"
		<< "Test on reading file for LCOE_CHP Plant from file LCOE_CHP_origin.csv\n"
		<< "-----------------------------------------------------------------------------" << std::endl;
	D_file_strm.change_file_attributes("LCOE_CHP_origin", "../Data_Files/TEST_on_Save_Read_Files/",
		"csv", std::ifstream::in);
	Read_File D_file_reading(D_file_strm.file);
	D_file_reading >> plantD;

	std::cout << "-----------------------------------------------------------------------------\n"
		<< "Check specifications for LCOE_CHP Plant from file LCOE_CHP_origin.csv\n"
		<< "-----------------------------------------------------------------------------" << std::endl;
	D_file_saving.new_outfile(std::cout);
	D_file_saving << plantD << std::endl;


/***********************************************************************************************************************
TEST ON READING MODIFIED PLANT SPECIFICATIONS 
***********************************************************************************************************************/
	
	// Used to move istream cursor to the next line
	std::string buffer;

	std::cout << "=============================================================================\n"
		<< "Test on reading file for LCOH Plant from file LCOH.csv\n"
		<< "-----------------------------------------------------------------------------" << std::endl;
	A_file_strm.change_file_attributes("LCOH", "../Data_Files/TEST_on_Save_Read_Files/",
		"csv", std::ifstream::in);
	A_file_reading.new_infile(A_file_strm.file);

	// the first line is neglected for typeset
	std::getline(*A_file_reading.infile, buffer);
	std::cout << buffer << std::endl;
	
	A_file_reading.table_init();
	A_file_reading.print_table();
	std::cout << std::endl;

	std::cout << "=============================================================================\n"
		<< "Test on file for LCOE Plant from file LCOE.csv\n"
		<< "-----------------------------------------------------------------------------" << std::endl;
	B_file_strm.change_file_attributes("LCOE", "../Data_Files/TEST_on_Save_Read_Files/", 
		"csv", std::iostream::in);
	B_file_reading.new_infile(B_file_strm.file);

	// the first line is neglected for typeset
	std::getline(*B_file_reading.infile, buffer);
	std::cout << buffer << std::endl;

	B_file_reading.table_init();
	B_file_reading.print_table();
	std::cout << std::endl;

	std::cout << "=============================================================================\n"
		<< "Test on file for LCOH_CHP Plant from file LCOH_CHP.csv\n"
		<< "-----------------------------------------------------------------------------" << std::endl;
	C_file_strm.change_file_attributes("LCOH_CHP", "../Data_Files/TEST_on_Save_Read_Files/",
		"csv", std::iostream::in);
	C_file_reading.new_infile(C_file_strm.file);
	
	// the first line is neglected for typeset
	std::getline(*C_file_reading.infile, buffer);
	std::cout << buffer << std::endl;

	C_file_reading.table_init();
	C_file_reading.print_table();
	std::cout << std::endl;

	std::cout << "=============================================================================\n"
		<< "Test on file for LCOE_CHP Plant from file LCOE_CHP.csv\n"
		<< "-----------------------------------------------------------------------------" << std::endl;
	D_file_strm.change_file_attributes("LCOE_CHP", "../Data_Files/TEST_on_Save_Read_Files/",
		"csv", std::iostream::in);
	D_file_reading.new_infile(D_file_strm.file);
	
	// the first line is neglected for typeset
	std::getline(*D_file_reading.infile, buffer);
	std::cout << buffer << std::endl;

	D_file_reading.table_init();
	D_file_reading.print_table();
	std::cout << std::endl;

	std::cout << "=============================================================================\n"
		<< "Test on file for LCOE Plant from file TEST_1_LCOE.csv\n"
		<< "-----------------------------------------------------------------------------" << std::endl;
	File_Stream fs("TEST_1_LCOE", "../Data_Files/", "csv", std::iostream::in);
	Read_File sf_read(fs.file);
	sf_read.table_init();
	sf_read.print_table();



	system("pause");
}