#include "prelude.h"

void main_()
{
	const char *v[] = { "This", "is", "an", "example" };

	auto sz = std::size(v);

	if (void *pbuf = std::aligned_alloc(alignof(std::string), sizeof(std::string) * sz)) {
		try {
			auto first = static_cast<std::string*>(pbuf);
			auto last = std::uninitialized_copy(std::begin(v), std::end(v), first);

			for (auto it = first; it != last; ++it)
				std::cout << *it << '_';

			//allocator<string>::destroy(first);
		} catch (...) {}
		std::free(pbuf);
	}
}