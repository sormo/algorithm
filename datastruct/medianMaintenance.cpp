#include "datastruct.h"
#include <cassert>
#include <vector>
#include "heap.h"

template <class T>
std::vector<T> MedianMaintenance(const std::vector<T> & data )
{
	Heap<T, std::greater<T>> lowHeap;
	Heap<T, std::less<T>> highHeap;
	std::vector<T> ret;

	// iterate over data stream
	for (auto v : data)
	{
		if (!lowHeap.Empty() && lowHeap.Root() >= v)
		{
			lowHeap.Push(v);
		}
		else if (!highHeap.Empty() && highHeap.Root() <= v)
		{
			highHeap.Push(v);
		}
		else
		{
			if (lowHeap.Empty() && highHeap.Empty())
			{
				lowHeap.Push(v);
			}
			else if (lowHeap.Empty() && highHeap.Root() >= v)
			{
				lowHeap.Push(v);
			}
			else if (highHeap.Empty() && lowHeap.Root() <= v)
			{
				highHeap.Push(v);
			}
			else
			{
				lowHeap.Empty() ? highHeap.Push(v) : lowHeap.Push(v);
			}
		}

		size_t sizeDiff = abs((int)highHeap.Size() - (int)lowHeap.Size());
		size_t sizeSum = highHeap.Size() + lowHeap.Size();

		if (sizeDiff >= 2 ||
				(sizeSum % 2 == 0 && sizeDiff >= 1) ||
				highHeap.Size() > lowHeap.Size() )
		{
			T tmp;

			if (highHeap.Size() > lowHeap.Size())
			{
				assert(highHeap.Pop(tmp));
				lowHeap.Push(tmp);
			}
			else
			{
				assert(lowHeap.Pop(tmp));
				highHeap.Push(tmp);
			}
		}

		ret.push_back(lowHeap.Root());
	}

	return ret;
}
