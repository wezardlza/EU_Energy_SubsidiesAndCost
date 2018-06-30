#include <pybind11/pybind11.h>
#include "../Header_Files/EUSAC.h"
#include "../Header_Files/SRF.h"
#include "../Header_Files/ZAMATH.h"

namespace py = pybind11;
namespace escn = eu_subsidies_and_cost;

// 'm' represent the module
PYBIND11_MODULE(EUSAC, m) {

	/* Module explanations */

	m.doc() = "This module defines some basic models of the project-based electricty and heat costs";
	

	py::class_<escn::Coefficient> coefficient(
		m, "Coefficient", "Define <class Coefficient>.");
	py::class_<escn::Physical_Quantity, escn::Coefficient> physical_qautity(
		m, "Physical_Quantity", "Define <class Physical_Quantity>.");

	// class definition
	coefficient
		.def(py::init<const std::string &, const std::string &, const double &>(),
			"Summary: Construct a coefficient, related the calculation of some levelised cost of an energy project"
			"\nParameters:"
			"\narg0 symbol: the symbol or abbrevation of the object"
			"\narg1 term: the additional explantions of the object"
			"\narg2 magnitude: the magnitude of the object")
		.def(py::init<escn::Coefficient &>(), "Summary: Define a cefficient with copy constructor")
		.def("get_symbol", &escn::Coefficient::get_symbol, "Summary: Get the symbol of the physical quantity")
		.def("get_term", &escn::Coefficient::get_term, "Summary: Get the physical explanation of the coefficient")
		.def("get_magnitude", &escn::Coefficient::get_magnitude, "Summary: Get the magnitude of the coefficient")
		.def("change_magnitude", &escn::Coefficient::change_magnitude, "Summary: Rewrite the magnitude")
		.def("get_count", &escn::Coefficient::get_count, "Summary: Get the number of the class objects")
		.def_property_readonly("symbol", &escn::Coefficient::get_symbol)
		.def_property_readonly("term", &escn::Coefficient::get_term)
		.def_property("magnitude", &escn::Coefficient::get_magnitude, &escn::Coefficient::change_magnitude)
		.def_property_readonly_static("count", &escn::Coefficient::get_count, py::return_value_policy::copy)
		;

	physical_qautity
		.def(py::init<const std::string &, const std::string &, const double &, const std::string &>(),
			"Summary: Define a physical quantity"
			"\nParameters:"
			"\narg0 symbol: the symbol or abbrevation of the object"
			"\narg1 term: the additional explantions of the object"
			"\narg2 magnitude: the magnitude of the object"
			"\narg3 unit: unit of the physical quantity")
		.def(py::init<escn::Physical_Quantity &>(), "Summary: Define a physical quantity with copy constructor")
		.def("get_unit", &escn::Physical_Quantity::get_unit)
		;
}
