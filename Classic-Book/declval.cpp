#include <utility>
#include <iostream>


/*
将任意类型 T 转换成引用类型，令在 decltype 表达式中不必经过构造函数就能使用成员函数。

通常在模板中使用 declval ，模板接受的模板实参通常可能无构造函数，但有同一成员函数，均返回所需类型。

注意，因为不存在对 declval 的定义，它只能用于不求值语境；
*/

struct Default { int foo() const { return 1; } };
 
struct NonDefault
{
	NonDefault(const NonDefault&) = default;
    int foo() const { return 1; }
};

using T0 = decltype(Default().foo());
//using T1 = decltype(NonDefault().foo());

//! 从而可以用统一的形式去获取类中成员的类型（绕过类的构造（可能无法默认构造），直接访问其成员函数的类型）
using T2 = decltype(std::declval<Default>().foo());
using T3 = decltype(std::declval<NonDefault>().foo());
 