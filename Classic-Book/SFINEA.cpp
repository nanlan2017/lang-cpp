#include "prelude.h"
#include "prelude_boost.h"

//x===============================================================================================================
//! SFINEA 使得我们可以对模板的特化匹配提供各式各样的匹配
template<int i>
struct A
{};

char g(int);
char g(float);

template <class T>
auto f(T) -> A<sizeof( g((T)0) )>
{
	return A<4>();
}

inline void test_SFINEA()
{
	//f(1);
}
//x===============================================================================================================
//todo    判断类是否存在foo()这个成员函数
template<typename T>
struct has_member_foo
{
private:
	/*
	//TODO    如果第一个式子是可通过的，就生成true_type
	//TODO    auto Check(int)  ->  true_type       // 如果foo存在，则此定义被编译 ——> 从而 Check(int) 能得到true_type.  否则就是 false_type
	//TODO    auto Check(...)  ->  false_type
	*/

	//! decltype(exp1, exp2, ...expN)  :  只有当exp1,exp2都是valid (compilable)时，才会产生expN 这个类型
	//! enable_if(test-T, T)           :  只有当T符合条件时，才会在此处生成一个T类型。
    template<typename U>
        static auto Check(int) -> decltype( std::declval<U>().foo(), std::true_type() );  

    template<typename U>
        static std::false_type Check(...);   // 就是匹配的 ： 其他情况下 —— 能够得到匹配（而不至于报错！！）
public:
	static const bool value = std::is_same<decltype(Check<T>(0)), std::true_type>::value;
};
 
struct myStruct
{
    void foo() { std::cout << "hello" << std::endl;  }
};
 
struct another
{
    void test() { std::cout << "test" << std::endl;  }
};
 
void test_sfinea()
{
	auto r1 = has_member_foo<myStruct>::value;
	auto r2 = has_member_foo<another>::value;
}
//x===============================================================================================================
//!  推导链条：
//!      T has foo()  --->   T* p->foo()  [Compilable]   -> decltype(~, UNT) will pass , become a specialization  ->  decltype(Ret) will differ

// Non-templated helper struct:
struct _test_has_foo {
    template<class T>
    static auto test(T* p) -> decltype(p->foo(), std::true_type());

    template<class>
    static auto test(...) -> std::false_type;
};

// Templated actual struct:
template<class T>
struct has_foo : decltype(_test_has_foo::test<T>(nullptr))
{};

void test_sfinea_2()
{
	auto r1 = has_foo<myStruct>::value;
	auto r2 = has_foo<another>::value;
}

//x===============================================================================================================
template <typename... Ts> 
using void_t = void;

template <typename T, typename = void>
struct has_typedef_foobar : std::false_type {};

template <typename T>
struct has_typedef_foobar<T, void_t<typename T::foobar>> : std::true_type {};

//template<typename T>
//struct has_typedef_foobar<T> : std::true_type
//{
//private:
//	using T = typename T::foobar;
//};

struct foo {
  using foobar = float;
};

void test_sfinea_3() {
  std::cout << std::boolalpha;
  std::cout << has_typedef_foobar<int>::value << std::endl;
  std::cout << has_typedef_foobar<foo>::value << std::endl;
}