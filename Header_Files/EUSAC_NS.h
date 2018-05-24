#pragma once
#ifndef EUSAC_NS
#define EUSAC_NS
#include <string>

using std::string;

namespace eu_subsidies_and_cost_ns {
	template <class Type>
	class Physical_Quantity
	{
	public:
		/*
		m: the maginitude of a physical quantity
		u: the unit of a physical quantity
		*/
		Physical_Quantity(const Type & m, const string &u);

	private:
		const Type magnitude;
		const string unit;
	};

	class LvlCost_Parameter
	{
	public:
		LvlCost_Parameter(double p);
	private:
		double param;
		const string * notation;
		const string * explanantion;
	};

}
#endif // !EUSAC_NS