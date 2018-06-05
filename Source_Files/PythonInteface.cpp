#include <pybind11/pybind11.h>
#include "../Header_Files/EUSAC_NS.h"

namespace py = pybind11;
namespace escn = eu_subsidies_and_cost_ns;

// 'm' represent the module
PYBIND11_MODULE(example_class, m) {

	// The module explanations
	m.doc() = "This module defines some basic models of the project-based electricty and heat costs";

	py::class_<escn::Physical_Quantity> pq(m, "Physical_Quantity", "Define <class Physical_Quantity>."); pq
	
	// Constructor
	.def(py::init<const double &, const std::string &>(),
		"Define a pet instance.")

}
