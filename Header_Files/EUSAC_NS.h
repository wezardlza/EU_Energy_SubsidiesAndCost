#pragma once
#ifndef EUSAC_NS
#define EUSAC_NS
#include <string>
#include <cmath>

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
		Coefficient(const double & maginitude = 0.0, const std::string & explanation = "");

		// Summary: Construct a coefficient.This is a copy constructor.
		// Parameters:
		// const Coefficient &: an object of the same class.
		// Return : void.
		Coefficient(const Coefficient &);

		// Summary: Get the magnitude of the coefficient.
		const double get_magnitude() const;

		// Summary: Get the physical explanation of the coefficient.
		const std::string get_explanation() const;

		// Summary: Get the number of the <class 'Coefficient'> objects.
		static int get_count();

	private:
		// The magnitude of the coefficient.
		double maginitude;

		// The physical explanation of the coefficient
		const std::string explanation;

		// The number of the <class 'Coefficient'> objects.
		static int count;

	};

	class LCOH
	{
	public:
		// Summary: Construct an object to manage the calculation of the LCOH
		// C: captial cost
		// LB: cosntruction period
		// FOM: fixed OM cost
		// VOM: variable OM cost
		// P: heat capacity
		// FC: fuel costs per unit of enengy input
		// r: weighted average cost of capital (WACC)
		// i: interest rate over the construction loan
		// FLH_H: equivalent full load hours for heat production
		// etaH: conversion efficiency in lower heating value (LHV) of heat
		LCOH(Physical_Quantity & C, Physical_Quantity & LB, Physical_Quantity & FOM, Physical_Quantity & VOM,
			Physical_Quantity & P, Physical_Quantity & FC, Coefficient & r, Coefficient & i,
			const Physical_Quantity & FLH_H = Physical_Quantity("Full load hours of heat", 0.0, "h"),
			const Coefficient & etaH = Coefficient(1.0, "Conversion efficiency in LHV of heat"));
		~LCOH();
		
		// Summary: Capital recovery factor
		inline static double alpha(Coefficient & r);
		// Summary: Electricity or heat produced annually.
		inline static double EH(Physical_Quantity & P, Physical_Quantity & FLH);

		/*Methods possibly hidden*/
		// Summary: Investment cost including finance cost for construction at a predefined interest rate
		inline static double I(Physical_Quantity & C, Physical_Quantity & LB, Coefficient & i);
		// Summary: Operation and maintainance cost
		inline static double OM(Physical_Quantity & FOM, Physical_Quantity & VOM, const double & EH);
		// Summary: Anual fuel cost
		inline static double F(Physical_Quantity & FC, Coefficient & eta, const double & EH);

		// Summary: Levelised cost of heat
		// alpha: capital recovery factor
		// I: investment cost including finance cost for construction at a predefined interest rate
		// OM: the operation and maintainance cost
		// F: anual fuel cost
		// EH: for LCOE object, EH is the electricity produced annually;
		//	for LCOH object, EH is the heat produced annually
		double operator () (const double & alpha, const double & I, const double & OM, const double & F,
			const double & EH);

	protected:
		Physical_Quantity & C;
		Physical_Quantity & LB;
		Physical_Quantity & FOM;
		Physical_Quantity & VOM;
		Physical_Quantity & P;
		Physical_Quantity & FC;
		Coefficient & r;
		Coefficient & i;

	private:
		// The full load hours of electricity
		Physical_Quantity & FLH_H;
		// The conversion efficiency in lower heating value (LHV) of heat
		Coefficient & etaH;

	};

	class LCOE : public LCOH
	{
	public:
		// Summary: Construct an object to manage the calculation of the LCOE
		// C: captial cost
		// LB: cosntruction period
		// FOM: fixed OM cost
		// VOM: variable OM cost
		// P: heat capacity
		// FC: fuel costs per unit of enengy input
		// r: weighted average cost of capital (WACC)
		// i: interest rate over the construction loan
		// LT: project duration
		// REV: variable by-product revenue
		// dv: not sure the physicial meaning yet
		// d: decommisioning cost factor
		// FLH_E: equivalent full load hours for electrcity production
		// etaE: conversion efficiency in lower heating value (LHV) of electrcity
		LCOE(Physical_Quantity & C, Physical_Quantity & LB, Physical_Quantity & FOM, Physical_Quantity & VOM, 
			Physical_Quantity & P, Physical_Quantity & FC, Coefficient & r, Coefficient & i, 
			Physical_Quantity & LT, Physical_Quantity & REV, Physical_Quantity & dv, Coefficient & d,
			const Physical_Quantity & FLH_E = Physical_Quantity("Full load hours of electrcity", 0.0, "h"),
			const Coefficient & etaE = Coefficient(1.0, "Conversion efficiency in LHV of electricity"));
		~LCOE();

		/*Methods rewritten*/
		// Summary: Investment cost including finance cost for construction at a predefined interest rate.
		inline static double I(Physical_Quantity & C, Physical_Quantity & LB, Physical_Quantity & LT, 
			Coefficient & r, Coefficient & i, Coefficient & d);
		// Summary: Operation and maintainance cost
		inline static double OM(Physical_Quantity & FOM, Physical_Quantity & VOM, 
			Physical_Quantity & REV, Physical_Quantity & dv, const double & EH);

	protected:
		Physical_Quantity & LT;
		Physical_Quantity & REV;
		Physical_Quantity & dv;
		Coefficient & d;

	private:
		Physical_Quantity & FLH_E;
		Coefficient & etaE;

	};

	class LCOH_CHP : public LCOH
	{
	public:
		// Summary: Construct an object to manage the calculation of the LCOH of CHP
		// C: captial cost
		// LB: cosntruction period
		// FOM: fixed OM cost
		// VOM: variable OM cost
		// P: heat capacity
		// FC: fuel costs per unit of enengy input
		// r: weighted average cost of capital (WACC)
		// i: interest rate over the construction loan
		// FLH_E: equivalent full load hours for electrcity production
		// FLH_H: equivalent full load hours for heat production
		// etaE: conversion efficiency in lower heating value (LHV) of electrcity
		// etaH: conversion efficiency in lower heating value (LHV) of heat
		// EP: electricity price a CHP intallation receives for electricity production as by-product
		LCOH_CHP(Physical_Quantity & C, Physical_Quantity & LB, Physical_Quantity & FOM, Physical_Quantity & VOM,
			Physical_Quantity & P, Physical_Quantity & FC, Coefficient & r, Coefficient & i, 
			Physical_Quantity & FLH_E, Physical_Quantity & FLH_H, Coefficient & etaE, Coefficient & etaH, 
			const Physical_Quantity & EP = Physical_Quantity("Wholesale electricity price", 0.0, "Euros/MWh"));
		~LCOH_CHP();

		/*Methods rewritten*/
		// Anual fuel cost
		inline static double F(Physical_Quantity & FC, Physical_Quantity & E, Physical_Quantity & H, 
			Coefficient & etaE, Coefficient & etaH);

		// Summary: Revenue of the by-product
		// HE: for LCOE_CHP object, HE is the heat produced annually (H);
		//	for LCOH_CHP object, HE is the electricity produced annually (E)
		// HE_P: for LCOE_CHP object, HE_P is the heat (HP) price; 
		//	for LOCH_CHP object, HE_P is the electricity (EP) price
		inline static double bp_revenue(Physical_Quantity & HE, Physical_Quantity & HE_P,
			Physical_Quantity & FLH_E, Physical_Quantity & FLH_H, Coefficient & etaE, Coefficient & etaH);

		// Summary: Levelised cost of heat for combined heat and power (CHP)
		// alpha: capital recovery factor
		// I: investment cost including finance cost for construction at a predefined interest rate
		// OM: the operation and maintainance cost
		// F: anual fuel cost
		// EH: for LCOE_CHP object, EH is the electricity produced annually (E);
		//	for LCOH_CHP object, EH is the heat produced annually (H)
		// bp_revenue: revenue of the by-product
		double operator () (const double & alpha, const double & I, const double & OM, const double & F,
			const double & EH, const double bp_revenue);

	protected:
		Physical_Quantity & FLH_E;
		Physical_Quantity & FLH_H;
		Coefficient & etaE;
		Coefficient & etaH;

	private:
		Physical_Quantity & EP;

	};

	class LCOE_CHP : public LCOH_CHP
	{
	public:
		// Summary: Construct an object to manage the calculation of the LCOE of CHP
		// C: captial cost
		// LB: cosntruction period
		// FOM: fixed OM cost
		// VOM: variable OM cost
		// P: heat capacity
		// FC: fuel costs per unit of enengy input
		// r: weighted average cost of capital (WACC)
		// i: interest rate over the construction loan
		// FLH_E: equivalent full load hours for electrcity production
		// FLH_H: equivalent full load hours for heat production
		// etaE: conversion efficiency in lower heating value (LHV) of electrcity
		// etaH: conversion efficiency in lower heating value (LHV) of heat
		// HP: heat price a CHP intallation receives for heat production as by-product
		LCOE_CHP(Physical_Quantity & C, Physical_Quantity & LB, Physical_Quantity & FOM, Physical_Quantity & VOM,
			Physical_Quantity & P, Physical_Quantity & FC, Coefficient & r, Coefficient & i,
			Physical_Quantity & FLH_E, Physical_Quantity & FLH_H, Coefficient & etaE, Coefficient & etaH,
			const Physical_Quantity & HP = Physical_Quantity("Wholesale heat price", 0.0, "Euros/MWh"));
		~LCOE_CHP();
	
	private:
		Physical_Quantity & HP;

	};


	// Decomission cost equals 15% capital overnight cost
	extern const double decommisioning_cost_factor;

	// Boiler efficiency
	extern const double boiler_efficiency;

	// Interest rate for overnight cost
	extern const double interest_rate;

}

