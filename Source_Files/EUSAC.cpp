/***********************************************************************************************************************
Author: Ziang Li
Institution: Control Group, UOM

	This file defines the members of the classes of LCOH, LCOE, LCOH_CHP and LCOE_CHP which are used for the levelised 
	cost of heat/electricty with/without the combined heat and power plant.
***********************************************************************************************************************/

#include "../Header_Files/EUSAC.h"
#include "../Header_Files/SRF.h"
#include "../Header_Files/ZAMATH.h"
#include <typeinfo>
#include <stdexcept>

namespace eu_subsidies_and_cost {


	/*##################################################################################################################
	Class 'Coefficient' 
	==================================================================================================================*/
	/* Friend */

	std::ostream & operator <<(std::ostream & outfile, const Coefficient & object) {
		outfile << object.symbol << ", ";
		outfile << object.term << ", ";
		outfile << Basic_Maths::string_cast<double>(object.magnitude) << ", ";
		outfile << "unitless";
		return outfile;
	}

	std::istream & operator >>(std::istream & infile, Coefficient & object) {
		std::string str;
		ROW_INDEX i(0);

		while (std::getline(infile, str, ',')) {
			if (i == 2) {
				object.change_magnitude(Basic_Maths::num_cast<double>(str));
				break;
			}
			++i;
		}

#ifdef __DEBUG__
		std::cout << object << std::endl;
#endif // __DEBUG__

		return infile;
	}

	/* Member functions */

	const std::string & Coefficient::get_symbol() const { return symbol; }

	const std::string & Coefficient::get_term() const { return term; }

	const double & Coefficient::get_magnitude() const { return magnitude; }

	double & Coefficient::change_magnitude(const double & new_magnitude) {
		magnitude = new_magnitude;
		return magnitude;
	}

	Coefficient & Coefficient::operator= (const Coefficient & coeff) {
		if (symbol == coeff.symbol && term == coeff.term) {
			magnitude = coeff.magnitude;
		}
		else {
			throw std::runtime_error("The two coefficients have different atrributes.");
		}
		return *this;
	}

	const std::size_t & Coefficient::get_count() { return count; }


	ROW Coefficient::_record() const {
		ROW record;
		record.push_back(symbol);
		record.push_back(term);
		record.push_back(Basic_Maths::string_cast<double>(magnitude));
		record.push_back("unitless");
		return record;
	}


	/* Constructor */

	Coefficient::Coefficient(const std::string & symbol, const std::string & term, const double & maginitude) :
		symbol(symbol), term(term), magnitude(maginitude) {
		++count;
	}

	Coefficient::Coefficient(const Coefficient & orig) :
		symbol(orig.symbol), term(orig.term), magnitude(orig.magnitude) {
		++count;
	}

	/* Destructor */

	Coefficient::~Coefficient() { --count; }

	
	/*##################################################################################################################
	Class 'Physical_Quantity'
	==================================================================================================================*/
	/* Friends */

	std::ostream & operator <<(std::ostream & outfile, const Physical_Quantity & object) {
		outfile << object.symbol << ", ";
		outfile << object.term << ", ";
		outfile << Basic_Maths::string_cast<double>(object.magnitude) << ", ";
		outfile << object.unit;
		return outfile;
	}

	std::istream & operator >>(std::istream & infile, Physical_Quantity & object) {
		std::string str;
		ROW_INDEX i(0);

		while (std::getline(infile, str, ',')) {
			if (i == 2) {
				object.change_magnitude(Basic_Maths::num_cast<double>(str));
				break;
			}
			++i;
		}

#ifdef __DEBUG__
		std::cout << object << std::endl;
#endif // __DEBUG__

		return infile;
	}

	/* Member functions */
	const std::string & Physical_Quantity::get_unit() const { return unit; }

	Physical_Quantity & Physical_Quantity::operator= (const Physical_Quantity & pq) {
		if (symbol == pq.symbol && term == pq.term && unit == pq.unit) {
			magnitude = pq.magnitude;
		}
		else {
			throw std::runtime_error("The two coefficients have different atrributes.");
		}
		return *this;
	}

	const std::size_t & Physical_Quantity::get_count() { return count; }

	ROW Physical_Quantity::_record() const {
		ROW record;
		record.push_back(symbol);
		record.push_back(term);
		record.push_back(Basic_Maths::string_cast<double>(magnitude));
		record.push_back(unit);
		return record;
	}

