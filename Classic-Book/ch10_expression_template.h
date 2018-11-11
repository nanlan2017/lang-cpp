#ifndef h_ch10_expression
#define h_ch10_expression

#include "prelude.h"
#include "prelude_boost.h"

template<typename T,std::size_t sz>
class Array 
	: public std::array<T,sz>
{
	template<typename Exp>
	Array& operator=(Exp const& xs)
	{
		for (std::size_t i = 0; i<sz; ++i) {
			this[i] = xs[i];
		}
		return *this;
	}
};
//x--------------------------------------------------------------------------------------------------------------------------
//todo     重载'=' 必须作为成员函数
template<typename T, std::size_t sz, typename Exp>
std::array<T,sz>& operator<=(std::array<T,sz>& r ,Exp const& xs)  
{
	for (std::size_t i = 0; i<sz; ++i) {
		r[i] = xs[i];
	}
	return r;
}	


namespace ch10
{
using namespace boost;
using namespace boost::mpl;

struct plus
{
	static float apply(float a,float b)
	{
		return a + b;
	}
};
struct minus
{
	static float apply(float a,float b)
	{
		return a - b;
	}
};

//x 将表达式“对象化”： 作为一个Expression对象
//todo   ▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇其实是保持住了“语法树”的原本形式；   并且可以自由的访问其中的“部分节点” 的计算
	//todo   ▇▇▇▇▇▇▇▇ 从而避免了 只取部分结果时还要对整颗语法树进行计算的 代价。
template<typename L, typename OpTag, typename R>
struct Expression
{

	using type = Expression<L, OpTag, R>;

	Expression(L const& l, R const& r):l(l),r(r){}

	float operator[](unsigned index) const {
		//取 OpTag所实际的运算，并对两边进行运算
		return OpTag::apply(l[index], r[index]);
	}

//private:
	L const& l;  // 引用并非不可以作为成员。 这样用它就可以存储任何类型的 Expression对象
	R const& r;
};


// 改写 + 
template<typename L, typename R>
auto operator+(L const& l, R const& r) -> Expression<L,plus,R>
{
	return Expression<L, plus, R>(l,r);
}

template<typename L, typename R>
auto operator-(L const& l, R const& r) -> Expression<L,minus,R>
{
	return Expression<L, minus, R>(l,r);
}

inline void test_exp_template()
{
	std::array<float, 5> xs = { 0.0, 1.0, 2.0, 3.0, 4.0 };
	std::array<float, 5> ys = { 0.5, 1.5, 2.5, 3.5, 4.5 };
	std::array<float, 6> zs = { 0.1, 1.1, 2.1, 3.1, 4.1, 5.1 };
	std::array<float, 5> res;

	//float xs[5] = { 0.0, 1.0, 2.0, 3.0, 4.0 };
	//float ys[5] = { 0.5, 1.5, 2.5, 3.5, 4.5 };
	//float zs[6] = { 0.1, 1.1, 2.1, 3.1, 4.1, 5.1 };

	// xs + ys
	auto exp1 = xs + ys;

	// xs - ys
	auto exp2 = xs - ys;

	// xs + ys + zs
	auto exp3 = exp1 + zs;

	// 访问表达式原始的计算对象
	float var1 = exp1.l[1];


	float r1 = exp1[1];   //! 此处未进行任何多余的计算，从而只计算了对应位置的相加
	float r2 = exp3[4];
	std::cout << r1 << std::endl;
	std::cout << r2 << std::endl;

	//res = xs + ys;
	res <= xs + ys;

}

}





#endif

