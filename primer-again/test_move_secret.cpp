#include "prelude.h"

/*
		//  移动过来
		auto dest = newdata;    //?  既然两块内存不是 在一块的 ？？  是怎么通过 move 避免拷贝、就能“在一块”的呢？
									//? <Primer>-P469 : 就好像这个obj实体并不在任何vec中，而vec中只是 “值语义”的obj的指针而已。---> 这样只要把指针拷贝过去就行了（如同swap)
		auto old_ele = elements;
		for( size_t i = 0; i < size(); ++i) {
			alloc.construct(dest++, std::move(*old_ele++));        //  string(string&&  r_obj)
		}
*/

void test_move()
{
	/*
	没有发生拷贝。那么 s2 的地址变了吗？？
	*/
	// 通过被move的obj的地址进行观察
	string s1 = string("i'm lily");
	cout << &s1 << endl;

	string s2;
	cout << &s2 << endl;

	s2 = std::move(s1);      //? s1 变为"" ,  s2具备了s1的值！
	//cout << &s1 << endl;  // error !
	cout << &s2 << endl; //? 地址没变！

}

void main_move()
{
	test_move();
}