#include "..\Header_Files\EUSAC_NS.h"
#include <iostream>

namespace escn = eu_subsidies_and_cost_ns;

int main(){
	extern const double escn::interest_rate;
	const double v = 9;
	double vv(1.0);
	const std::string x = "Hello";
	escn::Physical_Quantity a(v, x); 
	escn::LvlCost_Parameter b(vv);

	std::cout << "interest rate is " << escn::interest_rate << std::endl;
	system("pause");
}