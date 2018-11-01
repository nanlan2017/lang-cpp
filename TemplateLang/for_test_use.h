#ifndef h_fortest
#define h_fortest

//#include "prelude.h"
#define static_const static const
template<int n>
struct is_zero
{
	static_const bool val = false;
};

template<>
struct is_zero<0>
{
	static_const bool val = true;
};

//x=======================================================
template<int n>
struct is_one
{
	static_const bool val = false;
};

template<>
struct is_one<1>
{
	static_const bool val = true;
};
#endif

