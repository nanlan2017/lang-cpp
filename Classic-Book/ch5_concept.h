#ifndef h_ch5_concept
#define h_ch5_concept

#include "prelude.h"
#include "prelude_boost.h"

inline void test_ch5_iterator_concept()
{
	//  std::vector<int> ivec = { 2,5,7,9,11 };
	using types_seq = mpl::vector<int, long, double, short, char>;  //! ~ void_, unknown, unknown ...
	//  auto ipos = std::find(ivec.begin(),ivec.end(), 7);
	using iter1 = mpl::find<types_seq, long>::type;

	//! <iterator.hpp>--> v_iter
	using t0 = iter1::type; // long (deref)
	using t1 = iter1::pos;
	using t3 = iter1::category;  //todo    本iterator的类型是： 随机访问迭代器

	//  vec.end()
	using end1 = mpl::end<types_seq>::type;  //! iter-type ::  v_iter<seq, index>
	//  *iter;
	using elem1 = mpl::deref<iter1>::type;  // long
	// iter++,  iter--
	using iter2 = mpl::next<iter1>::type;
	//using iter2b = iter1::next::type; // iter本身没有next成员
	using iter3 = mpl::prior<iter1>::type;

	// 逾尾
	using iter4 = mpl::find<types_seq, char>::type;
	using iter5 = mpl::next<iter4>::type;
	using iter6 = mpl::next<iter5>::type;  // next只是简单的把 index+1
	using wrong = mpl::deref<iter5>::type;  // end : void_
	using wrong2 = mpl::deref<iter6>::type;  // >end: unknown

	//x 随机访问迭代器
	//x  不同的迭代器（前向、双向、随机） 只是因为它与序列的关联方式不一样（主要是关联数据、访问算法）
	//x  最基本的：肯定要 vector + 某个element的index
	//x   --------- 前向：  next 直接作为成员
	//x   ----------随机
	using t2 = mpl::advance<iter1, mpl::int_<3>>::type;  //! advance n = idx + n
	using dis1 = mpl::distance<iter1, iter4>::type;      //! long_<3>  // 


}


inline void test_ch5_sequence_concept()
{
	// 前向序列：  begin ,end, front
	// 双向序列：  begin ,end, front ,back
	// 随机序列：  at<Seq,n>

}


inline void test_ch5_()
{
	//!   ▇▇▇▇就像 vector_c 被计算后会成为 vector<integral_c<int>...> 一样
	//!    ▇▇▇▇Seq<> 被计算后经常会转变为 SeqN<> 
	using vec = mpl::vector<int, double>;
	using vec2 = mpl::pop_back<vec>::type;  //!  vector1<int>,  而不是普通的vector!
	auto r  = boost::is_same< vec2, mpl::vector<int>>::value;  // false !
	auto r2 = mpl::equal<vec2, mpl::vector<int> >::value;   // true
}

//x============================================================================================================================
struct none{};

template<typename T0 = none, typename T1 = none,typename T2 = none>
struct tiny
{
	using type = tiny;  //! ▇▇▇▇▇▇▇▇这个技巧很重要。序列一般内部的type返回自身
	using t0 = T0;
	using t1 = T1;
	using t2 = T2;
};

template<typename Tiny>
struct manipulate_tiny
{
	using t0 = typename Tiny::t0;
	using t1 = typename Tiny::t1;
	using t2 = typename Tiny::t2;

};

//! 编写其迭代器
//todo    如同mpl::v_iter
template<typename Tiny, typename Pos>
struct tiny_iter
{
	using category = mpl::random_access_iterator_tag;
};

//! next, prior support
namespace boost { namespace mpl {

template<typename Tiny,typename Pos>
struct next<tiny_iter<Tiny,Pos>>
{
	using type = tiny_iter<Tiny, typename next<Pos>::type>;
};

template<typename Tiny,typename Pos>
struct prior<tiny_iter<Tiny,Pos>>
{
	using type = tiny_iter<Tiny, typename prior<Pos>::type>;
};

} }
//! at
template<typename Tiny, int n>
struct tiny_at;

template<typename Tiny>
struct tiny_at<Tiny,0>
{
	using type = typename Tiny::t0;
};
template<typename Tiny>
struct tiny_at<Tiny,1>
{
	using type = typename Tiny::t1;
};
template<typename Tiny>
struct tiny_at<Tiny,2>
{
	using type = typename Tiny::t2;
};

struct tiny_tag{};

namespace boost { namespace mpl {
	
//x  方式一：提供at的特化
/*
template<typename T0,typename T1,typename T2,typename Pos>
struct at<tiny<T0,T1,T2>,Pos>
	: tiny_at<tiny<T0, T1, T2>, Pos::value>    // 注意，要针对tiny特化，不要影响其他类型
{ };
*/

//x  方式二：遵从mpl库中at的固有模式，从底层添加

} }


#endif

