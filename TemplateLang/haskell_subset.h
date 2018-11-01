#ifndef h_haskellsubset
#define h_haskellsubset
#include "for_test_use.h"
#include <string>

/*
"通配版"（/声明)  要写在最前面———— 和Haskell不同（Haskell是按照前面的只要匹配到就用，所以通配都写最后）
C++ requires template specialization to follow the template’s general definition (or declaration, as we’ll see later).
The pattern matching of arguments in C++ does not follow the order of declarations but rather is based on “best match”.
*/
template<class T> struct
isPtr
{
	static const bool value = false;
};

template<class U> struct
isPtr<U*>
{
	static const bool value = true;
};

template<class U> struct
isPtr<U * const>
{
	static const bool value = true;
};
//x=============================================================================================================
/*
count [] = 0
count (head:tail) = 1 + count tail
*/

//thanks to variadic templates and template parameter packs
// Just a declaration
template<class... list>
struct count;                     //!  ▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇这个后面无 <> 的通配版必须出现。 可以只是声明 不加实现。

template<>
struct count<>
{
	static const int value = 0;
};

template<class head, class... tail>
struct count<head, tail...>
{
	static const int value = 1 + count<tail...>::value;
};

inline void test_count()
{
	auto r = count<int, std::string, double>::value;  // 3
}
//x=============================================================================================================

/*
or_combinator f1 f2 =  λ x -> (f1 x) || (f2 x)
*/
template<template<int> class F1
	, template<int> class F2>
	struct or_comb
{
	template<int n>
	struct Ret
	{
		static const bool val = F1<n>::val || F2<n>::val;
	};
};

inline void test_comb()
{
	auto r1 = or_comb<is_zero, is_one>::Ret<1>::val;
	auto r2 = or_comb<is_zero, is_one>::Ret<3>::val;
}
//x=============================================================================================================
/*
f : [T] -> a
f []     = ...
f [x]    = // 在最后一个元素终止递归也可以！

f (x:xs) = ..x.. # f xs 


//todo  ▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇   LIST 参数的特化模式：

template <typename... List>
struct f;                         // 只有一个不加 <> 的，且必须存在 （其他都肯定加）

template<typename head, typename... tail>
struct f <head,tail...> 
{ }

template<>        // nil元素 （空列表的值）
struct f <>
{ }

*/


template<template<typename> class Predict
	, typename ...List>
struct all;

template<template<typename> class Predict
	, typename Head,typename ...Rest>
struct all<Predict,Head,Rest...>
{
	static const bool val = Predict<Head>::value && all<Predict, Rest...>::val;
};

template<template<typename> class Predict>
struct all<Predict>
{
	static const bool val = true;
};

inline void test_all_temp()
{
	auto r = all<isPtr, int*, double*>::val;
}
//x=============================================================================================================
/*
foldr :: (a->a->a) -> a -> [a] -> a
foldr f acc [x]    =  f acc x
foldr f acc (x:xs) =  
*/

template<template<class, int> class, int, class...> struct
fold_right;

template<template<class, int> class f, int init> struct
fold_right<f, init> {
    static const int value = init;
};

template<template<class, int> class f, int init, class head, class...tail> struct
fold_right<f, init, head, tail...> {
    static const int value = f<head, fold_right<f, init, tail...>::value>::value;
};
//x=============================================================================================================
template<int...> struct
sum;

template<> struct
sum<> {
    static const int value = 0;
};

template<int i, int... tail> struct
sum<i, tail...> {
    static const int value = i + sum<tail...>::value;
};
//x=============================================================================================================
// one x = 1
template<class T> struct
one {
    static const int value = 1;
};

// count lst = sum [one x | x <- lst]
template<typename ...List>
struct Count_
{
	//todo         [Pattern(E1),  Pattern(E2),   Pattern(E3)   ...]
	//todo    Haskell     [ Pattern(x)  |  x <- lst ] 
	//todo    C++TMP      Pattern(List)...                   // List是一个参数包
	static const int value = sum<one<List>::value...>::value;
	//                         sum< one<E1>::value,  one<E2>::value, ,,,
};

//template<typename Head,typename...Tail>
//struct Count_<Head,Tail...>
//{
//	static const int value = sum<one<Head>::value>::value + Count_<Tail...>::value;
//};

//template<>
//struct Count_<>
//{
//	static const int value = 0;
//};

inline void test_count__()
{
	
}
//x=============================================================================================================
template<template<typename> class F
		,typename ...List>
struct map_
{
	/*
	The problem is that it doesn’t compile. 
	As far as I know there is no way for a template to “return” a variable list of elements. 
	In my opinion, this is a major language design flaw
	*/
	//typedef F<List>... Ret;
};

template<typename hd,typename ...tl> 
struct typelist<hd, tl...> {
    typedef hd head;
    typedef typelist<tl...> tail;
};

#endif

