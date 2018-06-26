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
	extern const double escn::decommisioning_cost_factor;
	extern const double escn::boiler_efficiency;
	extern const double escn::interest_rate;

	const double & be = escn::boiler_efficiency;

	Save_CSV_File save("../Data_Files/TEST_1_LCOE.csv");
	escn::Physical_Quantity C("C", "capitial cost", 287000.0, "kGBP");
	escn::Physical_Quantity LB("LB", "construction period", 5.0, "yr");
	escn::Physical_Quantity LT("LT", "project duration", 20.0, "yr");
	escn::Physical_Quantity FOM("FOM", "fixed OM cost", 0.0, "kGBP/yr");
	escn::Physical_Quantity VOM("VOM", "variable OM cost", 0.0002038, "kGBP/MWh");
	escn::Physical_Quantity P_E("P_E", "electrcity capacity", 700.0, "MW");
	escn::Physical_Quantity P_H("P_H", "heat capacity", 700.0, "MW");

	// FC is the cost based on the thermal energy input
	escn::Physical_Quantity FC("FC", "fuel cost", 0.008, "kGBP/MWh");

	escn::Physical_Quantity REV("REV", "variable by-product revenue", 0.0, "kGBP/MWh");
	escn::Physical_Quantity dv("dv", "", 0.0, "kGBP/MWh");

	escn::Coefficient d("d", "decommisioning cost factor", 0.0);
	escn::Coefficient r("r", "weighted average cost of capital", 0.075);
	escn::Coefficient i("i", "interest rate over the construction loan", 0.0);

	escn::Physical_Quantity FLH_E("FLH_E", "full load hours of electricity", 7008.0, "h");
	escn::Physical_Quantity FLH_H("FLH_H", "full load hours of heat", 8000.0, "h");
	escn::Coefficient etaE("etaE", "conversion efficiency in LHV of electricity", 0.55);
	escn::Coefficient etaH("etaH", "conversion efficiency in LHV of heat", 0.90);

	// heat price is estimated by the cost of fuel and the boiler efficiency
	const escn::Physical_Quantity HP("HP", "heat price", FC.get_magnitude() / be, "heat price");

	/*std::cout << C << std::endl;
	std::cout << LB << std::endl;
	std::cout << LT << std::endl;
	std::cout << FOM << std::endl;
	std::cout << VOM << std::endl;
	std::cout << P_E << std::endl;
	std::cout << P_H << std::endl;
	std::cout << FC << std::endl;
	std::cout << REV << std::endl;
	std::cout << dv << std::endl;
	std::cout << d << std::endl;
	std::cout << r << std::endl;
	std::cout << i << std::endl;
	std::cout << FLH_E << std::endl;
	std::cout << FLH_H << std::endl;
	std::cout << etaE << std::endl;
	std::cout << etaH << std::endl;*/
	

	// Construct a stream
	std::ofstream outfile;

	// Construct hypothetic plant investments
	escn::LCOH plantA(C, LB, LT, FOM, VOM, FC, r, i, P_H);
	escn::LCOE plantB(C, LB, LT, FOM, VOM, FC, r, i, REV, dv, d, P_E, FLH_E, etaE);
	const std::string file_address1 = "../Data_Files/TEST_on_Save_Read_Files/LCOH.csv";
	const std::string file_address2 = "../Data_Files/TEST_on_Save_Read_Files/LCOE.csv";

	Save_CSV_File::open_file_check(file_address1);
	outfile.open(file_address1, std::ofstream::out);
	plantA.save(outfile);
	outfile.close();

	Save_CSV_File::open_file_check(file_address2);
	outfile.open("../Data_Files/TEST_on_Save_Read_Files/LCOE.csv", std::ofstream::out);
	plantB.save(outfile);
	outfile.close();

	// Read_CSV_File csv("../Data_Files/TEST_1_LCOE.csv");
	// csv.print_table();
	system("pause");
}