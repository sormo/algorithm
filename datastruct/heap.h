#pragma once

#include <limits>
#include <functional>
#include <vector>
#include "..\common\common.h"

// by default mininum element is at root
template <class T, class Compare = std::less<typename T>>
class Heap
{
public:
	void Push(const T & value)
	{
		m_array.push_back(value);
		// restore heap invariant
		BubbleUp(m_array.size() - 1);
	}

	bool Pop(T & value)
	{
		if (m_array.empty())
			return false;
		value = m_array[0];
		
		Swap(0, m_array.size()-1);
		m_array.pop_back();

		BubbleDown(0);

		return true;
	}

	const T & Root() 
	{ 
		return m_array[0]; 
	}
	bool Empty()
	{
		return m_array.empty();
	}
	size_t Size() 
	{ 
		return m_array.size(); 
	}
	// TODO check
	void Remove(const T & value)
	{
		for (size_t i = 0; i < m_array.size(); ++i)
		{
			if (m_array.at(i).second == value)
			{
				Swap(i, m_array.size() - 1);

				m_array.pop_back();

				// check, always bubble down ???
				BubbldeDown(i);

				break;
			}
		}
	}

private:

	// --- access virtual tree ---

	size_t Parent(size_t i)
	{
		if ( i == 0 )
			return INVALID_SIZE_T;

		if ( i % 2 == 0 ) // even
			return i/2 - 1;

		return i/2; // odd
	}
	size_t LChild(size_t i)
	{
		i++;
		return 2*i - 1 < m_array.size() ? 2*i - 1 : INVALID_SIZE_T;
	}
	size_t RChild(size_t i)
	{
		i++;
		return 2*i < m_array.size() ? 2*i : INVALID_SIZE_T;
	}

	// ---

	// --- bubble up ---
	void BubbleUp(size_t index)
	{
		size_t parentIndex = Parent(index);
		if (parentIndex == INVALID_SIZE_T)
			return;

		if (IsSmaller(parentIndex, index))
			return;

		Swap(index, parentIndex);
		BubbleUp(parentIndex);
	}

	// --- bubble down ---
	void BubbleDown(size_t index)
	{
		size_t lChildIndex = LChild(index);
		size_t rChildIndex = RChild(index);

		if ((lChildIndex != INVALID_SIZE_T && IsSmaller(lChildIndex, index))||
			(rChildIndex != INVALID_SIZE_T && IsSmaller(rChildIndex, index)))
		{
			size_t swapIndex = GetSwapIndex(lChildIndex, rChildIndex);
			Swap(swapIndex, index);
			BubbleDown(swapIndex);
		}
	}

	size_t GetSwapIndex(size_t a, size_t b)
	{
		if (a == INVALID_SIZE_T)
			return b;
		else if (b == INVALID_SIZE_T)
			return a;

		if (IsSmaller(a, b))
			return a;
		return b;
	}

	void Swap(size_t a, size_t b)
	{
		auto tmp = m_array[a];
		m_array[a] = m_array[b];
		m_array[b] = tmp;
	}

	bool IsSmaller(size_t l, size_t r)
	{
		return m_comparisonFunction(m_array[l], m_array[r]);
	}

protected:

	std::vector<T> m_array;
	Compare m_comparisonFunction;
};
