#ifndef h_ch3_highorder
#define h_ch3_highorder
#include "prelude_boost.h"
#include <boost/type_traits/add_pointer.hpp>

template<typename NumT>
struct square
	: mpl::int_<99999999>
{ };

template<int n>
struct square<mpl::int_<n>>
	: mpl::int_<n*n>
{};

struct square_f
{
	//todo  what's different?
	//template<typename T>
	//struct apply<T> : square<T> {};

	template<typename T>
	struct apply
	{
		using type = typename square<T>::type;
	};
};
//x-----------------------------------------------------------------------------
//!  apply call tool
// F_wrapper 是内部含有 apply 这个元函数的Wrapper Struct
template<typename F_Wrapper, typename...Args>
struct apply
	: F_Wrapper::template apply<Args...>
{};

//!  元函数转发版（更像Haskell)
//!   twice f x = f (f x)
template<typename F,typename T>
struct twice 
	: apply<F, typename apply<F,T>::type>
{};

//x===============================================================================================
struct add_pointer_f
{
	template<typename T>
	struct apply : boost::add_pointer<T>{};
};
inline void test_ch3_high()
{
	using Int3 = mpl::int_<3>;
	auto r0 = Int3::value;
	using T00 = Int3::value_type;
	using T01 = Int3::type;
	using T02 = Int3::tag;
	using T03 = Int3::next;


	//using T1 = twice<square_f, T>::type;
	using T1 = square_f::apply<Int3>::type;
	//using T2 = apply<square_f, Int3, Int3>::type;
	using T3 = twice<square_f, Int3>::type;

}
//x===============================================================================================
// two_pointers x = twice (\ ==> add_pointer _1) x
template<typename X>
struct two_pointers
	: twice<typename mpl::lambda<boost::add_pointer<mpl::_1>>::type, X> { };

inline void test_ch3_lambda()
{
	//  \x -> x       ---->   lambda(_1)
	//  \x -> x * 2   ---->   lambda(_1 * 2)       // 很像clojure里的写法
	BOOST_STATIC_ASSERT((
		std::is_same<int**
		, two_pointers<int>::type>()
		));

	//using T0 = apply<mpl::lambda<square<mpl::_1>>, mpl::int_<3>>::type;
	//!  lambda
	// 内部含有  apply 模板 的一个非模板struct
	//! lambda<square>  ====  
	//auto r1 = std::is_same < add_pointer_f
	//	, mpl::lambda<boost::add_pointer<mpl::_1>>::type>::value;

	auto r2 = std::is_same<add_pointer_f
		, boost::mpl::lambda<add_pointer_f>::type>::value;
}
#endif

