#ifndef H_PRELUD
#define H_PRELUD

#include <string>
#include <memory>
#include <iostream>

#include <iterator>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <array>
#include <algorithm>

#include <functional>
#include <type_traits>


//x=============================================================================================
#define static_const static const
#define static_constexpr static constexpr

#define PRINT(expression)  std::cout << expression << std::endl;

//?  c++的宏 比lisp 差在哪儿？  没法控制求值？？   ,  ,@ 

#define Print_Type(obj)                                           \
{                                                                 \
	PRINT(1)                                                      \
	PRINT(2)                                                      \
	std::cout << typeid(obj).name() << std::endl;                 \
	PRINT(3)                                                      \
}
#endif

