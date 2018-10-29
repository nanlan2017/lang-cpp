#include "prelude.h"

#include <memory>

void test_shared()
{
	shared_ptr<int> sp1 = make_shared<int>();

	int* sp1_raw = sp1.get();
	bool is_sp1_unique = sp1.unique();
	long sp1_count = sp1.use_count();

	cout << *sp1;

	//-------------------------------
	string s1 = "make it";
	auto ps2 = new auto(s1);

	//------------------------------- placement new (“定位new”）
	int* p2 = new (nothrow) int; // 分配失败，会返回一个空指针（而非bad_alloc异常）

	//------------------------------- 常见写法
	if (!sp1.unique()) {
		sp1.reset(new int(100));
	}
	++(*sp1);
}


void test_delete()
{
	int local_i = 3;
	int *p1 = &local_i;
	int *p2 = nullptr;

	//delete local_i;
	//delete p1;  // ▇▇▇▇▇▇行为未定义！不能释放 栈上的对象 (直接程序异常啦！！）
	delete p2;  // 释放nullptr 总是没错的（不过没啥用）

	double *heap_d = new double(3.3);
	auto pd1 = heap_d;
	delete heap_d;  //▇▇▇▇▇▇ delete后指针值还在吗？？？--->  heap_d 的指针值都变了！！
	heap_d = nullptr; // 如果还会保留这个变量，置为nullptr是个好习惯！
	delete pd1; // ▇▇▇▇▇▇未定义！ 该堆上内存已经释放、回收！

}

void test_share_ptr()
{
	shared_ptr<string> sp1;  // “empty"
	sp1 = make_shared<string>("fuck");
	sp1 = nullptr;  // 空的shared_ptr
}

void test_unique()
{
	unique_ptr<string> p1(new string("sterotype"));
	unique_ptr<string> p2(p1.release());  // release只是释放“unique控制权”（同时将此up置为nullptr)， 并不会释放目标对象
	unique_ptr<string> p3(new string("Tex"));
	p3.reset(p2.release());  // “Tex”被释放， 'sterotype'被p3接管。  p2为null-unique-pointer
	//p3 = move(p2);
}

void main_ch12()
{
	//test_shared();
	//test_delete();
	//test_unique();
	test_share_ptr();


	system("pause");
}