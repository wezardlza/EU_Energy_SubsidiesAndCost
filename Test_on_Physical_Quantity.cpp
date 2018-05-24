#pragma once
#ifndef PHYSICAL_QUANTITY
template <class Type>
class Physical_Quantity
{
public:
	//Note that the length of u is variable; u reprensents the unit of the physical value the C-type string
	Physical_Quantity(const Type q, const char *u) : value(q), unit_name(u) {}

private:
	const Type value;
	const char * unit_name;
};
#endif // !PHYSICAL_QUANTITY

int main(){
	const int v = 1;
	const char *x = "Hello";
	Physical_Quantity<int> a(v,x);
}