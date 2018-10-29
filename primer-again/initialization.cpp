#include "iostream"
using namespace std;

void e_list_initialization()
{
	// 两种基本写法
	int i1 = 3;
	int i2(3);

	// List Initilization
	int i3 = { 3 };
	int i4{ 3 };
}


int f_target(double* p_d)
{
	return 1;
}

/*
▇▇▇▇▇▇▇ 定义变量时未指定初始值， 则变量被“默认初始化”   ---> “默认值"

	内置类型：（包括指针！）
		1. 全局作用域  --->  0  ( int global_x; 相当于--->  int global_x = 0; )
		2. 局部变量    --->  不被初始化！（undefined)  --->  ☆☆☆ 只有局部的内置类型可能出现undefined !（包括指针） --->  raw值（内存原始0101)
    Class类型：
		 Dog dog;  ---> 若存在无参构造函数，则按无参构造进行初始化 
                         （不存在无参构造器的话，这种写法 编译器会报错！！)
*/
void e_default_initialization()
{
	//int i = { 3.14 }; // ERROR!
	//double x1 = x2 = 9999.99;
	int i2 = 3.14;

	int x = 3;
	int* px = &x;
	int& rx = x;
	int*& rpx = px;  // 还可以引用一个指针变量

	int(*pf)(double*) = &f_target;  // 声明一个  FUNCTION :: double* -> int 类型的指针变量 pf
	int(*pf2)(double*) = f_target;  // 指向函数时，可以省略 & 取地址
	double y = 3.14;
	(*pf)(&y);
}


// 变量定义=创建（definition = creation)  vs   变量声明


void const_compound()
{
	const int x = 3;
	int y = 9;

	//int& rx = x;   //ERROR !                  引用一个常量时，必须使用 const T 的引用
	const int &crx = x;

	const int &cry = y;  // ☆☆☆ 可以用 const int的 & 来引用一个 非const 对象
	//cry = 7;   //ERROR !                     ▲ 那么，用cry时 该对象表现为只读， 而用原本的y时 仍是非const;
	y = 7;

	//int* px = &x;   //ERROR !                指向一个常量时，必须使用 const T 的指针
	const int *cpx = &x;  // cpx :: const int <- *
	cpx = &y;             // ☆☆☆ 仍然可以换指向  int <- *    (其实是用 int* 的值赋给 const int* 对象）
	//*cpx = 4;  // ERROR !                      cpx对其指向的对象加了一层const修饰！

	/////////////////////////////////////////////////////////
	/*
	总结： 对于一个 const 对象，只能使用 const & 和 const * 来关联
	      但对于一个 mutable 对象， 仍可以使用 const & cr 和 const * cp来关联 （但 cr , *cp 访问该对象时表现为 const ) 

	==>  透过 & 和 * 来关联一个对象时，可能对其加了一层 const 。
	*/


	//////////////////////////////////////////////////////////
	// ===>   说白了，pointer有点特殊， 它除了像一般对象一样 可以区分自身的值 为 const /mutable 以外
	// ===>                            还可以对 其所关联的对象 加上一层保护 （当使用此指针访问时）
	// int y = 9;  const int* pt = &y ;   则这块内存对y来说是mutable的，对 *pt来说是 const的。
	//////////////////////////////////////////////////////////

	int m = 1;
	// ▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇
	// 这两种写法是一样的 （const 写在 * 前面）  ---▲  这个 const 区分称为  low-level const  (只有 指针/引用 才可能出现 low-level const) 
	// const int& r = m ;    "用来声明引用的const 都是 底层const"(引用本身不是对象，不存在顶层const)
	int const * p1 = &m;
	const int * p2 = &m;
	// 这种则指针本身是常量 (const 写在 * 后面） ---▲  这个 const 区分称为  top-level const
	int * const p3 = &m;
}


void auto_infer()
{
	int i = 0, &r = i;
	auto a = r;   // a :: int

	const int ci = 1, &cr = ci;   // cr 是底层const (引用的const都是底层const)
	auto b = ci; // b :: int  === auto会忽略顶层的 const属性， 但会保留 底层的const属性

	
	auto d = &ci;
	auto e = &cr;
}


























