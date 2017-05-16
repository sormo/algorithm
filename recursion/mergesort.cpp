#include "recursion.h"

#include <vector>
#include <cassert>

template <class T>
void Merge(std::vector<T> & data, const std::vector<T> & t1, const std::vector<T> & t2)
{
	size_t i1 = 0;
	size_t i2 = 0;

	data.clear();

	while(i1 < t1.size() || i2 < t2.size())
	{
		if (i1 == t1.size())
		{
			data.push_back(t2[i2++]);
		}
		else if (i2 == t2.size())
		{
			data.push_back(t1[i1++]);
		}
		else
		{
			if (t1[i1] < t2[i2])
			{
				data.push_back(t1[i1++]);
			}
			else
			{
				data.push_back(t2[i2++]);
			}
		}
	}
}

template <class T>
void Mergesort(std::vector<T> & data)
{
	if (data.size() <= 1)
		return;

	std::vector<T> d1(data.begin(), data.begin() + data.size()/2);
	std::vector<T> d2(data.begin() + data.size()/2, data.end());
	Mergesort<T>(d1);
	Mergesort<T>(d2);
	Merge(data, d1, d2);
}
