/***********************************************************************************************************************
Author: Ziang Li
Institution: Control Group, UOM

	This file declares the classes of LCOH, LCOE, LCOH_CHP and LCOE_CHP which are used for the levelised cost of 
	heat/electricty with/without the combined heat and power plant.  
***********************************************************************************************************************/

#pragma once
#ifndef __EUSAC__
#define __EUSAC__
// #define __DEBUG__

#include "../Header_Files/SRF_ALIAS.h"
#include "../Header_Files/SRF.h"
#include <string>
#include <cmath>
#include <fstream>

namespace eu_subsidies_and_cost {
		
	// A coefficient has no unit
	class Coefficient
	{
		// Summary: cout the coefficient
		friend std::ostream & operator <<(std::ostream & outfile, const Coefficient & object);

		// Summary: cin the coefficient
		friend std::istream & operator >>(std::istream & infile, Coefficient & object);

	public:

		// Summary: Construct a coefficient, related the calculation of some levelised cost of an 
		// energy project
		// Parameters:
		// symbol: the symbol or abbrevation of the object
		// term: the additional explantions of the object
		// magnitude: the magnitude of the object
		// Return : void
		Coefficient(const std::string & symbol = "", const std::string & term = "", const double & magnitude = 0.0);

		// Summary: Construct a coefficient.This is a copy constructor
		// Parameters:
		// const Coefficient &: an object of the same class
		Coefficient(const Coefficient &);

		// Summary: Destruct a cefficient
		// Return: void
		~Coefficient();
		
		// Summary: Get the symbol of the physical quantity
		const std::string & get_symbol() const;

		// Summary: Get the physical explanation of the coefficient
		const std::string & get_term() const;

		// Summary: Get the magnitude of the coefficient
		const double & get_magnitude() const;

		// Summary: Rewrite the magnitude
		double & change_magnitude(const double & new_magnitude);

		// Summary: Get the number of the class objects
		static const std::size_t & get_count();

	protected:
		const std::string term;
		const std::string symbol;
		double magnitude;

	private:
		//Summary: Form a record of the coefficient in a ROW object 
		ROW _record() const;

		// The number of attributes determining the class object
		static std::size_t n_attributes;
		
		// The number of the class objects
		static std::size_t count;
	};

	// A Physical_Quantity has a unit
	class Physical_Quantity : public Coefficient
	{
		// Summary: print the physical qunatity
		friend std::ostream & operator <<(std::ostream & outfile, const Physical_Quantity & object);

		// Summary: cin the coefficient
		friend std::istream & operator >>(std::istream & infile, Physical_Quantity & object);

	public:
		// Summary: Construct a physical quantity
		// Parameters:
		// symbol: the symbol or abbrevation of the object
		// term: the additional explantions of the object
		// magnitude: the magnitude of the object
		// unit: unit of the physical quantity
		// Return: void
		Physical_Quantity(const std::string & symbol = "", const std::string & term = "",
			const double & magnitude = 0.0, const std::string & unit = "unspecified!");

		// Summary: Construct a parameter related the calculation of some levelised cost of an energy project. This is 
		// a copy constructor
		// Parameters:
		// const Physical_Quantity &: an object of the same class
		// Return : void
		Physical_Quantity(const Physical_Quantity &);

		// Summary: Destruct a physical quantity
		// Return: void.
		~Physical_Quantity();

		// Summary: Get the unit of the physical quantity
		const std::string & get_unit() const;

		// Summary: Get the number of the class objects
		static const std::size_t & get_count();

	protected:
		const std::string unit;

	private:
		// Summary: Form a record of the coefficient in a ROW object 
		ROW _record() const;

		// The number of attributes determining the class object
		static std::size_t n_attributes;

		// The number of the class objects
		static std::size_t count;
	};

