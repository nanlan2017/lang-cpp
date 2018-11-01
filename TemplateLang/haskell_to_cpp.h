#ifndef h_haskell2cpp
#define h_haskell2cpp
#include "prelude.h"

/* [Haskell]
type Uri = String
type LocalName = String

type NameClass = AnyName
               | QName Uri LocalName
               | NsName Uri
               | NameClassChoice NameClass NameClass
*/
/*
In C++, the variants of NameClass are not connected directly. 
Each of them is defined as a separate struct. 
The members of each data type are given via template parameters. 
▇▇▇▇▇▇▇▇▇▇▇▇ We are using structs everywhere now: both functions and data types are defined via template structs.
*/
using Str = const char*;  //! 还是基本类型
using Uri = Str;
using LocalName = Str;


//! 有无必要让这几个类型都继承自NameClass类型？
// None of these types will be instantiated, so they do not require a complete definition.
//▇▇▇▇ 模板需要被实例化出具体的类型。 而类型本身并不需要实例化出对象。
struct AnyName;

template <Str U, Str L>
struct QName {                    //todo 整型值：非类型 的数据       // QName的成员数据是两个整型值
    static_constexpr Str Uri = U;
    static_constexpr Str LocalName = L;
};

template <Str U>   //!  Non-type parameter
struct NsName {
    static_constexpr Str Uri = U;
};

template <typename NC1, typename NC2>   //! type parameter
struct NameClassChoice {
    using NameClass1 = NC1;          //todo 而一个“类型”：是复合值
	using NameClass2 = NC2;
};
//x============================================================================================================================

constexpr int strCmp_constexpr(char const * s1, char const * s2)
{
	return ((0 == *s1) && (0 == *s2))
		? 0
		: ((*s1 == *s2) || ((*s1 == ' ') && (*s2 == '_')))
		? strCmp_constexpr(s1 + 1, s2 + 1)
		: (*s1 - *s2);
}
//x============================================================================================================================

/*
//todo  Haskell中的每一种函数调用的“pattern" <----------->  MetaTemplate中的一种模板特化
contains :: NameClass -> QName -> Bool

contains AnyName _ = True
contains (QName ns1 ln1) (QName ns2 ln2) = (ns1 == ns2) && (ln1 == ln2)
contains (NsName ns1) (QName ns2 _) = (ns1 == ns2)
contains (NameClassChoice nc1 nc2) n = (contains nc1 n) || (contains nc2 n)
*/
// contains :: Type -> Type -> Bool
template <typename NameClass, typename QName>
struct contains;

//!   contains<AnyName,T>  ---> @T
template <Str U, Str L>
struct contains<AnyName, QName<U,L>> {    //! ▇▇▇▇▇▇▇▇▇▇▇▇应该先定这行、然后把不定的参数补上！
    static_constexpr bool value = true;
};

//!  contains<QName<ns1,ln1>, QName<ns2,ln2>>   ----> @ns1,@ns2,@ln1,@ln2
template <Str U1, Str L1, Str U2, Str L2>
struct contains<QName<U1, L1>, QName<U2, L2>> {
    static_constexpr bool value = strCmp_constexpr(U1, U2) == 0 && strCmp_constexpr(L1, L2) == 0;
};

//! contains<NsName<ns1>,... 完全和Haskell的pattern写法一样啊！
//todo [Haskell]==========>  (QName ns1 ln1) 来模式匹配一个NameClass值
//todo [C++Meta]==========>  QName<ns1,ns2>  来匹配一个类型值。
//todo                   -------->▇▇▇▇▇▇▇▇▇▇▇▇   是可以将  reverse(List) 这个List通过匹配来拆开成  Cons<head,Tail>的！--------我知道这个List就是指 Cons<h,t>
template <Str U1, Str U2, Str L2>
struct contains<NsName<U1>,QName<U2,L2>> {
    static_constexpr bool value = strCmp_constexpr(U1, U2) == 0;
};
template <typename NameClass1, typename NameClass2,Str U2, Str L2>
struct contains<NameClassChoice<NameClass1,NameClass2>,QName<U2,L2>> {
    static_constexpr bool value = contains<NameClass1,QName<U2,L2>>::value
                                  || contains<NameClass2,QName<U2,L2>>::value;
};
//x============================================================================================================================
constexpr char xhtmlNS[]      = "http://www.w3.org/1999/xhtml";
constexpr char divLocalName[] = "div";
constexpr char pLocalName[]   = "p";

template<int i>
struct ShowInt
{
	enum { val = i};
};

inline void test_basicsss()
{
	constexpr int i = strCmp_constexpr("abcdefg", "ab");
	constexpr int j = 6;
	int arrt[i];       // i 确实是编译期计算的值
	auto i2 = ShowInt<i>::val;   //! dependent name ????
	auto i3 = ShowInt<4>::val;
	auto i4 = ShowInt<j>::val;

	static_assert(!false, "wrong!");
	//static_assert(!true, "wrong!");
	static_assert(i, "wrong");
}

inline void testContainsAnyName() {
    using PQName = QName<xhtmlNS, pLocalName>;
    static_assert(contains<AnyName,PQName>::value, "AnyName should match PQName.");
    //static_assert(!contains<AnyName,PQName>::value, "AnyName should match PQName.");  //! failed!
}

inline void testContainsQName() {
    using PQName = QName<xhtmlNS, pLocalName>;
    using DivQName = QName<xhtmlNS, divLocalName>;

	constexpr bool r = contains<DivQName, PQName>::value;  // false

    //static_assert(contains<DivQName,PQName>::value, "DivPQName should not match PQName.");  //! failed!
    static_assert(!contains<DivQName,PQName>::value, "DivPQName should not match PQName.");
}

inline void testContainsNsName() {
    using PQName = QName<xhtmlNS, pLocalName>;
    using HtmlNsName = NsName<xhtmlNS>;

    static_assert(contains<HtmlNsName,PQName>::value, "HtmlNsName should match PQName.");
    //static_assert(!contains<HtmlNsName,PQName>::value, "HtmlNsName should match PQName.");  //! failed!
}

inline void testContainsNameClassChoice() {
    using PQName = QName<xhtmlNS, pLocalName>;
    using DivQName = QName<xhtmlNS, divLocalName>;
    using HtmlNsName = NsName<xhtmlNS>;

    using NameChoice = NameClassChoice<DivQName,HtmlNsName>;

    static_assert(contains<NameChoice,PQName>::value, "NameChoice should match PQName.");
}
#endif

