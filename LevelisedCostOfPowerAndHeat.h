#pragma once
#ifndef LCOPAH
#define LCOPAH
template <class Type> class Physical_Quantity
{
public:
	//Note that the length of u is variable; u reprensents the unit of the physical value the C-type string
	template <size_t N> Physical_Quantity(const Type & v, const char (& u) [N]): {
		quantity = v;
		unit_name_length = N;
		unit_name = *u;
	}

private:
	const Type & quantity;
	size_t unit_name_length;
	char * unit_name;
};
#endif // !LCOPAH
void main() {
	const double v(1.0);
	const char *x = "Hello";
	Physical_Quantity <double> a(v,x);
}