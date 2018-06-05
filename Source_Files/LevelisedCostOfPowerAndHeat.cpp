#pragma once
#ifndef LCOPAH
#define LCOPAH
#include "../Header_Files/EUSAC_NS.h"

namespace escn = eu_subsidies_and_cost_ns;

/*----------------------------------------------------------------------------------------------------------------------
* Summary: Construct a physical quantity
* Parameters:
*	m: the magnitude of the physical quantity
*	u: the unit of the physical quantity
* Return : void
----------------------------------------------------------------------------------------------------------------------*/
escn::
Physical_Quantity::Physical_Quantity(const double & m, const std::string & u) : magnitude(&m), unit(&u) { ++count; }

/*----------------------------------------------------------------------------------------------------------------------
* Summary: Destruct a physical quantity
* Return : void
----------------------------------------------------------------------------------------------------------------------*/
escn::
Physical_Quantity::~Physical_Quantity() { --count; }

/*----------------------------------------------------------------------------------------------------------------------
* Summary: Construct a parameter related the calculation of some levelised cost of an energy project
* Parameters:
*	p: the magnitude of the parameter
* Return : void
----------------------------------------------------------------------------------------------------------------------*/
escn::
LvlCost_Parameter::LvlCost_Parameter(double & p) : param(&p), notation() {}


int escn::Physical_Quantity::count(0);

// The decomission cost equals 15% capital overnight cost
extern const double escn::decommisioning_cost_rate(0.15);

// The boiler efficiency
extern const double escn::boiler_efficiency(0.9);

// The interest rate for overnight cost
extern const double escn::interest_rate(0.05);

#endif // !LCOPAH