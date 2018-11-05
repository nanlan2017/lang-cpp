#include <type_traits>
using namespace std;

//x=========================================================================================
//! type categorization

template<typename T>
void use_traits_category()
{
	// void?  pointer?  reference?  array?  enum?  union?
	// integral?  float?  class?
	auto r1 = is_void<T>::value;

	//! R(C::*)(args...)  cv   ,   D C::*
	// 指向成员的指针 事实上并不是pointer, 而是一种 offset(偏移量)
	auto r2 = is_member_pointer<T>::value;


	//! R(args...)
	auto r3 = is_function<T>::value;

	/*---------------------------------------------*/
	// fundamental?  基本类型
	// compound?     复合类型
	// scalar?        
	// object?
}