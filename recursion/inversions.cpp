#pragma once
#include <vector>
#include <queue>

unsigned int CountNumberOfInversionsSplit(std::vector<unsigned int> & arr, size_t i, size_t m, size_t j)
{
	unsigned int ret = 0;
	size_t xi = 0; // left part
	size_t xj = m - i; // right part

	// TODO this can be done in-place, or at least copy only sub-array that is needed (:
	std::vector<unsigned int> copy(arr.begin() + i, arr.begin() + j);
	for (size_t k = i; k < j; k++)
	{
		if (copy[xj] < copy[xi])
		{
			arr[k] = copy[xj];
			xj++;
			ret += m - xi - i; // number of numbers left in left part
		}
		else
		{
			arr[k] = copy[xi];
			xi++;
		}

		// end cases
		if (xi + i == m)
		{
			break;
		}
		if (xj + i == j)
		{
			//ret += (m - xi)*(j - m); // those left in the left part are inversions with all in the right part
			//ret += (m - xi);
			for (size_t l = k + 1; l < j; l++)
				arr[l] = copy[xi++];
			break;
		}
	}

	return ret;
}

// i - inclusive, j - exclusive
unsigned int CountNumberOfInversionsRecursive(std::vector<unsigned int> & arr, size_t i, size_t j)
{
	// base case
	if ((j - i) == 1)
		return 0;

	size_t m = (j - i) / 2 + i;
	unsigned int a = CountNumberOfInversionsRecursive(arr, i, m);
	unsigned int b = CountNumberOfInversionsRecursive(arr, m, j);
	unsigned int c = CountNumberOfInversionsSplit(arr, i, m, j);

	return a + b + c;
}

unsigned int CountNumberOfInversions(const std::vector<unsigned int> & arr)
{
	// make copy of array, it will be sorted
	std::vector<unsigned int> copy = arr;
	return CountNumberOfInversionsRecursive(copy, 0, arr.size());
}