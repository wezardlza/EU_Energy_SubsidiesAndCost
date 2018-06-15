#include "../Header_Files/EUSAC_NS.h"

namespace eu_subsidies_and_cost_ns {

	/*##################################################################################################################
	Class 'Physical_Quantity' 
	==================================================================================================================*/
	// Get the readonly property of the class object
	const std::string & Physical_Quantity::get_term() const { return term; }

	const double & Physical_Quantity::get_magnitude() const { return magnitude; }

	const std::string & Physical_Quantity::get_unit() const { return unit; }

	const int & Physical_Quantity::get_count() { return count; }

	// Constructor
	Physical_Quantity::Physical_Quantity(
		const std::string & term, const double & magnitude, const std::string & unit) :
		term(term), magnitude(magnitude), unit(unit) {
		++count;
	}

	Physical_Quantity::Physical_Quantity(const Physical_Quantity & orig) :
		term(orig.term), magnitude(orig.magnitude), unit(orig.unit) {
		++count;
	}

	// Destructor
	Physical_Quantity::~Physical_Quantity() { --count; }

	
	/*##################################################################################################################
	Class 'Coefficient' 
	==================================================================================================================*/
	// Read_only value definitions
	const double & Coefficient::get_magnitude() const { return maginitude; }

	const std::string & Coefficient::get_explanation() const { return explanation; }

	const int & Coefficient::get_count() { return count; }

	// Constructor
	Coefficient::Coefficient(const double & maginitude, const std::string & explanation) :
		maginitude(maginitude), explanation(explanation) {
		++count;
	}

	Coefficient::Coefficient(const eu_subsidies_and_cost_ns::Coefficient & orig) :
		maginitude(orig.maginitude), explanation(orig.explanation) {
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
		Physical_Quantity & VOM, Physical_Quantity & P, Physical_Quantity & FC, Coefficient & r, Coefficient & i,
		const Physical_Quantity & FLH_H = Physical_Quantity("Full load hours of heat", 0.0, "h"),
		const Coefficient & etaH = Coefficient(1.0, "Conversion efficiency in LHV of heat")) : 
		C(C), LB(LB), LT(LT), FOM(FOM), VOM(VOM), P(P), FC(FC), r(r), i(i), FLH_H(FLH_H), etaH(etaH){
		++count;
	}
	LCOH::LCOH(const LCOH & orig) :
		C(orig.C), LB(orig.LB), LT(orig.LT), FOM(orig.FOM), VOM(orig.VOM), P(orig.P), FC(orig.FC), r(orig.r), i(orig.i),
		FLH_H(orig.FLH_H), etaH(orig.etaH) {
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
		Physical_Quantity & VOM, Physical_Quantity & P, Physical_Quantity & FC, Coefficient & r, Coefficient & i,
		Physical_Quantity & REV, Physical_Quantity & dv, Coefficient & d,
		const Physical_Quantity & FLH_E = Physical_Quantity("Full load hours of electrcity", 0.0, "h"),
		const Coefficient & etaE = Coefficient(1.0, "Conversion efficiency in LHV of electricity")) :
		LCOH::LCOH(C, LB, LT, FOM, VOM, P, FC, r, i), REV(REV), dv(dv), d(d), FLH_E(FLH_E), etaE(etaE){
		++count;
	}
	LCOE::LCOE(const LCOE & orig) :
		LCOH::LCOH(orig), REV(orig.REV), dv(orig.dv), d(orig.d), FLH_E(orig.FLH_E), etaE(orig.etaE){
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
		Physical_Quantity & VOM, Physical_Quantity & P, Physical_Quantity & FC, Coefficient & r, Coefficient & i,
		Physical_Quantity & FLH_E, Physical_Quantity & FLH_H, Coefficient & etaE, Coefficient & etaH,
		const Physical_Quantity & EP = Physical_Quantity("Wholesale electricity price", 0.0, "Euros/MWh")) :
		LCOH::LCOH(C, LB, LT, FOM, VOM, P, FC, r, i), FLH_E(FLH_E), FLH_H(FLH_H), etaE(etaE), etaH(etaH), EP(EP) {
		++count;
	}
	LCOH_CHP::LCOH_CHP(const LCOH_CHP & orig) : 
		LCOH::LCOH(orig), FLH_E(orig.FLH_E), FLH_H(orig.FLH_H), etaE(orig.etaE), etaH(orig.etaH), EP(orig.EP) {
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
		Physical_Quantity & VOM, Physical_Quantity & P, Physical_Quantity & FC, Coefficient & r, Coefficient & i,
		Physical_Quantity & FLH_E, Physical_Quantity & FLH_H, Coefficient & etaE, Coefficient & etaH,
		const Physical_Quantity & HP = Physical_Quantity("Wholesale heat price", 0.0, "Euros/MWh")) :
		LCOH_CHP::LCOH_CHP(C, LB, LT, FOM, VOM, P, FC, r, i, FLH_E, FLH_H, etaE, etaH), HP(HP) {
		++count;
	}
	LCOE_CHP::LCOE_CHP(const LCOE_CHP & orig) : LCOH_CHP::LCOH_CHP(orig), HP(orig.HP) {
		++count;
	}

	// Destructor
	LCOE_CHP::~LCOE_CHP() { --count; }

}

/*######################################################################################################################
Static counters of each classes
======================================================================================================================*/

// The number of Physical_Quantity objects
int eu_subsidies_and_cost_ns::Physical_Quantity::count(0);

// The number of Physical_Quantity objects
int eu_subsidies_and_cost_ns::Coefficient::count(0);

/*######################################################################################################################
Cosntant values
======================================================================================================================*/

extern const double eu_subsidies_and_cost_ns::decommisioning_cost_factor(0.15);

extern const double eu_subsidies_and_cost_ns::boiler_efficiency(0.9);

extern const double eu_subsidies_and_cost_ns::interest_rate(0.05);
