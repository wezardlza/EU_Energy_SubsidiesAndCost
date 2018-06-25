/***********************************************************************************************************************
Author: Ziang Li
Institution: Control Group, UOM

	This file declares the classes of LCOH, LCOE, LCOH_CHP and LCOE_CHP which are used for the levelised cost of 
	heat/electricty with/without the combined heat and power plant.  
***********************************************************************************************************************/

#pragma once
#ifndef __EUSAC__
#define __EUSAC__
#define __DEBUG__

#include <string>
#include <cmath>

namespace eu_subsidies_and_cost {

	// A Physical_Quantity has a unit
	class Physical_Quantity
	{
	public:

		// Summary: Construct a physical quantity
		// Parameters:
		// term: name of the physical quantity
		// magnitude: magnitude of the physical quantity
		// unit: unit of the physical quantity
		// Return: void
		Physical_Quantity(const std::string & term = "", const double & magnitude = 0.0, 
			const std::string & unit = "unitless");

		// Summary: Construct a parameter related the calculation of some levelised cost of an energy project. This is 
		// a copy constructor
		// Parameters:
		// const Physical_Quantity &: an object of the same class
		// Return : void
		Physical_Quantity(const Physical_Quantity &);

		// Summary: Destruct a physical quantity
		// Return: void.
		~Physical_Quantity();

		// Summary: Get the name of the physical quantity
		const std::string & get_term() const;

		// Summary: Get the magnitude of the physical quantity
		const double & get_magnitude() const;

		// Summary: Get the unit of the physical quantity
		const std::string & get_unit() const;

		// Summary: Get the number of the class objects
		static const int & get_count();

	private:
		const std::string term;
		double magnitude; 
		const std::string unit;  

		// The number of the class objects
		static int count;
	};

	// A coefficient has no unit
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

		// Summary: Construct a coefficient.This is a copy constructor
		// Parameters:
		// const Coefficient &: an object of the same class
		Coefficient(const Coefficient &);

		// Summary: Destruct a cefficient
		// Return: void
		~Coefficient();

		// Summary: Get the magnitude of the coefficient.
		const double & get_magnitude() const;

		// Summary: Get the physical explanation of the coefficient.
		const std::string & get_explanation() const;

		// Summary: Get the number of the class objects
		static const int & get_count();

	private:
		double maginitude;
		const std::string explanation;

