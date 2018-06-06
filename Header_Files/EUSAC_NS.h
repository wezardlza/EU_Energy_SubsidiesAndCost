#pragma once
#ifndef EUSAC_NS
#define EUSAC_NS
#include <string>

namespace eu_subsidies_and_cost_ns {
	class Physical_Quantity
	{
	public:
		// Summary: Construct a physical quantity.
		// Parameters:
		// magnitude: the magnitude of the physical quantity.
		// unit: the unit of the physical quantity.
		// Return: void.
		Physical_Quantity(const double & magnitude = 0.0, const std::string & unit = "unitless");

		// Summary: Construct a parameter related the calculation of some levelised cost of an energy project. This is 
		// a copy constructor.
		// Parameters:
		// const Physical_Quantity &: an object of the same class.
		// Return : void.
		Physical_Quantity(const Physical_Quantity &);

		// Summary: Destruct a physical quantity.
		// Return: void.
		~Physical_Quantity();

		// Summary: Get the magnitude of the physical quantity.
		const double get_magnitude() const;

		// Summary: Get the unit of the physical quantity.
		const std::string get_unit() const;

		// Summary: Get the number of the class objects.
		static int get_count();

	private:
		// The magnitude of the physical quantity.
		const double magnitude; 

		// The unit of the physical quantity.
		const std::string unit;  

		// The number of the class objects.
		static int count;
	};

	class LvlCost_Parameter
	{
	public:
		// Summary: Construct a parameter, i.e., a coefficient, related the calculation of some levelised cost of an 
		// energy project.
		// Parameters:
		// param: the magnitude of the object.
		// notation: the symbol or abbrevation of the object.
		// explanation: the additional explantions of the object.
		// Return : void
		LvlCost_Parameter(const double & param= 0.0, const std::string & notation = "", 
			const std::string & explanation = "");

		// Summary: Construct a parameter related the calculation of some levelised cost of an energy project. This is 
		// a copy constructor.
		// Parameters:
		// const LvlCost_Parameter &: an object of the same class.
		// Return : void.
		LvlCost_Parameter(const LvlCost_Parameter &);

		// Summary: Get the magnitude of the levelised-cost parameter.
		const double get_param() const;

		// Summary: Get the symbol or abbrevation of the levelised-cost parameter.
		const std::string get_notation() const;

		// Summary: Get the physical explanation of the levelised-cost parameter
		const std::string get_explanation() const;

		// Summary: Get the number of the class objects.
		static int get_count();

	private:
		// The magnitude of the levelised-cost parameter.
		double param; 

		// The symbol or abbrevation of the levelised-cost parameter.
		const std::string notation; 

		// The physical explanation of the levelised-cost parameter
		const std::string explanation;

		// The number of the class objects.
		static int count;

	};

	// The decomission cost equals 15% capital overnight cost.
	extern const double decommisioning_cost_rate;

	// The boiler efficiency.
	extern const double boiler_efficiency;

	// The interest rate for overnight cost.
	extern const double interest_rate;

}
#endif // !EUSAC_NS