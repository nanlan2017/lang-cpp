#include "prelude.h"

//! 0.  "type" has members, which can be type/int.    so , type 

//!  1. data struct 
// data Dog = Dog String Int
//todo       1.   ...F< People<age,Dog> ...   来模式匹配解析其值
//todo       2.   people::age,  typename people::Dog  来获取其内部成员值
template<int _age,typename _Dog>
struct People
{
	enum { age =  _age };
	using Dog = _Dog;
};


//!  2. function
template<int x, typename Dog>
struct Calc
{
	enum { val = x + Dog::age };             //todo   利用的都是 <模板参数>,   1. 如果是直接作为 成员数据， 就是 data struct   (也可用参数模式匹配 来解析成员值)
											 //todo                          2. 如果是利用它们计算出一个值， 就是 function
											 //todo                          3. 既有直接封装的，又带有计算， 则是 closure/ 函数对象
};

//!  3. closure  ,  function object
template<int _limit>
struct Judger
{
	enum { limit = _limit };

	template<int x>
	struct code
	{
		static const bool val = x < limit;
	};
};