#include "prelude.h"
using namespace std;
class Base
{
public:

	Base(int i) :baseI(i) {};

	virtual void print(void) { cout << ".......Base::print()"; }

	virtual void setI() { cout << ".......Base::setI()"; }

	virtual ~Base() {}

private:
	int baseI;
};

//test_vptr
void main()
{
	//TODO  根据vptr获取虚函数表，然后从虚函数表中获取第一个虚函数 进行调用。
	Base b(1000);

	//虚函数指针一般都放在对象内存布局的第一个位置上，这是为了保证在多层继承或多重继承的情况下能以最高效率取到虚函数表。
	//当vprt位于对象内存最前面时，对象的地址即为虚函数指针地址。
	int * vptr = (int *)(&b);

	cout << "vptr is : \t" << vptr << endl;

	typedef void(*Fun)();
	Fun vf1 = (Fun)*((int *)*vptr);

	cout << "First virtual function at: " << (int *)*(int*)(&b) << endl;
	vf1();

	system("pause");
}