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
		Physical_Quantity(const std::string & term = "", const double & magnitude = 0.0, const std::string & unit = "unitless");

		// Summary: Construct a parameter related the calculation of some levelised cost of an energy project. This is 
		// a copy constructor.
		// Parameters:
		// const Physical_Quantity &: an object of the same class.
		// Return : void.
		Physical_Quantity(const Physical_Quantity &);

		// Summary: Destruct a physical quantity.
		// Return: void.
		~Physical_Quantity();

		// Summary: Get the name of the physical quantity
		const std::string get_term() const;

		// Summary: Get the magnitude of the physical quantity.
		const double get_magnitude() const;

		// Summary: Get the unit of the physical quantity.
		const std::string get_unit() const;

		// Summary: Get the number of the <class 'Physical_Quantity'> objects.
		static int get_count();

	private:
		// The name of the physical quantity
		const std::string term;
		
		// The magnitude of the physical quantity.
		const double magnitude; 

		// The unit of the physical quantity.
		const std::string unit;  

		// The number of the <class 'Physical_Quantity'> objects.
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

		// Summary: Get the number of the <class 'LvlCost_Parameter'> objects.
		static int get_count();

	private:
		// The magnitude of the levelised-cost parameter.
		double param; 

		// The symbol or abbrevation of the levelised-cost parameter.
		const std::string notation; 

		// The physical explanation of the levelised-cost parameter
		const std::string explanation;

		// The number of the <class 'LvlCost_Parameter'> objects.
		static int count;

	};

	// Summary: The levelised cost of electricity.
	// alpha: capital recovery factor.
	// I: investment cost including finance cost for construction at a predefined interest rate.
	// OM: the operation and maintainance cost.
	// F: anual fuel cost.
	// E: electricity produced annually.
	double LCOE(const double & alpha, const double & I, const double & OM, const double & F, const double & E);
	
	// Summary: The levelised cost of heat.
	// alpha: capital recovery factor.
	// I: investment cost including finance cost for construction at a predefined interest rate.
	// OM: the operation and maintainance cost.
	// F: anual fuel cost.
	// H: heat produced annually.
	double LCOH(const double & alpha, const double & I, const double & OM, const double & F, const double & H);

	// Summary: The levelised cost of electricity for combined heat and power (CHP).
	// alpha: capital recovery factor.
	// I: investment cost including finance cost for construction at a predefined interest rate.
	// OM: the operation and maintainance cost.
	// F: anual fuel cost.
	// E: electricity produced annually.
	// H: heat produced annually.
	// etaE: conversion efficiency in lower heating value (LHV) of electrcity
	// etaH: conversion efficiency in lower heating value (LHV) of heat
	// EP: electricity price a CHP intallation receives for elelctricty production as by-product
	// HP: heat price a CHP intallation receives for heat production as by-product
	// FLH_E: equivalent full load hours for electrcity production
	// FLH_H: equivalent full load hours for heat production
	double LCOE_CHP(const double & alpha, const double & I, const double & OM, const double & F, 
		const double & E, const double & H, const double & etaE, const double & etaH, const double & HP, 
		const double & FLH_E, const double & FLH_H);

	// Summary: The levelised cost of heat for combined heat and power (CHP).
	// alpha: capital recovery factor.
	// I: investment cost including finance cost for construction at a predefined interest rate.
	// OM: the operation and maintainance cost.
	// F: anual fuel cost.
	// H: heat produced annually.
	// E: electricity produced annually.
	// etaH: conversion efficiency in lower heating value (LHV) of heat
	// etaE: conversion efficiency in lower heating value (LHV) of electrcity
	// HP: heat price a CHP intallation receives for heat production as by-product
	// EP: electricity price a CHP intallation receives for elelctricty production as by-product
	// FLH_H: equivalent full load hours for heat production
	// FLH_E: equivalent full load hours for electrcity production
	double LCOH_CHP(const double & alpha, const double & I, const double & OM, const double & F, 
		const double & H, const double & E, const double & etaH, const double & etaE, const double & EP, 
		const double & FLH_H, const double & FLH_E);

	// The decomission cost equals 15% capital overnight cost.
	extern const double decommisioning_cost_rate;

	// The boiler efficiency.
	extern const double boiler_efficiency;

	// The interest rate for overnight cost.
	extern const double interest_rate;

}

#endif // !EUSAC_NS
