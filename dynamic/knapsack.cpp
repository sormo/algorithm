#include "dynamic.h"
#include <vector>
#include <string>
#include <fstream>
#include <cassert>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iomanip>

// knapsack problem
// compute maximal sum of values of knapelems, which's sum of weights are lesser than W
// compute subset of array of knapelems, which's sum of weights is lesser than W and sum of values is maximal
//
// structure of optimal solution:
// on input we have array of knapelems D in arbitrary order
// in a case there is optimal knapsack subset S with sum of values V
//    S may (1) or may not (2) include knapelem at index i D[i]
//    S' is subset of S such that S' = S - { D[i] }
//        (1) V' = V - D[i].value
//            W' = W - D[i].weight
//            S' = S - { D[i] }
//        (2) V' = V
//            W' = W
//            S' = S
//
// set of solutions
//
// algorithm
// 2d array A[i,j] where
// i = 0 ... D.size A[i, ] knapelems included in solution
// j = 0 ... W weight included up to A[ ,j]
//
// when filling in element of A at indices i,j
// take maximum value max( A[i-1,j-wi] + vi , A[i-1,j] ) ; wi = D[i].weight ; vi = D[i].value
//                            (1)                (2)

std::vector<knapelem> ReadKnapsackInput(const std::string & file)
{
	std::ifstream f(file);
	assert(f.is_open());

	std::vector<knapelem> ret;
	std::string line;

	while(std::getline(f, line))
	{
		std::stringstream ss(line);
		DNUM value;
		DNUM weight;

		ss >> value;
		ss >> weight;

		ret.push_back({value, weight});
	}

	return ret;
}

void PrintKnapsackTable(const std::vector<std::vector<DNUM>> & table)
{
	for(const auto & i : table)
	{
		for (DNUM j : i)
			std::cout << std::setfill('0') << std::setw(4) << j << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

long ComputeKnapsack(DNUM W, const std::vector<knapelem> & D)
{
	// [i][j] = maximum value when taken into account first i knapelems allowing weight of j (1-based)
	std::vector<std::vector<DNUM>> A(D.size()+1, std::vector<DNUM>(W+1,0));

	// for i up to D.size included knapelems
	for (DNUM i = 1; i <= D.size(); i++)
	{
		// for each subsetset i of included knapelems compute values for all valid weights
		for (DNUM j = 1; j <= W; j++)
		{
			// indexing to array from 1 ... D.size inclusive
			DNUM wi = D[i-1].weight;
			DNUM vi = D[i-1].value;
			// prevWeightIdx is weight that had knapsack before including this item assuming only j weight knapsack is allowed
			size_t prevWeightIdx = wi > j ? 0 : j-wi;

			// in a case this item can not be included, inherit value from knapsack with one less item
			DNUM inheritPreviousValue = A[i-1][j];
			// if included
			DNUM takeCurrentValue = A[i-1][prevWeightIdx] + vi;

			A[i][j] = inheritPreviousValue;

			// TODO weight of this item must be smaller then j ?
			if (wi <= j)
				A[i][j] = std::max(inheritPreviousValue, takeCurrentValue);
		}

		//printKnapsackTable(A);
	}

	return A[D.size()][W];
}

long ComputeKnapsackOpt(const DNUM W, const std::vector<knapelem> & D)
{
	std::vector<std::vector<DNUM>> A(2, std::vector<DNUM>(W+1,0));
	std::vector<DNUM> & p = A[0]; // previous
	std::vector<DNUM> & c = A[1]; // current

	for (DNUM i = 1; i <= D.size(); i++)
	{
		// indexing to array from 1 ... D.size inclusive
		const auto & d = D[i - 1];
		DNUM wi = d.weight;
		DNUM vi = d.value;

		for (DNUM j = 1; j <= W; j++)
		{
			size_t piw = wi > j ? 0 : j - wi;

			DNUM inheritPreviousValue = p[j];
			DNUM takeCurrentValue = p[piw] + vi;

			c[j] = inheritPreviousValue;

			if (wi <= j)
				c[j] = std::max(inheritPreviousValue, takeCurrentValue);
		}

		std::swap(std::move(p), std::move(c));
	}

	// must be previous because of last swap
	return p[W];
}

