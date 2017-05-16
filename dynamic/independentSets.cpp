#include "dynamic.h"
#include <vector>
#include <algorithm>

std::vector<DNUM> Reconstruct(const std::vector<DNUM> & A)
{
	std::vector<DNUM> ret;

	for (int i = A.size() - 1; i > 1; i--)
	{
		if (A[i] != A[i - 1])
		{
			ret.insert(ret.begin(), A[i] - A[i - 2]);
			i--;
		}
	}

	// this means that first one was kept
	if (A[1] == A[2])
		ret.insert(ret.begin(), A[1]);

	return ret;
}

std::vector<DNUM> IndependentSets(const std::vector<DNUM> & seq)
{
	std::vector<DNUM> A(seq.size() + 1, 0);

	A[0] = 0;
	A[1] = seq[0];

	for (size_t i = 2; i <= seq.size(); i++)
		A[i] = std::max(A[i-1], A[i-2] + seq[i-1]);

	return Reconstruct(A);
}
