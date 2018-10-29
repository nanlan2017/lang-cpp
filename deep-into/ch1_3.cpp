#include "ch1_3.h"
#include "prelude.h"

void process_arr(int* arr_head)
{
	
}

void main_ch13()
{
	int arr[4] = { 1, 2, 3, 4 };
	cout << &arr[3] << endl;
	auto r1 = max_elem(arr,4);
	auto& r2 = max_elem(arr, 4);
	cout << &r1 << endl;
	cout << &r2 << endl;  // 引用的就是arr[3] 这个元素对象

	char carr[7] = "loveit";

	const int conarr[4] = { 1, 2, 3, 4 };
	process_arr(arr);
	//process_arr(conarr);

	use_Fuc();

	system("pause");
}