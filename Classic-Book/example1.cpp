#include "libs/mpl/book/chapter1/binary.hpp"
#include "prelude.h"

//template<typename T>
//void showtype(T&&);

//! 算法的动态版本
namespace dynamic {
	

}

namespace wjh {
template<int n>
struct to_binary
{
	enum { val = to_binary<n/10>::val*2 + n % 10 };
};

template<>
struct to_binary<0>
{
	enum { val = 0 };
};
}
//x----------------------------------------------------------------------------------------------------------------------------
//!  
template<typename T, typename UnaryOp1, typename UnaryOp2>
T apply_fg(T x, UnaryOp1 f , UnaryOp2 g)
{
	return f(g(x));
}

float square(float x)
{
	return x*x;
};

void test_applyfg()
{
	auto r1 = apply_fg(5.0f, square, negate<>());
	auto r2 = apply_fg(5.0f, negate<float>(), square);
}
//  你如果把两个函数封装在同一个类型里的话， 不好。

//x=============================================================================================================================
// what for ?
//template<typename T1,typename T2>
//void swap(T1& a, T2& b)
//{
//	T1 tmp = a;
//	a = b;
//	b = tmp;
//}

//? 能否使其类型参数匹配为：其中的某个成员类型相同时
//?         即：对其参数类型进行约束？

template<bool use_swap>
struct iter_swap_impl;

template<>
struct iter_swap_impl<true>
{
	template <typename Iter>
	static void do_it(Iter it1, Iter it2)
	{
		std::swap(*it1, *it2);
	}
};

template<>
struct iter_swap_impl<false>
{
	template <typename Iter1, typename Iter2>
	static void do_it(Iter1 it1, Iter2 it2)
	{
		typename iterator_traits<Iter1>::value_type tmp = *it1;
		*it1 = *it2;
		*it2 = tmp;
	}	
};


template <typename Iter1, typename Iter2>
void iter_swap(Iter1 it1, Iter2 it2)
{
	//todo  Iter1, Iter2 具有相同的value_type ，且其引用的类型是真正的引用而非代理  ---->  则 use_swap
	using v1 = typename iterator_traits<Iter1>::value_type;
	using r1 = typename iterator_traits<Iter1>::reference;

	using v2 = typename iterator_traits<Iter2>::value_type;
	using r2 = typename iterator_traits<Iter2>::reference;

	const bool use_swap = is_same<v1, v2>::value && is_reference<r1>::value && is_reference<r2>::value;

	//todo  根据情况进行算法派发（dispatching)
	iter_swap_impl<use_swap>::do_it(it1, it2);
}
//x=============================================================================================================================


void main_ex()
{
	auto r1 = binary<101>::value;
	auto r2 = wjh::to_binary<20>::val;
	system("pause");
}
