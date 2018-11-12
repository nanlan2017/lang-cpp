#include "prelude.h"
#include "prelude_boost.h"

struct NonTrival1
{
	NonTrival1();
	int i;
};
NonTrival1::NonTrival1() = default;


struct Trival1
{
	Trival1() = default;
	int i;
};



void test_is_trival()
{
	//std::is_trivial_v<int>;

	//! trival    class/struct
	// 一句话： trival class 意味着该类保有所有的default成员，且没有virtual 
	auto r1 = std::is_trivial<Trival1>::value;     // true
	auto r2 = std::is_trivial<NonTrival1>::value;  // false
	//! standard-layout    class/struct
	auto r3 = std::is_standard_layout<Trival1>::value;     // true
	auto r4 = std::is_standard_layout<NonTrival1>::value;  // true

	//! pod (plain old data)
	auto r5 = std::is_pod<Trival1>::value;     // true
	auto r6 = std::is_pod<NonTrival1>::value;  // false

}

