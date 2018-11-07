#ifndef h_exer_chap4
#define h_exer_chap4
#include "prelude_boost.h"
#include "prelude.h"


//x========================================================================================================

namespace wjh {
	

template<typename T>
struct is_data_member_pointer
{
	// 是成员指针  &  其目标是数据成员 （而非成员方法）
	using type = typename mpl::and_<boost::is_member_pointer<T>
		, mpl::not_<boost::is_function<T>>>::type;
};
}
#endif

