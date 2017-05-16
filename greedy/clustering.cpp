#include <string>
#include <fstream>
#include <cassert>
#include <sstream>
#include <vector>
#include <map>
#include <limits>
#include <algorithm>

#include "greedy.h"
#include "unionFind.h"
#include <set>

std::vector<ClusterEdge> ReadClusterInput(const std::string & file)
{
	std::vector<ClusterEdge> edges;

	std::ifstream f(file);
	assert(f.is_open());

	std::string line;
	while(getline(f, line))
	{
		std::stringstream ss(line);
		ClusterEdge e;

		ss >> e.v1;
		ss >> e.v2;
		ss >> e.cost;

		edges.push_back(e);
	}

	return edges;
}

NUM Cluster(NUM k, std::vector<ClusterEdge> edges)
{
	// sort edges
	std::sort(std::begin(edges), std::end(edges), [](const ClusterEdge & a, const ClusterEdge & b) { return a.cost < b.cost; });

	// prepare clusters
	std::set<NUM> nodes;
	std::for_each(std::begin(edges), std::end(edges), [&nodes](const ClusterEdge & e) { nodes.insert(e.v1); nodes.insert(e.v2); });

	UnionFind<NUM> clusters;
	std::map<NUM, UnionFind<NUM>::Node> nodesMap;

	std::for_each(std::begin(nodes), std::end(nodes), [&clusters, &nodesMap](NUM n) { nodesMap[n] = clusters.Insert(n); });

	size_t merges = 0;
	for (const ClusterEdge & e : edges)
	{
		auto node1 = nodesMap[e.v1];
		auto node2 = nodesMap[e.v2];

		if (clusters.Find(node1) != clusters.Find(node2))
		{
			// find first edge that is not inside same cluster
			if (nodes.size() - merges == k)
				return e.cost;

			clusters.Union(node1, node2);
			merges++;
		}
	}

	assert(false);
	return 0;
}

// ---

void SetNthBit(NUM & num, int n)
{
	NUM tmp = 1;
	tmp = tmp << n;
	num = num | tmp;
}

std::vector<NUM> ReadClusterBinInput(const std::string & file)
{
	std::vector<NUM> ret;

	std::ifstream f(file);
	assert(f.is_open());

	std::string line;
	while (std::getline(f, line))
	{
		NUM n = 0;
		int cnt = 0;

		for (std::string::reverse_iterator it = line.rbegin(); it != line.rend(); it++)
		{
			char c = *it;
			if (c == '1')
				SetNthBit(n, cnt);
			if (c == '1' || c == '0')
				cnt++;
		}

		ret.push_back(n);
	}

	return ret;
}

size_t HammingDistance(NUM a, NUM b)
{
	size_t ret = 0;

	NUM val = a ^ b;
	while (val)
	{
		++ret;
		val &= (val - 1);
	}

	return ret;
}

// TODO generate distance set according to separation 
// currently only numbers with separation 0,1,2 are included
std::set<NUM> GenerateDistanceSet(size_t bits, NUM separation, NUM number)
{
	std::set<NUM> ret;

	for (size_t i = 0; i < bits; ++i)
	{
		NUM a = number;
		a ^= (1u << i);

		ret.insert(a);

		for (size_t j = i + 1; j < bits; ++j)
		{
			NUM b = number;
			b ^= (1u << i);
			b ^= (1u << j);

			ret.insert(b);
		}
	}

	return ret;
}

NUM ClusterBin(size_t bits, std::vector<NUM> nodes, NUM separation)
{
	UnionFind<NUM> clusters;
	std::map<NUM, UnionFind<NUM>::Node> nodesMap;

	std::for_each(std::begin(nodes), std::end(nodes), [&clusters, &nodesMap](NUM n) 
	{
		if (nodesMap.find(n) == nodesMap.end())
			nodesMap[n] = clusters.Insert(n); 
	});

	size_t merges = 0;
	for (auto n1 : nodesMap)
	{
		auto distanceSet = GenerateDistanceSet(bits, separation, n1.first);

		for (auto d : distanceSet)
		{
			auto n2 = nodesMap.find(d);
			if (n2 == nodesMap.end())
				continue;

			if (clusters.Find(n1.second) != clusters.Find(n2->second))
			{
				merges++;
				clusters.Union(n1.second, n2->second);
			}
		}

		/*for (size_t j = i + 1; j < nodes.size(); ++j)
		{
			auto node1 = nodesMap[nodes[i]];
			auto node2 = nodesMap[nodes[j]];

			if (clusters.Find(node1) == clusters.Find(node2))
				continue;

			if (hammingDistance(nodes[i], nodes[j]) >= separation)
				continue;

			merges++;
			clusters.Union(node1, node2);
		}*/
	}

	return nodesMap.size() - merges;
}
