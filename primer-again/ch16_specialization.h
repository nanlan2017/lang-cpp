#ifndef h_spec
#define h_spec

#include "prelude.h"
#include "Sales_item.h"
namespace std {
	template<>   //?  template<> 说明这是某个模板的完全特化版本： T === Sales_data
	struct hash<Sales_data>
	{
		using result_type = size_t;
		using argument_type = Sales_data;

		// 对于Sale_data的每一个对象， 调用此函数对象  计算出一个唯一的hash值
		size_t operator()(const Sales_data& s) const
		{
			return hash<string>()(s.bookNo) ^ hash<unsigned>()(s.units_sold) ^ hash<double>()(s.revenue);
		}
	};
}

inline void use_hash()
{
	
}
//?  只有类模板存在 “部分特例化“ （偏特化），    函数模板只能完全特化！！

#endif