	/* Constructor */
	Physical_Quantity::Physical_Quantity(
		const std::string & symbol, const std::string & term, const double & magnitude, const std::string & unit) :
		Coefficient::Coefficient(symbol, term, magnitude), unit(unit) {
		++count;
	}

	Physical_Quantity::Physical_Quantity(const Physical_Quantity & orig) :
		Coefficient::Coefficient(orig), unit(orig.unit) {
		++count;
	}

	/* Destructor */

	Physical_Quantity::~Physical_Quantity() { --count; }


	/*##################################################################################################################
	Class 'LCOH' 
	==================================================================================================================*/
	/* Friends */

	std::ostream & operator <<(Save_File & log, const LCOH & object) {
		*log.outfile << "# " << typeid(object).name() << std::endl;
		object.save_public(*log.outfile);
		object.save_private(*log.outfile);
		return *log.outfile;
	}
	
	std::istream & operator >>(Read_File & log, LCOH & object) {
		std::string str;
		std::vector<std::istringstream *> vec;

		// Obatin the class name
		std::getline(*log.infile, str);
		std::string class_id = typeid(object).name();
		if (LCOH::find_class_id(str) != class_id) {
			throw std::runtime_error(
				CONST_LABEL::ERRO + "File: The file cannot assign the value of an object for " + class_id);
		}
		
		while (std::getline(*log.infile, str))
		{
			std::istringstream *ins = nullptr;
			ins->str(str);
			vec.push_back(std::move(ins));			
		}
		*vec[0] >> object.C;
		*vec[1] >> object.LB;
		*vec[2] >> object.LT;
		*vec[3] >> object.FOM;
		*vec[4] >> object.VOM;
		*vec[5] >> object.FC;
		*vec[6] >> object.r;
		*vec[7] >> object.i;
		*vec[8] >> object.P_H;
		*vec[9] >> object.FLH_H;
		*vec[10] >> object.etaH;
		return *log.infile;
	}

	/* Overloaded operator */

	double LCOH::operator()
		(const double & alpha, const double & I, const double & OM, const double & F, const double & EH) {
		return (alpha * I + OM + F) / EH;
	}

	/* Vitual functions */

	double LCOH::run() {
		const double & alpha_ = alpha(LT, r);
		const double & I_ = I(C, LB, i);
		const double & EH_ = EH(P_H, FLH_H);
		const double & OM_ = OM(FOM, VOM, EH_);
		const double & F_ = F(FC, etaH, EH_);
		return (*this)(alpha_, I_, OM_, F_, EH_);
	}

	std::ostream & LCOH::save_public(std::ostream & outfile) const {
		outfile << C << std::endl;
		outfile << LB << std::endl;
		outfile << LT << std::endl;
		outfile << FOM << std::endl;
		outfile << VOM << std::endl;
		outfile << FC << std::endl;
		outfile << r << std::endl;
		outfile << i << std::endl;
		return outfile;
	}

	std::ostream & LCOH::save_private(std::ostream & outfile) const {
		outfile << P_H << std::endl;
		outfile << FLH_H << std::endl;
		outfile << etaH << std::endl;
		return outfile;
	}
	
	const std::string & LCOH::find_class_id(std::string & str) {
		int i = str.find_first_of('#', 0);
		if (i != -1) {
			str.erase(0, i + 1);
			Read_File::Trim(str);
		}
		else
		{
			throw std::runtime_error(CONST_LABEL::ERRO + "No sharp sign located. The data is not class-specified.");
		}
		return str;
	}


	/* Constructor */

	LCOH::LCOH(const Physical_Quantity & C, const Physical_Quantity & LB, const Physical_Quantity & LT, 
		const Physical_Quantity & FOM, const Physical_Quantity & VOM, const Physical_Quantity & FC, 
		const Coefficient & r, const Coefficient & i, const Physical_Quantity & P_H, const Physical_Quantity & FLH_H, 
		const Coefficient & etaH) : 
		C(C), LB(LB), LT(LT), FOM(FOM), VOM(VOM), FC(FC), r(r), i(i), P_H(P_H), FLH_H(FLH_H), etaH(etaH){
		++count;
	}

	LCOH::LCOH(const LCOH & orig) :
		C(orig.C), LB(orig.LB), LT(orig.LT), FOM(orig.FOM), VOM(orig.VOM), FC(orig.FC), r(orig.r), 
		i(orig.i), P_H(orig.P_H), FLH_H(orig.FLH_H), etaH(orig.etaH) {
		++count;
	}

	/* Destructor */

	LCOH::~LCOH() { --count; }


