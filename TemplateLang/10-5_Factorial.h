#ifndef h_10_5_fac
#define h_10_5_fac
#include "prelude.h"
/*
Fact :: Int -> Int
Fact n = n * Fact (n-1)
Fact 0 = 1

*/

//!  Factorial :: int -> int       ("val")
template<int n>
struct Factorial  //!原型版：此处没有《》
{
	enum { val = n * Factorial<n-1>::val };
};
template<>     // 完全特化：原型其中的type,int都已定
struct Factorial<0>   // 特化版要在这里写 <...>
{
	enum { val = 1 };
};

inline void test_fact()
{
	auto r0 = Factorial<5>::val;
}
//x=====================================================================================================================
//! IF :: int -> Type     -> Type     -> Type
//! IF :: bool-> typename -> typename -> type
//  f  false x y = y   //todo 特化模式1
//  f  _     x y = x   //todo 通配模式
template<bool cond,typename A,typename B>
struct IF
{
	using Ret = A;
};
template<typename A,typename B>
struct IF<false,A,B>
{
	using Ret = B;
};
//x  F<..>::X  这个X可能是指alias,可能是指常量 (默认)，此时需要加typename告诉编译器这是个type alias
inline void test_if()
{
	using T0 = IF<(1 + 5 > 4), string, vector<int>>::Ret;  // 字面值表达式 属于 constexpr
}
//x=====================================================================================================================
/*
常量对象的 指针值， 引用， 都是编译期就能确定的。
https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.2.0/com.ibm.zos.v2r2.cbclx01/template_non-type_arguments.htm

A non-type template argument provided within a template argument list is an expression whose value can be determined at compile time. 
Such arguments must be constant expressions, addresses of functions or objects with external linkage, or addresses of static class members. 
Non-type template arguments are normally used to initialize a class or to specify the sizes of class members.

For non-type integral arguments,   //todo 整型 ： int/short/long , bool , char   (字面值都是编译期常量？？）
the instance argument matches the corresponding template parameter as long as the instance argument has a value and sign appropriate to the parameter type.

For non-type address arguments,    //todo 地址型
the type of the instance argument must be of the form identifier or &identifier, 
and the type of the instance argument must match the template parameter exactly, 
except that a function name is changed to a pointer to function type before matching.

The resulting values of non-type template arguments within a template argument list form part of the template class type. 
If two template class names have the same template name and if their arguments have identical values, they are the same class.
*/
enum
{
	val = false,
	v2 = 4,
	v3 = 'c',
	//v4 = 3.2
	//v4 = nullptr
};

template<bool p1, int p2, const char* p3>           //! 只要这个指针/引用的对象----地址值是在编译期确定，就可以作为模板参数（整形编译期常量）
struct Params
{
	
};
//x=====================================================================================================================
inline
int my_max(const int x, const int y)
{
	return x > y ? x : y;
}
//inline
constexpr int my_max_constexpr(const int x, const int y)
{
	return x > y ? x : y;
}

template<int x ,int y>
struct Maxium
{
	enum
	{
		v1 = max(x, y),  
		v3 = my_max(x,y),		// 非constexpr的函数调用是 运行期求值的
		v4 = my_max_constexpr(x,y)  //! constexpr 
	};
};

inline void test_maxium()
{
	using T0 = Maxium<5, 6>;
	auto r1 = T0::v1;  //todo 未发生编译期计算，结果未默认的 enumerator值：0
	auto r3 = T0::v3;  //todo 未发生编译期计算，结果未默认的 前一个enumerator值 + 1
	auto r4 = T0::v4;  // 6 ，正确
}
//x=====================================================================================================================
//! 局部let计算出来的 部分值使用 private 。 只把结果值暴露为 public ------>  这时候用 Class比 struct好。

// 用两个整数来表示浮点数  Float函数
template<int _base, int _exp>
struct Float
{
	enum
	{
		base = _base,
		exp = _exp
	};
	// 到 const float 的类型转换函数
	operator const float() const{
		return _base * pow(10, _exp);  // base就是base, exp是小数点左移的位数       2.5 就是 25 * 10^-1  , 记作 F2_5
	}


};

template<typename Float>
struct Sqrt
{
	
};

inline void test_float()
{
	using F1 = Float<25, -1>;
	float f1 = F1();
	//int ay[F1()];
	/*---------------------------*/
	// 2.5
	using F2_5 = Float<25, -1>;
	using F4_0 = Float<4, 0>;


}
//x=====================================================================================================================
//! 高阶函数
/*
Acc :: Int -> (Int->Int) -> Int
Acc n f = f n + Acc (n-1) f
Acc 0 f = f 0
*/
template<int n,
		template<int> class F>    //! F : 是具备Int参数的模板类型       template<, ,> class F
struct Acc
{
	enum {val = F<n>::val + Acc<n-1,F>::val };
};

template<template<int> class F>
struct Acc<0,F>
{
	enum {val = F<0>::val };
};

template<int n>
struct Square
{
	enum { val = n*n };
};


//--------------------------------------------------------------------
// Squrare是一个模板， 并且传给了F， 内部再调用 F<...>::val
//! ▇▇▇▇▇▇▇▇如果编译器不支持模板参数为模板类型，（只支持平凡类型），则可以把它封装在一个非模板类型中（作为成员模板）
struct SquareWrapper
{
	template<int n>                  //! ▇▇▇▇▇▇▇▇
	struct Apply                     //! A::B                // B is value(default)
	{                                //! typename A::B       // B is type
		enum { val = n*n };          //! A::template B       // B is template           
	};
};

template<int n,
		 typename F_Wrapper>
struct Acc2
{
	enum
	{
		val = F_Wrapper::template Apply<n>::val + Acc2<n-1,F_Wrapper>::val
	};
};

template<typename F_Wrapper>
struct Acc2<0,F_Wrapper>
{
	enum {val = F_Wrapper::template Apply<0>::val };
};

inline void test_Acc()
{
	// 3^2 + 2^2 + 1^2 
	int r = Acc<3, Square>::val;

	int r1 = Acc2<3, SquareWrapper>::val;
}
//x=====================================================================================================================
//! 把一个元函数作为结果返回：返回的值（肯定是一个模板类了）
//!   
struct ReturnFunction
{
	template <int n>
	using RetF = Square<n>;         //! ▇▇▇▇▇▇▇▇ 定义了一个模板成员，并为其绑定了一个模板

	//using RetF2 = Square; 
};

inline void test_fback()
{
	auto r = ReturnFunction::RetF<4>::val;  // 16
}
//x=====================================================================================================================





#endif
