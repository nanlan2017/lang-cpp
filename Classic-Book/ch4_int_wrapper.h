#ifndef h_ch4_wrapper
#define h_ch4_wrapper
#include "prelude.h"
#include "prelude_boost.h"

//x=========================================  bool ==============================================================
//  paramtype 决定： 当是标量时， 使用值拷贝； 否则才使用引用
template<typename T>
struct param_type
	//!  identity,     eval_if
	//!  函数转发：相当于直接等于其中一个元函数
	: mpl::eval_if<mpl::or_<boost::is_scalar<T>,boost::is_reference<T>>    //x bool_ 上的运算： or_, and_ , not_
				, mpl::identity<T>
				, boost::add_reference<T const>>
{
	using t0 = typename mpl::if_<typename boost::is_scalar<T>::type
		//! 延缓请求类型的成员：先确定出类型，再去请求成员
		, mpl::identity<T>
		, boost::add_reference<T const>>::type;   // 先决定类型，再请求其type成员（避免两个类型都被完全实例化）
};

template<typename T>
struct holder
{
public:
	holder(typename param_type<T>::type x);     // 如果T是标量类型，则 (T x) , 否则为 (const T& x)
};

inline void test_boolen_wrapper()
{
	using t0 = param_type<int>::type;
	using t1 = param_type<std::vector<int>>::type;
	using t2 = param_type<std::vector<int>&>::type;

	int i = 3;
	holder<int> h1(i);
	std::vector<int> iv;
	holder<std::vector<int>> h2(iv);

	if (boost::is_scalar<int>()) {
		
	}

	using t5 = mpl::if_<boost::is_scalar<int>, long, double>::type;
}
//x=========================================  integral ==============================================================
//!  int_
//!  long_
//!  -----> integral_c

// 值等价性：
//!  equal_to
//!  equal (for Sequence)

inline void test_integral_wrapper()
{
	using Int3 = mpl::int_<3>;

	using Int4 = mpl::next<Int3>::type;

	using Intc5 = mpl::next<mpl::integral_c<int, 4>>::type;
}
#endif