	/*##################################################################################################################
	Class 'LCOE' 
	==================================================================================================================*/
	/* Friends */
	
	/*std::ostream & operator <<(Save_File & log, const LCOE & object) {
		*log.outfile << "# " << typeid(object).name() << std::endl;
		object.save_public(*log.outfile);
		object.save_private(*log.outfile);
		return *log.outfile;
	}*/

	// Summary: Read the object from the existing file
	std::istream & operator >>(Read_File & log, LCOE & object) {
		std::string str;
		std::vector<std::istringstream *> vec;
		while (std::getline(*log.infile, str))
		{
			std::istringstream * ins = nullptr;
			ins->str(str);
			vec.push_back(std::move(ins));
		}
		*vec[0] >> object.C;
		*vec[1] >> object.LB;
		*vec[2] >> object.LT;
		*vec[3] >> object.FOM;
		*vec[4] >> object.VOM;
		*vec[5] >> object.FC;
		*vec[6] >> object.r;
		*vec[7] >> object.i;
		*vec[8] >> object.REV;
		*vec[9] >> object.dv;
		*vec[10] >> object.d;
		*vec[11] >> object.P_E;
		*vec[12] >> object.FLH_E;
		*vec[13] >> object.etaE;
		return *log.infile;

	}


	/* Virtual functions */
	
	double LCOE::run() {
		const double & alpha_ = alpha(LT, r);
		const double & I_ = I(C, LB, i, LT, r, d);
		const double & EH_ = EH(P_E, FLH_E);
		const double & OM_ = OM(FOM, VOM, EH_, REV, dv);
		const double & F_ = F(FC, etaE, EH_);
		return (*this)(alpha_, I_, OM_, F_, EH_);
	}

	std::ostream & LCOE::save_public(std::ostream & outfile) const {
		LCOH::save_public(outfile);
		outfile << REV << std::endl;
		outfile << dv << std::endl;
		outfile << d << std::endl;
		return outfile;
	}

	std::ostream & LCOE::save_private(std::ostream & outfile) const {
		outfile << P_E << std::endl;
		outfile << FLH_E << std::endl;
		outfile << etaE << std::endl;
		return outfile;
	}

	/* Constructor */
	
	LCOE::LCOE(const Physical_Quantity & C, const Physical_Quantity & LB, const Physical_Quantity & LT, 
		const Physical_Quantity & FOM, const Physical_Quantity & VOM, const Physical_Quantity & FC, 
		const Coefficient & r, const Coefficient & i, const Physical_Quantity & REV, const Physical_Quantity & dv, 
		const Coefficient & d, const Physical_Quantity & P_E, const Physical_Quantity & FLH_E , 
		const Coefficient & etaE) :
		LCOH::LCOH(C, LB, LT, FOM, VOM, FC, r, i), REV(REV), dv(dv), d(d), P_E(P_E), FLH_E(FLH_E), etaE(etaE) {
		++count;
	}
	LCOE::LCOE(const LCOE & orig) :
		LCOH::LCOH(orig), REV(orig.REV), dv(orig.dv), d(orig.d), FLH_E(orig.FLH_E), etaE(orig.etaE) {
		++count;
	}

	/* Destructor */
	LCOE::~LCOE() { --count; }


	/*##################################################################################################################
	Class 'LCOH_CHP'
	==================================================================================================================*/
	/* Friends */
	
	/*std::ostream & operator <<(Save_File & log, const LCOH_CHP & object) {
		*log.outfile << "# " << typeid(object).name() << std::endl;
		object.save_public(*log.outfile);
		object.save_private(*log.outfile);
		return *log.outfile;
	}*/

	// Summary: Read the object from the existing file
	std::istream & operator >>(Read_File & log, LCOH_CHP & object) {
		std::string str;
		std::vector<std::istringstream *> vec;
		while (std::getline(*log.infile, str))
		{
			std::istringstream * ins = nullptr;
			ins->str(str);
			vec.push_back(std::move(ins));
		}
		*vec[0] >> object.C;
		*vec[1] >> object.LB;
		*vec[2] >> object.LT;
		*vec[3] >> object.FOM;
		*vec[4] >> object.VOM;
		*vec[5] >> object.FC;
		*vec[6] >> object.r;
		*vec[7] >> object.i;
		*vec[8] >> object.P_E;
		*vec[9] >> object.P_H;
		*vec[10] >> object.FLH_E;
		*vec[11] >> object.FLH_H;
		*vec[12] >> object.etaE;
		*vec[13] >> object.etaH;
		*vec[14] >> object.EP;
		return *log.infile;
	}

