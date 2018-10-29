#include "prelude.h"

void by_new()
{
	string* pstr_arr = new string[10]{ "first","second" };
	// pstr_arr 仍然是指向一个string， 肯定和 普通的单个 pointer 有些不同 （它知道自己处于一个动态数组）

	delete[] pstr_arr;

	//------------------------ new + unique_ptr
	unique_ptr<string[]> uptr(new string[10]{ "first","second" });
	cout << uptr[1];
	uptr.release();

	//------------------------ new + shared_ptr
	shared_ptr<string> sptr(new string[10]{ "first","second" },
		                      [](string* ptr) {delete[] ptr; });   // 必须提供 匿名的deletor 函数： delete[]
///*
	// 访问
	for (size_t i = 0; i < 10; i++) {
		cout << *(sptr.get() + i);
	}
	auto v0 = *sptr; // "first" // 表现得和单个元素一样
	sptr.reset(); // 释放该动态数组
//*/

}

void by_lib_allocator()
{
	//?          《标准库提供的”动态数组“ API》
	// allocate  ->  construct  -> destory() ->  de-allocate() 
	//  划分             构建         析构             回收

	// allocator<T>  a;
	// a.allocate(个数);
	// a.construct( T* ptr_position, &args)
	// a.destory(T* ptr_position)
	// a.de-allocate(T* ptr_position, 个数)  // 必须与allocate的 位置、个数 吻合！


	//-------------------------------  填充动态数组 （而非一个个construct)
	// un-initialized -~~
	//                copy (源begin,源end, T* ptr_postion)
	//				 copy_n (源begin,个数, T* ptr_postion)

	//				 fill (目标_begin, 目标_end,  object)  // 均为object拷贝
	//				 fill_n （目标_begin, 个数,  object)  // 均为object拷贝

}

void main_dynamic()
{
	by_new();
	by_lib_allocator();

	string s = "love";
	addressof(s);
}