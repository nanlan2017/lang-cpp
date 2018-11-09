#ifndef h_ch8_dignostics
#define h_ch8_dignostics

#include "prelude.h"
#include "prelude_boost.h"


namespace ch8 {
using namespace mpl;
struct nil{};

template<typename _head, typename _tail = nil>
struct node
{
	using head = _head;
	using tail = _tail;
};

template<typename list>
struct total_size
{
private:
	using tail_size = typename total_size<typename list::tail>::type;
public:
	using type = int_<(sizeof_<typename list::head>::value + tail_size::value)>;
};

template<>
struct total_size<nil>
{
	using type = int_<0>;
};

using sz1 = sizeof_<bool>::type;
using sz2 = sizeof_<char>::type;
using sz3 = sizeof_<short>::type;
using sz4 = sizeof_<int>::type;
using sz5 = sizeof_<long>::type;
using sz6 = sizeof_<float>::type;
using sz7 = sizeof_<double>::type;


using r = total_size<node<long, node<int, node<char>>>>::type;
}

namespace ch8_dignostics {
	
using namespace std;

inline void copy_list_map(std::list<string> &l, std::map<string,string>& m)
{
	//std::copy(l.begin(), l.end(), std::back_inserter(m));
}
}

#endif
