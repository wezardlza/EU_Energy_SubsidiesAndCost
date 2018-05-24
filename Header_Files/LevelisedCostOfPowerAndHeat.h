#pragma once
#ifndef LCOPAH
#define LCOPAH
#include "EUSAC_NS.h"

template <class Type>
eu_subsidies_and_cost_ns::
	Physical_Quantity<Type>::Physical_Quantity(const Type & m, const string & u):
		Physical_Quantity<Type>::magnitude(m),
		Physical_Quantity<Type>::unit(u)
		{}

eu_subsidies_and_cost_ns::
	LvlCost_Parameter::LvlCost_Parameter(double p): 
		param(p) {}

// The interest rate for overnight cost
const double interest_rate(0.05);

#endif // !LCOPAH