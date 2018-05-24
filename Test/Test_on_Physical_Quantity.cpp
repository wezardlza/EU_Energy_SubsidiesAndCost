#include "..\Header_Files\LevelisedCostOfPowerAndHeat.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using eu_subsidies_and_cost_ns::interest_rate;
using eu_subsidies_and_cost_ns::Physical_Quantity;
using eu_subsidies_and_cost_ns::LvlCost_Parameter;


int main(){
	extern const double interest_rate;
	int v = 9;
	double vv(1.0);
	const string x = "Hello";
	const Physical_Quantity<int> a(v, x);
	LvlCost_Parameter b(vv);
	cout << "interest rate is " << interest_rate << endl;
	system("pause");
}