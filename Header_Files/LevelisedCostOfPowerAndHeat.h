#pragma once
#ifndef LCOPAH
#define LCOPAH
#include "EUSAC_NS.h"


/*---------------------------------------------------------------------------------------------------------
* Summary: Construct a physical quantity
* Parameters:
*	m: the maginitude of the physical quantity
*	u: the unit of the physical quantity
* Return : void
----------------------------------------------------------------------------------------------------------*/
template <class Type>
eu_subsidies_and_cost_ns::
	Physical_Quantity<Type>::Physical_Quantity(const Type & m, const string & u):
		magnitude(& m), unit(& u)
		{}

/*---------------------------------------------------------------------------------------------------------
* Summary: Construct a parameter related the calculation of some levelised cost of an energy project
* Parameters:
*	p: the maginitude of the parameter
* Return : void
----------------------------------------------------------------------------------------------------------*/
eu_subsidies_and_cost_ns::
	LvlCost_Parameter::LvlCost_Parameter(double & p): 
		param(& p), notation() {}


#endif // !LCOPAH