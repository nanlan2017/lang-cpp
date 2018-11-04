#ifndef h_haskellutils
#define h_haskellutils
#include "prelude.h"

//todo   将两个内部含有 exec() 成员的类型数据，串联成一个类型
template<typename T1,typename ...Args>
struct Sequence
{
	static void exec()
	{
		T1::exec();
		Sequence<Args...>::exec();
		// E1::exec();    E2::exec();   ....      如何展开成这样 ？？？
		//Args::exec();
	}

	//? env
	template <typename Env>
	static void exec_env(Env&& env)
	{
		T1::exec_env(forward<Env>(env));
		Sequence<Args...>::exec_env(forward<Env>(env));
	}
};

template<typename T>
struct Sequence<T>
{
	static void exec()
	{
		T::exec();
	}

	//? env
	template <typename Env>
	static void exec_env(Env&& env)
	{
		T::exec_env(forward<Env>(env));
	}
};
//x------------------------------------------------------------------------------------

#endif
