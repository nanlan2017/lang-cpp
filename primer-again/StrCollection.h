#ifndef h_strcollection
#define h_strcollection

#include "prelude.h"
#include <memory>

class StrBlobPtr;
class StrBlob
{
public:
	friend class StrBlobPtr;

	using size_type = vector<string>::size_type;

	StrBlob() { data = make_shared<vector<string>>(); }
	StrBlob(initializer_list<string> il) { data = make_shared<vector<string>>(il); }

	// const 
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	// 
	void push_back(const string& str) { data->push_back(str); }
	void pop_back() { data->pop_back(); }
	// 
	//string& front() { return data->front(); }
	//? todo  返回类型从语义考虑，该不该加const呢？
	string& front() const { return data->front(); }  // 这里并不是返回 *this啊， 所以返回引用不要求 const T&
	//string& back() { return data->back(); }
	string& back() const { return data->back(); }

	StrBlobPtr begin();
	StrBlobPtr end();
private:
	shared_ptr<vector<string>> data;
	void check(size_type index, const string& msg) const;
};

inline void StrBlob::check(const size_type index, const string& msg) const
{
	if (index >= data->size() ) {
		throw out_of_range(msg);
	}
}

class StrBlobPtr
{
public:
	StrBlobPtr(): curr(0){}
	StrBlobPtr(/*const*/ StrBlob& blob, size_t sz=0): wptr(blob.data), curr(sz) {}

	string& operator *() const  // vector整体的const 性和 其中的item的const性 是分离的吗？
	{
		// 通过 weak_ptr去访问关联的对象（无法使用 *解引用）
		// 先check一下是否expired， 再通过lock()获得 shared_ptr 去访问
		auto sp = check(curr);
		return (*sp)[curr];
	}

	// 返回一个新的 x 
	StrBlobPtr& operator ++()
	{
		curr++;
		return *this;
	}


private:
	// 并没有关联StrBlob啊，而是关联 vector<string>
	weak_ptr<vector<string>> wptr;
	std::size_t curr;  // string/vector是size_type , 内置数组是 size_t

	shared_ptr<vector<string>> check(size_t index) const
	{
		auto ret = wptr.lock();  // 若未expired，则返回一个shared_ptr， 否则返回 empty的shared_ptr (会转换为false)
		if(!ret) throw runtime_error("already expired");
		if (index >= ret->size()) throw out_of_range("not that many!");
		return ret;
	}
};

inline StrBlobPtr StrBlob::begin()
{
	return StrBlobPtr(*this);
}

inline StrBlobPtr StrBlob::end()
{
	return StrBlobPtr(*this, data->size());
}




#endif

