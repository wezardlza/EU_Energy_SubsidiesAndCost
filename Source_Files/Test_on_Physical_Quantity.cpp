/***********************************************************************************************************************
Author: Ziang Li
Institution: Control Group, UOM

	Tests of methods in EUSAC.h.
***********************************************************************************************************************/
#include "../Header_Files/EUSAC.h"
#include <iostream>

namespace escn = eu_subsidies_and_cost;

void Test_on_Physical_Quantity(){

	extern const escn::Physical_Quantity &C0;
	extern const escn::Physical_Quantity &LB0;
	extern const escn::Physical_Quantity &LT0;
	extern const escn::Physical_Quantity &FOM0;
	extern const escn::Physical_Quantity &VOM0;
	extern const escn::Physical_Quantity &P_E0;
	extern const escn::Physical_Quantity &P_H0;

	// FC is the cost based on the thermal energy input
	extern const escn::Physical_Quantity &FC0;

	extern const escn::Physical_Quantity &REV0;
	extern const escn::Physical_Quantity &dv0;

	extern const escn::Coefficient d0;
	extern const escn::Coefficient r0;
	extern const escn::Coefficient i0;

	extern const escn::Physical_Quantity FLH_E0;
	extern const escn::Physical_Quantity FLH_H0;
	extern const escn::Coefficient etaE0;
	extern const escn::Coefficient etaH0;

	// heat price is estimated by the cost of fuel and the boiler efficiency
	extern const escn::Physical_Quantity HP0;
 
	// Construct hypothetic plant investments
	escn::LCOE plantA(C0, LB0, LT0, FOM0, VOM0, FC0, r0, i0, REV0, dv0, d0, P_E0, FLH_E0, etaE0);
	double alpha_A = escn::LCOE::alpha(LT0, r0);
	double EH_A = escn::LCOE::EH(P_E0, FLH_E0);
	double I_A = escn::LCOE::I(C0, LB0, i0, LT0, r0,d0);
	double OM = escn::LCOE::OM(FOM0, VOM0, EH_A, REV0, dv0);
	double F = escn::LCOE::F(FC0, etaE0, EH_A);

	std::cout << "#############################################################################\n" 
		<<  "Test on Physical_Quantity" 
		<< "#############################################################################"
	       	<< std::endl << std::endl;
	std::cout << "Plant A Investment Data:" << std::endl;
	std::cout << "Capital recovery factor\t\talpha\t" << alpha_A << std::endl;
	std::cout << "Annual electricity produced\t\tE\t" << EH_A << std::endl;
	std::cout << "Investment cost\t\t\tI\t" << I_A << std::endl;
	std::cout << "Operation and maintenance cost\tOM\t" << OM << std::endl;
	std::cout << "Annual fuel cost\t\tF\t" << F << std::endl;

	std::cout << "Interest rate:\t\t\t\t" << escn::i0 << std::endl;

	// system("pause");
}
