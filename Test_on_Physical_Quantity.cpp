class Physical_Quantity
{
public:
	//Note that the length of u is variable; u reprensents the unit of the physical value the C-type string
	template<size_t N> Physical_Quantity(double, const char(&)[N]);

private:
	double quantity;
	size_t unit_name_length;
	char * unit_name;
};

int main() {
	double v = 1.0;
	const char *x = "Hello";
	Physical_Quantity a(v, x);
}

template<size_t N>
Physical_Quantity::Physical_Quantity(double q, const char(& u)[N])
{
	Physical_Quantity<Type>::quantity = q;
	Physical_Quantity<Type>::unit_name = u;
	Physical_Quantity<Type>::unit_name_length = N;
}