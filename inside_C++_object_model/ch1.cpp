#include "prelude.h"

//!  static /  virtual  / ~
class Point
{
public:
	Point(float xval);
	virtual ~Point();

	float x() const;
	static int PointCount();

protected:
	virtual std::ostream& print(std::ostream& os) const;

	float _x;
	static int _point_count;
};

//x==================================================== 虚基类
using namespace std;
class A0// 声明为基类A0
{
	int nv;//默认为私有成员
public://外部接口
	A0(int n) { nv = n; cout << "Member of A0" << endl; }//A0类的构造函数
	void fun() { cout << "fun of A0" << endl; }
};



class B1 :virtual public A0
{
	int nv1;
public:
	B1(int a) :A0(a) { cout << "Member of B1" << endl; }
};

class B2 :virtual public A0
{
	int nv2;
public:
	B2(int a) :A0(a) { cout << "Member of B2" << endl; }
};



class D1 :public B1, public B2
{
	int nvd;
public:
	D1(int a) :A0(a), B1(a), B2(a) { cout << "Member of D1" << endl; }// 此行的含义，参考下边的 “使用注意5”
	void fund() { cout << "fun of D1" << endl; }
};

//test_ch1
int test_ch1(void)
{
	D1 d1(1);
	//d1.fund();
	//d1.fun();
	return 0;
}