#pragma once
#ifndef LCOPAH
#define LCOPAH
#include "../Header_Files/EUSAC_NS.h"

namespace escn = eu_subsidies_and_cost_ns;


/*######################################################################################################################
Class 'Physical_Quantity'
========================================================================================================================
Get the readonly property of the class object
----------------------------------------------------------------------------------------------------------------------*/

const double escn::Physical_Quantity::get_magnitude() const { return magnitude; }

const std::string escn::Physical_Quantity::get_unit() const { return unit; }

int escn::Physical_Quantity::get_count() { return count; }

/*======================================================================================================================
Construct a physical quantity
----------------------------------------------------------------------------------------------------------------------*/
escn::Physical_Quantity::Physical_Quantity(const double & magnitude, const std::string & unit) :
	magnitude(magnitude), unit(unit) {
	++count;
}

escn::Physical_Quantity::Physical_Quantity(const Physical_Quantity & orig) :
	magnitude(orig.magnitude), unit(orig.unit) {
	++count;
}

/*======================================================================================================================
Destruct a physical quantity
----------------------------------------------------------------------------------------------------------------------*/
escn::Physical_Quantity::~Physical_Quantity() { --count; }


/*######################################################################################################################
Class 'LvlCost_Parameter'
========================================================================================================================
Construct a levelised-cost parameter
----------------------------------------------------------------------------------------------------------------------*/
escn::LvlCost_Parameter::LvlCost_Parameter(
	const double & param, const std::string & notation, const std::string & explanation) :
	param(param), notation(notation), explanation(explanation) {
	++count;
}

escn::LvlCost_Parameter::LvlCost_Parameter(const escn::LvlCost_Parameter & orig) :
	param(orig.param), notation(orig.notation), explanation(orig.explanation) {
	++count;
}

/*======================================================================================================================
Read_only value definitions
----------------------------------------------------------------------------------------------------------------------*/
const double escn::LvlCost_Parameter::get_param() const { return param; }

const std::string escn::LvlCost_Parameter::get_notation() const { return notation; }

const std::string escn::LvlCost_Parameter::get_explanation() const { return explanation; }

int escn::LvlCost_Parameter::get_count() { return count; }


/*######################################################################################################################
Static counters of each classes
======================================================================================================================*/

// The number of Physical_Quantity objects
int escn::Physical_Quantity::count(0);

// The number of Physical_Quantity objects
int escn::LvlCost_Parameter::count(0);

/*######################################################################################################################
Cosntant values
======================================================================================================================*/

extern const double escn::decommisioning_cost_rate(0.15);

extern const double escn::boiler_efficiency(0.9);

extern const double escn::interest_rate(0.05);

#endif // !LCOPAH