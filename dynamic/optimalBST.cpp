#include "dynamic.h"
#include <vector>
#include <string>
#include <fstream>
#include <cassert>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <iomanip>

// optimal binary search tree
//
// input: frequencies nodes with id index is being searched for
// output: minimum average search time, tree that minimizes search time

std::vector<float> ReadOptimalBSTInput(const std::string & file)
{
	std::vector<float> ret;

	std::ifstream f(file);
	assert(f.is_open());

	std::string line;

	while (std::getline(f, line))
		ret.push_back((float)std::atof(line.c_str()));

	return ret;
}

float OptimalBST(const std::vector<float> & frequencies)
{
	std::vector<std::vector<float>> A(frequencies.size(), std::vector<float>(frequencies.size(), 0.0f));

	// initialization (diagonal)
	for (size_t i = 0; i < frequencies.size(); ++i)
		A[i][i] = frequencies[i];

	// algorithm
	for (size_t s = 0; s <= frequencies.size(); ++s)
	{
		for (size_t i = 0; i < frequencies.size(); ++i)
		{
			size_t j = i + s - 1;
			if (j >= frequencies.size())
				break;

			float sum = std::accumulate(std::begin(frequencies) + i, std::begin(frequencies) + j + 1, 0.0f);

			std::vector<float> tmp;
			for (size_t r = i; r <= j; ++r)
				tmp.push_back(sum + 
				((r > i) ? A[i][r-1] : 0.0f) + 
				((r < j) ? A[r+1][j] : 0.0f));
			A[i][j] = *std::min_element(std::begin(tmp), std::end(tmp));
		}
	}

	return A[0][frequencies.size()-1];
}

void Print(const std::vector<std::vector<std::pair<float, size_t>>> & A)
{
	for (size_t i = 0; i < A.size(); ++i)
	{
		for (size_t j = 0; j < A[i].size(); ++j)
			std::cout << std::setfill('0') << std::setw(4) << A[i][j].first << "(" << A[i][j].second << ")" << " ";
		std::cout << std::endl;
	}
}

std::tuple<float, AdjacencyList> OptimalBSTEx(const std::vector<float> & frequencies)
{
	std::vector<std::vector<std::pair<float, size_t>>> A(
		frequencies.size(), std::vector<std::pair<float, size_t>>(
			frequencies.size(), { 0.0f, 0 }));

	// initialization (diagonal)
	for (size_t i = 0; i < frequencies.size(); ++i)
		A[i][i] = { frequencies[i], i };

	// algorithm
	for (size_t s = 0; s <= frequencies.size(); ++s)
	{
		for (size_t i = 0; i < frequencies.size(); ++i)
		{
			size_t j = i + s - 1;
			if (j >= frequencies.size())
				break;

			float sum = std::accumulate(std::begin(frequencies) + i, std::begin(frequencies) + j + 1, 0.0f);

			std::vector<std::pair<float, size_t>> tmp;
			for (size_t r = i; r <= j; ++r)
				tmp.push_back({ sum +
				((r > i) ? A[i][r - 1].first : 0.0f) +
					((r < j) ? A[r + 1][j].first : 0.0f), r });
			A[i][j] = *std::min_element(std::begin(tmp), std::end(tmp), [](auto & a, auto & b) { return a.first < b.first; });
		}
	}

	Print(A);

	// reconstruction
	AdjacencyList ret;

	std::function<void(Vertice*, size_t, size_t)> reconstruction = [&ret, &A, &reconstruction, size = frequencies.size() - 1](Vertice * root, size_t i, size_t j)
	{
		long vid = A[i][j].second;

		for (auto v : ret.vertices)
		{
			if (v->id == vid)
				return;
		}

		auto v = new Vertice(vid);
		ret.vertices.push_back(v);

		if (root)
		{
			auto e = new Edge();
			e->tail = root;
			e->head = v;
			ret.edges.push_back(e);
		}

		if (i == j)
			return;

		// problem , what if vid is 0 or right most index ?
		reconstruction(v, i, vid == 0 ? 0 : vid - 1);
		reconstruction(v, vid == size ? size : vid + 1, j);
	};

	reconstruction(nullptr, 0, frequencies.size() - 1);

	return{ A[0][frequencies.size() - 1].first, ret };
}
