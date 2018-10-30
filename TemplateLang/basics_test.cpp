#include "basics.h"
#include <string>

void test_basics()
{
	using R1 = IF<(2 + 3 < 4), int, std::string>::Ret;

 
	//无法使用局部变量或者动态变量作为模板参数
	pointerT<ca>("Wendy"); //指针
 
	referenceT<cr>("Wendy"); //引用
 
	fpointerT<global_f>("Caroline Wendy"); //函数指针


}
