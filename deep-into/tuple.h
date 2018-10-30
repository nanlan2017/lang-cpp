#ifndef h_tuple
#define h_tuple
#include "prelude.h"

// tuple<int, string, char> 会自动构造一个  继承自tuple<string,char>、并添加了int的类
template<typename T, typename ...Args>
class Tuple : public Tuple<Args...>
{
private:
	T val;
public:
	//!cons
	Tuple(T&& v,Args&&... args)
		:Tuple<Args...>(forward<Args>(args)...)        // 可变参数 + 完美转发
		,val(forward<T>(v))
	{}

	//!const
	decltype(auto) get(size_t n) const
	{
		static_assert(n <= sizeof(Args));
		if (n == 0)
			return val;
		else
			return Tuple<Args...>::get(n - 1);
	}
};

template<size_t n,
		template<typename...> class Tuple, 
		typename... ArgsWrapper>
struct tuple_element<n, Tuple<ArgsWrapper...>>
{
	//! 这就是一门模板新语言（很像Haskell: 没有可变量、有基本的结构）
	// 没有其他的函数了。 只有不可变的编译时常量表达式、和类型。
	//! 把template struct当成函数来用 ——>  其数据就是 类型、整形 (template params就是参数）
	//!                              ——>  通过特化实现选择结构（乃至IF)
	//!                              ——>  通过递归实现循环
	/*
	template<typename T,typename...Args>
	struct helper<0,T,Args>
	{
		using type = T;
	};
	template<size_t m, typename T, typename ...Args>
	struct helper : public helper<m-1, Args...,void>
	{};
	*/
	/*------------------------------*/
	using type = helper<n, ArgsWrapper..., void>::type;
};

inline 
void usecase_tuple()
{
	


}
#endif