	extern const Physical_Quantity & C0;
	extern const Physical_Quantity & LB0;
	extern const Physical_Quantity & LT0;
	extern const Physical_Quantity & FOM0;
	extern const Physical_Quantity & VOM0;
	extern const Physical_Quantity & FC0;
	extern const Physical_Quantity & REV0;
	extern const Physical_Quantity & dv0;
	extern const Physical_Quantity & P_E0;
	extern const Physical_Quantity & P_H0;
	extern const Physical_Quantity & FLH_E0;
	extern const Physical_Quantity & FLH_H0;
	extern const Physical_Quantity & EP0;
	extern const Coefficient & r0;
	extern const Coefficient & i0;
	extern const Coefficient & d0;
	extern const Coefficient & etaE0;
	extern const Coefficient & etaH0;
	extern const Physical_Quantity & HP0;

	class LCOH
	{
		// Summary: Save the object initialization arguments
		friend std::ostream & operator <<(Save_File & log, const LCOH & object);

		// Summary: Read the object from the existing file
		friend std::istream & operator >>(Read_File & log, LCOH & object);

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
		// P_H: heat capacity
		// FLH_H: equivalent full load hours for heat production
		// etaH: conversion efficiency in lower heating value (LHV) of heat
		LCOH(const Physical_Quantity & C = C0,
			const Physical_Quantity & LB = LB0,
			const Physical_Quantity & LT = LT0,
			const Physical_Quantity & FOM = FOM0,
			const Physical_Quantity & VOM = VOM0,
			const Physical_Quantity & FC = FC0,
			const Coefficient & r = r0,
			const Coefficient & i = i0,
			const Physical_Quantity & P_H = P_H0,
			const Physical_Quantity & FLH_H = FLH_H0,
			const Coefficient & etaH = etaH0);
		LCOH(const LCOH &);
		~LCOH();
		

		inline const Physical_Quantity & get_P_H() const;

		inline const Physical_Quantity & get_FLH_H() const;

		inline const Coefficient & get_etaH() const;

		inline void change_P_H(const double & new_magnitude);

		inline void change_FLH_H(const double & new_magnitude);

		inline void change_etaH(const double & new_magnitude);

		inline static double alpha(Physical_Quantity & LT, Coefficient & r);

		inline static double EH(Physical_Quantity & P_EH, Physical_Quantity & FLH);


		/* Methods possibly hidden */

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
		static const std::size_t & get_count ();

		// Summary: Save the protected object initialization arguments
		virtual std::ostream & save_public(std::ostream & outfile) const;

		Physical_Quantity C;
		Physical_Quantity LB;
		Physical_Quantity LT;
		Physical_Quantity FOM;
		Physical_Quantity VOM;
		Physical_Quantity FC;
		Coefficient r;
		Coefficient i;

	protected:
		// Summary: Obtain the class id name of the file storing a LCOH object 
		//	Find the first "#" in a string and delete chars before "#" (including "#")
		//	The class id (std::string) is labbeled by a "#" in front of it 
		static const std::string & find_class_id(std::string & str);

	private:
		Physical_Quantity P_H;
		Physical_Quantity FLH_H;
		Coefficient etaH;

		// Summary: Save the protected object initialization arguments
		virtual std::ostream & save_private(std::ostream & outfile) const;

		// The number of the class objects
		static std::size_t count;

	};

	class LCOE : public LCOH
	{
		// Summary: Save the object initialization arguments
		friend std::ostream & operator <<(Save_File & log, const LCOE & object);

		// Summary: Read the object from the existing file
		friend std::istream & operator >>(Read_File & log, LCOE & object);

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
		// P_E: electricity capacity
		// FLH_E: equivalent full load hours for electrcity production
		// etaE: conversion efficiency in lower heating value (LHV) of electrcity
		LCOE(const Physical_Quantity & C = C0,
			const Physical_Quantity & LB = LB0,
			const Physical_Quantity & LT = LT0,
			const Physical_Quantity & FOM = FOM0,
			const Physical_Quantity & VOM = VOM0,
			const Physical_Quantity & FC = FC0,
			const Coefficient & r = r0,
			const Coefficient & i = i0,
			const Physical_Quantity & REV = REV0,
			const Physical_Quantity & dv = dv0,
			const Coefficient & d = d0,
			const Physical_Quantity & P_E = P_E0,
			const Physical_Quantity & FLH_E = FLH_E0,
			const Coefficient & etaE = etaE0);
		LCOE(const LCOE &);
		~LCOE();

