/**
	虚继承（虚基类）
*/
 
// 基类A
class A
{
public:
	int dataA;
};
 
class B : virtual public A
{
public:
	int dataB;
};
 
class C : virtual public A
{
public:
	int dataC;
};
 
class D : public B, public C
{
public:
	int dataD;
};
