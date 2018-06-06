#include "..\Header_Files\EUSAC_NS.h"
#include <iostream>

namespace escn = eu_subsidies_and_cost_ns;

int main(){
	
	extern const double escn::decommisioning_cost_rate;
	extern const double escn::boiler_efficiency;
	extern const double escn::interest_rate;
	const double v = 9;
	double vv(1.0);
	const std::string unit = "kg";


	escn::Physical_Quantity a; 

	std::cout << "magnitude of the a physical quantity: " << a.get_magnitude() << std::endl;
	std::cout << "interest rate is: " << escn::interest_rate << std::endl;
	system("pause");
}