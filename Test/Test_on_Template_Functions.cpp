#include <iostream>
using namespace std;
class A
{
public:
	template<typename T>  void A1(T temp);
	template<typename T>  A(T temp);
};
template<typename T>
void A::A1(T temp)
{
	cout << temp << endl;
}
template<typename T>
A::A(T temp)
{
	cout << temp << endl;
}
template <typename T>
void test(T temp)
{
	cout << temp << endl;
}
void main()
{
	test<int>(12);  //��ͨģ�庯��
	A aa(12); //��ע����һ��
	aa.A1<int>(15); //��Ա������ģ�庯��
	system("pause");
}