		inline const Physical_Quantity & get_P_E() const;

		inline const Physical_Quantity & get_FLH_E() const;

		inline const Coefficient & get_etaE() const;

		inline void change_P_E(const double & new_magnitude);

		inline void change_FLH_E(const double & new_magnitude);

		inline void change_etaE(const double & new_magnitude);

		/*Methods rewritten*/

		inline static double I(Physical_Quantity & C, Physical_Quantity & LB, Coefficient & i, 
			Physical_Quantity & LT, Coefficient & r, Coefficient & d);

		inline static double OM(Physical_Quantity & FOM, Physical_Quantity & VOM, const double & EH, 
			Physical_Quantity & REV, Physical_Quantity & dv);

		// Summary: Get the number of the class objects
		static const std::size_t & get_count();

		// Summary: Save the protected object initialization arguments
		std::ostream & save_public(std::ostream & outfile) const override;

		Physical_Quantity REV;
		Physical_Quantity dv;
		Coefficient d;

	private:
		Physical_Quantity P_E;
		Physical_Quantity FLH_E;
		Coefficient etaE;

		// Summary: Save the protected object initialization arguments
		std::ostream & save_private(std::ostream & outfile) const override;

		// The number of the class objects
		static std::size_t count;

	};

	class LCOH_CHP : public LCOH
	{
		// Summary: Save the object initialization arguments
		friend std::ostream & operator <<(Save_File & log, const LCOH_CHP & object);

		// Summary: Read the object from the existing file
		friend std::istream & operator >>(Read_File & log, LCOH_CHP & object);

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
		LCOH_CHP(const Physical_Quantity & C = C0,
			const Physical_Quantity & LB = LB0,
			const Physical_Quantity & LT = LT0,
			const Physical_Quantity & FOM = FOM0,
			const Physical_Quantity & VOM = VOM0,
			const Physical_Quantity & FC = FC0,
			const Coefficient & r = r0,
			const Coefficient & i = i0,
			const Physical_Quantity & P_E = P_E0,
			const Physical_Quantity & P_H = P_H0,
			const Physical_Quantity & FLH_E = FLH_E0,
			const Physical_Quantity & FLH_H = FLH_H0,
			const Coefficient & etaE = etaE0,
			const Coefficient & etaH = etaH0,
			const Physical_Quantity & EP = EP0);
		LCOH_CHP(const LCOH_CHP &);
		~LCOH_CHP();

		inline const Physical_Quantity & get_EP() const;

		inline void change_EP(const double & new_magnitude);

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
		static const std::size_t & get_count();

		// Summary: Save the protected object initialization arguments
		virtual std::ostream & save_public(std::ostream & outfile) const override;

		Physical_Quantity P_E;
		Physical_Quantity P_H;
		Physical_Quantity FLH_E;
		Physical_Quantity FLH_H;
		Coefficient etaE;
		Coefficient etaH;

	private:
		Physical_Quantity EP;

		// Summary: Save the protected object initialization arguments
		virtual std::ostream & save_private(std::ostream & outfile) const override;

		// The number of the class objects
		static std::size_t count;

	};

	class LCOE_CHP : public LCOH_CHP
	{
		// Summary: Save the object initialization arguments
		friend std::ostream & operator <<(Save_File & log, const LCOE_CHP & object);

