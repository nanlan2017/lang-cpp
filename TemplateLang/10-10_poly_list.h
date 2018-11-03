#ifndef h_polylist
#define h_polylist

#include "10-10_cons_list.h"
//! 把cons的第一个参数声明为一个类型，而非int，（一个类型是可以绑定一个int成员的，而且还可以用一个Wrapper来用 typename取代int)


/*
就像 Java里可以把 int/double 装箱为 类类型一样，
//todo 通过把 int/bool 值封装成 TypesEnum型的 一个变量，就可以统一用 typename来传递它们 （其值放在 T::val 中)

*/
//! 
template<int n>
struct Int
{
	enum { val = n};
};

struct _End      // 改为两个 Type型 数据的结合
{
	using Head = Int<endValue>;
	using Tail = _End;
};

template<typename _Head, typename _Tail = _End>  //可以嵌套列表了————> 树
struct _Cons
{
	using Head = _Head;
	using Tail = _Tail;
};
//x=======================================================================================  二叉树 (int)
struct BTEnd
{
	enum { val = endValue};
	using Left = BTEnd;
	using Right = BTEnd;
};

template<int _val, typename _Left = BTEnd,typename _Right = BTEnd>
struct BTNode
{
	enum { val = _val };
	using Left = _Left;
	using Right = _Right;
};
//x====================================================================================
#endif