		// The number of the class objects
		static int count;

	};

	class LCOH
	{
	public:

		// Summary: Construct an object to manage the calculation of the LCOH
		// C: captial cost
		// LB: cosntruction period
		// LT: project duration
		// FOM: fixed OM cost
		// VOM: variable OM cost
		// P_H: heat capacity
		// FC: fuel costs per unit of enengy input
		// r: weighted average cost of capital (WACC)
		// i: interest rate over the construction loan
		// FLH_H: equivalent full load hours for heat production
		// etaH: conversion efficiency in lower heating value (LHV) of heat
		LCOH(Physical_Quantity & C, Physical_Quantity & LB, Physical_Quantity & LT,Physical_Quantity & FOM, 
			Physical_Quantity & VOM, Physical_Quantity & FC, Coefficient & r, Coefficient & i,
			const Physical_Quantity & P_H = Physical_Quantity("heat capacity", 650, "MW"),
			const Physical_Quantity & FLH_H = Physical_Quantity("full load hours of heat", 0.0, "h"),
			const Coefficient & etaH = Coefficient(1.0, "conversion efficiency in LHV of heat"));
		LCOH(const LCOH &);
		~LCOH();
		
		inline static double alpha(Physical_Quantity & LT, Coefficient & r);

		inline static double EH(Physical_Quantity & P_EH, Physical_Quantity & FLH);


		/*Methods possibly hidden*/
		inline static double I(Physical_Quantity & C, Physical_Quantity & LB, Coefficient & i);

		inline static double OM(Physical_Quantity & FOM, Physical_Quantity & VOM, const double & EH);

		inline static double F(Physical_Quantity & FC, Coefficient & eta, const double & EH);

		// Summary: Levelised cost of heat
		// alpha: capital recovery factor
		// I: investment cost including finance cost for construction at a predefined interest rate
		// OM: the operation and maintainance cost
		// F: annual fuel cost
		// EH: for LCOE object, EH is the electricity produced annually (E);
		//	for LCOH object, EH is the heat produced annually (H)
		double operator () (const double & alpha, const double & I, const double & OM, const double & F,
			const double & EH);

		// Summary: Get the number of the class objects
		static const int & get_count();

	protected:
		Physical_Quantity C;
		Physical_Quantity LB;
		Physical_Quantity LT;
		Physical_Quantity FOM;
		Physical_Quantity VOM;
		Physical_Quantity FC;
		Coefficient r;
		Coefficient i;

	private:
		Physical_Quantity P_H;
		Physical_Quantity FLH_H;
		Coefficient etaH;

		// The number of the class objects
		static int count;

	};

	class LCOE : public LCOH
	{
	public:

		// Summary: Construct an object to manage the calculation of the LCOE
		// C: captial cost
		// LT: project duration
		// LB: cosntruction period
		// FOM: fixed OM cost
		// VOM: variable OM cost
		// P_E: electricity capacity
		// FC: fuel costs per unit of enengy input
		// r: weighted average cost of capital (WACC)
		// i: interest rate over the construction loan
		// REV: variable by-product revenue
		// dv: not sure the physicial meaning yet
		// d: decommisioning cost factor
		// FLH_E: equivalent full load hours for electrcity production
		// etaE: conversion efficiency in lower heating value (LHV) of electrcity
		LCOE(Physical_Quantity & C, Physical_Quantity & LB, Physical_Quantity & LT, Physical_Quantity & FOM, 
			Physical_Quantity & VOM, Physical_Quantity & FC, Coefficient & r, Coefficient & i,
			Physical_Quantity & REV, Physical_Quantity & dv, Coefficient & d,
			const Physical_Quantity & P_E = Physical_Quantity("electricity capacity", 650, "MW"),
			const Physical_Quantity & FLH_E = Physical_Quantity("full load hours of electrcity", 0.0, "h"),
			const Coefficient & etaE = Coefficient(1.0, "conversion efficiency in LHV of electricity"));
		LCOE(const LCOE &);
		~LCOE();


		/*Methods rewritten*/
		inline static double I(Physical_Quantity & C, Physical_Quantity & LB, Coefficient & i, 
			Physical_Quantity & LT, Coefficient & r, Coefficient & d);

		inline static double OM(Physical_Quantity & FOM, Physical_Quantity & VOM, const double & EH, 
			Physical_Quantity & REV, Physical_Quantity & dv);

		// Summary: Get the number of the class objects
		static const int & get_count();

	protected:
		Physical_Quantity REV;
		Physical_Quantity dv;
		Coefficient d;

	private:
		Physical_Quantity P_E;
		Physical_Quantity FLH_E;
		Coefficient etaE;

		// The number of the class objects
		static int count;

	};

	class LCOH_CHP : public LCOH
	{
	public:

		// Summary: Construct an object to manage the calculation of the LCOH of CHP
		// C: captial cost
		// LB: cosntruction period
		// LT: project duration
		// FOM: fixed OM cost
		// VOM: variable OM cost
		// P_E: electricity capacity
		// P_H: heat capacity
		// FC: fuel costs per unit of enengy input
		// r: weighted average cost of capital (WACC)
		// i: interest rate over the construction loan
		// FLH_E: equivalent full load hours for electrcity production
		// FLH_H: equivalent full load hours for heat production
		// etaE: conversion efficiency in lower heating value (LHV) of electrcity
		// etaH: conversion efficiency in lower heating value (LHV) of heat
		// EP: electricity price a CHP intallation receives for electricity production as by-product
		LCOH_CHP(Physical_Quantity & C, Physical_Quantity & LB, Physical_Quantity & LT, Physical_Quantity & FOM, 
			Physical_Quantity & VOM, Physical_Quantity & FC, Coefficient & r, Coefficient & i, Physical_Quantity & P_E,
			Physical_Quantity & P_H, Physical_Quantity & FLH_E, Physical_Quantity & FLH_H, Coefficient & etaE, 
			Coefficient & etaH, 
			const Physical_Quantity & EP = Physical_Quantity("wholesale electricity price", 0.0, "Euros/MWh"));
		LCOH_CHP(const LCOH_CHP &);
		~LCOH_CHP();


		/*Methods rewritten*/
		inline static double F(Physical_Quantity & FC, Physical_Quantity & E, Physical_Quantity & H, 
			Coefficient & etaE, Coefficient & etaH);

		inline static double bp_revenue(Physical_Quantity & HE, Physical_Quantity & HE_P,
			Physical_Quantity & FLH_EH, Physical_Quantity & FLH_HE, Coefficient & etaEH, Coefficient & etaHE);

		// Summary: Levelised cost of heat for combined heat and power (CHP)
		// alpha: capital recovery factor
		// I: investment cost including finance cost for construction at a predefined interest rate
		// OM: the operation and maintainance cost
		// F: annual fuel cost
		// EH: for LCOE_CHP object, EH is the electricity produced annually (E);
		//	for LCOH_CHP object, EH is the heat produced annually (H)
		// bp_revenue: revenue of the by-product
		double operator () (const double & alpha, const double & I, const double & OM, const double & F,
			const double & EH, const double bp_revenue);

		// Summary: Get the number of the class objects
		static const int & get_count();

	protected:
		Physical_Quantity P_E;
		Physical_Quantity P_H;
		Physical_Quantity FLH_E;
		Physical_Quantity FLH_H;
		Coefficient etaE;
		Coefficient etaH;

	private:
		Physical_Quantity EP;

		// The number of the class objects
		static int count;

	};

	class LCOE_CHP : public LCOH_CHP
	{
	public:

		// Summary: Construct an object to manage the calculation of the LCOE of CHP
		// C: captial cost
		// LB: cosntruction period
		// FOM: fixed OM cost
		// VOM: variable OM cost
		// P_E: electricity capacity
		// P_H: heat capacity
		// FC: fuel costs per unit of enengy input
		// r: weighted average cost of capital (WACC)
		// i: interest rate over the construction loan
		// FLH_E: equivalent full load hours for electrcity production
		// FLH_H: equivalent full load hours for heat production
		// etaE: conversion efficiency in lower heating value (LHV) of electrcity
		// etaH: conversion efficiency in lower heating value (LHV) of heat
		// HP: heat price a CHP intallation receives for heat production as by-product
		LCOE_CHP(Physical_Quantity & C, Physical_Quantity & LB, Physical_Quantity & LT, Physical_Quantity & FOM, 
			Physical_Quantity & VOM, Physical_Quantity & FC, Coefficient & r, Coefficient & i, Physical_Quantity & P_E,
			Physical_Quantity & P_H, Physical_Quantity & FLH_E, Physical_Quantity & FLH_H, Coefficient & etaE, 
			Coefficient & etaH, 
			const Physical_Quantity & HP = Physical_Quantity("wholesale heat price", 0.0, "Euros/MWh"));
		LCOE_CHP(const LCOE_CHP &);
		~LCOE_CHP();

		// Summary: Get the number of the class objects
		static const int & get_count();
	
	private:
		Physical_Quantity HP;

		// The number of the class objects
		static int count;

	};


	// Decomission cost equals 15% capital overnight cost
	extern const double decommisioning_cost_factor;

	// Boiler efficiency
	extern const double boiler_efficiency;

	// Interest rate for overnight cost
	extern const double interest_rate;

	/* Inline functions of LCOH */

	// Summary: Capital recovery factor
	inline double LCOH::alpha(Physical_Quantity & LT, Coefficient & r) {
		return r.get_magnitude() / (1 - std::pow(1 + r.get_magnitude(), -LT.get_magnitude()));
	}

	// Summary: Electricity or heat produced annually
	inline double LCOH::EH(Physical_Quantity & P_EH, Physical_Quantity & FLH) {
		return P_EH.get_magnitude() * FLH.get_magnitude();
	}

	// Summary: Investment cost including finance cost for construction at a predefined interest rate
	inline double LCOH::I(Physical_Quantity & C, Physical_Quantity & LB, Coefficient & i) {
		double s(0.0);
		double base(1.0 + i.get_magnitude());
		for (int temp = 0; temp < LB.get_magnitude(); ++temp) {
			s += std::pow(base, temp + 1);
		}
		return C.get_magnitude() / LB.get_magnitude() * s;
	}

	// Summary: Operation and maintainance cost
	inline double LCOH::OM(Physical_Quantity & FOM, Physical_Quantity & VOM, const double & EH) {
		return FOM.get_magnitude() + VOM.get_magnitude() * EH;
	}

	// Summary: Annual fuel cost
	inline double LCOH::F(Physical_Quantity & FC, Coefficient & eta, const double & EH) {
		return FC.get_magnitude() * EH / eta.get_magnitude();
	}


	/* Inline functions of LCOE */

	// Summary: Investment cost including finance cost for construction at a predefined interest rate
	inline double LCOE::I(Physical_Quantity & C, Physical_Quantity & LB, Coefficient & i,
		Physical_Quantity & LT, Coefficient & r, Coefficient & d) {
		return LCOH::I(C, LB, i) * (1 + d.get_magnitude() / std::pow(1.0 + r.get_magnitude(), LT.get_magnitude()));
	}

	// Summary: Operation and maintainance cost
	inline double LCOE::OM(Physical_Quantity & FOM, Physical_Quantity & VOM, const double & EH,
		Physical_Quantity & REV, Physical_Quantity & dv) {
		return FOM.get_magnitude() + (VOM.get_magnitude() - REV.get_magnitude() + dv.get_magnitude())* EH;
	}


	/* Inline functions of LCOH_CHP */

	// Summary: Annual fuel cost
	inline double LCOH_CHP::F(Physical_Quantity & FC, Physical_Quantity & E, Physical_Quantity & H,
		Coefficient & etaE, Coefficient & etaH) {
		return FC.get_magnitude() * (E.get_magnitude() + H.get_magnitude()) / 
			(etaE.get_magnitude() + etaH.get_magnitude());
	}

	// Summary: Revenue of the by-product
	// HE: for LCOE_CHP object, HE is the heat produced annually (H);
	//	for LCOH_CHP object, HE is the electricity produced annually (E)
	// HE_P: for LCOE_CHP object, HE_P is the heat (HP) price; 
	//	for LOCH_CHP object, HE_P is the electricity (EP) price
	// FLH_EH: for LCOE_CHP object, FLH_EH is the equivalent full load hours for electrcity production (FLH_E); 
	//	for LOCH_CHP object, FLH_EH is the equivalent full load hours for heat production (FLH_H)
	// FLH_HE: for LCOE_CHP object, FLH_HE is the equivalent full load hours for heat production (FLH_H); 
	//	for LOCH_CHP object, FLH_HE is the equivalent full load hours for electricity production (FLH_E)
	// etaEH: for LCOE_CHP object, conversion efficiency in lower heating value (LHV) of electrcity (etaE)£»
	//	for LCOH_CHP object, conversion efficiency in lower heating value (LHV) of heat (etaH)
	// etaHE: for LCOE_CHP object, conversion efficiency in lower heating value (LHV) of heat (etaH);
	//	for LCOH_CHP object, conversion efficiency in lower heating value (LHV) of electrcity (etaE)
	inline double LCOH_CHP::bp_revenue(Physical_Quantity & HE, Physical_Quantity & HE_P,
		Physical_Quantity & FLH_EH, Physical_Quantity & FLH_HE, Coefficient & etaEH, Coefficient & etaHE) {
		return HE.get_magnitude() * HE_P.get_magnitude() * etaHE.get_magnitude() * 
			FLH_HE.get_magnitude() / etaEH.get_magnitude() / FLH_EH.get_magnitude();
	}

}

#endif // !__EUSAC__
