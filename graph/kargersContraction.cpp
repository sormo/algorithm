#include "graph.h"
#include "adjacencyList.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cassert>

Undirected::Edge<unsigned long long> * GetRandomEdge(Undirected::AdjacencyList<unsigned long long> & G)
{
	int rv1 = rand() % G.edges.size();
	return G.edges[rv1];
}

void ContractEdge(Undirected::AdjacencyList<unsigned long long> & G, Undirected::Edge<unsigned long long> * E)
{
	Undirected::Vertice<unsigned long long> * v1 = E->vertex1;
	Undirected::Vertice<unsigned long long> * v2 = E->vertex2;

	// this can't be self-loop
	assert(v1 != v2);

	// iterate over all edges of v2 (that is being merged)
	auto it = begin(v2->edges);
	while ( it != end(v2->edges) )
	{
		auto adjacentVertice = v2->GetAdjacent(*it);
		// this vertice points to v1, will create self loop
		if (adjacentVertice == v1)
		{
			auto itAdjacent = find(begin(adjacentVertice->edges), end(adjacentVertice->edges), *it);
			assert(itAdjacent != end(adjacentVertice->edges));
			auto itList = find(begin(G.edges), end(G.edges), *it);
			assert(itList != end(G.edges));

			delete *it;

			adjacentVertice->edges.erase(itAdjacent);
			G.edges.erase(itList);
			it = v2->edges.erase(it);

			continue;
		}

		// change endpoint that pointed to v2 to point to v1 (no reference to v2 should be left anywhere)
		if ((*it)->vertex1 == v2)
			(*it)->vertex1 = v1;
		else
			(*it)->vertex2 = v1;
		// this edge will be owned now by v1
		v1->edges.push_back(*it);

		it++;
	}
	// finally erase v2 vertice from ajacency list
	auto itVertice = find(begin(G.vertices), end(G.vertices), v2);
	assert(itVertice != end(G.vertices));
	delete *itVertice;
	G.vertices.erase(itVertice);
}

int KargersMincut(Undirected::AdjacencyList<unsigned long long> & G)
{
	// input G = (V,E)
	int repetitions = (int)pow(G.vertices.size(), 2);
	int mincut = repetitions;

	srand((unsigned int)time(NULL));

	for ( int i = 0; i < repetitions; i++)
	{
		Undirected::AdjacencyList<unsigned long long> GC = G.Copy();

		while (GC.vertices.size() > 2)
		{
			ContractEdge(GC, GetRandomEdge(GC));
		}

		mincut = std::min<int>(mincut, GC.vertices[0]->edges.size());
	}

	return mincut;
}