		// Summary: Read the object from the existing file
		friend std::istream & operator >>(Read_File & log, LCOE_CHP & object);

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
		LCOE_CHP(const Physical_Quantity & C = C0, 
			const Physical_Quantity & LB = LB0, 
			const Physical_Quantity & LT = LT0, 
			const Physical_Quantity & FOM = FOM0, 
			const Physical_Quantity & VOM = VOM0, 
			const Physical_Quantity & FC = FC0, 
			const Coefficient & r = r0, 
			const Coefficient & i = i0, 
			const Physical_Quantity & P_E = P_E0,
			const Physical_Quantity & P_H = P_H0, 
			const Physical_Quantity & FLH_E = FLH_E0, 
			const Physical_Quantity & FLH_H = FLH_H0, 
			const Coefficient & etaE = etaE0, 
			const Coefficient & etaH = etaH0, 
			const Physical_Quantity & HP = HP0);
		LCOE_CHP(const LCOE_CHP &);
		~LCOE_CHP();

		inline const Physical_Quantity & get_HP() const;

		inline void change_HP(const double & new_magnitude);

		// Summary: Get the number of the class objects
		static const std::size_t & get_count();
	
	private:
		Physical_Quantity HP;

		// Summary: Save the protected object initialization arguments
		std::ostream & save_private(std::ostream & outfile) const;

		// The number of the class objects
		static std::size_t count;

	};

	
	/* Inline functions of LCOH */

	// Summary: Get the heat capacity
	inline const Physical_Quantity & LCOH::get_P_H() const { return P_H; }

	// Summary: Get the equivalent full load hours for heat production
	inline const Physical_Quantity & LCOH::get_FLH_H() const { return FLH_H; }

	// Summary: Get the conversion efficiency in lower heating value(LHV) of heat
	inline const Coefficient & LCOH::get_etaH() const { return etaH; }

	// Summary: Change the heat capacity
	inline void LCOH::change_P_H(const double & new_magnitude) { P_H.change_magnitude(new_magnitude); }

	// Summary: Change the equivalent full load hours for heat production
	inline void LCOH::change_FLH_H(const double & new_magnitude) { FLH_H.change_magnitude(new_magnitude); }

	// Summary: Change the conversion efficiency in lower heating value(LHV) of heat
	inline void LCOH::change_etaH(const double & new_magnitude) { etaH.change_magnitude(new_magnitude); }

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
	
	// Summary: Get the elelctricity capacity
	inline const Physical_Quantity & LCOE::get_P_E() const { return P_E; }

	// Summary: Get the equivalent full load hours for electrcity production
	inline const Physical_Quantity & LCOE::get_FLH_E() const { return FLH_E; }

	// Summary: Get the conversion efficiency in lower heating value (LHV) of electricity
	inline const Coefficient & LCOE::get_etaE() const { return etaE; }
	
	// Summary: Change the elelctricity capacity
	inline void LCOE::change_P_E(const double & new_magnitude) { P_E.change_magnitude(new_magnitude); }

	// Summary: Change equivalent full load hours for electrcity production
	inline void LCOE::change_FLH_E(const double & new_magnitude) { FLH_E.change_magnitude(new_magnitude); }

	// Summary: Change the conversion efficiency in lower heating value (LHV) of electricity
	inline void LCOE::change_etaE(const double & new_magnitude) { etaE.change_magnitude(new_magnitude); }

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

	// Summary: Getthe elelctricity price
	inline const Physical_Quantity & LCOH_CHP::get_EP() const { return EP; }

	// Summary: Change the elelctricity price
	inline void LCOH_CHP::change_EP(const double & new_magnitude) { EP.change_magnitude(new_magnitude); }

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


	/* Inline functions of LCOE_CHP */

	// Summary: Get the heat price
	inline const Physical_Quantity & LCOE_CHP::get_HP() const { return HP; }

	// Summary: Change the heat price
	inline void LCOE_CHP::change_HP(const double & new_magnitude) { HP.change_magnitude(new_magnitude); }

}
#endif // !__EUSAC__
