#pragma once
#ifndef EUSAC_NS
#define EUSAC_NS
#include <string>

namespace eu_subsidies_and_cost_ns {

	// A Physical_Quantity has a unit.
	class Physical_Quantity
	{
	public:
		// Summary: Construct a physical quantity.
		// Parameters:
		// magnitude: the magnitude of the physical quantity.
		// unit: the unit of the physical quantity.
		// Return: void.
		Physical_Quantity(const std::string & term = "", const double & magnitude = 0.0, 
			const std::string & unit = "unitless");

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
		// The name of the physical quantity.
		const std::string term;
		
		// The magnitude of the physical quantity.
		const double magnitude; 

		// The unit of the physical quantity.
		const std::string unit;  

		// The number of the <class 'Physical_Quantity'> objects.
		static int count;
	};

	// A coefficient has no unit.
	class Coefficient
	{
	public:
		// Summary: Construct a coefficient, related the calculation of some levelised cost of an 
		// energy project.
		// Parameters:
		// param: the magnitude of the object.
		// notation: the symbol or abbrevation of the object.
		// explanation: the additional explantions of the object.
		// Return : void
		Coefficient(const double & maginitude = 0.0, const std::string & notation = "",
			const std::string & explanation = "");

		// Summary: Construct a coefficient.This is a copy constructor.
		// Parameters:
		// const Coefficient &: an object of the same class.
		// Return : void.
		Coefficient(const Coefficient &);

		// Summary: Get the magnitude of the coefficient.
		const double get_magnitude() const;

		// Summary: Get the symbol or abbrevation of the coefficient.
		const std::string get_notation() const;

		// Summary: Get the physical explanation of the coefficient.
		const std::string get_explanation() const;

		// Summary: Get the number of the <class 'Coefficient'> objects.
		static int get_count();

	private:
		// The magnitude of the coefficient.
		double maginitude;

		// The symbol or abbrevation of the coefficient.
		const std::string notation; 

		// The physical explanation of the coefficient
		const std::string explanation;

		// The number of the <class 'Coefficient'> objects.
		static int count;

	};

	class LCOE
	{
	public:
		LCOE(Physical_Quantity & C, Physical_Quantity & LB, Physical_Quantity & LT, Physical_Quantity & FOM,
			Physical_Quantity & VOM, Physical_Quantity & REV, Physical_Quantity & P, Physical_Quantity & FLH,
			Physical_Quantity & FC, Coefficient & r, Coefficient & i, Coefficient & d, Coefficient & dv, 
			Coefficient & etaE);
		~LCOE();

		// The apital recovery factor.
		inline Coefficient alpha(Coefficient & r);
		// The investment cost including finance cost for construction at a predefined interest rate.
		inline Physical_Quantity I(Physical_Quantity & C, Physical_Quantity & LB, Physical_Quantity & LT, 
			Coefficient & r, Coefficient & i, Coefficient & d);
		// The operation and maintainance cost.
		inline Physical_Quantity OM(Physical_Quantity & FOM, Physical_Quantity & VOM, Physical_Quantity & E, 
			Physical_Quantity & REV, Physical_Quantity & dv);
		// The anual fuel cost.
		inline Physical_Quantity F(Physical_Quantity & FC, Physical_Quantity & E, Coefficient & etaE);
		// The electricity produced annually.
		inline Physical_Quantity E(Physical_Quantity & P, Physical_Quantity & FLH);

		// Summary: The levelised cost of electricity.
		// alpha: capital recovery factor.
		// I: investment cost including finance cost for construction at a predefined interest rate.
		// OM: the operation and maintainance cost.
		// F: anual fuel cost.
		// E: electricity produced annually.
		double operator () (const double & alpha, const double & I, const double & OM, const double & F,
			const double & E);

	private:
		// The weighted average cost of capital (WACC).
		Coefficient r;
		// The interest rate over the construction loan.
		Coefficient i;
		// The decommisioning cost factor.
		Coefficient d;
		// The conversion efficiency in lower heating value (LHV) of electrcity.
		Coefficient etaE;
		// The captial cost.
		Physical_Quantity C;
		// The cosntruction period.
		Physical_Quantity LB;
		// The project duration.
		Physical_Quantity LT;
		// The fixed OM cost.
		Physical_Quantity FOM;
		// The variable OM cost
		Physical_Quantity VOM;
		// The variable by-product revenue.
		Physical_Quantity REV;
		// The electrical capacity.
		Physical_Quantity P;
		// The full load hours.
		Physical_Quantity FLH;
		// The fuel costs per unit of enengy input.
		Physical_Quantity FC;
		// Not sure the physicial meaning yet.
		Physical_Quantity dv;

	};

	class LCOH
	{
	public:
		LCOH();
		~LCOH();
		// The apital recovery factor.
		inline Coefficient alpha(Coefficient & r);
		// The investment cost including finance cost for construction at a predefined interest rate.
		inline Physical_Quantity I(Physical_Quantity & C, Physical_Quantity & LB, Coefficient & i);
		// The operation and maintainance cost.
		inline Physical_Quantity OM(Physical_Quantity & FOM, Physical_Quantity & VOM, Physical_Quantity & H);
		// The anual fuel cost.
		inline Physical_Quantity F(Physical_Quantity & FC, Physical_Quantity & H, Coefficient & eta);
		// The heat produced annually.
		inline Physical_Quantity H(Physical_Quantity & P, Physical_Quantity & FLH);

		// Summary: The levelised cost of heat.
		// alpha: capital recovery factor.
		// I: investment cost including finance cost for construction at a predefined interest rate.
		// OM: the operation and maintainance cost.
		// F: anual fuel cost.
		// H: heat produced annually.
		double operator () (const double & alpha, const double & I, const double & OM, const double & F, 
			const double & H);

	private:
		// The weighted average cost of capital (WACC).
		Coefficient r;
		// The interest rate over the construction loan.
		Coefficient i;
		// The conversion efficiency in lower heating value (LHV) of heat.
		Coefficient etaH;
		// The fixed OM cost.
		Physical_Quantity FOM;
		// The variable OM cost
		Physical_Quantity VOM;
		// The heat capacity.
		Physical_Quantity P;
		// The full load hours.
		Physical_Quantity FLH;
		// The fuel costs per unit of enengy input.
		Physical_Quantity FC;

	};


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
	extern const double decommisioning_cost_factor;

	// The boiler efficiency.
	extern const double boiler_efficiency;

	// The interest rate for overnight cost.
	extern const double interest_rate;

}

#endif // !EUSAC_NS
