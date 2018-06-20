/***********************************************************************************************************************
Author: Ziang Li
Institution: Control Group, UOM

	Tests of methods in EUSAC.h.
***********************************************************************************************************************/
#include "..\Header_Files\EUSAC.h"
#include <iostream>

namespace escn = eu_subsidies_and_cost;

int main(){

	extern const double escn::decommisioning_cost_factor;
	extern const double escn::boiler_efficiency;
	extern const double escn::interest_rate;

	const double & be = escn::boiler_efficiency;

	escn::Physical_Quantity C("capitial cost", 287000.0, "kGBP");
	escn::Physical_Quantity LB("construction period", 5.0, "yr");
	escn::Physical_Quantity LT("project duration", 20.0, "yr");
	escn::Physical_Quantity FOM("fixed OM cost", 0.0, "kGBP/yr");
	escn::Physical_Quantity VOM("variable OM cost", 0.0002038, "kGBP/MWh");
	escn::Physical_Quantity P_E("electrcity capacity", 700.0, "MW");
	escn::Physical_Quantity P_H("heat capacity", 700.0, "MW");

	// FC is the cost based on the thermal energy input
	escn::Physical_Quantity FC("fuel cost", 0.008, "kGBP/MWh");

	escn::Physical_Quantity REV("variable by-product revenue", 0.0, "kGBP/MWh");
	escn::Physical_Quantity dv("", 0.0, "kGBP/MWh");

	escn::Coefficient d(0.0, "decommisioning cost factor");
	escn::Coefficient r(0.075, "weighted average cost of capital");
	escn::Coefficient i(0.0, "interest rate over the construction loan");

	escn::Physical_Quantity FLH_E("full load hours of electricity", 7008.0, "h");
	escn::Physical_Quantity FLH_H("full load hours of heat", 8000.0, "h");
	escn::Coefficient etaE(0.55, "conversion efficiency in LHV of electricity");
	escn::Coefficient etaH(0.90, "conversion efficiency in LHV of heat");

	// heat price is estimated by the cost of fuel and the boiler efficiency
	const escn::Physical_Quantity HP("heat price", FC.get_magnitude() / be, "heat price");
 
	// Construct hypothetic plant investments
	escn::LCOE plantA(C, LB, LT, FOM, VOM, FC, r, i, REV, dv, d, P_E, FLH_E, etaE);
	double alpha_A = escn::LCOE::alpha(LT, r);
	double EH_A = escn::LCOE::EH(P_E, FLH_E);
	double I_A = escn::LCOE::I(C, LB, i, LT, r, d);
	double OM = escn::LCOE::OM(FOM, VOM, EH_A, REV, dv);
	double F = escn::LCOE::F(FC, etaE, EH_A);

	std::cout << "Plant A Investment Data:" << std::endl;
	std::cout << "Capital recovery factor\t\talpha\t" << alpha_A << std::endl;
	std::cout << "Annual electricity produced\t\tE\t" << EH_A << std::endl;
	std::cout << "Investment cost\t\t\tI\t" << I_A << std::endl;
	std::cout << "Operation and maintenance cost\tOM\t" << OM << std::endl;
	std::cout << "Annual fuel cost\t\tF\t" << F << std::endl;

	std::cout << "Interest rate:\t\t\t\t" << escn::interest_rate << std::endl;
	system("pause");
}