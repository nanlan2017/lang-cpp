#ifndef h_ch16_flip
#define h_ch16_flip

#include "prelude.h"

//?  ▇▇ C++ 中如何定义 flip                      (▇▇▇▇▇▇▇▇▇▇▇▇▇▇在Haskell中的类型 如何用C++来表达！！！）
/*
flip :: (a->b) -> b -> a  // 单参函数
flip f x y = f y x
*/
// flip 函数，    flip (f , p1, p2) =  f(p2, p1);
template<typename A, typename B, typename C>
auto flip(C(*f)(B&,A&), A& pa, B& pb) -> C           // f :: B -> A -> C 
{
	Print_Type(f);
	Print_Type(pa)
	return f(pb, pa);
}

//? 完美转发！
template<typename FunT, typename A , typename B>
auto flip_(FunT f, A&& pa, B&& pb)
{
	//?  forward<int>--> int&&
	f(forward<B>(pb), forward<A>(pa));
}
#endif

