#ifndef h_ch3
#define h_ch3

#include "prelude_boost.h"
#include "prelude.h"

//x=================================================================================================================



//! 用 Meter<3> 取代 3 （表：米)

//todo  如何用一个类型来 Wrap float ?



//x-------------------------------------------------------------------------------------
/*
template<int i>
struct Meter
{};

template<int i>
struct Second
{};

template<int i>
struct Speed
{ };

template<int i, int j>
auto operator /(Meter<i>,Second<j>)
{
	return Speed<i - j>();
}

template<typename Meter,typename Second>
struct div;

template<int i,int j>
struct div<Meter<i>,Second<j>>
{
	using type = Speed<i - j>;
};
//x-------------------------------------------------------------------------------------
template<int base, int offset>
struct Float
{
	static constexpr float value = base * std::pow(10, offset);
};

template<typename Float>
struct _Meter
{
	static constexpr float value = Float::value;  // 此值是无单位的
};

template<typename Float>
struct _Second
{
	static constexpr float value = Float::value;
};

template<typename Float>
struct _Speed
{
	static constexpr float value = Float::value;
};

//template<int b1, int o1, int b2, int o2>
//auto operator /(_Meter<Float<b1,o1>>, _Second<Float<b2,o2>)
//{
//	return 
//}
*/
//x=======================================================================================================================
// mass           质量          kg   
// length         长度          m
// time           时间          s
// charge         电荷          C
// temperature    温度          oc
// intensity      密度          kg/m^3
// angle          角度?         o
//!  类型序列▇▇▇▇▇▇▇▇▇▇
//!  vector_c,  tranform,  equal
//                                        m, l, t, c, d, i, a
using mass         = mpl::vector_c<int, 1, 0, 0, 0, 0, 0, 0>;
using length       = mpl::vector_c<int, 0, 1, 0, 0, 0, 0, 0>;
using time         = mpl::vector_c<int, 0, 0, 1, 0, 0, 0, 0>;
using charge       = mpl::vector_c<int, 0, 0, 0, 1, 0, 0, 0>;
using temperature  = mpl::vector_c<int, 0, 0, 0, 0, 1, 0, 0>;
using intensity    = mpl::vector_c<int, 0, 0, 0, 0, 0, 1, 0>;
using angle        = mpl::vector_c<int, 0, 0, 0, 0, 0, 0, 1>;
//                                         m, l, t,  c, d, i,  a
using velocity     = mpl::vector_c<int, 0, 1, -1, 0, 0, 0, 0>;  // 速度   l/t
using acceleration = mpl::vector_c<int, 0, 1, -2, 0, 0, 0, 0>;  // 加速度 l/t^2
using momentum     = mpl::vector_c<int, 0, 1, 1, -1, 0, 0, 0>;  // 动量   ml/t
using force        = mpl::vector_c<int, 1, 1, -2, 0, 0, 0, 0>;  // 力     ml/t^2

//! 将单位类型与数值的类型绑定（最终类型）、并可赋数值
template<typename T,typename Dimension>
struct quantity
{
	explicit quantity(T x):m_value(x){}
	T value() const { return m_value; }

	// D1  r = v1 * v2 ;   只当结果量纲与 D1 equal时，才可以赋值。
	template<typename OtherDimension>
	quantity(const quantity<T,OtherDimension>& rhs):m_value(rhs.value())
	{
		static_assert(mpl::equal<Dimension, OtherDimension>::type::value,"dimension not same!");

		//BOOST_STATIC_ASSERT((
		//	mpl::equal<Dimension, OtherDimension>::type::value
		//	));
	}
private:
	T m_value;
};
//x-----------------------------------------------------------------------
template<typename T,typename D1,typename D2>
auto operator+(quantity<T,D1> x, quantity<T,D2> y) -> quantity<T,D1>
{
	static_assert(mpl::equal<D1, D2>::type::value, "+ need equal dimensions");
	return quantity<T, D1>(x.value() + y.value());
}

template<typename T,typename D1,typename D2>
auto operator-(quantity<T,D1> x, quantity<T,D2> y) -> quantity<T,D1>
{
	static_assert(mpl::equal<D1, D2>::type::value, "- need equal dimensions");
	return quantity<T, D1>(x.value() - y.value());
}

