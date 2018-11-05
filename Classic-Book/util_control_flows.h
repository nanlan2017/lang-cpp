#ifndef h_control_flows
#define h_control_flows

#include <type_traits>
//x===========================================================================================================================
const int endValue = ~(~0u >> 1);
constexpr int Default = endValue;
struct NoMatch;

template<int _val, typename _T>
struct Case;

/*
data Case = Case { val = Int, T = Type }

switch :: Int -> [Case] -> Type
switch c [(Case Default T): _]    =    T
switch c [(Case val T):cases]     =    if c==val then T else switch c cases
*/

template<int cond, typename... Cases>
struct Switch;

template<int cond, int _val, typename _T, typename...Cases>
struct Switch<cond, Case<_val, _T>, Cases...>
{
	using type = typename std::conditional<(cond == _val), _T, typename Switch<cond, Cases...>::type>::type;

	//using Tt = (1 == 1) ? int : double;
	//using Ret = (cond == _val) ? _T : Switch<cond, Cases...>::Ret;  // ?: 运算的各项必须是值（不能是类型）
};

template<int cond, typename _T, typename...Cases>
struct Switch<cond, Case<Default, _T>, Cases...>
{
	using type = _T;
};

template<int cond>
struct Switch<cond>
{
	using type = NoMatch;
};

inline void test_switch()
{
	using T0 = Switch<(1 + 2)
		, Case<1, int>
		, Case<2, double>
		, Case<3, long>
		, Case<Default, float>>::type;

	using T1 = Switch<(1 + 2)
		, Case<1, int>
		, Case<2, double>
		, Case<Default, float>
		, Case<3, long>>::type;

	// 无匹配,无default
	using T2 = Switch<(1 + 2)
		, Case<1, int>
		, Case<2, double>>::type;
}
//x===========================================================================================================================

#endif