inline double eu_subsidies_and_cost_ns::LCOH::alpha(Coefficient & r) {
	return r.get_magnitude() / (1 - (1 + r.get_magnitude()));
}
inline double eu_subsidies_and_cost_ns::LCOH::EH(Physical_Quantity & P, Physical_Quantity & FLH) {
	return P.get_magnitude() * FLH.get_magnitude();
}
inline double eu_subsidies_and_cost_ns::LCOH::OM(Physical_Quantity & FOM, Physical_Quantity & VOM, const double & EH) {
	return FOM.get_magnitude() + VOM.get_magnitude() * EH;
}
inline double eu_subsidies_and_cost_ns::LCOH::F(Physical_Quantity & FC, Coefficient & eta, const double & EH) {
	return FC.get_magnitude() * EH / eta.get_magnitude();
}
inline double eu_subsidies_and_cost_ns::LCOH::I(Physical_Quantity & C, Physical_Quantity & LB, Coefficient & i) {
	double s(0.0);
	double base(1.0 + i.get_magnitude());
	for (int temp = 0; temp < LB.get_magnitude(); ++temp) { 
		s += std::pow(base, temp + 1);
	}
	return C.get_magnitude() / LB.get_magnitude() * s;
}
inline double eu_subsidies_and_cost_ns::LCOH::OM(Physical_Quantity & FOM, Physical_Quantity & VOM, const double & EH) {

}
inline double eu_subsidies_and_cost_ns::LCOH::F(Physical_Quantity & FC, Coefficient & eta, const double & EH) {

}
#endif // !EUSAC_NS