	/* Member functions */
	
	double LCOH_CHP::operator () (const double & alpha, const double & I, const double & OM, const double & F,
		const double & EH, const double bp_revenue) {
		return (alpha * I + OM + F) / EH - bp_revenue;
	}

	double LCOH_CHP::run() {
		const double & alpha_ = alpha(LT, r);
		const double & I_ = I(C, LB, i);
		const double & E_ = EH(P_E, FLH_E);
		const double & H_ = EH(P_H, FLH_H);
		const double & OM_ = OM(FOM, VOM, H_);
		const double & F_ = F(FC, E_, H_, etaE, etaH);
		const double & bp_revenue_ = bp_revenue(E_, EP, FLH_H, FLH_E, etaH, etaE);
		return (*this)(alpha_, I_, OM_, F_, H_, bp_revenue_);
	}

	std::ostream & LCOH_CHP::save_public(std::ostream & outfile) const {
		LCOH::save_public(outfile);
		outfile << P_E << std::endl;
		outfile << P_H << std::endl;
		outfile << FLH_E << std::endl;
		outfile << FLH_H << std::endl;
		outfile << etaE << std::endl;
		outfile << etaH << std::endl;
		return outfile;
	}

	std::ostream & LCOH_CHP::save_private(std::ostream & outfile) const {
		outfile << EP << std::endl;
		return outfile;
	}

	/* Constructor */
	
	LCOH_CHP::LCOH_CHP(const Physical_Quantity & C, const Physical_Quantity & LB, const Physical_Quantity & LT, 
		const Physical_Quantity & FOM, const Physical_Quantity & VOM, const Physical_Quantity & FC, 
		const Coefficient & r, const Coefficient & i, const Physical_Quantity & P_E,
		const Physical_Quantity & P_H, const Physical_Quantity & FLH_E, const Physical_Quantity & FLH_H, 
		const Coefficient & etaE,  const Coefficient & etaH, const Physical_Quantity & EP) :
		LCOH::LCOH(C, LB, LT, FOM, VOM, FC, r, i), P_E(P_E), P_H(P_H), FLH_E(FLH_E), FLH_H(FLH_H), etaE(etaE), 
		etaH(etaH), EP(EP) {
		++count;
	}
	
	LCOH_CHP::LCOH_CHP(const LCOH_CHP & orig) : 
		LCOH::LCOH(orig), P_E(orig.P_E), P_H(orig.P_H), FLH_E(orig.FLH_E), FLH_H(orig.FLH_H), etaE(orig.etaE), 
		etaH(orig.etaH), EP(orig.EP) {
		++count; 
	}

	/* Destructor */
	
	LCOH_CHP::~LCOH_CHP() { --count; }


	/*##################################################################################################################
	Class 'LCOE_CHP'
	==================================================================================================================*/
	/* Friends */
	
	/*std::ostream & operator <<(Save_File & log, const LCOE_CHP & object) {
		*log.outfile << "# " << typeid(object).name() << std::endl;
		object.save_public(*log.outfile);
		object.save_private(*log.outfile);
		return *log.outfile;
	}*/
	
	// Summary: Read the object from the existing file
	std::istream & operator >>(Read_File & log, LCOE_CHP & object) {
		std::string str;
		std::vector<std::istringstream *> vec;
		while (std::getline(*log.infile, str))
		{
			std::istringstream * ins = nullptr;
			ins->str(str);
			vec.push_back(std::move(ins));
		}
		*vec[0] >> object.C;
		*vec[1] >> object.LB;
		*vec[2] >> object.LT;
		*vec[3] >> object.FOM;
		*vec[4] >> object.VOM;
		*vec[5] >> object.FC;
		*vec[6] >> object.r;
		*vec[7] >> object.i;
		*vec[8] >> object.P_E;
		*vec[9] >> object.P_H;
		*vec[10] >> object.FLH_E;
		*vec[11] >> object.FLH_H;
		*vec[12] >> object.etaE;
		*vec[13] >> object.etaH;
		*vec[14] >> object.HP;
		return *log.infile;
	}

	/* Virtual functions */
	
	double LCOE_CHP::run() {
		const double & alpha_ = alpha(LT, r);
		const double & I_ = I(C, LB, i);
		const double & E_ = EH(P_E, FLH_E);
		const double & H_ = EH(P_H, FLH_H);
		const double & OM_ = OM(FOM, VOM, E_);
		const double & F_ = F(FC, E_, H_, etaE, etaH);
		const double & bp_revenue_ = bp_revenue(H_, HP, FLH_E, FLH_H, etaE, etaH);
		return (*this)(alpha_, I_, OM_, F_, E_, bp_revenue_);
	}

