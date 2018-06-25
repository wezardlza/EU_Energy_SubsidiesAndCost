/***********************************************************************************************************************
Author: Ziang Li
Institution: Control Group, UOM

	This file defines the members of the classes of LCOH, LCOE, LCOH_CHP and LCOE_CHP which are used for the levelised 
	cost of heat/electricty with/without the combined heat and power plant.
***********************************************************************************************************************/
#include "../Header_Files/EUSAC.h"

namespace eu_subsidies_and_cost {

	/*##################################################################################################################
	Class 'Physical_Quantity' 
	==================================================================================================================*/
	// Get the readonly property of the class object
	const std::string & Physical_Quantity::get_symbol() const { return symbol; }
	
	const std::string & Physical_Quantity::get_term() const { return term; }

	const double & Physical_Quantity::get_magnitude() const { return magnitude; }

	const std::string & Physical_Quantity::get_unit() const { return unit; }

	const int & Physical_Quantity::get_count() { return count; }

	void Physical_Quantity::record_row(std::ofstream & ofile) {
		ofile.seekp(0, std::ofstream::end);
		ofile << term << "," << magnitude << "," << unit << std::endl;
	}

	// Constructor
	Physical_Quantity::Physical_Quantity(
		const std::string & symbol, const std::string & term, const double & magnitude, const std::string & unit) :
		symbol(symbol), term(term), magnitude(magnitude), unit(unit) {
		++count;
	}

	Physical_Quantity::Physical_Quantity(const Physical_Quantity & orig) :
		symbol(orig.symbol), term(orig.term), magnitude(orig.magnitude), unit(orig.unit) {
		++count;
	}

	// Destructor
	Physical_Quantity::~Physical_Quantity() { --count; }

	
	/*##################################################################################################################
	Class 'Coefficient' 
	==================================================================================================================*/
	// Read_only value definitions
	const std::string & Coefficient::get_symbol() const { return symbol; }

	const std::string & Coefficient::get_term() const { return term; }

	const double & Coefficient::get_magnitude() const { return magnitude; }

	const int & Coefficient::get_count() { return count; }

	void Coefficient::record_row(std::ofstream & ofile) {
		ofile.seekp(0, std::ofstream::end);
		ofile << term << "," << magnitude << "," << "unitless" << std::endl;
	}

	// Constructor
	Coefficient::Coefficient(const std::string & symbol, const std::string & term, const double & maginitude) :
		symbol(symbol), term(term), magnitude(maginitude) {
		++count;
	}

	Coefficient::Coefficient(const Coefficient & orig) :
		symbol(orig.symbol), term(orig.term), magnitude(orig.magnitude) {
		++count;
	}

	// Destructor
	Coefficient::~Coefficient() { --count; }

	/*##################################################################################################################
	Class 'LCOH' 
	==================================================================================================================*/

	// Member functions
	double LCOH::operator()
		(const double & alpha, const double & I, const double & OM, const double & F, const double & EH) {
		return (alpha * I + OM + F) / EH;
	}

	const int & LCOH::get_count() { return count; }

	// Constructor
	LCOH::LCOH(Physical_Quantity & C, Physical_Quantity & LB, Physical_Quantity & LT, Physical_Quantity & FOM, 
		Physical_Quantity & VOM, Physical_Quantity & FC, Coefficient & r, Coefficient & i, 
		const Physical_Quantity & P_H, const Physical_Quantity & FLH_H, const Coefficient & etaH) : 
		C(C), LB(LB), LT(LT), FOM(FOM), VOM(VOM), FC(FC), r(r), i(i), P_H(P_H), FLH_H(FLH_H), etaH(etaH){
		++count;
	}
	LCOH::LCOH(const LCOH & orig) :
		C(orig.C), LB(orig.LB), LT(orig.LT), FOM(orig.FOM), VOM(orig.VOM), FC(orig.FC), r(orig.r), 
		i(orig.i), P_H(orig.P_H), FLH_H(orig.FLH_H), etaH(orig.etaH) {
		++count;
	}

	// Destructor
	LCOH::~LCOH() { --count; }

	/*##################################################################################################################
	Class 'LCOE' 
	==================================================================================================================*/

	// Member functions
	const int & LCOE::get_count() { return count; }

