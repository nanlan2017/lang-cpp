#ifndef h_basics
#define h_basics
#include "prelude.h"
//! 这就是一门模板新语言（很像Haskell: 没有可变量、有基本的结构）
	// 没有其他的函数了。 只有不可变的编译时常量表达式、和类型。
	//! 把template struct当成函数来用 ——>  其数据就是 类型、整形 (template params就是参数）
	//!                              ——>  通过特化实现选择结构（乃至IF)
	//!                              ——>  通过递归实现循环

/*
data TypesEnum = Int | Bool | ....
*/

/*
if :: bool -> TYE -> TYE -> TYE
if true x y = x
if _    x y = y

*/
template<bool cond, typename A, typename B>
struct IF
{
	using Ret = B;
};

template<typename A,typename B>
struct IF<true,A,B>
{
	using Ret = A;
};

//x -----------------------------------------------------------------

//指针
template<const char* C>
void pointerT(const char* str){
	std::cout << C << " " << str << std::endl;
}
 
//引用
template<char (&ra)[9]>
void referenceT(const char* str){
	std::cout << ra << " " << str << std::endl;
}
 
char ca[] = "Caroline"; //初始化指针
char cr[9] = "Caroline"; //初始化引用, 包含一个结尾符号
 
inline void global_f(const char* c) {std::cout << c << std::endl; }
 
//函数指针
template<void (*F)(const char*)>
void fpointerT(const char* c) {
	F(c);
}

#endif

