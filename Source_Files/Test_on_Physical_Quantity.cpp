/***********************************************************************************************************************
Author: Ziang Li
Institution: Control Group, UOM

	Tests of methods in EUSAC.h.
***********************************************************************************************************************/
#include "../Header_Files/EUSAC.h"
#include <iostream>

namespace escn = eu_subsidies_and_cost;

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
extern const escn::Coefficient &escn::d0;
extern const escn::Coefficient &escn::r0;
extern const escn::Coefficient &escn::i0;
extern const escn::Physical_Quantity &escn::FLH_E0;
extern const escn::Physical_Quantity &escn::FLH_H0;
extern const escn::Coefficient &escn::etaE0;
extern const escn::Coefficient &escn::etaH0;
extern const escn::Physical_Quantity &escn::HP0;

void Test_on_Physical_Quantity(){
 
	// Construct hypothetic plant investments
	escn::LCOE plantA(escn::C0, escn::LB0, escn::LT0, escn::FOM0, escn::VOM0, escn::FC0, escn::r0, escn::i0, escn::REV0,
		       	escn::dv0, escn::d0, escn::P_E0, escn::FLH_E0, escn::etaE0);
	double alpha_A = escn::LCOE::alpha(escn::LT0, escn::r0);
	double EH_A = escn::LCOE::EH(escn::P_E0, escn::FLH_E0);
	double I_A = escn::LCOE::I(escn::C0, escn::LB0, escn::i0, escn::LT0, escn::r0,escn::d0);
	double OM = escn::LCOE::OM(escn::FOM0, escn::VOM0, EH_A, escn::REV0, escn::dv0);
	double F = escn::LCOE::F(escn::FC0, escn::etaE0, EH_A);

	std::cout << "#############################################################################\n" 
		<<  "Test on Physical_Quantity\n" 
		<< "#############################################################################"
	       	<< std::endl << std::endl;
	std::cout << "Plant A Investment Data:" << std::endl;
	std::cout << "Capital recovery factor\t\talpha\t" << alpha_A << std::endl;
	std::cout << "Annual electricity produced\t\tE\t" << EH_A << std::endl;
	std::cout << "Investment cost\t\t\tI\t" << I_A << std::endl;
	std::cout << "Operation and maintenance cost\tOM\t" << OM << std::endl;
	std::cout << "Annual fuel cost\t\tF\t" << F << std::endl;

	std::cout << escn::i0 << std::endl;
	std::cout << std::endl; 
	// system("pause");
}
