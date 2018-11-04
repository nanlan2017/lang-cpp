#include "prelude.h"
#include <cstdarg>

//! 可变参数模板   ...(省略号)
// 肯定也是把剩下的参数打包成一个数组: &rest args， 但是内部使用这个数组时不是用 args,而是  args...
// ...Args       ----->   Args...
template<typename T,typename ...Args>
void vfoo(const T& t, const Args&... args)
{
	//!   ...args           <----- [a,b,c]
	//!   Patter(args)...   -----> [Patter(a),Patter(b),Patter(c)]
	cout << sizeof...(Args) << endl;  //模板参数包 （0或多个）
	cout << sizeof...(args) << endl;  //函数参数包
}

/*     通过递归方式来处理一个不定长度的列表（模式匹配到head元素）
f :: os -> [T] -> a
f os [x]    = os << x
f os (x:xs) = os << x  ; f os xs ;
*/

//todo 模板struct我可以理解（模板参数当参数）； 那么模板函数怎么理解？
template<typename T>
ostream& print(ostream& os,const T& t)  //! 和Haskell一样，必须先定义递归终止的那种情况
{
	return os << t;
}
template<typename T, typename...Args>
ostream& print(ostream& os, const T& t, const Args&... rest)
{
	//! 可以对此'rest'进行遍历嘛？？？
	os << t << " ,";
	return print(os, rest...);
}


template<typename T>
void patf(const T& t){}

template<typename ...Args>
void vf(ostream& os,const Args&... rest)
{
	print(os, patf(rest)...);
	//-->     patf(a),patf(b),,,,
}

//! 结合转发
template<typename ...Args>
void fun(Args&&... rest)
{
	// 把这些参数转发给works函数
	works(forward<Args>(rest)...);
}

//x---------------------------------------------------------------------------------------------------------------
//! 可变参数宏
int sum(int count, ...)
{
	//! va = varadic arguments
	//! list, start, arg,end
	va_list ap;
	va_start(ap, count);

	int sum = 0;
	for (int i = 0; i < count; i++) {
		sum += va_arg(ap, int);   //第二个参数表示形参类型
	}
	
	va_end(ap);  //用于清理
 
	return sum;
}

//! initializer-list
int sum2(initializer_list<int> ilist)
{
	int sum = 0;
 
	for (int i : ilist) //类似于容器的操作
	{
		sum += i;
	}
 
	return sum;
}

//! ...?
/*
int sum3(int i, int ... args)
{
	int sum = i;
	for (auto it : args) {
		sum += it;
	}
	return sum;
}
*/
//x---------------------------------------------------------------------
//! 先声明这个模板：是个好习惯！！！
template<typename ...Elements>
struct _tuple;
/*
tuple :: [T] -> To (自身类型)
tuple (t:ts) = <t,>~(tuple ts)    // ~: add field to (tuple ts) by Inherit
tuple []     = <>
*/

//!  这是一种特例化：_tuple<###> 肯定要写的！！
template<typename Head,typename ...Tail>                  //x 通过递归，能够把Args展开?
struct _tuple<Head,Tail...> :private _tuple<Tail...>             //最后是  tuple<TLast> : tuple<>
{
	Head headval;
};

template<>
struct _tuple<>
{};

/*
tuple :: [Ts] -> T

tuple [T]    = T
tuple (T:Ts) = T : tuple Ts  //x 此处 Ts本就可以为空，所以边界条件 可以是 [] 或 [x]
*/
//x----------------------------------------------------------------------
//!  可以认为，“模板元语言”还支持 List 结构 （且支持模式匹配去递归处理List) ————>  和Haskell就更像了。

//!        “模板元语言” 中的变量只有两种类型：  
//!                         参数/内部值： Type(typename) 或者 Integer  
//!          f(x,y,z)--> res  的对应写法   template<Type a,Type y,Type c> struct F { res = ...}
template<int...nums>
struct Multiply;
//todo		Multiply :: [Int] -> Int
//todo		Multiply [] = 1
//todo		Multiply (x:xs) = x * (Multiply xs)
template<int n,int...restnums>
struct Multiply<n,restnums...>
{
	static const int val = n * Multiply<restnums...>::val;
};

template<>
struct Multiply<>
{
	static const int val = 1;
};
//x----------------------------------------------------------------------


void main_varadic()
{
	cout << sum(3, 1, 2, 3) <<endl;
	cout << sum(4, 1, 2, 3)<<endl;//x --出错

	cout << sum2({ 1,2,3 })<<endl;
	cout << sum2({ 1,2,3,4,5 })<<endl;

	vfoo(3, "abc", 2,2);  //2个模板参，3个函数参
	vfoo(6.67, 'b', 5.4,7); //3个模板参，3个函数参

	_tuple<int, double, string> tup;

	auto r = Multiply<3, 4, 5>::val;

	system("pause");
}