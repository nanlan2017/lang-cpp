#include "prelude.h"

// 说模板元编程不支持柯里化（currying）而不算函数式语言的也是够了
// 组合使用变长模板参数、模板模板参数和SFINAE即可实现

//! 还支持高阶函数，模板参数可以是另一个模板
/*
curry f &rest Binded
*/
template<template<class...> class T
		, class...Binded>
struct curry
{
	//! 啥时候用模板函数？模板函数的角色应当是什么？？
	// TestFunc ts = F ts
	template<class...TestArgs>
	static typename  T<TestArgs...>::type TestFunc(TestArgs...);
	// TestFunc _ = void
	static void TestFunc(...);

	template<class X>
	using type = typename std::conditional<
		std::is_same< 
			decltype( TestFunc( std::declval<Binded>()..., std::declval<X>() ) ), 
			void
		>::value,
		curry<T, Binded..., X>,
		decltype(TestFunc(std::declval<Binded>()..., std::declval<X>()))
	>::type;
};

// TestFunc :: T -> T -> T -> T        
// TestFunc a b c = tuple a b c        (模板类型参数是变量）
template<class R, class S, class T>
struct TestFunc
{
	using type = std::tuple<R,S,T>;
};

/*
Scheme实现Curry
//todo ———— 返回一个闭包（也是函数对象）

(defun curry (f x &rest rest)
	(lambda (&args) (f x args)))

f :: a -> b -> c...


//todo 就是把已提供的 参数值放在 新得到的函数中

curry:: 
curry :: (T->T->T->T) -> T -> (T->T->T)
// （T->T) 这个签名对应的是  template<T> struct F { using RetT = Tr;}

curry< F<a,b,c> , T1>    ===>    F<T1,b,c>
*/



void main_curry()
{
	using R = curry<TestFunc>::type<char>::type<short>::type<long>;
	cout << typeid(R).name() << endl;
}