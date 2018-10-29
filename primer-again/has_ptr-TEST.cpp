#include "has_ptr.h"

void test_V()
{
	HasPtrV v0 = HasPtrV("a");	
	HasPtrV v1 = HasPtrV("b");

	// 拷贝构造
	HasPtrV v2(v0);
	v1 = v2;
}

void test_P()
{
	HasPtrP v0 = HasPtrP("a");	
	HasPtrP v1 = HasPtrP("b");

	// 拷贝构造
	HasPtrP v2(v0);
	v1 = v2;
}

void test_Ct()
{
	HasPtrCt v0 = HasPtrCt("a");	
	HasPtrCt v1 = HasPtrCt("b");

	// 拷贝构造
	HasPtrCt v2(v0);
	v1 = v2;
}


void main_has() {
	test_V();
	test_P();
	test_Ct();
	system("pause");
}