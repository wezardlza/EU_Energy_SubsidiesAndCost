#include <pybind11/pybind11.h>
#include <pybind11/iostream.h>
#include "../Header_Files/EUSAC.h"
#include "../Header_Files/SRF.h"
#include "../Header_Files/ZAMATH.h"

namespace py = pybind11;
namespace escn = eu_subsidies_and_cost;
extern const escn::Physical_Quantity & escn::C0;
extern const escn::Physical_Quantity & escn::LB0;
extern const escn::Physical_Quantity & escn::LT0;
extern const escn::Physical_Quantity & escn::FOM0;
extern const escn::Physical_Quantity & escn::VOM0;
extern const escn::Physical_Quantity & escn::FC0;
extern const escn::Physical_Quantity & escn::REV0;
extern const escn::Physical_Quantity & escn::dv0;
extern const escn::Physical_Quantity & escn::P_E0;
extern const escn::Physical_Quantity & escn::P_H0;
extern const escn::Physical_Quantity & escn::FLH_E0;
extern const escn::Physical_Quantity & escn::FLH_H0;
extern const escn::Physical_Quantity & escn::EP0;
extern const escn::Coefficient & escn::r0;
extern const escn::Coefficient & escn::i0;
extern const escn::Coefficient & escn::d0;
extern const escn::Coefficient & escn::etaE0;
extern const escn::Coefficient & escn::etaH0;
extern const escn::Physical_Quantity & escn::HP0;

