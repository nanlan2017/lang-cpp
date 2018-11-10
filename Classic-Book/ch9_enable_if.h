#ifndef h_ch9_enableif
#define h_ch9_enableif

#include "prelude.h"
#include "prelude_boost.h"

namespace wjh
{

template<bool b,typename T>
struct enable_if_c
{
	using type = T;
};

template<typename T>
struct enable_if_c<false, T>
{
};

using t0 = typename enable_if_c<boost::is_arithmetic<int>::value, double>::type;
//using t1 = typename enable_if_c<boost::is_arithmetic<void>::value, double>::type;
//x-----------------------------------------------
template<typename Cond,typename T>
struct enable_if : enable_if_c<Cond::value,T>
{ };

using t0 = typename enable_if<boost::is_arithmetic<int>, double>::type;
//using t1 = typename enable_if<boost::is_arithmetic<void>, double>::type;
}


using namespace boost;
//todo  该函数模板只能应用于算术类型的迭代器上
//! enable_if
template<typename Iter>
typename enable_if<is_arithmetic<typename iterator_value<Iter>::type>
					,typename iterator_value<Iter>::type>::type
sum(Iter start,Iter end)          //! 只有当T符合条件时，才会产生一个T（否则的话无法实例化，——报错——自然就被禁止了）=======> ▇▇▇▇▇▇▇▇相当于concept mapping
{
	typename iterator_value<Iter>::type x(0);
	for(; start!= end; ++start) {
		x += *start;
	}
	return x;
}

//todo  添加一个重载版本，可应用于 vector<vector<int>>
template<typename ContainerIter>
struct inner_value
	: iterator_value<typename iterator_value<ContainerIter>::type>::iterator
{};

//! disable_if                           lazy_disable_if
template<typename Iter>
typename lazy_disable_if<is_arithmetic<typename iterator_value<Iter>::type>      //x 符合条件时禁用！
						, inner_value<Iter>>::type                      //x  lazy : 只有当第一个条件通过时， 才进行第二个参数的计算。（否则的话计算会出错！）
sum(Iter start,Iter end)
{
	typename inner_value<Iter>::type x(0);
	for (; start!= end; ++start) {
		x += sum(start->begin(), start->end());   // 调用上面的那个
	}
	return x;
}
#endif

