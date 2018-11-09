#ifndef h_callable_object
#define h_callable_object

#include "prelude.h"
#include "prelude_boost.h"

struct add1_obj
{
	template<typename T>
	T operator()(T i)
	{
		return i + 1;
	}
};

template<typename T>
T add1_tempf(T i)
{
	return i + 1;
}

inline int add1_int_tmp(int i)
{
	return i + 1;
}
//x------------------------------------------------------

template<typename F>
void consume_callable(F func)
{
	std::cout << func(1) << std::endl;
}

inline void consume_callable_int(int(*func)(int))
{
	std::cout << func(1) << std::endl;
}
//x------------------------------------------------------
inline void test_callable()
{
	consume_callable(add1_obj());   //!▇▇▇▇▇ 函数对象，完全就相等于创建一个闭包（实际上也是 闭包、lambda的实质：创建一个函数对象）————强在比一般的函数 选择性的包含状态

	//use_callable(add1);      //todo add1 是泛型的 函数， 所以接收方无法据它 推断出类型参数 F 的类型！

	consume_callable(add1_int_tmp);


	//consume_callable_int(add1_obj());  //todo   这样也不行
	consume_callable_int(add1_tempf);
}
#endif

