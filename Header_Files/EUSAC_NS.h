#pragma once
#ifndef EUSAC_NS
#define EUSAC_NS
#include <string>

using std::string;

namespace eu_subsidies_and_cost_ns {
	template <class Type>
	class Physical_Quantity
	{
	public:
		Physical_Quantity(const Type & m, const string & u);

	private:
		// The magnitude of the physical quantity
		const Type * magnitude; 
		// The unit of the physical quantity
		const string * unit;  
	};

	class LvlCost_Parameter
	{
	public:
		LvlCost_Parameter(double & p);

	private:
		// The magnitude of the parameter
		double * param; 
		// The notation of the parameter in the "Subsidies and costs of EU energy Final report"
		const string * notation; 
		// The physical explanation of the parameter
		const string * explanantion;
	};
	
	// The interest rate for overnight cost
	const double interest_rate(0.05);

	// The decomission cost equals 15% capital overnight cost
	const double decommisioning_cost_rate(0.15);

	// The boiler efficiency
	const double boiler_efficiency(0.9);
}
#endif // !EUSAC_NS