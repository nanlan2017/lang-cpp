#include "prelude.h"
#include <functional>

//? 函数对象一： 函数
int add(int x, int y) { return x + y; }

//? 函数对象二： 重载了()运算符的对象
struct divide
{
	int operator ()(int x, int y) { return x / y; }
};

void test_ittt()
{
	//? 函数对象三： lambda
	// lambda 对象的类型 是啥？
	auto mod = [](int x, int y) {return x % y; };
	cout << typeid(mod).name() << endl;



	map<string, int(*)(int, int)>  binops;          //x ---->   它们都可称为同一种类型：  function<int (int,int)>
	binops.insert({ "+", add });  // 可以传递
	 
	//?     指向成员函数的指针  （某个object的 ?)
	//int (*pt)(int, int);



	map<string, function<int(int, int)>> ops = {
		{"+", add},
		{"-", std::minus<int>()},
		{"/", divide()},
		{"*", [](int i,int j) {return i*j; }},
		{"%", mod}
	};

	cout << ops["+"](3, 4) << endl;
	PRINT(ops["*"](3, 4));
}

void main_fun()
{
	test_ittt();
}


//int& ret()
//{
//	return 3;
//}