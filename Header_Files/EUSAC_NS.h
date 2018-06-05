#pragma once
#ifndef EUSAC_NS
#define EUSAC_NS
#include <string>

namespace eu_subsidies_and_cost_ns {
	class Physical_Quantity
	{
	public:
		Physical_Quantity(const double & m, const std::string & u);
		~Physical_Quantity();
	private:
		// The magnitude of the physical quantity
		const double * magnitude; 
		// The unit of the physical quantity
		const std::string * unit;  

		static int count;
	};

	class LvlCost_Parameter
	{
	public:
		LvlCost_Parameter(double & p);

	private:
		// The magnitude of the parameter
		double * param; 
		// The notation of the parameter in the "Subsidies and costs of EU energy Final report"
		const std::string * notation; 
		// The physical explanation of the parameter
		const std::string * explanantion;
	};

	// The decomission cost equals 15% capital overnight cost
	extern const double decommisioning_cost_rate;

	// The boiler efficiency
	extern const double boiler_efficiency;

	// The interest rate for overnight cost
	extern const double interest_rate;

}
#endif // !EUSAC_NS