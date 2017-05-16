#include <string>
#include <vector>
#include <limits>
#include "..\datastruct\heap.h"
#include "..\graph\adjacencyList.h"
#include "greedy.h"
#include <fstream>
#include <cassert>
#include <map>
#include <algorithm>
#include <sstream>

long long CountEdgeWeights(const std::vector<const Edge*> & e)
{
	long long ret = 0;

	for (auto edge : e)
		ret += edge->weigth;

	return ret;
}

std::vector<const Edge*> ComputePrimsMSTNaive(const AdjacencyList & V)
{
	std::vector<const Vertice*> X;
	std::vector<const Edge*> T;

	X.push_back(*V.vertices.begin());

	while(X.size() != V.vertices.size())
	{
		const Edge * bestEdge = nullptr;
		const Vertice * bestVertice = nullptr;
		int minWeight = std::numeric_limits<int>::max();

		for (const Edge * e : V.edges)
		{
			if (e->weigth < minWeight)
			{
				if (std::find(X.begin(), X.end(), e->tail) != X.end() && std::find(X.begin(), X.end(), e->head) == X.end())
				{
					bestEdge = e;
					bestVertice = e->head;
					minWeight = e->weigth;
				}
				else if (std::find(X.begin(), X.end(), e->head) != X.end() && std::find(X.begin(), X.end(), e->tail) == X.end())
				{
					bestEdge = e;
					bestVertice = e->tail;
					minWeight = e->weigth;
				}
			}
		}

		assert(bestEdge);
		X.push_back(bestVertice);
		T.push_back(bestEdge);
	}

	return T;
}

struct PrimsHeapContext
{
	Vertice * vertex;
	Edge * bestEdge;

	//bool operator==(const PrimsHeapContext & o) { return o.vertex == vertex; }
	//bool operator<(const PrimsHeapContext & o) { return o.vertex < vertex; }

};

struct PrimsEdgeContext : public Edge::Context
{
	bool isInXOrInCut = false;
};

// TODO Prim with heap

/*
std::vector<Edge*> computePrimsMSTHeap(AdjacencyList & V)
{
	std::map<PrimsHeapContext, int> vertexMap;

	std::vector<Vertice*> X;
	std::vector<Edge*> T;
	Heap<PrimsHeapContext, heapType::min> H; // T minus X

	Vertice * initialVertex = *V.vertices.cbegin();
	X.push_back(initialVertex);

	// initialize heap
	for (auto it = V.vertices.begin() + 1; it != V.vertices.end(); it++)
	{
		// get smallest edge of vertex that crosses cut with start vertex
		int key = std::numeric_limits<int>::max();
		Edge * edge = nullptr;

		for (Edge * e : (*it)->edges)
		{
			e->context = std::shared_ptr<Edge::Context>(dynamic_cast<Edge::Context*>(new PrimsEdgeContext));
			if (e->head == initialVertex || e->tail == initialVertex)
			{
				dynamic_cast<PrimsEdgeContext*>(e->context.get())->isInXOrInCut = true;
				if (key < e->weigth)
				{
					edge = e;
					key = e->weigth;
				}
			}
		}

		if (key != std::numeric_limits<int>::max())
		{
			H.insert(key, { *it, edge });
			vertexMap[{ *it, edge }] = key;
		}
	}

	// add vertices to X maintaining the invariant
	while(X.size() != V.vertices.size())
	{
		// this vertex (V - X) has smallest edge that is in cut (X, V - X) 
		auto v = H.root();
		T.push_back(v.bestEdge);
		X.push_back(v.vertex);

		// cut (X, V - X) has changed
		// all edges of v that are not in X are in cut
		for (auto e : v.vertex->edges)
		{
			PrimsEdgeContext * context = dynamic_cast<PrimsEdgeContext*>(e->context.get());
			if (context->isInXOrInCut)
				continue;

			Vertice * n = e->getOtherVertex(v.vertex);
			int key = std::numeric_limits<int>::max();
			auto it = std::find_if(std::begin(vertexMap), std::end(vertexMap), [n](const std::pair<PrimsHeapContext, int> & v) { return v.first.vertex == n; });
			if (it != vertexMap.end())
				key = it->second;

			if (e->weigth < key)
			{
				if (it != vertexMap.end())
					H.remove(it->first);
				key = e->weigth;
			}

			H.insert(key, {n, e});
			vertexMap[{n, e}] = key;

			context->isInXOrInCut = true;
		}
	}

	return T;
}
*/
