#include "libs/mpl/book/chapter1/binary.hpp"
#include "prelude.h"
#include <functional>

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
//x------------------------------------------------------------------------
//expr = ( term[expr.val = placeholders::_1])


void main()
{
	auto r1 = binary<101>::value;
	auto r2 = wjh::to_binary<20>::val;
	system("pause");
}
