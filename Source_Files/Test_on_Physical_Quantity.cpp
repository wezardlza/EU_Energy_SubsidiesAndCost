#include "..\Header_Files\EUSAC_NS.h"
#include <iostream>

namespace escn = eu_subsidies_and_cost_ns;

int main(){
	
	extern const double escn::decommisioning_cost_rate;
	extern const double escn::boiler_efficiency;
	extern const double escn::interest_rate;
	double alpha(0.08), I(10), OM(6), F(4), E(2.3);
	const double v = 9;
	double vv(1.0);
	const std::string unit = "kg";

	escn::Physical_Quantity a; 
	escn::LCOE_CHP(0.1, 0.2, 3, 2, 3, 4, 1, 2, 3, 4, 5);

	std::cout << "levelised cost of the electricity:\n\t\t" << eu_subsidies_and_cost_ns::LCOE(alpha, I, OM, F, E) << std::endl;
	std::cout << "magnitude of the a physical quantity:\n\t\t" << a.get_magnitude() << std::endl;
	std::cout << "interest rate is:\n\t\t" << escn::interest_rate << std::endl;
	system("pause");
}