#ifndef h_strvec
#define h_strvec
#include "prelude.h"

/*
自己实现一个vector ， （不过只能装string对象）
—— 采用动态数组来管理所存储的strings
*/
class StrVec        // 值语义  ————>  其实是指向 一块动态数组的 指针
{
public:
	// 其实是先默认初始化、再执行构造函数体
	StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
	// 三五法则
	StrVec(const StrVec& rhs)
	{
		/*
		// 先划分同样大的内存，然后把右侧对象的元素拷贝过来
		auto head = alloc.allocate(rhs.capacity());
		elements = head;
		first_free = uninitialized_copy(rhs.begin(), rhs.end(), head);
		cap = elements + rhs.capacity();
		*/
		auto newdata = this->alloc_and_copy(rhs.begin(), rhs.end());
		elements = newdata.first;
		cap = first_free = newdata.second;
	}
	StrVec& operator =(const StrVec& rhs)
	{
		/*
		// 先拷贝右侧的，再释放左侧的、再关联
		//? newvec 销毁，这块会被其释放！  所以得把 newvec 拷贝在 堆上！
		StrVec* newvec = new StrVec(rhs); // 和 StrVec newvec(rhs); 是一样的，都是拷贝构造
		free();
		elements = newvec->begin();
		first_free = newvec->end();
		cap = elements + newvec->capacity();
		return *this;
		*/
		auto data = alloc_and_copy(rhs.begin(), rhs.end());
		free();
		elements = data.first;
		cap = first_free = data.second;
		return *this;
	}

	StrVec(StrVec&& tmp_obj) noexcept
	: elements(tmp_obj.elements), first_free(tmp_obj.first_free), cap(tmp_obj.cap)
	{
		tmp_obj.elements = tmp_obj.first_free = tmp_obj.cap = nullptr;   // 临时对象要被析构的，此处避免被析构
	}

	StrVec& operator =(StrVec&& robj) noexcept
	{
		if (this == &robj) return *this;  //? dying 的obj 可能自赋值吗？可能 ：   s = move(s);   // s 是 左值对象

		free();
		elements = robj.elements;
		first_free = robj.first_free;
		cap = robj.cap;
		robj.elements = robj.first_free = robj.cap = nullptr;
		return *this;
	}

	~StrVec() { free(); }
	/*--------------------------------------------*/
	// 添加元素： 先确保容量够、再在first_free construct 一个
	void push_back(const string& s)
	{
		check_alloc();
		alloc.construct(first_free++, s);
	}


	// Reader
	size_t capacity() const { return cap - elements; }
	size_t size() const { return first_free - elements; }
	// getter
	string* begin() const { return elements; }
	string* end() const { return first_free; }

private:
	string* elements;
	string* first_free;
	string* cap;
	static allocator<string> alloc;  // 这个实体压根不属于/关联任何object， 可以看作一个全局的，像是 cout 一样的 工具实体。


	// 容器本身的改变， 就靠这4个动作
	// ——>  push元素时： check  --> 如果容量不够： 重新分配、copy， 再push
	void check_alloc() { if (first_free == cap) re_allocate(); }

	void re_allocate()       // 当容量不足时，进行重新划分内存，并把原来的元素拷贝过去
	{
		//?  引申出： 原有的那个块没必要拷贝、再释放， 应该 move "接管"
		//?     move : 将一个 lvalue-object 变成一个 rvalue-object ，从而可以匹配 T&& /const T& 、可以“被接管”
		auto new_capacity = size() ? 2 * size() : 1;
		auto newdata = alloc.allocate(new_capacity);

		/*
		//  移动过来
		auto dest = newdata;    //?  既然两块内存不是 在一块的 ？？  是怎么通过 move 避免拷贝、就能“在一块”的呢？
									//? <Primer>-P469 : 就好像这个obj实体并不在任何vec中，而vec中只是 “值语义”的obj的指针而已。---> 这样只要把指针拷贝过去就行了（如同swap)
		auto old_ele = elements;
		for( size_t i = 0; i < size(); ++i) {
			alloc.construct(dest++, std::move(*old_ele++));        //  string(string&&  r_obj)
		}  //x 什么类会需要定义move接管呢？  值语义的obj
		*/
		//? "move iterator"
		auto last = uninitialized_copy(make_move_iterator(begin()), make_move_iterator(end()), newdata);

		free();
		elements = newdata;
		first_free = last;
		cap = elements + new_capacity;
	};

	/*----------------------------------------------*/
	// 工具函数。拷贝用得！
	pair<string*,string*> alloc_and_copy(string* b,string* e)
	{
		string* new_head = alloc.allocate(e-b);
		auto new_end = uninitialized_copy(b, e, new_head);
		return { new_head, new_end };
	}

	// 清除objects， 回收内存空间
	void free()
	{
		if (!elements) return;

		for (auto pt = elements; pt != first_free; /**/ ) {
			alloc.destroy(pt++);
		}
		alloc.deallocate(elements, first_free - elements);
	}
};

#endif

