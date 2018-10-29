//#pragma comment(lib, "libboost_thread_vc140-mt-gd-1_67.lib")

#include "fibonacci.h"
#include <iostream>

#include <boost/thread/thread.hpp> 

void hello()
{
std::cout << "Hello world, I'm a thread!" << std::endl;
}

void main_fibonacci()
{
	boost::thread thrd(&hello);
	thrd.join();
	system("pause");

}

void test_fib()
{
	/*
	需模板实例化 Fib<10> 
	--> 里面定义了一个enum值： （也是编译器确定） --> 需实例化Fib<9>
	--> 直到确定了最后一个enum值
	*/
	auto fib_10 = Fib<10>::Result;		// 推断得：89
}

