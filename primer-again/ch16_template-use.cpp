#include "ch16_template_compare.h"

void use()
{
	//? compair<int>  这个具体函数被实例化编译
	auto r = compare(3, 5);
	auto r2 = compare<double>(2.3, 1);  // 可以指定`函数模板`实例化的类型参数啊！
}

void type_manipulation()
{
	using Ty1 = remove_reference<int&>::type;  // int

}


void main_t()
{
	use();
}