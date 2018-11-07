#ifndef h_exer_chap3
#define h_exer_chap3

#include "prelude.h"
#include "prelude_boost.h"

#include "ch3_high_order.h"
//x============================================================================================================================
namespace wjh {
	
template<unsigned long n>
struct binary
{
	BOOST_STATIC_ASSERT((
		n == 0 || n ==1
		));
	static_assert((n == 0 || n == 1), "n must be 0 or 1 !");
	static unsigned const value = binary<n / 10>::value << 1 | n % 10;
};

template<>
struct binary<0>
{
	static unsigned const value = 0;
};

inline void testexer_3_0()
{
	auto r0 = binary<0>::value;
	auto r1 = binary<1>::value;

	//auto r2 = binary<10>::value;
	//auto r5 = binary<10101>::value;
}
}
//x============================================================================================================================
using namespace mpl;


//!  transform =  zip/ zipWith  / map

using tv = vector_c<int, 1, 2, 3>;

// t0 = map (+ 1) [1,2,3]
using t0 = mpl::transform<tv, mpl::plus<_1, int_<1>>>::type;
//x---------------------------------------------------------
// t1 = map (\x -> x*x) [...]      // square
using t1 = mpl::transform<tv, mpl::multiplies<_1, _1>>::type;
//x---------------------------------------------------------

// f = twice add_pointer
// t2 = f (f x)
// t2 = (\x -> twice add_pointer (twice add_pointer x))  int
// ---> twice add_pointer (twice add_pointer _)
using t2 = twice<add_pointer<_>, int>::type;
using t3 = twice<add_pointer<_>, t2>::type;
using t4 = twice<add_pointer<_>, twice<add_pointer<_>, int>::type>::type;


//!  _ 这个占位符好麻烦？？
// v = apply (\x -> twice (\y -> add_pointer y) x) int
//          ----->  twice (\y -> add_pointer y) int
//          ----->  
// [ok]  twice (\y -> add_pointer y) int
//using t7 = twice<add_pointer<_>, int>::type;
//// [ok]
//using t8 = mpl::apply<add_pointer<_>, int>::type;
////
//using fexp1 = twice<add_pointer<_>, _1>;
//
//using t60 = mpl::apply<fexp1, int>::type;
//using t6 = mpl::apply<twice<add_pointer<_2>, _1>, int>::type;
//
//using t5 = mpl::apply<twice<twice<add_pointer<_>,_>, _>, int>::type;
//x============================================================================================================================
// twice f x = apply (\x -> f x) (f x)
template<typename F,typename X>
using new_twice = mpl::apply<typename mpl::lambda<F>::type, typename mpl::apply<F, X>::type>;

using t8 = new_twice<boost::add_pointer<_>, int>::type;
#endif

