#include "prelude.h"
#include <cassert>

void use_vector()
{
	vector<string> svec{ "i","love","you" };

	vector<int> ivec(10);  // vector的行为定义： 不指定初始值时，采用默认初始化（内置类型采用 默认<0>, 而非默认<undefined> )
}


void pointer_operator()
{
	int i = 1, j = 3;
	int *p1 = &i, *p2 = &j;
	if(p1 < p2) {  // 两个目标不是同一个对象，比较毫无意义
		//
	}

	char* p3 = "hello";
	//if (p1 < p3) {}  // 两个变量类型不同， 不存在该  (<) :: int* -> char*

}


void rvalue_test()
{
	int i = 3;
	int* p = &i;

	// *p 得到的 lvalue :: int  --->  ▇▇▇▇▇▇▇decltype(lvalue T)  == T&
	decltype(*p) k = i;  // int& k = i;
	// &p 得到的 rvalue :: int** ---> ▇▇▇▇▇▇▇decltype(rvalue T)  == T
	decltype(&p) m = &p;
}


// 其实这四个都是 函数模板。   模板的类型参数为转换的目标类型
void type_cast()
{
	// static_cast  (不能去除 const性质）
	int i = 2, j = 3;
	double v1 = static_cast<double>(i);

	// const_cast  （唯一作用是 擦除const性质）
	char c = 'L';
	const char c2 = 'I';
	const char* pc = &c;
	const char* pcc = &c2;
	char *p2 = const_cast<char*>(pc);
	char *p22 = const_cast<char*>(pcc);   // 就算那个 c2 本身是const， 其实不过是那块内存 对c2 这个name表现为 const!
	*p2 = 'M';
	//*pc = "N"; //EROOR
	*p22 = 'A';

	// reinterpret_cast
	int* ip = &i;
	char* pc2 = reinterpret_cast<char*>(ip);  //  int* ---> char*  ：用一个char* pc2 指向

	// dynamic_cast
	// ? 用于 子类指针<--> 父类指针 的转换？
}

void iterate_seq()
{
	vector<int> ivec = { 1,2,3 };
	for(auto &ele : ivec) {    // 这才是拿到 ivec中存放的 object本身
		ele = ele * 2;
	}
	for (auto e :ivec) {    // 毫无意义，这里已经对 object进行了拷贝
		e = e * 2;     
	}
}

void test_goto()
{
	assert(false);
}

// 这两种写法是一样的， pf 都是指针
//void has_function_param(bool pf(int));
//void has_function_param2(bool(*pf)(int));


// ▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇
string global_str = "hi,lily";
string& ret_ref()
{
	return global_str;
}

void call_ret_ref()
{
	string& r1 = ret_ref();  // 等价于  string& r1 = global_str;    语义时：把别名name r1 绑定到返回的这个对象上 （返回引用=== 返回对象本身-而非副本）
		// 此时，调用点就像在使用哪个object本身
	string r2 = ret_ref();   // 等价于  string r2 = global_str;   当然就是拷贝了！
	ret_ref() = "hi,jack";   // 等价于  global_str = "hi,jack";  
}

