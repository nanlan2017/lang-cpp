#include <iostream>
#include <tuple>
using namespace std;

template<template<class...> class F, class...Binded>
struct curry
{
private:
	// Func
	template<class...Args>
	static auto Func(Args...) -> typename  F<Args...>::type;
	// 对于重载决议的目的，变长参数的优先级最低，故它们常用作 SFINAE 中的全部捕获回落。
	static auto Func(...) -> void;

public:
	template<class arg>
	using apply = typename std::conditional<
		std::is_same<         // 如果f所需的参数还未绑定完，则将其继续绑定， 否则
			decltype( Func(std::declval<Binded>()..., std::declval<arg>() ) ), // 只要 F<Binded..., arg> 可以编译，就不为void
			void
		>::value,
		curry<F, Binded..., arg>,
		decltype(Func(std::declval<Binded>()..., std::declval<arg>()))
	>::type;
};

template<class R, class S, class T>
struct TestFunc
{
	using type = std::tuple<R,S,T>;
};

//test_curry
void test_curry()
{
	using T1 = curry<TestFunc>::apply<char>;   // curry<TestFunc, char>
	using T2 = T1::apply<short>;               // curry<TestFunc, char, short>
	using T3 = T2::apply<long>;                // ---> tuple<char,short,long>
	//using T4 = T3::apply<int>;                 // x 

	cout << typeid(curry<TestFunc>::apply<char>::apply<short>::apply<long>).name() << endl;
}