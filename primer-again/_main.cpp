#include "Sales_item.h"

// 全局的变量（其内部内置类型仍会被 初始化为0值》）
Sales_item gobal_salesdata;  // 观察其 revenue成员（内置类型、未指定初始值）    是否被 0值初始化
int global_iarr[10];
string* global_ptr;  // 会被初始化为 nullptr (0值)

// test_init
void main_main()
{
	/*////////////////////////////////////////////////////////////////
	//▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇
	复合类型中 元素的默认初始化表现 与该复合类型变量 的位置有关！！								
	—— 只有内置类型的默认初始化会分为 0值 / undefined raw  （包括指针）						
    那么 一个 对象/数组如果是 全局的，它里面的内置类型成员 也会被 初始化为0值！		
	*///////////////////////////////////////////////////////////////////

	Sales_item local_salesdata;   // 观察此时其成员的值: 未指定初始值的double(内置类型）使用 默认初始化<局部> ---> undefined!!  而非默认初始化<全局>-->0
	int local_iarr[10];
	int second_iarr[10] = { 1 ,2,3 };
	//local_iarr = second_iarr; // 数组是不能直接赋值的

	auto diff = &local_iarr - &second_iarr;
	//cout << typeid(diff);

	
	//void ppp(int);   // 声明了一个ppp函数
	//ppp(3);      // 运行时才发现没有实现？？？   unresolved symbol ! (build-link时就通不过！）

	system("pause");
	//Dog dog;
}

