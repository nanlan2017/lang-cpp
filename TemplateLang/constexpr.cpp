#include "prelude.h"

const int get_const() { return 1; }   //! 运行期常量
constexpr int get_const_expr() { return 1; }  //! constexpr : 编译器常量
#define GET_CONST 1

void showerr(const int cond)
{
	//! array dimension
	//int iarr[get_const()] = { 4 };  //--> 编译器必须确定类型，维数必须是编译器常量
	int iarr2[get_const_expr()] = { 4 };
	int iarr3[GET_CONST] = { 4 };

	//! enumerator
	//enum { e1 = get_const() };
	enum { e2 = get_const_expr()};

	//! case-value
	switch (cond) {
		//case get_const():
		case get_const_expr(): break;
		default: break;
	}
}

constexpr int fc(int x)
{
	static_assert(0 == 0, "assert fail");
	return x;
}

//x----------------------------------------- 
struct MySt
{
	constexpr  MySt(int x):i(x){}
	int i;
};

constexpr MySt mt = { 0 };

//x----------------------------------------- 
constexpr int foo(int i)
{
    return i + 5;
}

void main_constexpr()
{
    int i = 10;

	int ia[foo(5)];
    
    foo(i); // Call is Ok
    
    // But...
    //int ia2[foo(i)]; // Error
   
}

