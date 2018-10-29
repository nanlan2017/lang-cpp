#include "prelude.h"
#include <tuple>
#include <list>
#include <boost/type.hpp>

void use_case()
{
	using TupType1 = tuple<string, vector<double>, int, list<int>>;
	tuple<string, vector<double>, int, list<int>> tup1{ "constants", {3.14,2.4}, 5, {2,3} };

	//? tuple_size (size)
	cout << tuple_size<TupType1>::value;   // Ä£°åÍÆ¶Ï£º4
	//? tuple_element (type)
	using SecondElemType = tuple_element<1, TupType1>::type;
	//? get<index>(tuple)
	auto elem_2nd = get<1>(tup1);
	//? make_tuple
	auto tup2 = make_tuple(3, 20.3, "fuck it");
}
