#ifndef h_ch9_generator
#define h_ch9_generator

#include "prelude.h"
#include "prelude_boost.h"

//!                    ▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇其实就是实现Haskell中的函数组合啊！  f.g  (C++TMP里是 两个可调用对象的compose）

// compose_fg ： 组合两个可调用对象，产生一个新的可调用对象
//!  类型参数到底是归于类，还是归于其成员方法？完全看语义（这个参数是否只关联该方法）
//todo   比如这个R类型？

template<typename R, typename F,typename G>
struct compose_fg
{
	compose_fg(F const& f, G  const& g)
		:fobj(f),gobj(g)
	{ }

	template<typename T>
	R operator()(const T& x) const        // 显然，R类型需要我们去指定
	{
		return fobj(gobj(x));
	}

private:
	F fobj;
	G gobj;
};

template<typename R,typename F, typename G>
auto compose(F const& f, G const& g) -> compose_fg<R,F,G>
{
	return compose_fg<R, F, G>(f, g);
}

// sin2(x)
inline float sin_squared(float x)
{
	return std::sin(std::sin(x));
};

inline void test_composefg()
{
	float in_arr[5] = { 0.1,0.2,0.3,0.4,0.5 };
	float out_arr[5];

	// compose  (-)  sin_squared
	//todo  显然，compose_fg 需要实例化，而此时必须手动输入模板类型实参
	auto composed_func = compose_fg<float
						, std::negate<>
						, float(*)(float)
					   >(std::negate<>(), sin_squared);

	float* ignored = std::transform(in_arr,in_arr+5, out_arr,composed_func);

	//x 优化： 利用compose
	//!  类型书写的问题太多，掩盖了本质简单的计算（所以Haskell是个好语言）
	float* ignored2 = std::transform(in_arr, in_arr + 5, out_arr, compose<float>(std::negate<>(), &sin_squared));
}

template<typename F, bool F_empty, typename G, bool G_empty>
struct storage;

//todo   4种特化形式

template<typename R, typename F,typename G>
struct compose_fg2 
	: storage<F,boost::is_empty<F>::value
			, G,boost::is_empty<G>::value>
{
	using base = storage<F, boost::is_empty<F>::value, G, boost::is_empty<G>::value>;

	compose_fg2(F const& f, G  const& g)
		:base(f,g)
	{ }

	template<typename T>
	R operator()(const T& x) const        // 显然，R类型需要我们去指定
	{
		F const& f = this->get_f();
		G const& g = this->get_f();
		return f(g(x));
	}

private:
	//F fobj;
	//G gobj;
};

#endif