	// Constructor
	LCOE::LCOE(Physical_Quantity & C, Physical_Quantity & LB, Physical_Quantity & LT, Physical_Quantity & FOM, 
		Physical_Quantity & VOM, Physical_Quantity & FC, Coefficient & r, Coefficient & i,
		Physical_Quantity & REV, Physical_Quantity & dv, Coefficient & d, const Physical_Quantity & P_E, 
		const Physical_Quantity & FLH_E , const Coefficient & etaE) :
		LCOH::LCOH(C, LB, LT, FOM, VOM, FC, r, i), REV(REV), dv(dv), d(d), P_E(P_E), FLH_E(FLH_E), etaE(etaE) {
		++count;
	}
	LCOE::LCOE(const LCOE & orig) :
		LCOH::LCOH(orig), REV(orig.REV), dv(orig.dv), d(orig.d), FLH_E(orig.FLH_E), etaE(orig.etaE) {
		++count;
	}

	// Destructor
	LCOE::~LCOE() { --count; }

	/*##################################################################################################################
	Class 'LCOH_CHP'
	==================================================================================================================*/
	// Member functions
	double LCOH_CHP::operator () (const double & alpha, const double & I, const double & OM, const double & F,
		const double & EH, const double bp_revenue) {
		return (alpha * I + OM + F) / EH - bp_revenue;
	}
	const int & LCOH_CHP::get_count() { return count; }

	// Constructor
	LCOH_CHP::LCOH_CHP(Physical_Quantity & C, Physical_Quantity & LB, Physical_Quantity & LT, Physical_Quantity & FOM, 
		Physical_Quantity & VOM, Physical_Quantity & FC, Coefficient & r, Coefficient & i, Physical_Quantity & P_E,
		Physical_Quantity & P_H, Physical_Quantity & FLH_E, Physical_Quantity & FLH_H, Coefficient & etaE, 
		Coefficient & etaH, const Physical_Quantity & EP) :
		LCOH::LCOH(C, LB, LT, FOM, VOM, FC, r, i), P_E(P_E), P_H(P_H), FLH_E(FLH_E), FLH_H(FLH_H), etaE(etaE), 
		etaH(etaH), EP(EP) {
		++count;
	}
	LCOH_CHP::LCOH_CHP(const LCOH_CHP & orig) : 
		LCOH::LCOH(orig), P_E(orig.P_E), P_H(orig.P_H), FLH_E(orig.FLH_E), FLH_H(orig.FLH_H), etaE(orig.etaE), 
		etaH(orig.etaH), EP(orig.EP) {
		++count; 
	}

	// Destructor
	LCOH_CHP::~LCOH_CHP() { --count; }

	/*##################################################################################################################
	Class 'LCOE_CHP'
	==================================================================================================================*/
	// Member functions
	const int & LCOE_CHP::get_count() { return count; }

	// Constructor
	LCOE_CHP::LCOE_CHP(Physical_Quantity & C, Physical_Quantity & LB, Physical_Quantity & LT, Physical_Quantity & FOM,
		Physical_Quantity & VOM, Physical_Quantity & FC, Coefficient & r, Coefficient & i, Physical_Quantity & P_E, 
		Physical_Quantity & P_H, Physical_Quantity & FLH_E, Physical_Quantity & FLH_H, Coefficient & etaE, 
		Coefficient & etaH, const Physical_Quantity & HP) :
		LCOH_CHP::LCOH_CHP(C, LB, LT, FOM, VOM, FC, r, i, P_E, P_H, FLH_E, FLH_H, etaE, etaH), HP(HP) {
		++count;
	}
	LCOE_CHP::LCOE_CHP(const LCOE_CHP & orig) : LCOH_CHP::LCOH_CHP(orig), HP(orig.HP) {
		++count;
	}

	// Destructor
	LCOE_CHP::~LCOE_CHP() { --count; }

	/*##################################################################################################################
	Static counters of each class
	==================================================================================================================*/

	// The number of Physical_Quantity objects
	int Physical_Quantity::count(0);

	// The number of Coeffcient objects
	int Coefficient::count(0);

	// The number of LCOH objects
	int LCOH::count(0);

	// The number of LCOE objects
	int LCOE::count(0);

	// The number of LCOH_CHP objects
	int LCOH_CHP::count(0);

	// The number of LCOE_CHP objects
	int LCOE_CHP::count(0);

	/*##################################################################################################################
	Cosntant values
	==================================================================================================================*/

	extern const double decommisioning_cost_factor(0.15);

	extern const double boiler_efficiency(0.9);

	extern const double interest_rate(0.05);

}
