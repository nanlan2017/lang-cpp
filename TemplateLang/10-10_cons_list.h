#ifndef h_10_10_conslist
#define h_10_10_conslist
#include "prelude.h"
#include "10-5_Factorial.h"
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
//todo   这里类型全部成为了数据， 换句话说：不存在“类型” 这个概念了。

// head [] = nil
// tail [] = []
const int endValue = ~(~0u >> 1);
struct End           //todo end就是一个特殊值啊: 空列表  Haskell []   /  lisp '()
{
	enum { head = endValue};
	using Tail = End;   //?   ???
};

// cons :: Int -> TList ->  TList
template<int n, typename _Tail = End>
struct Cons
{
	enum { head = n };
	using Tail = _Tail;
};

//! ▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇
//! 你要见识过 church数 后，就不会惊讶 如果用一个图灵完备的语言， 如果用最基本的元素（变量、函数、条件+ 递归） 来构建出各种复杂的数据结构、算法了。
//!    ------>    cons,   if/switch/cond   ,   (atom? /   car | cdr )  eq?  


//todo Haskell中定义数据结构是通过 data MyType = ...
//todo                Cons是函数，可用来计算类型； Cons<...> 自身又是一个值（类型）
template<typename List>
struct Length
{
	enum { val = 1 + Length<typename List::Tail>::val };
};

//! nil/  '()
template<>
struct Length<End>
{
	enum { val = 0};
};
/*----------------------------------*///todo  car,cdr
template<typename List>
struct Head
{
	enum { val = List::head};
};

// Tail<End>::Ret ---> End
template<typename List>
struct Tail
{
	using Ret = typename List::Tail;   
};

/*----------------------------------*///todo  list
/*
本文将介绍如何使用C++11模板元编程实现Scheme中的list及相关函数式编程接口，
如list，cons，car，cdr，length，is_empty，reverse，append,map，transform，enumerate，lambda等
*/

/*
list x &rest args
= cons x (list args)
*/
template<int n,int...args>
struct List                //! ▇▇▇▇显然，只可能有一个Struct名后不加<>      (其他都是特化版)
{
private:
	//using Tail = List<forward<int>(args...)>;  //x wront

	using Tail = List<args...>;
public: 
	using Ret = Cons<n, typename Tail::Ret>;
};

template<int n>
struct List<n>
{
	using Ret = Cons<n>;
};
/*----------------------------------*///todo  is_empty
template<typename List>
struct Is_Empty
{
	//enum { val = static_cast<bool>(Length<List>::val == 0) };

	static_constexpr bool val = Length<List>::val == 0;
};
/*----------------------------------*///todo  append
/*
append :: [Int] -> Int -> [Int]
append (x:xs) n = cons x (append xs n)
append [] n = cons n
*/
template<typename List,int n>
struct Append;

template<int headval,typename Tail,int n>
struct Append<Cons<headval,Tail>,n>
{
	using Ret = Cons<headval, typename Append<Tail,n>::Ret>;
};

template<int n>
struct Append<End,n>
{
	using Ret = Cons<n>;
};
/*----------------------------------*///todo  reverse
/*
reverse (x:xs) = reverse xs ++ x
*/
template<typename List>        //! 无法对一个本身就是List的结构进行模式匹配（拆解）
struct Reverse;

template<int headval,typename Tail>        //! 无法对一个本身就是List的结构进行模式匹配（拆解）
struct Reverse<Cons<headval,Tail>>                 //!  ▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇只要是递归调用的(内部调了自身），必然要再去定义一个特化版的 递归终止边界———————— 即是某个参数值达到临界值时
{
	using Ret = typename Append<typename Reverse<Tail>::Ret, headval>::Ret;
};

template<>
struct Reverse<End>
{
	using Ret = End;
};
/*----------------------------------*///todo  map
// map (x:xs) f = cons (f x) (map xs f)    --- 第二个参数会达到临界值 End (空列表)
// map End f = End
template<typename List,
		template<int> class F>
struct Map;                               //todo  这个通配声明是必要的！ （否则报错！）

template<int headval,typename Tail,     
		template<int> class F>
struct Map<Cons<headval,Tail>,F>          //todo ▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇通过模式匹配来拆解一个 F<a,b,c>类型！   //此处是  List === Cons<headval,Tail>
{
	using Ret = Cons<F<headval>::val, typename Map<Tail, F>::Ret>;
};
/*
template<typename List,
		template<int> class F>
struct Map   
{
private:
	enum { headVal = Head<List>::val };   //todo  本来不是参数的模式匹配拆解，而是手动在内部计算！  太2了。
	using Tail = typename Tail<List>::Ret;
public:
	using Ret = Cons<F<headVal>::val
		, typename Map<Tail, F>::Ret >;
};
*/
template<template<int> class F>
struct Map<End,F>
{
	using Ret = End;
};

//todo ---------------------------------------
template<template<int> class F
		,int ...Args>
struct map_
{
	using Ret = typename List<F<Args>::val...>::Ret;
};
/*----------------------------------*///todo  Last
//!  注意惰性求值（递归终止时，不要再被递归一步！）

// last [x] = x
// last (x:xs) = last xs

template<typename List>
struct Last;

// last (x:xs) = if (null? xs) then x else last xs
//!  null? xs  就对应的   last (x:End) 这个特化嘛！
template<int headval,typename Tail>
struct Last<Cons<headval,Tail>>
{
	//using Ret = typename Last<Tail>::Ret;
	enum { val = Last<Tail>::val };
};

template<int headval>
struct Last<Cons<headval,End>>
{
	//using Ret = Head;
	enum { val = headval};
};
// ---------------------------------------

inline void test_cons()
{
	//! 可以继续把其中的Int类型进行参数化！！

	//  cons , length
	using list1 = Cons<2>;
	auto len1 = Length<list1>::val;
	// head(car), tail(cdr)
	auto head1 = Head<list1>::val;
	using tail1 = Tail<list1>::Ret;
	// is_empty
	bool r3 = Is_Empty<tail1>::val;
	// list
	using list2 = List<4, 5,7,9,11>::Ret;
	// append, reverse, map
	using added_list1 = Append<list1, 9>::Ret;
	using reversed_list1 = Reverse<added_list1>::Ret;
	using mapped_square = Map<reversed_list1, Square>::Ret;

	// map_, last
	using mapped_new = map_<Square,3,7,10>::Ret;
	auto last = Last<mapped_new>::val;
}
//x==========================================================================================================================

#endif