// 定义同类型的 + - 运算符
template<typename T,typename D>
quantity<T,D> operator+(quantity<T,D> x, quantity<T,D> y)
{
	return quantity<T, D>(x.value() + y.value());
}

template<typename T,typename D>
quantity<T,D> operator-(quantity<T,D> x, quantity<T,D> y)
{
	return quantity<T, D>(x.value() - y.value());
}
//x---------------------------------------------------------------------
struct plus_f
{
	template<typename T1,typename T2>
	struct apply : mpl::plus<T1,T2>{};         // 相当于 define f(x,y) =  g(x,y)   
};

//struct minus_f
//{
//	template<typename T1,typename T2>
//	struct apply : mpl::minus<T1,T2>{};       //!  meta-function  forwarding  元函数转发
//};

template<typename T1,typename T2>
struct divide_dimension : mpl::transform<T1, T2, mpl::minus<mpl::placeholders::_1,mpl::placeholders:: _2>>{};

//! transform = zipWith (Haskell)
template<typename T,typename D1, typename D2>
auto operator*(quantity<T,D1> x,quantity<T,D2> y)  -> quantity<T,typename mpl::transform<D1,D2,plus_f>::type> 
{
	using dim = typename mpl::transform<D1, D2, plus_f>::type;
	return quantity<T, dim>(x.value() * y.value());
}

template<typename T,typename D1, typename D2>
auto operator/(quantity<T,D1> x,quantity<T,D2> y) -> quantity<T,typename divide_dimension<D1,D2>::type> 
{
	using dim = typename divide_dimension<D1,D2>::type;  // 先计算结果的量纲类型
	return quantity<T, dim>(x.value() / y.value());
}
//x=======================================================================================================================

inline void test_ch3()
{
	//using T0 = div<Meter<10>, Second<2>>::type;

	//Meter<10> m10;
	//Second<2> sec2;
	//auto r0 = m10 / sec2;

	/*------------------------------------------------------*/
	//! mpl::Int_   |   Wrapper
	static int const five = mpl::int_<5>::value;

	//  2.5 kg
	auto mass1 = quantity<float, mass>(2.5f);
	// 1.0 m
	auto len1 = quantity<float, length>(1.0f);
	// 3.4 kg
	auto mass2 = quantity<float, mass>(3.4f);
	auto r1 = mass1 + mass2;

	//! mpl::plus
	using namespace mpl;
	BOOST_STATIC_ASSERT((
		mpl::plus<int_<5>, int_<6>>::type::value == 11
		));
	static_assert(mpl::plus<int_<5>, int_<6>>() == 11,"");

	//! mpl::transform    (zipWith)
	using T1 = mpl::transform<vector_c<int, 1, 2>, vector_c<int, 100, 101>, plus_f>::type;
	//!      占位符
	using T3 = mpl::transform<vector_c<int, 1, 2>, vector_c<int, 100, 101>, mpl::plus<_1,_2 >>::type;

	quantity<float, acceleration> acc1(9.8f);
	
	cout << "force = " << (mass1 * acc1).value() << endl;
	using T2 = mpl::transform<mass, acceleration, plus_f>::type;  // vector_c<int,1,1,-2,0,0,0,0>

	//! mpl::equal
	auto r3 = mpl::equal<vector_c<int, 1, 2>                              // 这是我们使用的类型
		, vector2<integral_c<int, 1>, integral_c<int, 2>>>::value;        // transform返回的新量纲

	auto r6 = mpl::equal<force
		, mpl::transform<mass, acceleration, plus_f>::type>::value; //true

	auto r7 = mpl::equal<momentum
		, mpl::transform<mass, acceleration, plus_f>::type>::value; //false

	quantity<float, force> f1(5.2f);
	quantity<float, force> f2 = mass1 * acc1;
	//todo   既然不能自动把  vec<1,0> 转变为 mass, 就放宽 + 的条件为 demension equal  
	//!  (所有赋值、加、减的 两个量 的要求设定为： 量纲equal 才可进行值计算
	quantity<float, force> f3 = f1 + mass1 * acc1;  // 没有自动进行量纲转等嘛！
	//auto r9 = mass1 + mass1 * acc1; // 此处asset报错！！
	//quantity<float, momentum> r4 = mass1 * acc1;  //! 编译build时，即assert!
}
#endif