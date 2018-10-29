#include "prelude.h"

class Foo
{
public:
	Foo& operator =(const Foo&) &;      // 只会当左侧被赋值对象是 l-value object


	Foo  somefun() const &;

	//? 重载成员函数： 基于 这两个接口所针对的 object的 左/右值 性质不同
	//?    reference qualifier
	Foo sorted() &&
	{
		// 可以直接利用原有元素，不必拷贝
		sort(data.begin(), data.end());
		return *this;
	}
	Foo sorted() const &
	{
		/*
		// 假设  a.sorted() :  拷贝a 得到b  -->  排序b  --> 返回b的拷贝
		Foo ret(*this);
		sort(ret.data.begin(), ret.data.end());
		return ret;
		*/
		return Foo(*this).sorted();  // 拷贝a 得到 tmp-b --> 排序b 并拷贝排序好的 --> 再次拷贝
	}
private:
	vector<int> data;
};