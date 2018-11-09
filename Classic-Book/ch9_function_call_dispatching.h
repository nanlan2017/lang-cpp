#ifndef h_ch9_dispatching
#define h_ch9_dispatching

#include "prelude.h"
#include "prelude_boost.h"

// dc<T>(x) 一般等价于 static_cast, 除非T 是，等价于dy_cast

// 让一个函数基于tag（true,false) 特化
template<typename TargetType, typename U>
TargetType impl(U& x, mpl::true_)  // true:对应那种符合特殊情形
{
	return dynamic_cast<TargetType>(x);
}
template<typename TargetType, typename U>
TargetType impl(U& x, mpl::false_)  // true:对应那种符合特殊情形
{
	return static_cast<TargetType>(x);
}

template<typename TargetType, typename U>
TargetType dispatcher(U& x)
{
	return impl<x, typename boost::is_polymorphic<U>::type>();
}


template<typename TargetType, typename U>
TargetType desperate_cast(U& x)
{
	return dispatcher<TargetType>(x);   //x TargetType 一直作为函数的模板参数在传递 （虽然在函数内部直到最后一个函数才用它！）
}

#endif
