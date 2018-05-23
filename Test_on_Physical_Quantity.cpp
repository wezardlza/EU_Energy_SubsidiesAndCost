template <class Type>
class Physical_Quantity
{
public:
	//Note that the length of u is variable; u reprensents the unit of the physical value the C-type string
	Physical_Quantity(Type q, const char *u) : quantity(q), unit_name(u){}

private:
	Type quantity;
	const char * unit_name;
};

int main(){
	int v = 1;
	const char *x = "Hello";
	Physical_Quantity<int> a(v, x);
}