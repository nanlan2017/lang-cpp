#ifndef h_code_Generate
#define h_code_Generate

#include "prelude.h"
#include "10-5_Factorial.h"
#include "haskell_utils.h"

//x==================================================================================================
namespace book {
//todo 将代码中出现的 pow<3>(x) 展开为 x*x*x    -----> 优化了函数调用的开销
template<int n>
//inline 
int power(const int& x){ return x * power<n - 1>(x);}
template<>
inline int power<1>(const int& x) { return x; }
template<>
inline int power<0>(const int& x) { return 1; }

inline void test_mypower()
{
	// 2^5
	auto r = power<5>(2);   //----> inline的： 等价于在写  auto r = 2*2*2*2*2;
}
//x=========================================== edo ==================================================
/*
int i = 1;
ewhile 	(i<10) 
	statement(i);        // statement ::  print(i);
	i++;

===>
	print(1);
	print(2);
	....
	print(9);
*/


/*   //todo    Common Lisp
(defmacro ewhile (	
*/
//x=========================================== ewhile ===============================================
//todo 每次递归都是 statement(i), 并判断性进入下一次递归
template <int i = 1>
struct Print_Body
{
	enum { i = i };
	static void exec() { cout << i << endl; }       //! body: 封装了body数据
	using Next = Print_Body<i + 1>;
};

template<int n>
struct Print_Cond
{
	template<typename Body>
	struct judge
	{
		static const bool  val = Body::i < n;        //! condition
	};
};
//x======================================================================================================

/*
//todo   data Body = Body Int Statement Body
Ewhile 	:: (Body->bool) -> Body -> ..
Ewhile conder (Body i stats nextbody) = if (conder i) then Ewhile conder nextbody else ..
*/

struct Stop { static void exec() { cout << "stopped..." << endl; } };       //!  ▇▇▇▇这个 Stop 值的设计 很重要。 

template <typename Conder
		,typename Body>
struct Ewhile
{
private:
	static const bool flag = Conder::template judge<Body>::val;
public:
	static void exec()  //! 代码生成是通过inline内联函数体来实现的！
	{
		/*
		if (flag) {
			body::exec();
			Ewhile<cond,nextbody>;
		} else {
			stop::exec();
		}
		*/
		//IF<flag, Body, Stop>::Ret::exec();        // 先判断执行本次递归体
		//IF<flag, Ewhile<Conder, typename Body::Next>, Stop>::Ret::exec();  // 送入下一次递归
		IF < flag
			, Sequence<Body, Ewhile<Conder, typename Body::Next>>
			, Stop>::Ret::exec();
	}

	template<typename Env>
	static void exec_env(Env&& env)
	{
		IF < flag
			, Sequence<Body, Ewhile<Conder, typename Body::Next>>
			, Stop>::Ret::exec(forward<Env>(env));
	}
};

inline void test_ewhile()
{
	Ewhile< Print_Cond<10>, Print_Body<>>::exec();
}
//x=========================================== efor =================================================

}
#endif