// 'm' represent the module
PYBIND11_MODULE(EUSAC, m) {
	
	/* Module document */

	m.doc() = "This module defines some basic models of the project-based electricty and heat costs";

	
	/* Module class alias */

	py::class_<File_Address> file_address_(m, "File_Address", "Define <class File_Address>.");
	py::class_<File_Stream> file_stream_(m, "File_Stream", "Define <class File_Stream>.");
	py::class_<Read_File> read_file_(m, "Read_File", "Define <class Read_File>.");
	py::class_<Save_File> save_file_(m, "Save_File", "Define <class Save_File>.");
	py::class_<escn::Coefficient> coefficient(m, "Coefficient", "Define <class Coefficient>.");
	py::class_<escn::Physical_Quantity, escn::Coefficient> physical_qautity(
		m, "Physical_Quantity", "Define <class Physical_Quantity>.");
	py::class_<escn::LCOH> lcoh(m, "LCOH", "Define <class LCOH>.");
	

	/* Class definition */
	
	/* Class File_Address */

	file_address_.def(py::init<const std::string &>(),
		"Summary: Construct an address to store the file"
		"\nname: name of the file ")
		.def_readwrite_static("directory", &File_Address::directory, 
			"directory of the succeeding files, default is \"./ \"")
		.def_readwrite_static("format", &File_Address::format, "format of the succeeding files, default is \".csv\"")
		.def_readwrite("file_name", &File_Address::file_name, "name of the file ")
		.def("file_address", &File_Address::file_address)
		.def_static("is_file_acessible", &File_Address::is_file_acessible)
		;


	/* Class File_Stream */
	
	file_stream_.def(py::init<const std::string &, const std::string &, const std::string &,
		const std::ios_base::openmode &>(),
		"Summary: Construct an address to store the file"
		"\nfile_name: name of the file"
		"\ndirectory: directory of the succeeding files, default is \"./\""
		"\nformat: format of the succeeding files, default is \".csv\""
		"\nfile_mode: file mode of the succeeding files, default is \"std::ios_base::in\"")
		.def_readwrite_static("file_mode", &File_Stream::file_mode)

		.def("change_file_attributes", 
		(void (File_Stream::*)(const std::string & file_name, const std::string & directory,
			const std::string & format, const std::ios_base::openmode & file_mode)) 
			&File_Stream::change_file_attributes, 
			"Summary: Change the name, directory, format, or open mode of the file")
		.def("change_file_attributes",
		(void (File_Stream::*)(const std::string & file_name, const std::string & directory,
			const std::string & format))
			&File_Stream::change_file_attributes,
			"Summary: Change the name, directory, or formatof the file")
		.def("change_file_attributes",
		(void (File_Stream::*)(const std::ios_base::openmode & file_mode))
			&File_Stream::change_file_attributes,
			"Summary: Change the open mode of the file")
		.def("change_file_attributes",
		(void (File_Stream::*)(const std::string & file_name))
			&File_Stream::change_file_attributes,
			"Summary: Change the name of the file")
		.def("get_file_adddress", &File_Stream::get_file_address)
		.def("get_file_name", &File_Stream::get_file_name)
		;

	/* Class Save_File */

	/* From the author's perspective, istream is not easily supported due to pybind11 limitation, a function
	is defined to offer just save function interface */

	m.def("save", [](const escn::LCOH &lcoh_object, const std::string &name, const std::string &directory, 
		const std::string &format) {
		File_Stream A_file_strm(name, directory, format, std::iostream::out);
		Save_File A_file_saving(A_file_strm.file);
		A_file_saving << lcoh_object << std::endl; }, 
		"Summary: Save a LCOH instance"
			"\nlcoh_object: a LCOH instance"
			"\nname: name of the file"
			"\ndirectory: directory of the succeeding files. \"./\" is the current folder"
			"\nformat:format of the succeeding files, default is \"csv\"");

	/* Class Read_File */

	/* From the author's perspective, istream is not easily supported due to pybind11 limitation, a function
	is defined to offer just save function interface */

	m.def("read", [](const escn::LCOH &lcoh_object, const std::string &name, const std::string &directory,
		const std::string &format) {
		File_Stream A_file_strm(name, directory, format, std::iostream::out);
		Save_File A_file_saving(A_file_strm.file);
		A_file_saving << lcoh_object << std::endl;
	});

	/* Class Coefficient */

	coefficient.def(py::init<const std::string &, const std::string &, const double &>(),
			"Summary: Construct a coefficient, related the calculation of some levelised cost of an energy project"
			"\nParameters:"
			"\narg0 symbol: the symbol or abbrevation of the object"
			"\narg1 term: the additional explantions of the object"
			"\narg2 magnitude: the magnitude of the object")
		.def(py::init<escn::Coefficient &>(), "Summary: Define a cefficient with copy constructor")
		.def(py::init<>(), "Default coefficient")
		.def("get_symbol", &escn::Coefficient::get_symbol, "Summary: Get the symbol of the physical quantity")
		.def("get_term", &escn::Coefficient::get_term, "Summary: Get the physical explanation of the coefficient")
		.def("get_magnitude", &escn::Coefficient::get_magnitude, "Summary: Get the magnitude of the coefficient")
		.def("change_magnitude", &escn::Coefficient::change_magnitude, "Summary: Rewrite the magnitude")
		.def_static("get_count", &escn::Coefficient::get_count, "Summary: Get the number of the class objects")
		.def_property_readonly("symbol", &escn::Coefficient::get_symbol, "symbol of the physical quantity")
		.def_property_readonly("term", &escn::Coefficient::get_term, "physical explanation of the coefficient")
		.def_property("magnitude", &escn::Coefficient::get_magnitude, &escn::Coefficient::change_magnitude, 
			"magnitude of the coefficient")
		// .def_property_readonly_static("count", &escn::Coefficient::get_count)

		.def("cprint", [](escn::Coefficient & coeff) {
		py::scoped_ostream_redirect output; 
		std::cout << coeff << std::endl;}, "Summary: Output the class instance")
		;
	
	
	/* Class Physical_Quantity */

	physical_qautity.def(py::init<const std::string &, const std::string &, const double &, const std::string &>(),
			"Summary: Define a physical quantity"
			"\nParameters:"
			"\narg0 symbol: the symbol or abbrevation of the object"
			"\narg1 term: the additional explantions of the object"
			"\narg2 magnitude: the magnitude of the object"
			"\narg3 unit: unit of the physical quantity")
		.def(py::init<escn::Physical_Quantity &>(), "Summary: Define a physical quantity with copy constructor")
		.def(py::init<>(), "Default physical quantity")
		.def("get_unit", &escn::Physical_Quantity::get_unit, "Summary: Get the unit of the physical quantity")
		.def_static("get_count", &escn::Physical_Quantity::get_count, "Summary: Get the number of the class objects")
		.def("get_unit", &escn::Physical_Quantity::get_unit, "Summary: Get the unit of the physical quantity")

		.def("cprint", [](escn::Physical_Quantity & pq) {
		py::scoped_ostream_redirect output;
		std::cout << pq << std::endl; }, "Summary: Output the class instance")
		;
	

	/* Constant */

	m.def("C0", []() {return escn::C0; }, "Default capital cost")
		.def("LB0", []() {return escn::LB0; }, "Default_cosntruction period")
		.def("LT0", []() {return escn::LT0; }, "Default project duration")
		.def("FOM0", []() {return escn::FOM0; }, "Default fixed OM cost")
		.def("VOM0", []() {return escn::VOM0; }, "Default variable OM cost")
		.def("FC0", []() {return escn::FC0; }, "Default fuel costs per unit of enengy input")
		.def("REV0", []() {return escn::REV0; }, "Default variable by-product revenue")
		.def("dv0", []() {return escn::dv0; }, "Not sure the physicial meaning yet")
		.def("P_E0", []() {return escn::P_E0; }, "Default electricity capacity")
		.def("P_H0", []() {return escn::P_H0; }, "Default capital cost")
		.def("FLH_E0", []() {return escn::FLH_E0; },
			"Default equivalent full load hours for electrcity production")
		.def("FLH_H0", []() {return escn::FLH_H0; },
			"Default equivalent full load hours for heat production")
		.def("EP0", []() {return escn::EP0; },
			"Defacult electricity price a CHP intallation receives for electricity production as by-product")
		.def("r0;", []() {return escn::r0; }, "Default weighted average cost of capital (WACC)")
		.def("i0;", []() {return escn::i0; }, "Default interest rate over the construction loan")
		.def("d0;", []() {return escn::d0; }, "Default decommisioning cost factor")
		.def("etaE0;", []() {return escn::etaE0; },
			"Default conversion efficiency in lower heating value (LHV) of electrcity")
		.def("etaH0;", []() {return escn::etaH0; },
			"Default conversion efficiency in lower heating value (LHV) of heat")
		.def("HP0", []() {return escn::HP0; },
			"Default heat price a CHP intallation receives for heat production as by-product")
		;


	/* Class LCOH */

	lcoh.def(py::init<
		const escn::Physical_Quantity &,
		const escn::Physical_Quantity &,
		const escn::Physical_Quantity &,
		const escn::Physical_Quantity &,
		const escn::Physical_Quantity &,
		const escn::Physical_Quantity &,
		const escn::Coefficient &,
		const escn::Coefficient &,
		const escn::Physical_Quantity &,
		const escn::Physical_Quantity &,
		const escn::Coefficient &>(),
		"Summary: Construct an object to manage the calculation of the LCOH"
		"\nC: captial cost"
		"\nLB: cosntruction period"
		"\nLT: project duration"
		"\nFOM: fixed OM cost"
		"\nVOM: variable OM cost"
		"\nP_H: heat capacity"
		"\nFC: fuel costs per unit of enengy input"
		"\nr: weighted average cost of capital (WACC)"
		"\ni: interest rate over the construction loan"
		"\nP_H: heat capacity"
		"\nFLH_H: equivalent full load hours for heat production"
		"\netaH: conversion efficiency in lower heating value (LHV) of heat)")
		.def(py::init<const escn::LCOH &>(), "Summary: Define a LCOH instance with copy constructor")
		.def(py::init<>(), "Default LCOH instance")
		
		.def_property("P_H", &escn::LCOH::get_P_H, &escn::LCOH::change_P_H, 
			"Summary: Get the heat capacity")
		.def_property("FLH_H", &escn::LCOH::get_FLH_H, &escn::LCOH::change_FLH_H, 
			"Summary: Get the equivalent full load hours for heat production")
		.def_property("etaH", &escn::LCOH::get_etaH, &escn::LCOH::change_etaH, 
			"Summary: Get the conversion efficiency in lower heating value(LHV) of heat")
		
		.def("alpha", &escn::LCOH::alpha, "Summary: Capital recovery factor")
		.def("EH", &escn::LCOH::EH, "Summary: Electricity or heat produced annually")
		.def("I", &escn::LCOH::I, 
			"Summary: Investment cost including finance cost for construction at a predefined interest rate")
		.def("OM", &escn::LCOH::OM, "Summary: Operation and maintainance cost")
		.def("F", &escn::LCOH::F, "Summary: Annual fuel cost")

		.def("__call__", [](escn::LCOH & self, double & alpha, const double & I, const double & OM, const double & F,
			const double & EH) {return self(alpha, I, OM, F, EH); })
		.def("get_count", &escn::LCOH::get_count, "Summary: Get the number of the class objects")

		.def_readwrite("C", &escn::LCOH::C, "captial cost")
		.def_readwrite("LB", &escn::LCOH::LB, "cosntruction period")
		.def_readwrite("LT", &escn::LCOH::LT, "project duration")
		.def_readwrite("FOM", &escn::LCOH::FOM, "fixed OM cost")
		.def_readwrite("VOM", &escn::LCOH::VOM, "variable OM cost")
		.def_readwrite("FC", &escn::LCOH::FC, "fuel cost")
		.def_readwrite("r", &escn::LCOH::r, "weighted average cost of capital(WACC)")		
		.def_readwrite("i", &escn::LCOH::i, "interest rate over the construction loan")		
		.def("cprint", [](escn::LCOH &lcoh_object) {
		py::scoped_ostream_redirect output;
		Save_File sf(std::cout); 
		sf << lcoh_object; })
		;										
		

}
