#ifndef h_ch9_sizeof
#define h_ch9_sizeof

#include "prelude.h"
#include "prelude_boost.h"

namespace wjh {
	
using yes = char;
typedef char(&no)[2];

using sz1 = mpl::sizeof_<yes>::type;
using sz2 = mpl::sizeof_<no>::type;


template<typename T>
struct is_class_or_union
{
	template<typename U>
	static yes tester(int U::*arg);

	template<typename U>
	static no tester();

	//todo  看看当U==T 时，选择了哪一个重载？
	static const bool value = sizeof(is_class_or_union::tester<T>(0) == sizeof(yes));

	using type = mpl::bool_<value>;
};
}


#endif