	std::ostream & LCOE_CHP::save_private(std::ostream & outfile) const {
		outfile << HP << std::endl;
		return outfile;
	}

	/* Constructor */
	
	LCOE_CHP::LCOE_CHP(const Physical_Quantity & C, 
		const Physical_Quantity & LB, 
		const Physical_Quantity & LT, 
		const Physical_Quantity & FOM,
		const Physical_Quantity & VOM, 
		const Physical_Quantity & FC, 
		const Coefficient & r, 
		const Coefficient & i, 
		const Physical_Quantity & P_E,
		const Physical_Quantity & P_H, 
		const Physical_Quantity & FLH_E, 
		const Physical_Quantity & FLH_H, 
		const Coefficient & etaE,
		const Coefficient & etaH, 
		const Physical_Quantity & HP) :
		LCOH_CHP::LCOH_CHP(C, LB, LT, FOM, VOM, FC, r, i, P_E, P_H, FLH_E, FLH_H, etaE, etaH), HP(HP) {
		++count;
	}
	LCOE_CHP::LCOE_CHP(const LCOE_CHP & orig) : LCOH_CHP::LCOH_CHP(orig), HP(orig.HP) {
		++count;
	}

	/* Destructor */
	
	LCOE_CHP::~LCOE_CHP() { --count; }


	/*##################################################################################################################
	Static counters of each class
	==================================================================================================================*/
	std::size_t Coefficient::n_attributes(3);
	
	std::size_t Physical_Quantity::n_attributes(4);

	std::size_t Physical_Quantity::count(0);

	std::size_t Coefficient::count(0);

	std::size_t LCOH::count(0);

	std::size_t LCOE::count(0);

	std::size_t LCOH_CHP::count(0);

	std::size_t LCOE_CHP::count(0);


	/*##################################################################################################################
	Cosntant values
	==================================================================================================================*/
	const Physical_Quantity & C0 = Physical_Quantity("C", "capital cost", 287000.0, "kGBP");
	const Physical_Quantity & LB0 = Physical_Quantity("LB", "cosntruction period", 5.0, "yr");
	const Physical_Quantity & LT0 = Physical_Quantity("LT", "project duration", 20.0, "yr");
	const Physical_Quantity & FOM0 = Physical_Quantity("FOM", "fixed OM cost", 0.0, "kGBP/yr");
	const Physical_Quantity & VOM0 = Physical_Quantity("VOM", "variable OM cost", 0.0002038, "kGBP/MWh");
	const Physical_Quantity & FC0 = Physical_Quantity("FC", "fuel costs per unit of enengy input",
		0.008, "kGBP/MWh");
	const Physical_Quantity & REV0 = Physical_Quantity("REV", "variable by-product revenue", 0.0, "kGBP/MWh");
	const Physical_Quantity & dv0 = Physical_Quantity("dv", "", 0.0, "kGBP/MWh");
	const Physical_Quantity & P_E0 = Physical_Quantity("P_E", "electricity capacity", 650, "MW");
	const Physical_Quantity & P_H0 = Physical_Quantity("P_H", "heat capacity", 650, "MW");
	const Physical_Quantity & FLH_E0 = Physical_Quantity("FLH_E", "full load hours of electrcity", 0.0, "h");
	const Physical_Quantity & FLH_H0 = Physical_Quantity("FLH_H", "full load hours of heat", 8000.0, "h");
	const Physical_Quantity & EP0 = Physical_Quantity("EP", 
		"wholesale electricity price", 0.03, "kGBP/MWh");
	const Coefficient & r0 = Coefficient("r", "weighted average cost of capital (WACC)", 0.075);
	const Coefficient & i0 = Coefficient("i", "interest rate over the construction loan", 0.05);
	const Coefficient & d0 = Coefficient("d", "decommisioning cost factor", 0.15);
	const Coefficient & etaE0 = Coefficient("etaE", "conversion efficiency in LHV of electricity", 1.0);
	const Coefficient & etaH0 = Coefficient("etaH", "conversion efficiency in LHV of heat", 0.90);
	const Physical_Quantity & HP0 = Physical_Quantity("HP",
		"wholesale heat price", FC0.get_magnitude() / etaH0.get_magnitude(), "Euros/MWh");
}
