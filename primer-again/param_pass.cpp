#include "prelude.h"

void f_1(int* pint){}

void call()
{
	int i = 3;
	const int j = 4;

	f_1(&i);
	//f_1(&j);  //  int* pint = &j ;   // ERROR! 必须用const T* 去关联const对象
	// const 引用可以绑定 const对象、字面值、...
	// 所以： 最好用的 就是 const引用了！ 

}



/*
 initilizer_list<T>  其实就是 List<T> 啊， 就跟 可以传数组一样！！！
————>  貌似没有 lisp中的 &rest 灵活，毕竟人家是动态类型的！
*/
// const T& 可以绑定 字面值！（既可以作为 lvalue引用、也可以作为右值引用）
void error_handler(const int& count, const initializer_list<string>& il)
{
	cout << count;
	for(auto &str : il) {
		cout << str;
	}
}

vector<string> get_strs()
{
	return { "fuck","it" };  // {} 列表字面值可以自动适配 vector返回值  
}

void call_error_handler()
{
	error_handler(5, { "it","is","wrong" });

	vector<string> backed_strs = get_strs();
}

// 所有函数都可改写为： 《尾置返回类型-风格》 trailing return type  格式 // 当返回类型较复杂时
auto f_2(int i) -> int
{
	return 1;
}

auto f_3(int i) -> int (*)[10]
{
	return nullptr;
}

//int(*foo(int))[10];  // 这个有点迷，很不值观！

void call_f()
{
	using Type_int10Arr = int[10];
	Type_int10Arr* (*pt)(int) = nullptr;   // 声明一个指针
	pt = f_3;

	decltype(f_3) *p2 = f_3;

}

/////////////////////// 为const 提供const版的   /////////////////////////////////////////////////
const string& shorter(const string& s1, const string& s2)  // const 版本
{
	return (s1 < s2) ? s1 : s2;
}

// 当返回对象的引用时：问一句：该对象不是再函数体内创建的吧？！
string& shorter(string& s1, string& s2)                // 借助const版本 实现非const版本
{
	auto &r = shorter(const_cast<const string&>(s1), const_cast<const string&>(s2));
	// r :: const string&
	return const_cast<string&>(r);
}

void f_callit()
{
	const string cstr1 = "love";
	const string cstr2 = "like";

	string str3 = "fuck";
	string str4 = "fun";

	shorter(cstr1, cstr2);     // 匹配 shorter:: const string& -> const string& ===> const string&
	shorter(str3, str4);       // 匹配 shorter:: string& -> string& ===> string&

	//void ppp(int);   // 声明了一个ppp函数
	//ppp(3);      // 运行时才发现没有实现？？？
}
