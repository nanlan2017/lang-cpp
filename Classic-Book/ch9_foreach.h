#ifndef h_ch9_foreach
#define h_ch9_foreach

#include "prelude.h"
#include "prelude_boost.h"

template<typename T>
struct wrap {};

struct print_type
{
	template<typename T>
	void operator()(wrap<T>) const
	{
		std::cout << typeid(T).name() << std::endl;
	}
};


//x=================================================================================================================== vistor 模式 
//   每个数据提供自身的visit()， 函数只是统一调用visit方法

//!  函数对象若是自身并不带有成员状态，则将其实例化就和提供那个函数调用运算一样。
struct visit_type
{
	template<typename Visitor>
	void operator()(Visitor) const
	{
		Visitor::visit();
	}
};

//todo   这个和上面的函数类 是一样的吧？？？
template<typename Visitor>
void f_visit_type(Visitor)
{
	Visitor::visit();
}

template<typename T>
struct print_visitor
{
	static void visit()
	{
		std::cout << typeid(T).name() << std::endl;
	}
};


#endif

