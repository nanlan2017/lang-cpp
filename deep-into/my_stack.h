#ifndef h_mystack
#define h_mystack
#include <stdexcept>
#include "prelude.h"
//? 借助链表实现的栈结构
template<typename T>
struct MyStack;

template<typename T = int>
struct Node   //? 定义每一个类型时，都要仔细考虑它的实现：值语义？引用语义？是否提供移动？有哪些构造方式？测试用例？？
{
private:
	T val;
	Node* next = nullptr;
public:
	//! constructors
	/*
	Node(4); Node("li");
	Node(4,nod);
	*/
	//explicit Node(const T& val):val(val){}
private:
	//! ▇▇▇▇▇如果按值传递，意味着你方法见到这个对象时，就是已经拷贝得到的；
	//!     按引用传递，则可以接受这个对象后，再在函数内部决定是否拷贝
	//! ▇▇▇▇▇▇▇▇▇▇▇▇ 拷贝这种行为, 取决于这个函数 在语义上到底需不需要 拷贝/直接操作 作为参数的这个对象。
	Node(const T& val, Node* next_node):val(val),next(next_node){}   // 用指针，就可以传nullptr了！  
																	 //! shared_ptr 只用于资源性质的东西！（总是作为成员，不可能作为参数传递）
	//! self-base
	//基于另一个object被创建、用另一个object赋值
	//todo   [C#|Java 将是C++的最佳实践]
	//todo  在Java中，一个object instance 只会被创建、按引用传递。         
	//todo   ——>  1. obj1 = obj2；           就是让obj1也引用obj2的对象   
	//todo   ——>  2. T obj1 = new T(obj2);   ！一般没有这种构造函数！
	//todo   ——>  3. intance的拷贝靠显式调用clone();
	//todo   ——>  4. 所有object都建立在堆上，并且自动GC，不存在临时对象、悬挂指针等问题。
	Node(const Node& node) = default;  //! 拷贝创建 （既然是拷贝，当然不在乎提供的原本是rvalue/ lvalue了。 所以用const T&）
	//! const

	//! modifiers

	//! others
	friend MyStack<T>;  //todo private构造+friend : 相当于内部类了（只有friend class可以使用它)
};

template<typename T = int>
struct MyStack
{
public:
	using NodeType = Node<T>;

	//! constructors
	MyStack() = default;                   //? 默认构造 MyStack() 时,stack里应当没有任何node!  (那么head显然就不能用T形式！）
	MyStack(const T& val):head(new NodeType(val)){}
	MyStack(const NodeType& node):head(new NodeType(node)){}
	//! semantics
	// 该对象不可以复制、也不可以赋值
	MyStack(const MyStack& obj) = delete;
	MyStack operator=(const MyStack& obj) = delete;
	~MyStack()
	{
		while (!empty()) {
			pop();
		}
	}
	//! const
	bool empty() const { return head == nullptr; }
	const T& top() const noexcept(false)
	{
		if (empty()) throw std::runtime_error("no node to get top");
		else return head->val;
	}
	//! modifier
	void push(const T& v)  //! push：那必然是要拷贝的（但只要拷贝一次），毕竟我stack是值语义的。
	{
		head = new NodeType(v, head);
	}

	void pop();
	//! other

private:
	NodeType* head = nullptr;
};
template <typename T>
void MyStack<T>::pop()
{
	if (head) {
		NodeType* tmp = head;
		head = head->next;
		delete tmp;
	} else {
		throw new std::runtime_error("no elements to pop");
	}
}

template<typename T>
class CountStack:MyStack<T>
{
	using Base = MyStack<T>;
private:
	unsigned size;
public:
	//!cons
	CountStack():Base(),size(0){}
	//!const
	unsigned get_size() const
	{
		return size;
	}
	//!modifiers
	void push(const T& val)
	{
		Base::push(val);
		++size;
	}
	void pop()
	{
		if (size >0) {
			Base::pop();
			--size;
		}
	}
};

template<typename TV, typename TN>
struct SNode
{
	TV val;
	TN* next;
	//!cons
	SNode(const TV& v,TN* next):val(v),next(next){}
};

inline
void test_snode()
{
	// 构造  3 -> 'c' -> "love"
	//      no3   no2      no1
	auto no1 = SNode<string, void>("love", nullptr);
	auto no2 = SNode<char, decltype(no1)>('c', &no1);
	auto no3 = SNode<int, decltype(no2)>(3, &no2);
}



#endif



