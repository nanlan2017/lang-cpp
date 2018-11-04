#ifndef h_recursion
#define h_recursion
#include "10-10_cons_list.h"

//! 把递归都搞成尾递归
//!    ▇▇▇▇▇▇▇▇方式：把循环更新的状态栈也放在递归参数中


//! ▇▇静态代码不存在对同一数据的多次求值：     Fib<3>::Ret 无论出现多少次，只会求值一次  （不同于动态代码中的 fib(3) 调用）
//x==========================================================================================================
inline int fib(int n)
{
	//  0  1  ...
	int i = 1;
	int x = 1, y = 0;

	while (i < n) {
		++i;
		x += y;      // x + y 
		y = x - y;   // 上一步的x 
	}
	return x;
}

namespace wjhtest {
	
template<bool cond, int n ,int i, int x ,int y>
struct Fib_
{
	enum { val = Fib_<(i+1<n), n, i+1, x+y, x>::val };
};

template<int n ,int i, int x ,int y>
struct Fib_<false,n,i,x,y>
{
	enum {val = x};
};

template<int n>
struct FibMain
{
	enum { val = Fib_<(n>1),n,1, 1,0>::val };
};

inline void test_fibmain()
{
	// 0 1 2 3 4 5 6 7  8  9  10 11
	// 0 1 1 2 3 5 8 13 21 34 55 89
	auto r1 = FibMain<5>::val;
	auto r2 = FibMain<10>::val;
}
}
//x==========================================================================================================
/*
template<int n, int i ,int x ,int y>
struct Fib_Env
{
	enum { result = x };
};

template<typename Fib_Env>
struct Fib_Predict; //! 原型声明
template<int n, int i ,int x ,int y>
struct Fib_Predict<Fib_Env<n,i,x,y>>
{
	static const bool val = i < n;            //x bool 值 和 int 值可能互相转化， 我还是 bool 显示保持类型吧！
};

template<typename Fib_Env>
struct Fib_Update;  //! 原型声明
template<int n, int i ,int x ,int y>
struct Fib_Update<Fib_Env<n,i,x,y>>
{
	using Ret = Fib_Env<n, i + 1, x + y, x>;
};


template<template<int,int,int,int> class Predict        // 模板的 template 参数必须把 参数类型都 标齐嘛！
	, template<int,int,int,int> class Update
	, template<int,int,int,int> class InitEnv>
struct Fib_While
{
	using InitEnv = Fib_Env<5, 1, 1, 0>;
	using Result = typename IF<Fib_Predict<InitEnv>::val, InitEnv, typename Fib_Update<InitEnv>::Ret>::Ret;


	//using Ret = typename IF<Predict<InitEnv>::val, typename Update<InitEnv>::Ret, InitEnv>::Ret;
};

inline void test_Fib_00()
{
	//auto r = 
}
*/
//x ==========================================================================================================
//!  Haskell中的typeclass如何在C++TMP中表达？？
//!     struct 既可以表达数据、又可以表达函数 （事实上，是模板元的唯一construct)
//如何抽象呢？？
/*
如何在 lisp 中实现while:
//todo  先判断当前状态是否要iterate， 如果需要，则iterate ----> 继续回开头

//todo     在haskell中实现 while
while  f_cond_judge   f_update  state  
=  if (f_cond_judge state)  then  state  
                            else  while f_cond_judge f_update (f_update state)

data Env a = Env a

while :: (Env a -> bool)  -> (Env a -> Env a) -> Env a -> Env a
while fpred fupdate state = if (fpred state) then state else while fpred fupdate (fupdate state)

*/

//! 不存在 Env<T> State 这种模板参数 -------->   要不就是 typename / template / int 

template<bool _flag
	,template<typename> class Predict
	,template<typename> class Update
	,typename Env>
struct WhileS               //! 内部调用自身的，必须在参数上体现递归边界点！
{
	using Ret = typename WhileS<true, Predict, Update, typename Update<Env>::Ret>::Ret;
					
};

template<template<typename> class Predict
	,template<typename> class Update
	,typename Env>
struct WhileS<false,Predict,Update,Env>
{
	using Ret = Env;
};
//x ==========================================================================================================
/*
template<typename Env
	, template<Env> class Predict
	, template<Env> class Update>  //! 类型依赖
struct Whilexx;

//template<typename Env
//	, template<Env> class Predict
//	, template<Env> class Update>  //! 类型依赖
//struct While<Predict,Update,Env>   //! 参数顺序————无需与类型依赖顺序一致！
//{
//	using Ret = typename IF<Predict<Env>::val, typename Update<Env>::Ret, Env>::Ret;
//};
template<typename Env
	, template<Env> class Predict
	, template<Env> class Update>
struct Whilexx<Env,Predict,Update>
{
	using Ret = typename IF<Predict<Env>::val, typename Update<Env>::Ret, Env>::Ret;
};

template<int n>
struct Fibs
{
	using InitEnv = Fib_Env<5, 1, 1, 0>;

	using Ret = typename Whilexx<InitEnv, Fib_Predict, Fib_Update>::Ret;
	//using Ret = typename While<Fib_Predict, Fib_Update, InitEnv>::Ret;       //Env = Fib_Env
};
*/
//x ==========================================================================================================
namespace book {
	
template<int n, int i, int x ,int y>          //!  这就是模板元中的 数据结构 (相当于动态中的 struct)
struct 	FibEnv
{
	enum
	{
		n = n,
		i = i,
		x = x,
		y = y
	};
};

//! 函数template 和 数据typename要分清楚——————————Env显然是个typename
template<typename Env>
struct FibIter
{
	using Ret = FibEnv<Env::n, Env::i + 1, Env::x + Env::y, Env::x>;
};

template<typename Env>
struct FibCond
{
	static const bool val = Env::i < Env::n;
};

//x===========================================================================
template<bool flag
		, template<typename> class Predict
		, template<typename> class Update             //! 只会有关键字，不需要命名！！！——————只需要指定类型是 typename/ int 就可以了。
		, typename Env>
struct __While
{
private:
	using NewEnv = typename Update<Env>::Ret;
public:
	using Ret = typename __While<Predict<NewEnv>::val, Predict, Update, NewEnv>::Ret;
};

template<template<typename> class Predict
		, template<typename> class Update
		, typename Env>
struct __While<false,Predict,Update,Env>
{
	using Ret = Env;
};

//! while
template<template<typename> class Predict
		, template<typename> class Update
		, typename InitEnv>
struct While
{
	using Ret = typename __While<Predict<InitEnv>::Ret, Predict, Update, InitEnv>::Ret;
};
//x===========================================================================
template<int n>
struct Fib
{
	enum
	{
		val = While<FibCond, FibIter, FibEnv<n, 1, 1, 0>>::Ret::x,
		//v2 = 3
		vals = WhileS<true, FibCond,FibIter,FibEnv<n,1,1,0>>::Ret::x
	};
};

inline void test_book_fib()
{
	auto r = book::Fib<0>::val;

	auto r2 = Fib<10>::val;
}
}
#endif

