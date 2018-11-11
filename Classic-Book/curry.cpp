#include <iostream>
#include <tuple>
using namespace std;

template<template<class...> class T, class...Binded>
struct curry
{
	template<class...TestArgs>
	static typename  T<TestArgs...>::type TestFunc(TestArgs...);

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

template<class R, class S, class T>
struct TestFunc
{
	using type = std::tuple<R,S,T>;
};


void test_curry()
{
	cout << typeid(curry<TestFunc>::type<char>::type<short>::type<long>).name() << endl;
}