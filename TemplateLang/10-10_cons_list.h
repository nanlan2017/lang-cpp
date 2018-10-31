#ifndef h_10_10_conslist
#define h_10_10_conslist
#include <boost/thread/lock_types.hpp>

//!  现在想想：元编程可以对类型、整型值进行计算，   怎么用它来进行“元编程”———— lisp宏,Ruby元编程（根据部分node,构建语法树)

//todo  接受一个名称， 以该名字定义一个 函数，空函数体即可
//x Ruby支持运行时动态类， 运行时 define function
//x  C#的partial class貌似也可以？？
//x    C++和Lisp则必须在编译时就展开成语法树
/*
[lisp]
(defmacro create (name)
	`(defun ,name ()
		())
*/

//!  DSL 那个，就是通过 一些枚举的整形值（配置值）+ 结合选择结构 ————————>  最后得到一个类型（自然也就得到了诸多成员）
/*
//!  ▇▇▇▇想想你现在可以对类型、整型值随便计算，并且其内部还可以嵌套这两种数据。最后的计算结果也不过是一个数据

//!              ▇▇▇▇原子类型其实是整形，
//!                ▇▇▇▇而TypesEnum类型其实是一种复合类型：它可以有各种成员： 类型/整型值
*/

//x==========================================================================================================================
//todo 既然有数据了，当然可以定义数据结构 (在模板元中)

const int endValue = ~(~0u >> 1);

//todo   这里类型全部成为了数据， 换句话说：不存在“类型” 这个概念了。
struct End
{
	enum { head = endValue};
	using Tail = End;   //?   ???
};


template<int n, typename _Tail = End>
struct Cons
{
	enum { head = n };
	using Tail = _Tail;
};



//todo Haskell中定义数据结构是通过 data MyType = ...
//todo                Cons是函数，可用来计算类型； Cons<...> 自身又是一个值（类型）
template<typename List>
struct Length
{
	enum { val = 1 + Length<typename List::Tail>::val };
};

template<>
struct Length<End>
{
	enum { val = 0};
};

inline void test_cons()
{
	//  2~3~7~'b'~false~End
	using list0 = Cons<2, Cons<3, Cons<7, Cons<'b', Cons<false>>>>>;
	auto len0 = Length<list0>::val;

	//  2~End
	using list1 = Cons<2>;
	auto len1 = Length<list1>::val;
}
//x==========================================================================================================================

#endif

