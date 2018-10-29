#ifndef H_PRELUD
#define H_PRELUD

#include <string>
#include <iostream>

#include <vector>
#include <set>
#include <map>
#include <algorithm>

#include <memory>


#define PRINT(expression)  std::cout << expression << std::endl;
using namespace std;

//?  c++的宏 比lisp 差在哪儿？  没法控制求值？？   ,  ,@ 

#define Print_Type(obj)                                           \
{                                                                 \
	PRINT(1)                                                      \
	PRINT(2)                                                      \
	std::cout << typeid(obj).name() << std::endl;                 \
	PRINT(3)                                                      \
}
#endif

