#ifndef h_ch16_1
#define h_ch16_1

#include "prelude.h"

template<typename T>
int compare(const T& v1, const T& v2)  
{
	/*
	if (v1 > v2) return 1;     //? T须支持> 运算符
	else return -1;
	
	//?  更泛化的版本： 使用标准库提供的函数对象：less<T>  :: 根据T的类型，自动选择合适的比较运算符
	if (less<T>(v1, v2)) return 1;
	else return -1;
	*/
	return 0;
}


template<typename Ty, typename F = less<Ty>>   // 类型也是变量。 F这个类型变量的默认值就是 less<Ty>
int comp(const Ty& v1, const Ty& v2, F f = F()) // 参数的默认值： 可选的第3个参数：函数对象
{
	if (f(v1, v2)) return 1;
	else return -1;
}


template<unsigned M, unsigned N>
int compare(const char(&s1)[M], const char(&s2)[N])
{
	return strcmp(s1, s2);
}


//? 类本身不是模板，但有个成员函数是模板  ——>▇▇▇▇  函数模板  使用时没有任何特别（其类型参数将由实参自动推定）
//?                                   ——>▇▇▇▇  有时候函数模板的类型变量并不是体现在 参数列表上！ 这时需要 像Class 一样显式指定
class DebugDelete
{
public:
	DebugDelete(ostream& os = cerr):os(os){}

	template<typename T>
	void operator ()(T* ptr) const
	{
		os << "deleting unique_ptr" << endl;
		delete ptr;
	}

private:
	ostream& os;
};

inline void use_case()
{
	unique_ptr<int, DebugDelete> uptr(new int(), DebugDelete());
	uptr.release();  // 会调用 DebugDelete::operater()<int>(int*)
}

/*
template<typename T>
T fobj(T, T);       // 如果调用的实参是 const的，则T 必然包含const

template<typename T>
T fref(const T&, const T&);

inline void use_f()
{
	int a[10], b[20], c[10];
	fobj(a, b);   // T = int*  (数组名转化为指针）
	//fref(a, b);   // 无法推导出T 
	//fref(a, c);   // 即使维度相同也不行  
}
*/
//? 结合使用 decltype,  remove_ref ::  返回迭代器所指向的元素的拷贝。
template<typename It>
auto fcn(It beg, It end) -> typename remove_reference<decltype(*beg)>::type
{
	return *beg;
}
/****************************************************************************/
/*
//?        ▇▇▇▇▇▇▇▇就看看它们有没有办法 和 调用的实参 对上
template<typename T>
void g1(T);      //?  object拷贝，左右const 都行！(抛弃顶层const,留底层const)  ——>  const int * const pt;   则形参会初始化得到  const int*  p; 
template<typename T>
void g2(const T&);   //?  左值；   const 右值
template<typename T>
void g3(T&&)    //?  左值； 非const右值
{
	vector<T> vec;
}
	
template<typename T>
void g2(T&);     //?  只能接受左值，而且必然推断为 左值引用

inline void test_fold()
{
	int i = 0;                // int  l-value + non-const
	const int ci = 0;         // int  l-value + const

	g1(i);
	g1(ci);
	g1(3);

	g2(i);
	g2(ci);
	g2(3);

	g3(i);
	g3(ci);
	g3(3);
}
*/
// 给我任意对象（r
template<typename T>
auto _move(T&& obj) -> typename remove_reference<T>::type&&
{
	return static_cast<typename remove_reference<T>::type&&>(obj);
}

inline void use_move()
{
	int i = 3;
	static_cast<int&&>(i);    // move(i)  ----> 其结果是一个 rvalue object , 然后按引用返回

	/*  右值
	int&&  move(int&& i) {
		return static_cast<int&&>(i);  ==  return i;
	}

	    左值        ------------- 只要返回值里是引用& 符号，就不会对 return 的 obj 进行拷贝 
				   -------------  return 的必然是一个obj对象--不可能是"引用"， 只能是 rvalue/ lvalue的 object
								------------- 我们使用一个 "引用” 时， 完全相当于  在使用那个被引用的object
	int&&  move(int& i) {
		return static_cast<int&&>(i);
	}
	*/
}
#endif

