#include "_Exer_chap2.h"
#include "ch3_dimension.h"
#include "_Exer_chap3.h"
#include "ch8_dignostics.h"    //x 必须include进来/在main中能运行到才会编译
#include "ch9_foreach.h"
#include "ch10_expression_template.h"
#include "ch11_dsl_radio.h"

//x---------------------------------------------------------------------------------------
using typevec = mpl::vector<int, long, char*>;
using typevec_ref = mpl::vector<int, long, char*, int&>;  // 含有引用类型，无法被“值初始化”

void test_foreach()
{
	
	//  函数模板不就是天生的 跨越编译期、运行期的嘛！
	//mpl::for_each<typevec>(print_type());
	//mpl::for_each<typevec_ref>(print_type());  报错，

	mpl::for_each<typevec_ref, wrap<mpl::_1>>(print_type());    //x 调用一个运行期函数，当然要用值调用（而不是凭个类型）， 所以for_each会将该类型进行“默认初始化”

	// visitor模式
	mpl::for_each<typevec_ref, print_visitor<_>>(visit_type());
	//mpl::for_each<typevec_ref, print_visitor<_>>(f_visit_type);

}

void main99()
{
	ch10::test_exp_template();

	system("pause");
	
}

