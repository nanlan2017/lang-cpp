#include "prelude.h"


/* --------------------------------------------------------------------------------------------------
基于策略(Policy)的类设计是将templates和多重继承组合起来，这样可以产生程序库中的“设计元素”。
Policies由templates和多重继承组成。
一个class如果使用了policies,就称其为host class,那是一个拥有多个template参数的class template,每一个参数代表一个policy.
host class所有的机能都来自policies,运作起来就像是一个聚合了数个policies的容器。
----------------------------------------------------------------------------------------------------*/
template <
	class RunPolicy,
	class FlyPolicy
>
class Bird : public RunPolicy, public FlyPolicy       
{
};

/*
class BirdOO : public IRunnable, public IFlyable
{
};
*/

struct Dog
{
	int age = 0;
	std::string name;
};

//!   一个Policy概念就是一个接口（util业务能力),  这个接口的实现都是policy class
/*
定义一个ploicy 用来产生对象,
Creator policy是一个带有型别为T的class template,它必须提供一个名为Create()的函数给外界使用，
此函数不接受参数，返回一个指向T的指针。
下面是三种产生对象的方法即policy
*/
//TODO     为 Creator Policy 制作3个 Policy Class
//Policy 1:  new T
template<class T>
struct OpNewCreator
{
	static T * Create()
	{
		return new T;
	}
};

//Policy 2:  malloc -> placement new
template<class T>
struct MallocCreator
{
	static T * Create()
	{
		void* buf = std::malloc(sizeof(T));
		if (!buf)  return 0;
		return new(buf) T;
	}
};

//Policy 3:  
template<class T>
struct PrototypeCreator
{
	PrototypeCreator(T* pObj = nullptr)
		:pPrototype_(pObj){}

	T * Create(){return pPrototype_ ? pPrototype_->Clone() : 0;}

	T *GetPrototype() { return pPrototype_; }
	void setPrototype(T* pObj) { pPrototype_ = pObj; }

private:
	T * pPrototype_;
};

//test_creator
void main()
{
	Dog* dog1 = OpNewCreator<Dog>::Create();
	Dog* dog2 = MallocCreator<Dog>::Create();
	Dog* dog3 = PrototypeCreator<Dog>(dog2).Create();
}


//TODO    通过继承/组合, 你可以让 类型A 拥有类型B 的业务能力（比如CreateT）。  但这种能力的赋予是一次性的
//TODO    如果 CreateT这种能力 的提供实现由多种： B1, B2, B3,    
//TODO                     ▇▇▇▇▇▇▇▇▇▇▇▇[如果你想在一个依赖Creator Component 的类中替换其 Creator种类， 该怎么办]
//TODO                     那么你 可能需要  分别定义 A1, A2, A3  来继承他们，才能复合出想要的类型。
//TODO        ▇▇▇▇▇▇▇▇【将其所要继承（关联）的类型 参数化 (作为模板的类型参数) (自身类型模板化)】  ---------> 可以使得这种组装方便的多， 且 A<B1>, A<B2>, A<B3> 即可！
//TODO        一句话： 通过类型的参数化，将类型的关联“解耦”
/*
如果一个类采用了一个或多个policy class,就称其为host或host classes.上面定义的WidgetManager采用了一个policy,称其为host class.Hosts主要负责把上面定义的policies的结构和行为组成一个风复杂的结构和行为。
*/
struct Widget
{ };

struct Gadget
{};

template<class CreationPolicy>
class WidgetManager:public CreationPolicy
{
public:
	using CreationPolicy = CreationPolicy;
};


template<template<class> class CreationPolicy>
class WidgetMan:public CreationPolicy<Widget>   // 反正已知WidgetMan总是创建Widget实例
{
public:
	using CreationPolicy = CreationPolicy<Widget>;
};



void test_host()
{
	// 组合1 ： 该类型 具备 Widget类型的 new create 能力
	using MyWidgetPtr = WidgetManager<OpNewCreator<Widget>> ;
	auto* w = MyWidgetPtr::CreationPolicy::Create();

	// 组合2 ： 
	using MyWidgetPtr2 = WidgetManager<MallocCreator<Widget>> ;
	auto* w2 = MyWidgetPtr2::CreationPolicy::Create();


	using MyWigetMan = WidgetMan<OpNewCreator>;
	auto* w3 = MyWigetMan::CreationPolicy::Create();
}

//x===========================================================================================================

//!  若policy class本身不是模板， 则host将其作为typename即可
//!  若policy class本身就是模板类型， 则host需要将其作为 template template
template<template<class> class CreationPolicy = OpNewCreator>
class WidgetManager :public CreationPolicy<Widget>
{
	void DoSomething()
	{
		Gadget *pW = CreationPolicy<Gadget>::Create();
	}

	void SwitchPrototype(Widget *pNewPrototype)
	{
		CreationPolicy<Widget> &myPolicy = *this;
		delete myPolicy.GetPrototype();
		myPolicy.SetPrototype(pNewPrototype);
	}

};