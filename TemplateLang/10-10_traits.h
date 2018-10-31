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

template<int n, typename _Tail>
struct Cons
{
	enum { head = n };
	using Tail = _Tail;
};
#endif

