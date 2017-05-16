#include "dynamic.h"

#include <unordered_map>
#include <algorithm>
#include <set>
#include <vector>
#include <bitset>
#include <iostream>

using VertexSet = unsigned int;
bool isBit(VertexSet set, size_t index) { return (set & (1 << index)) != 0; }
void setBit(VertexSet & set, size_t index) { set |= (1 << index); }
void clearBit(VertexSet & set, size_t index) { set &= (~(1 << index)); }

// in the key there are both vertices encoded (16 bits first, 16 bits second)
std::unordered_map<unsigned int, float> g_distances;

void PrintSubsets(size_t numberOfVertices, std::multimap<size_t, VertexSet> & sets)
{
	for (auto it = sets.begin(); it != sets.end(); it++)
	{
		for (size_t i = 0; i < numberOfVertices; ++i)
			std::cout << isBit(it->second, i);
		std::cout << "(" << it->first << ")" << std::endl;
	}
	std::cout << std::endl;
}

float GetFirstEdgeBetweenVertices(size_t k, size_t j, const Undirected::AdjacencyList<float> & G)
{
	auto v1 = G.vertices[k];
	auto v2 = G.vertices[j];

	for (auto e : v1->edges)
	{
		// if this is edge between v1 and v2
		if (e->vertex1 == v1 && e->vertex2 == v2 || e->vertex2 == v1 && e->vertex1 == v2)
			return e->weigth;
	}
	return std::numeric_limits<float>::max();
}

void CreateDistances(const Undirected::AdjacencyList<float> & G)
{
	for (unsigned int i = 0; i < G.vertices.size(); i++)
	{
		for (unsigned int j = i; j < G.vertices.size(); j++)
		{
			unsigned int key = i + (j << 16);
			g_distances[key] = GetFirstEdgeBetweenVertices(i, j, G);
		}
	}
}

float GetDistance(size_t k, size_t j)
{
	size_t m = std::min(k, j);
	size_t n = m == k ? j : k;
	return g_distances[m + (n << 16)];
}

VertexSet ConvertToBitset(const std::vector<bool> & tmp)
{
	VertexSet ret = 0;

	for (size_t i = 0; i < tmp.size(); i++)
	{
		if (tmp[i])
			setBit(ret, i);
	}

	return ret;
}

void GenerateSubsets(size_t numberOfVertices, std::multimap<size_t, VertexSet> & sets)
{
	for (size_t R = 0; R < numberOfVertices; R++)
	{
		// create vector of bools with R 1s and iterate over all permutations
		std::vector<bool> v(numberOfVertices - 1, false);
		std::fill(v.begin(), v.begin() + R, true);
		std::sort(v.begin(), v.end());

		do {
			std::vector<bool> tmp = v;
			tmp.insert(tmp.begin(), true);

			sets.insert({ R + 1, ConvertToBitset(tmp) });

		} while (std::next_permutation(v.begin(), v.end()));
	}
	//printSubsets(numberOfVertices, sets);
}

bool CheckSubset2(VertexSet & KS, const VertexSet & S, size_t j)
{
	if (!isBit(KS, j))
		return false;

	clearBit(KS, j);

	bool ret = KS == S;
	setBit(KS, j);

	return ret;
}

// in a key there is vertex index and vertex set encoded
unsigned int CreateAKey(const VertexSet & k, size_t j)
{
	return k + (j << 25);
}

float TravelingSalesman(const Undirected::AdjacencyList<float> & G)
{
	std::multimap<size_t, VertexSet> sets;
	std::unordered_map<unsigned int, float> A;
	const size_t INITIAL_INDEX = 0;
	const size_t VERTICES_SIZE = G.vertices.size();

	CreateDistances(G);
	GenerateSubsets(G.vertices.size(), sets);

	// insert base cases
	// 0 if size of subset is 1
	for (auto & s : sets)
	{
		if (s.first == 1)
			A[CreateAKey(s.second, INITIAL_INDEX)] = 0;
		else
			A[CreateAKey(s.second, INITIAL_INDEX)] = std::numeric_limits<float>::max();
	}

	// through all subset sizes
	for (size_t subsetSize = 2; subsetSize <= VERTICES_SIZE; subsetSize++)
	{
		std::cout << subsetSize << std::endl;
		// through each subset of size subsetSize
		auto range = sets.equal_range(subsetSize);
		for (auto it = range.first; it != range.second; it++)
		{
			// through each index in subset
			for (size_t j = 1; j < VERTICES_SIZE; ++j)
			{
				// skip if this vertex is not in set
				if (!isBit(it->second, j))
					continue;

				float minValue = std::numeric_limits<float>::max();
				for (size_t k = 0; k < VERTICES_SIZE; ++k)
				{
					if (k == j)
						continue;
					if (!isBit(it->second, k))
						continue;

					VertexSet tmpS = it->second;
					clearBit(tmpS, j);

					auto it = A[CreateAKey(tmpS, k)];
					if (it != std::numeric_limits<float>::max())
						minValue = std::min(minValue, it + GetDistance(k, j));
				}

				A[CreateAKey(it->second, j)] = minValue;
			}
		}
	}

	// we made it
	float minValue = std::numeric_limits<float>::max();
	auto range = sets.equal_range(G.vertices.size());
	for (auto it = range.first; it != range.second; it++)
	{
		VertexSet S = it->second;
		for (size_t j = 1; j < G.vertices.size(); j++)
		{
			if (j == INITIAL_INDEX)
				continue;
			minValue = std::min(minValue, A[CreateAKey(S, j)] + GetDistance(j, INITIAL_INDEX));
		}
	}

	return minValue;
}
