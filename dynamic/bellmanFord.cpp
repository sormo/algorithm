#include "dynamic.h"
#include <vector>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <cassert>
#include <iostream>

// [i][v] = minimum path (first i vertices allowed to use in shortest path from s to v)
using Vector2d = std::vector<std::unordered_map<Vertice*, long>>;

long BellmanFord(const AdjacencyList & G, Vertice * S, Vector2d & A)
{
	// initialization, shortest path to S using 0 vertices
	for (Vertice * v : G.vertices)
	{
		A[0][v] = v == S ? 0 : std::numeric_limits<long>::max();
	}

	for (size_t i = 1; i <= G.vertices.size(); i++)
	{
		// compute shortest path to S using first i vertices
		// finish early optimization, if there is no change during iteration through vertices
		bool finishEarly = true;
		// v is destination vertex, we are now fixing path s->v using first i vertices
		for (Vertice * v : G.vertices)
		{
			long minimumEdge = std::numeric_limits<long>::max();
			// for each edge for which v is head
			for (Edge * e : v->heads)
			{
				// check if it is possible to get to tail vertex using one less vertices
				long length = A[i - 1][e->tail];
				if (length == std::numeric_limits<long>::max())
					continue;
				minimumEdge = std::min(minimumEdge, length + e->weigth);
			}
			// A[i][v] = min shortest path S->v using i edges
			A[i][v] = std::min(A[i-1][v], minimumEdge);

			if (finishEarly)
				finishEarly = A[i][v] == A[i-1][v];
		}

		//if (finishEarly)
		//	break;
	}

	// negative cycle detection
	for (Vertice * v : G.vertices)
	{
		if (A[G.vertices.size() - 1][v] != A[G.vertices.size()][v])
			return std::numeric_limits<long>::max();
	}

	// output smallest shortest path among paths from S to any other vertex
	long ret = std::numeric_limits<long>::max();
	for (Vertice  * v: G.vertices)
	{
		ret = std::min(ret, A[G.vertices.size()-1][v]);
	}

	return ret;
}

long BellmanFord(const AdjacencyList & G, Vertice * S)
{
	// this is only optimization to prevent multiple allocations
	Vector2d A(G.vertices.size() + 1, std::unordered_map<Vertice*, long>());

	return BellmanFord(G, S, A);
}

long AllPairBellmanFord(const AdjacencyList & G)
{
	long ret = std::numeric_limits<long>::max();
	Vector2d A(G.vertices.size() + 1, std::unordered_map<Vertice*, long>());

	for (Vertice * v : G.vertices)
	{
		ret = std::min(ret, BellmanFord(G, v, A));
		// if it containt cycle, report it
		if (ret == std::numeric_limits<long>::max())
			return ret;
	}

	return ret;
}

std::vector<Vertice*> BellmanFordVariation(const AdjacencyList & G, Vertice * S, Vertice * D)
{
	std::vector<Vertice*> ret;

	std::unordered_map<Vertice *, long> weights;
	std::unordered_map<Vertice *, Vertice*> predecessors;

	// initialization
	for (Vertice * v : G.vertices)
	{
		weights[v] = std::numeric_limits<long>::max();
		predecessors[v] = nullptr;
	}
	weights[S] = 0;

	// edge relaxation
	// make |V|-1 updates for each edge
	for (size_t i = 1; i < G.vertices.size(); i++)
	{
		for (Edge * e : G.edges)
		{
			Vertice * u = e->tail;
			Vertice * v = e->head;

			if (weights[u] != std::numeric_limits<long>::max() && weights[u] + e->weigth < weights[v])
			{
				weights[v] = weights[u] + e->weigth;
				predecessors[v] = u;
			}
		}
	}

	// negative cycle detection
	for (Edge * e : G.edges)
	{
		Vertice * u = e->tail;
		Vertice * v = e->head;

		if (weights[u] + e->weigth < weights[v])
			return ret; // negative cycle
	}

	// path reconstruction
	Vertice * tmp = D;
	
	do {
		ret.insert(ret.begin(), tmp);
		tmp = predecessors[tmp];
	} while (tmp != S);
	ret.insert(ret.begin(), S);

	return ret;
}
