#include "my_stack.h"
#include "prelude.h"

void test_my_stack()
{
	string ia = "ia", ib = "ib";
	CountStack<string> str_stack;
	str_stack.push(ia);
	str_stack.push(ib);
	cout << str_stack.get_size() << endl;
	str_stack.pop();
}

void main()
{
	//test_my_stack();
	test_snode();
	system("pause");
}