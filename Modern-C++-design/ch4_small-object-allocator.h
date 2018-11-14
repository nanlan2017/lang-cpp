#ifndef h_ch4_small
#define h_ch4_small

#include "prelude.h"

using namespace std;

// block_size 统一由上层管理。 其实对一个chunk来说 是一个固定值。 为了节省chunk空间，不存放block_size

//  |---b1---|---b2---|---b3---|---b4---|---b5---|---b6---|---...
//  { size   }  以char(1 byte)计
struct Chunk
{
	// chunk大块本身
	void init(size_t block_size, unsigned char blocks_amount)      
	{                                                              // chunk中block的数量限制在 char= 255个以内
		pData = new unsigned char[block_size * blocks_amount];
		firstAvailableBlock = 0;  // 索引
		blocksAvailable = blocks_amount;

		// 在每个尚未使用区块的第一格 存放 下一个尚未使用区块的区块index
		unsigned char i = 1, *p = pData;
		for (; i != blocks_amount; p += block_size) {
			*p = ++i;
		}
	}
	void release();

	// 使用一个区块
	void* allocate(size_t block_size)     
	{
		if (!blocksAvailable) return nullptr;
		unsigned char* pResult = pData + (firstAvailableBlock * block_size);  // 定位到第一个可用的block
		// 更新chunk状态
		firstAvailableBlock = *pResult;
		--blocksAvailable;
		//
		return pResult;
	}
	void de_allocate(void* p, size_t block_size)
	{
		assert(p >= pData);
		unsigned char* to_release = static_cast<unsigned char*>(p);   // to_release指向即将被释放的那个block
		*to_release = firstAvailableBlock;
		assert((to_release - pData) % block_size == 0);
		*to_release = firstAvailableBlock;
		firstAvailableBlock = static_cast<unsigned char>((to_release - pData) / block_size);
		assert(firstAvailableBlock == (to_release - pData) / block_size);
		++blocksAvailable;
	}

	unsigned char* pData;                   // 指向被管理的内存本身
	unsigned char firstAvailableBlock;      // 第一个可用block的索引
	unsigned char blocksAvailable;
};

class FixedAllocator
{
	
private:
	using Chunks = vector<Chunk>;

	size_t        block_size;
	unsigned char num_blocks;
	Chunks        chunks;

	Chunks* alloc_chunk;
	Chunks* de_alloc_chunk;
};

class SmallObjAllocator
{
	
};

class SmallObj
{
public:
	static void* operator new(size_t size);
	static void operator delete(void* p ,size_t size);
	virtual ~SmallObj() = default;

};

#endif

