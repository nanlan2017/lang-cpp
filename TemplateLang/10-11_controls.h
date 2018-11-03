#ifndef h_controls
#define h_controls

#include "prelude.h"
#include "10-5_Factorial.h"
#include "10-10_cons_list.h"

//!  一个类型可以看作是数据的封装（因为它里面还可以定义成员整型数据、成员类型）
//!  一个类型本身当然也是一个数据。
//！           跟Haskell的data 参数化类型 一样嘛？？？

/*

data Tree a = Empty | Node a (Tree a) (Tree a)
data Shape = Circle Float Float Float | Rectangle Float Float Float Float
*/
// 
//  if<bool, T1, T2> 模板是基于偏特化的 (相当于bool值上的if)
//    要不依赖于偏特化，则要把 计算过程 显式写在内部 （剔除了自动靠参数 进行条件选择）
//! 其实这个例子体现的，是可以将 值的模式匹配/偏特化（这种自动的if选择）,  显式通过在同一个 模式内部的计算（通过部分值），来不依赖于偏特化。

namespace wjh
{

//struct SelectThen
//{
//	template <typename _Then, typename _Else>
//	struct Result
//	{
//		using RET = _Then;
//	};
//};
//
//struct SelectElse
//{
//	template <typename _Then, typename _Else>
//	struct Result
//	{
//		using RET = _Else;
//	};
//};

template<bool cond>
struct ChooseSelector
{
	//using RET = SelectElse;

	template <typename _Then, typename _Else>
	struct F
	{
		using RET = _Else;
	};
};

template<>
struct ChooseSelector<true>
{
	//using RET = SelectThen;

	template <typename _Then, typename _Else>
	struct F
	{
		using RET = _Then;
	};
};

//X 第一步：完全特化。  根据 cond 选择一个 函数 （ 该函数均放在 
//X 第二步：将剩下两个参数传给这个函数。
	//!  很像 curry 化!  / 闭包 ！ 
template<bool cond, typename _Then, typename _Else>
class if_
{

	//using Selector = typename ChooseSelector<cond>::RET;
public:

	//using Ret = typename Selector::template Result<_Then, _Else>::RET;

	using RET = typename ChooseSelector<cond>::template F<_Then, _Else>::RET;
};

inline void test_new_if()
{
	//using t0 = if_<(1 + 1 > 3), int, double>::Ret;
	using t1 = if_<(1 + 1 > 3), int, double>::RET;
}
}
//x====================================================================================================================
/*
Switch< 1,
	Case<1,A,
	Case<2,B,
	Case<Default,C>>  ---> 1
*/

constexpr int Default = endValue;
struct NoMatch;

template<int _val, typename _T>
struct Case;

/*
data Case = Case { val = Int, T = Type }

switch :: Int -> [Case] -> Type
switch c [(Case Default T): _]    =    T
switch c [(Case val T):cases]     =    if c==val then T else switch c cases
*/

template<int cond, typename... Cases>
struct Switch;

template<int cond, int _val, typename _T, typename...Cases>
struct Switch<cond, Case<_val, _T>, Cases...>
{
	using Ret = typename IF<(cond == _val), _T, typename Switch<cond, Cases...>::Ret>::Ret;

	//using Tt = (1 == 1) ? int : double;
	//using Ret = (cond == _val) ? _T : Switch<cond, Cases...>::Ret;  // ?: 运算的各项必须是值（不能是类型）
};

template<int cond, typename _T, typename...Cases>
struct Switch<cond, Case<Default, _T>, Cases...>
{
	using Ret = _T;
};

template<int cond>
struct Switch<cond>
{
	using Ret = NoMatch;
};

inline void test_switch()
{
	using T0 = Switch<(1 + 2)
		, Case<1, int>
		, Case<2, double>
		, Case<3, long>
		, Case<Default, float>>::Ret;

	using T1 = Switch<(1 + 2)
		, Case<1, int>
		, Case<2, double>
		, Case<Default, float>
		, Case<3, long>>::Ret;

	// 无匹配,无default
	using T2 = Switch<(1 + 2)
		, Case<1, int>
		, Case<2, double>>::Ret;
}
//x====================================================================================================================
/*
template <typename T>
struct Fuck
{
	。。。
	foo(){...}
}

... Fuck<int> ...                // 模板进行“实例化” ： Fuck<int> 这个类型被编译       //todo  部分实例化  （其实只相当于一个类型的声明  struct Dog;)


... Fuck<int>::foo(x)...          //todo 完全实例化     （实例化后的类型的成员只在被访问时，才进行实例化）<--- "惰性"
                                        //todo ---------------->  代码中只请求我们应该请求的类型 的Ret/val 成员，--------->  先算出 对象struct，再请求其成员


*/

//=========>  手动要求彻底实例化：  template class Fuck<int>;   //注意有"template"
//x====================================================================================================================




#endif

