#include "prelude.h"

class SmallInt
{
public:
	SmallInt(int i = 0)
	{
		if (i > 255) {
			throw out_of_range("too big!");
		}
		val = i;
	}

	// 定义向 int 的转换
	//operator int() const
	//{
	//	return val;
	//}

	//?  C++ 11 改进： 显式的类型转换
	explicit operator int() const
	{
		return val;
	}

private:
	int val;
};

void test_333()
{
	//?  一次只允许一次类型转换？  x   --->   自定义的类型转换可以跟在 系统提供的隐式类型转换之后
	SmallInt si = 3.14;

	static_cast<int>(si) + 3;  //? 转换处你就能看到！！
}