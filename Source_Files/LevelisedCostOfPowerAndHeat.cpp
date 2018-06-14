#include "../Header_Files/EUSAC_NS.h"

/*######################################################################################################################
Class 'Physical_Quantity'
========================================================================================================================
Get the readonly property of the class object
----------------------------------------------------------------------------------------------------------------------*/
const std::string eu_subsidies_and_cost_ns::Physical_Quantity::get_term() const { return term; }

const double eu_subsidies_and_cost_ns::Physical_Quantity::get_magnitude() const { return magnitude; }

const std::string eu_subsidies_and_cost_ns::Physical_Quantity::get_unit() const { return unit; }

int eu_subsidies_and_cost_ns::Physical_Quantity::get_count() { return count; }

/*======================================================================================================================
Construct a physical quantity
----------------------------------------------------------------------------------------------------------------------*/
eu_subsidies_and_cost_ns::Physical_Quantity::Physical_Quantity(
	const std::string & term, const double & magnitude, const std::string & unit) :
	term(term), magnitude(magnitude), unit(unit) {
	++count;
}

eu_subsidies_and_cost_ns::Physical_Quantity::Physical_Quantity(const Physical_Quantity & orig) :
	term(orig.term), magnitude(orig.magnitude), unit(orig.unit) {
	++count;
}

/*======================================================================================================================
Destruct a physical quantity
----------------------------------------------------------------------------------------------------------------------*/
eu_subsidies_and_cost_ns::Physical_Quantity::~Physical_Quantity() { --count; }


/*######################################################################################################################
Class 'Coefficient'
========================================================================================================================
Construct a coefficient
----------------------------------------------------------------------------------------------------------------------*/
eu_subsidies_and_cost_ns::Coefficient::Coefficient(
	const double & maginitude, const std::string & explanation) :
	maginitude(maginitude), explanation(explanation) {
	++count;
}

eu_subsidies_and_cost_ns::Coefficient::Coefficient(
	const eu_subsidies_and_cost_ns::Coefficient & orig) :
	maginitude(orig.maginitude), explanation(orig.explanation) {
	++count;
}

/*======================================================================================================================
Read_only value definitions
----------------------------------------------------------------------------------------------------------------------*/
const double eu_subsidies_and_cost_ns::Coefficient::get_magnitude() const { return maginitude; }

const std::string eu_subsidies_and_cost_ns::Coefficient::get_notation() const { return notation; }

const std::string eu_subsidies_and_cost_ns::Coefficient::get_explanation() const { return explanation; }

int eu_subsidies_and_cost_ns::Coefficient::get_count() { return count; }


/*######################################################################################################################
Levelised cost of electricity/heat
======================================================================================================================*/

// Levelised cost of electricity without CHP 
double eu_subsidies_and_cost_ns::LCOE::operator()
(const double & alpha, const double & I, const double & OM, const double & F, const double & E) {
	return (alpha * I + OM + F) / E;
}

// Levelised cost of heat without CHP
double eu_subsidies_and_cost_ns::LCOH::operator()
(const double & alpha, const double & I, const double & OM, const double & F, const double & H) {
	return (alpha * I + OM + F) / H;
}

// Levelised cost of electricity without CHP 
double eu_subsidies_and_cost_ns::LCOE_CHP::operator()
(const double & alpha, const double & I, const double & OM, const double & F, 
	const double & E, const double & H, const double & etaE, const double & etaH, const double & HP, 
	const double & FLH_E, const double & FLH_H) {
	return (alpha * I + OM + F) / E - H * HP * etaH * FLH_H / (etaE * FLH_E);
}

// Levelised cost of heat without CHP
double eu_subsidies_and_cost_ns::
LCOH_CHP(const double & alpha, const double & I, const double & OM, const double & F, 
	const double & H, const double & E, const double & etaH, const double & etaE, const double & EP, 
	const double & FLH_H, const double & FLH_E) {
	return (alpha * I + OM + F) / H - E * EP * etaE * FLH_E / (etaH * FLH_H);
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
