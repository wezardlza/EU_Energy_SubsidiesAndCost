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
	extern const escn::Physical_Quantity &escn::C0;
	extern const escn::Physical_Quantity &escn::LB0;
	extern const escn::Physical_Quantity &escn::LT0;
	extern const escn::Physical_Quantity &escn::FOM0;
	extern const escn::Physical_Quantity &escn::VOM0;
	extern const escn::Physical_Quantity &escn::P_E0;
	extern const escn::Physical_Quantity &escn::P_H0;
	extern const escn::Physical_Quantity &escn::FC0;
	extern const escn::Physical_Quantity &escn::REV0;
	extern const escn::Physical_Quantity &escn::dv0;
	extern const escn::Physical_Quantity &escn::FLH_E0;
	extern const escn::Physical_Quantity &escn::FLH_H0;
	extern const escn::Coefficient &escn::d0;
	extern const escn::Coefficient &escn::r0;
	extern const escn::Coefficient &escn::i0;
	extern const escn::Coefficient &escn::etaE0;
	extern const escn::Coefficient &escn::etaH0;
	extern const escn::Physical_Quantity &escn::EP0;
	extern const escn::Physical_Quantity &escn::HP0;

	escn::Physical_Quantity C(escn::C0.get_symbol(), escn::C0.get_term(), 4.0, escn::C0.get_unit());

	std::cout << "Note: Check the assignment operator of Coefficent." << std::endl;
	std::cout << C << std::endl;
	C = escn::C0;
	std::cout << C << std::endl;

