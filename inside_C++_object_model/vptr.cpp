#include "prelude.h"
//#include <concepts>
using namespace std;
class Base
{
public:

	Base(int i) :baseI(i) {};

	int getI() const { return baseI; }

	static void countI() {}

	virtual void print(void) { cout << ".......Base::print()"; }

	virtual void setI() { cout << ".......Base::setI()"; }

	virtual ~Base() {}

private:
	int baseI;

	static int baseS;
};

void testBase(Base& p)
{
	//RTTICompleteObjectLocator str = *((RTTICompleteObjectLocator*)*((int*)*(int*)(&p) - 1));

	//x输入static函数的地址
    p.countI();//先调用函数以产生一个实例
    cout << "static函数countI()的地址：" << p.countI << endl;
 
    //x验证nonstatic数据成员
    cout << "推测nonstatic数据成员baseI的地址：" << (int *)(&p) + 1 << endl;
    cout << "根据推测出的地址，输出该地址的值：" << *((int *)(&p) + 1) << endl;
    cout << "Base::getI():" << p.getI() << endl;
}


//!  我只看  non-static的成员变量 + virtual 的成员函数
class Derive : public Base
{
public:
    Derive(int d) :Base(1000),      DeriveI(d){};

    //overwrite父类虚函数
    virtual void print(){ cout << "Drive::Drive_print()" ; }

    // Derive声明的新的虚函数
    virtual void Drive_print(){ cout << "Drive::Drive_print()" ; }
    virtual ~Derive(){}
private:
    int DeriveI;
};

class Base_2
{
public:
    Base_2(int i) :base2I(i){};

    virtual ~Base_2(){}

    int getI(){ return base2I; }

    static void countI(){};

    virtual void print(void){ cout << "Base_2::print()"; }
 
private:
 
    int base2I;
 
    static int base2S;
};
 
class Drive_multyBase :public Base, public Base_2
{
public:

    Drive_multyBase(int d) :Base(1000), Base_2(2000) ,Drive_multyBaseI(d){};
 
    virtual void print(void){ cout << "Drive_multyBase::print" ; }
 
    virtual void Drive_print(){ cout << "Drive_multyBase::Drive_print" ; }
 
private:
    int Drive_multyBaseI;
};

//test_vptr
void main()
{
	//TODO  根据vptr获取虚函数表，然后从虚函数表中获取第一个虚函数 进行调用。
	Base b(1000);

	/*
	int* vptr;
	int  baseI;
	*/

	//虚函数指针一般都放在对象内存布局的第一个位置上，这是为了保证在多层继承或多重继承的情况下能以最高效率取到虚函数表。
	//当vprt位于对象内存最前面时，对象的地址即为虚函数指针地址。
	int * ptr_vptr = (int *)(&b);

	cout << "vptr is : \t" << ptr_vptr << endl;

	typedef void(*Fun)();
	Fun vf1 = (Fun)*((int *)*ptr_vptr);

	cout << "First virtual function at: " << (int *)*(int*)(&b) << endl;
	vf1();

	system("pause");
}