#ifndef h_10_10_traits
#define h_10_10_traits
#include "10-5_Factorial.h"
#define statcon static const


//! 1. member traits  
//! 2. traits class
//! 3. traits template

struct FooBase
{
	enum  {fooBase = 100, foo1, foo2};
	enum {id = fooBase};
};

struct Foo1 : FooBase
{
	enum { id = foo1 };          //! 类型内部定义与自己类型相关的信息
};

struct Foo2 : FooBase
{
	enum { id = foo2 };
};


template<typename SomeFoo>
struct TestFoo
{
	enum { val = SomeFoo::id };  //! 访问信息成员
};
inline void test_foobase()
{
	auto r = TestFoo<Foo1>::val;
}
//x============================================================================================================
//! 2. traits class
//!    把多个信息（无非是类型、整型值）进一步统一放在一个成员类型中





//x============================================================================================================
//! 3. traits template
//!    相当于一个函数 F<type> 调用后则各种信息值同时确定—————— 一个类型内部可以包含很多个成员信息


//todo  numeric_traits  :: Type -> [Info...]
template<typename T>
struct nume_traits
{
	//x 通配属性
	static T max() noexcept;
};

//! 擅用基类和继承
struct IntBase
{
	
};

template<>
struct nume_traits<long> : public IntBase
{
	using Type = long;
};

template<>
struct nume_traits<int>
{
	// bool, int ,char
	statcon bool has_infinity = false;
	statcon bool is_bounded = false;
	static int max() noexcept { return 1000000; }   // 非整型值无法于编译器使用
};

inline void test_traits()
{
	bool r = nume_traits<int>::is_bounded;
}
//x============================================================================================================
//! 类型提升
//  Promotion<A,B>::Type  返回两个类型中 精度较高的那个类型   （ T::precision 更大的那个)
template<typename A, typename B>
struct Promotion
{
private:
	enum
	{
		a_max_exp = nume_traits<A>::has_infinity,
		b_max_exp = nume_traits<B>::has_infinity
	};
public:
	using Type = typename IF< (a_max_exp < b_max_exp), A, B>::Ret;
};
//x============================================================================================================


#endif