/***********************************************************************************************************************
	TEST ON SAVING DEFAULT PLANT SPECIFICATIONS
***********************************************************************************************************************/
	// Check the functions of constructor and destructor
	std::cout << "Note: There exist some constant Coefficient and Physical_Quantity instances"
		"\ndefined and imported from other source files." << std::endl;
	std::cout << "The number of Coefficient object:\t" << escn::Coefficient::get_count() << std::endl;
	std::cout << "The number of Physical_Quantity object:\t" << escn::Physical_Quantity::get_count() << std::endl;
	std::cout << "The number of LCOH object:\t\t" << escn::LCOE::get_count() << std::endl;
	std::cout << "The number of LCOE object:\t\t" << escn::LCOH::get_count() << std::endl;
	std::cout << "The number of LCOH_CHP object:\t\t" << escn::LCOH_CHP::get_count() << std::endl;
	std::cout << "The number of LCOE_CHP object:\t\t" << escn::LCOE_CHP::get_count() << std::endl;

	escn::Coefficient c;
	std::cout << "Note: Another Coefficient instance \"c\" is constructed." << std::endl;
	std::cout << "The number of Coefficient object:\t" << escn::Coefficient::get_count() << std::endl;
	std::cout << "The number of Physical_Quantity object:\t" << escn::Physical_Quantity::get_count() << std::endl;
	std::cout << "The number of LCOH object:\t\t" << escn::LCOE::get_count() << std::endl;
	std::cout << "The number of LCOE object:\t\t" << escn::LCOH::get_count() << std::endl;
	std::cout << "The number of LCOH_CHP object:\t\t" << escn::LCOH_CHP::get_count() << std::endl;
	std::cout << "The number of LCOE_CHP object:\t\t" << escn::LCOE_CHP::get_count() << std::endl;

	{
		escn::Physical_Quantity pq;
		std::cout << "Note: Another Physical_Quantity instance \"pq\" is constructed in a nested scope." << std::endl;
		std::cout << "The number of Coefficient object:\t" << escn::Coefficient::get_count() << std::endl;
		std::cout << "The number of Physical_Quantity object:\t" << escn::Physical_Quantity::get_count() << std::endl;
		std::cout << "The number of LCOH object:\t\t" << escn::LCOE::get_count() << std::endl;
		std::cout << "The number of LCOE object:\t\t" << escn::LCOH::get_count() << std::endl;
		std::cout << "The number of LCOH_CHP object:\t\t" << escn::LCOH_CHP::get_count() << std::endl;
		std::cout << "The number of LCOE_CHP object:\t\t" << escn::LCOE_CHP::get_count() << std::endl; 
	}


	std::cout << "Note: Physical_Quantity instance \"pq\" is desstructed when moving out of the nested scope." << std::endl;
	std::cout << "The number of Coefficient object:\t" << escn::Coefficient::get_count() << std::endl;
	std::cout << "The number of Physical_Quantity object:\t" << escn::Physical_Quantity::get_count() << std::endl;
	std::cout << "The number of LCOH object:\t\t" << escn::LCOE::get_count() << std::endl;
	std::cout << "The number of LCOE object:\t\t" << escn::LCOH::get_count() << std::endl;
	std::cout << "The number of LCOH_CHP object:\t\t" << escn::LCOH_CHP::get_count() << std::endl;
	std::cout << "The number of LCOE_CHP object:\t\t" << escn::LCOE_CHP::get_count() << std::endl;

	// Construct default investments
	escn::LCOH plantA;
	std::cout << "Note: LCOH instance \"plantA\" is constructed" << std::endl;
	std::cout << "The number of Coefficient object:\t" << escn::Coefficient::get_count() << std::endl;
	std::cout << "The number of Physical_Quantity object:\t" << escn::Physical_Quantity::get_count() << std::endl;
	std::cout << "The number of LCOH object:\t\t" << escn::LCOE::get_count() << std::endl;
	std::cout << "The number of LCOE object:\t\t" << escn::LCOH::get_count() << std::endl;
	std::cout << "The number of LCOH_CHP object:\t\t" << escn::LCOH_CHP::get_count() << std::endl;
	std::cout << "The number of LCOE_CHP object:\t\t" << escn::LCOE_CHP::get_count() << std::endl;

	escn::LCOE plantB;
	std::cout << "Note: LCOE instance \"plantB\" is constructed" << std::endl;
	std::cout << "The number of Coefficient object:\t" << escn::Coefficient::get_count() << std::endl;
	std::cout << "The number of Physical_Quantity object:\t" << escn::Physical_Quantity::get_count() << std::endl;
	std::cout << "The number of LCOH object:\t\t" << escn::LCOE::get_count() << std::endl;
	std::cout << "The number of LCOE object:\t\t" << escn::LCOH::get_count() << std::endl;
	std::cout << "The number of LCOH_CHP object:\t\t" << escn::LCOH_CHP::get_count() << std::endl;
	std::cout << "The number of LCOE_CHP object:\t\t" << escn::LCOE_CHP::get_count() << std::endl;

	escn::LCOH_CHP plantC;
	std::cout << "Note: LCOH_CHP instance \"plantC\" is constructed" << std::endl;
	std::cout << "The number of Coefficient object:\t" << escn::Coefficient::get_count() << std::endl;
	std::cout << "The number of Physical_Quantity object:\t" << escn::Physical_Quantity::get_count() << std::endl;
	std::cout << "The number of LCOH object:\t\t" << escn::LCOE::get_count() << std::endl;
	std::cout << "The number of LCOE object:\t\t" << escn::LCOH::get_count() << std::endl;
	std::cout << "The number of LCOH_CHP object:\t\t" << escn::LCOH_CHP::get_count() << std::endl;
	std::cout << "The number of LCOE_CHP object:\t\t" << escn::LCOE_CHP::get_count() << std::endl;

	escn::LCOE_CHP plantD;
	std::cout << "Note: LCOE_CHP instance \"plantD\" is constructed" << std::endl;
	std::cout << "The number of Coefficient object:\t" << escn::Coefficient::get_count() << std::endl;
	std::cout << "The number of Physical_Quantity object:\t" << escn::Physical_Quantity::get_count() << std::endl;
	std::cout << "The number of LCOH object:\t\t" << escn::LCOE::get_count() << std::endl;
	std::cout << "The number of LCOE object:\t\t" << escn::LCOH::get_count() << std::endl;
	std::cout << "The number of LCOH_CHP object:\t\t" << escn::LCOH_CHP::get_count() << std::endl;
	std::cout << "The number of LCOE_CHP object:\t\t" << escn::LCOE_CHP::get_count() << std::endl;


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