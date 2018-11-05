#ifndef h_exer_chap2
#define h_exer_chap2
#include "prelude.h"
#include <boost/polymorphic_cast.hpp>

//x========================================================================================================
template<typename T>
struct add_const_ref: conditional<is_reference<T>::value, T , const T&>
{};

inline void testexer_2_0()
{
	// int& -> int&
	auto r1 = is_same<int&, add_const_ref<int&>::type>::value;
	// int ->  const int &
	auto r2 = is_same<int, add_const_ref<int>::type>::value;
}
//x========================================================================================================
// c 是复合类型 （ 非基本Integral / void)
template<typename c,typename x, typename y>
struct replace_type
{
	using type = c;
	//todo  算法： 如果c 是 x 类型的引用， 则 替换为 y 类型的引用
	// if ( is_same (remove_ref c, x) ,
	using type0 = typename conditional<is_same<typename remove_pointer<c>::type, x>::value
		, typename add_pointer<y>::type
		, void>::type;
	// if~ else if ~ -------->  switch
};

template <typename S, typename T>
struct replace_type<S, S, T>
{
    using type = T;
};

template<typename x, typename y>
struct replace_type<x*,x,y>
{
	using type = y*;
};

template<typename x, typename y, int N>
struct replace_type<x*[N],x,y>
{
	using type = y*[N];
};

//template<typename S, typename T>
//struct replace_type<const S, S ,T>
//{
//	using type = const T;
//};

//!  这个有必要提供啊？
template <typename T, typename SourceType, typename TargetType>
using replace_type_t = typename replace_type<T, SourceType, TargetType>::type;

template<typename R, typename...Args, typename S , typename T>
struct replace_type<R(*)(Args...),S,T>
{
private:
	// 先替换返回值部分
	using RetT = typename replace_type<R, S, T>::type;
public:
	using type = RetT(*)(replace_type_t<Args,S,T>...);
	using type0 = RetT(*)(typename replace_type<Args, S, T>::type...);
};

inline void testexer_2_1()
{
	using t1 = replace_type<void*, void, int>::type;                  // int*
	using t1t = replace_type_t<void*, void, int>;

	using t2 = replace_type<const int*[10], const int, double>::type; // double*[10]

	//todo      为什么 const char&  替换 char& -> long 后，没成为 const long
	//todo      因为  "const char" 被当作一个独立的type
	using t3 = replace_type<char&(*)(char&, char& , const char&), char&, long>::type;       // long(*)(long, const long, const long)
	using t4 = replace_type<char&(*)(char&, char& , const char&), char&, long>::type0;       // long(*)(long, const long, const long)



    static_assert(
            is_same<
                    long & (*) (long &, long &),
                    replace_type_t<char & (*) (char &, char &), char &, long &>
            >(),
            ""
    );
    static_assert(
            std::is_same<
                    long (*) (double &, long),
                    replace_type_t<float & (*) (double &, float &), float &, long>
            >(),
            ""
    );
}
//x========================================================================================================

template<typename Target,typename Source>
inline Target polymorphic_downcast(Source& x)
{
	// 利用指针版：  B& -> B*  
	return *boost::polymorphic_downcast<add_pointer<typename remove_reference<Target>::type>::type>(&x);
}


struct A { virtual ~A(){} };     // trival = default
struct B : A { };
inline void testexpr_2_2()
{
	B b;
	A* a_ptr = &b;
	B* b_ptr = boost::polymorphic_downcast<B*>(a_ptr);

	A& a_ref = b;
	B& b_ref = ::polymorphic_downcast<B&>(a_ref);   //  A&  --> A* ,     B& ---> B*
}

//x========================================================================================================
template <typename T> struct name_of { static constexpr auto value = ""; };

template <> struct name_of<char>        { static constexpr auto value = "char"; };
template <> struct name_of<short int>   { static constexpr auto value = "short int"; };
template <> struct name_of<int>         { static constexpr auto value = "int"; };
template <> struct name_of<long int>    { static constexpr auto value = "long int"; };


template<typename T>
struct type_descriptor
{
	// 这是 对象的 ()运算符  
	//! T()()
	string operator ()()             
	{
		return "";
	}
	 
	// instance -> string 的隐式类型转换   
	//! T()
	operator string()
	{
		return to_string();
	}

	string to_string()
	{
		//!  is_const<T>::value    |    is_const<T>::type::value
		//!  is_const<T>()    
		//!  is_const_v<T>

		//!  remove_const<T>::type
		//!  remove_const_t<T>
		if (is_const<T>()) {
			return type_descriptor<remove_const_t<T>>().to_string() + " const";
		}
		if (is_volatile<T>()) {
			return type_descriptor<remove_const_t<T>>().to_string() + " volatile";
		}
		if (std::is_pointer<T>()) {
            return type_descriptor<std::remove_pointer_t<T>>().to_string() + " *";
        }
        if (std::is_lvalue_reference<T>()) {
            return type_descriptor<std::remove_reference_t<T>>().to_string() + " &";
        }
        if (std::is_rvalue_reference<T>()) {
            return type_descriptor<std::remove_reference_t<T>>().to_string() + " &&";
        }
		//! 数组
		if (std::is_array<T>()) {
            extents_.clear();
            get_next_extent<T>();
            std::string s = type_descriptor<std::remove_all_extents_t<T>>().to_string();
            for (int extent : extents_) {
                if (0 == extent) {
                    s += "[]";
                } else {
                    s += "[" + std::to_string(extent) + "]";
                }
            }
            return s;
        }
		return name_of<T>::value;
	}
private:
	// 用于解析数组的维度 extents
    template <typename U>
    void get_next_extent()
    {
		// 递归终止  int[2] -> int
        if (!std::is_array<U>()) {
            return;
        }
        extents_.push_back(std::extent<U>());
        get_next_extent<std::remove_extent_t<U>>();
    }

	//  int[3][4][4]    ---->  3,4,5
    std::vector<int> extents_;

};

inline void testexer_2_3()
{
	//todo  为什么此处不会自动转为 string
	cout << type_descriptor<int*>().to_string() << endl;
	cout << type_descriptor<int[2][3]>().to_string() << endl;

}

//x========================================================================================================


#endif

