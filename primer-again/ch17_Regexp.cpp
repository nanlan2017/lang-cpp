#include "prelude.h"
#include <regex>

void test_reg()
{
	// i 除非在c之后，否则必须在c之前
	string pattern("[^c]ei");
	pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
	regex reg(pattern);  //? 创建一个regex对象

	string test_str = "receipt friend theif receive";

	smatch results; //? 用于保存match的结果

	if (regex_search(test_str, results, reg))
		cout << results.str() << endl;



}