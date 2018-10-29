#ifndef h_Sales_item
#define h_Sales_item

#include "prelude.h"

/*
该类型不存在 “无参构造器”

*/
struct Dog
{
public:
	Dog() = default;
	Dog(const int& age): myage(age){}

private:
	string name;
	int myage;
	string* ptr_in_dog;
};

							// ▇▇▇▇▇  初始化的疑惑都解决了。现在完全理解了初始化 这个行为。
struct Sales_item  // 既然its_dog无法支持默认初始化(无法提供默认值) ---> 那么Sales_data也就无法提供默认值了！
				   // --->  编译器不会容忍 非内置类型 的 undefined ! (只会报错）   ----->  int i; 可以，    Dog dog; 报错！
                   // --->  T()=default;  保留默认的无参构造就行了；  // T() = 0 是删除编译器提供的默认组件！
{
	string bookNo;                // 非内置类型、未指定初始值的 成员：  默认初始化取决于是否有“无参构造器” （大多数会有）
	unsigned units_sold = 0;      //▇▇▇▇▇ 若不指定 初始值的话， 内置类型为 默认初始化<局部> == undefined (不进行初始化)---当然，包括指针（不会自动变为nullptr)
	double revenue;

	Dog its_dog;                 // 观察一个不存在无参构造器的 成员类型 是如何“默认初始化”的 
};

struct Sales_data
{
private:
	string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
public:
	Sales_data() = default;
	Sales_data(const string s):bookNo(s) {}
	Sales_data(const string s, const unsigned sold, const double p) : bookNo(s),units_sold(sold),revenue(sold*p){}

	const Sales_data& show() const   // const成员函数返回this，则必须返回const &
	{
		return *this;
	}

	friend struct hash<Sales_data>;
};

#endif

