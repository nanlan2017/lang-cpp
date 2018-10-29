#ifndef h_hasptr
#define h_hasptr

#include "prelude.h"

// value-like : 拷贝指针所管理的资源
/*
不用多想指针的问题： 内部的指针完全是不可见的。
*/
class HasPtrV
{
private:
	int i;
	string* ps;
public:
	// 默认构造
	HasPtrV(const string& s = string()):i(0),ps(new string(s)){}


	// 左值拷贝： 创建、赋值
	HasPtrV(const HasPtrV& rhs): i(rhs.i),ps(new string(*rhs.ps)){}
	/*-----------------------------------------
	      // 提防：自我赋值   a = a;
	HasPtrV& operator =(const HasPtrV& rhs)
	{
		i = rhs.i;
		// 此时先要释放被赋值对象的原有资源啊！(还必须是先拷贝右侧后）  --->  赋值= 先释放左侧 + 拷贝右侧
		auto newp = new string(*rhs.ps);
		delete ps;
		ps = newp;
		return *this;
	}
	*/
	HasPtrV& operator =(HasPtrV rhs)  // 赋值 = 拷贝 + 释放原
	{
		swap(*this, rhs);
		return *this;
	}
	//----------------------------------------
	// 析构
	~HasPtrV() { delete ps; }

	//?  一个 value-like 的、通过指针持有资源的类， 可以优化本类对象的 swap  
	//?    (否则，系统的swap会 1次拷贝+ 2次赋值）——而value-like Holder会导致资源也进行拷贝。
	//? ————> 当某个类型提供了优化版本的swap时，上级类的swap要确保调用此成员的优化版swap，而不是系统默认版dumb-swap
	friend void swap(HasPtrV&, HasPtrV&) noexcept;

};

inline
void swap(HasPtrV& l, HasPtrV& r) noexcept //? noexcept? (异常安全？= 发生异常/执行中途断掉 仍能保证 状态合理）
{
	std::swap(l.ps, r.ps);
	std::swap(l.i, r.i);
}
/*****************************************************************************************************************
******************************************************************************************************************
******************************************************************************************************************
******************************************************************************************************************/
// 析构函数里不能释放资源，而最后一个user必须释放那个指针的资源。
//▇▇▇▇▇▇▇▇▇▇ 除非提供一个接口能 先执行 delete ps ;  否则无法析构！ （最后一个user 该咋释放 那个资源！）
// ————————>  ▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇ shared_ptr 的应用场景还是 “共享的资源”：  也就是 pointer-like的类里、对资源成员 使用 shared_ptr 是最好的！
class HasPtrP
{
private:
	int i;
	string* ps;
public:
	// 默认构造
	HasPtrP(const string& s = string()) :i(0), ps(new string(s)) {}

	/*
	// 左值拷贝： 创建、赋值
	HasPtrP(const HasPtrP& rhs) = default;
	HasPtrP& operator =(const HasPtrP& rhs) = default;
	// 析构
	~HasPtrP() = default;
	*/

	//?  提供给最后一个引用者 的释放接口
	void free_resoure() const { delete ps; }
};

/******************************************************************************************************************/
class RefCounter
{
public:
	unsigned cnt = 0;

	explicit RefCounter(const int i):cnt(i){}
	RefCounter& operator ++() { ++cnt;  return *this; }
};

class HasPtrCt
{
	// 自动关联一个 计数器、记录该object的资源对象 的关联数
private:
	int i;
	string* ps;
	RefCounter* pcounter;   // 和 ps 资源的 引用者个数 对应
public:
	// 默认构造
	HasPtrCt(const string& s = string())
		:i(0)
		,ps(new string(s))
		,pcounter(new RefCounter(1)){}
	// 
	HasPtrCt(const HasPtrCt& rhs)
		:i(rhs.i)
		,ps(rhs.ps)
		,pcounter(rhs.pcounter)
	{ ++(*pcounter); }

	HasPtrCt& operator =(const HasPtrCt& rhs)
	{
		i = rhs.i;

		// 现加右边资源的引用数 、 再减左边资源的引用数 + update 左边资源
		++(*rhs.pcounter);
		pcounter->cnt -= 1;
		if (pcounter->cnt == 0) {
			delete pcounter;
			delete ps;
		}

		ps = rhs.ps;
		pcounter = rhs.pcounter;
		return *this;
	}

	~HasPtrCt()
	{
		// 只当自己是最后一个User时，释放
		if (pcounter->cnt == 1) {
			delete pcounter;
			delete ps;
		}		
	}
};

#endif

