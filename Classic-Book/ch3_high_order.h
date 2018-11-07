#ifndef h_ch3_highorder
#define h_ch3_highorder
#include "prelude_boost.h"
#include <boost/type_traits/add_pointer.hpp>
//using namespace mpl;

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
struct apply    // 已经和mpl库里的一样了。
	: mpl::lambda<F_Wrapper>::type::template apply<Args...>     //todo    先lambda一下（从而不仅可以接收元函数类、还可以接收占位符表达式）
{};

//!  元函数转发版（更像Haskell)
//!   twice f x = f (f x)
template<typename F,typename T>
struct twice 
	: ::apply<F, typename ::apply<F,T>::type>
{};

inline void test_apply_lambda()
{
	using T0 = twice<boost::add_pointer<mpl::_1>, int>::type;

	using T1 = ::apply<boost::add_pointer<mpl::_1>, int>::type;

}

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

//!  ▇▇▇▇▇▇▇▇▇▇▇▇以前还没有template参数，所以传递一个函数都得Wrap在一个类里，此时这个类称为"元函数类"
//!        plus,minus这样的显然是一个元函数（模板类型），不能直接作为typename进行传递。
//!                但是 plus<_1,_2> 就生成了一个具体类型，可以传递（但需要lambda化才能进行内部apply)
//!           而接受函数参数的函数内部，回直接用apply调用此函数（ lambda<param_f>::template apply<...>::type )

//!  ▇▇▇▇▇▇▇▇▇▇▇▇所有函数调用的语义，其结果都要写 ::type  取出来！  (但写在lambda里的占位符表达式无需取::type)

//todo 取出lambda生成的元函数类中的apply元函数
template<typename M, typename N> 
using apply_plus = mpl::lambda<mpl::plus<mpl::_1, mpl::_2>>::type::template apply<M, N>;

inline void test_ch3_lambda()
{
	//  \x -> x       ---->   lambda(_1)
	//  \x -> x * 2   ---->   lambda(_1 * 2)       // 很像clojure里的写法
	BOOST_STATIC_ASSERT((
		std::is_same<int**
		, two_pointers<int>::type>()
		));

	//! mpl::apply
	auto r4 = mpl::apply<mpl::plus<mpl::_1, mpl::_2>, mpl::int_<3>, mpl::int_<4>>::type::value;

	//using T0 = apply<mpl::lambda<square<mpl::_1>>, mpl::int_<3>>::type;
	//!  lambda
	// 内部含有  apply 模板 的一个非模板struct
	//! lambda<square>  ====  
	using T00 = boost::add_pointer<mpl::_1>;
	using T01 = mpl::lambda <T00>::type;          //!  lambda：把一个占位符表达式 转化为 元函数类（内有apply元函数)
	using T02 = T01::template apply<int>::type;

	auto r1 = std::is_same <add_pointer_f, T01>::type::value;

	//todo    原本就是元函数的，则lambda对其无影响
	auto r2 = std::is_same<add_pointer_f
		, boost::mpl::lambda<add_pointer_f>::type>::value;

	//todo     plus<_1,_2>  进行lambda化 ------>  得到内部含 apply元函数的 元函数类   ------>  显式调用该apply元函数
	using T1 = mpl::lambda<mpl::plus<mpl::_1, mpl::_2>>::type::template apply<mpl::int_<3>, mpl::int_<4>>::type;

	using T3 = apply_plus<mpl::int_<3>, mpl::int_<4>>::type;
}

//x================================================================================================================
inline void test_compose()
{
	using Int7 = mpl::int_<7>;
	using Int3 = mpl::int_<3>;
	//  f = \x y -> (x+y) * (x-y)
	//  f = \_1 _2 -> (_1 + _2) * (_1 - _2)
	using Fexp = mpl::multiplies<mpl::plus<mpl::_1, mpl::_2>, mpl::minus<mpl::_1, mpl::_2>>;
	using Fcla = mpl::lambda<Fexp>::type;
	using T0 = Fcla::apply<Int7, Int3>::type;
	//auto r0 = mpl::equal<T0, mpl::int_<4>>::value;

	//! true!!!
	auto r1 = mpl::equal<mpl::int_<3>, mpl::int_<4>>::type::value;

}
//x================================================================================================================

#endif

