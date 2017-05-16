#include "adjacencyList.h"

#include <map>
#include <set>
#include <limits>

// heap implementation
//#include "heap.h"

std::map<Vertice *, int> DijkstraNaive(AdjacencyList & G, Vertice * S)
{
	std::map<Vertice*, int> A;
	std::set<Vertice*> X;

	A.insert(std::pair<Vertice*, int>(S, 0));
	X.insert(S);

	while(X.size() != G.vertices.size())
	{
		std::pair<Vertice*, int> minw(nullptr, std::numeric_limits<int>::max());
		for (auto v : X)
		{
			for ( auto e : v->tails)
			{
				if (X.find(e->head) != X.end())
					continue;
				// we have found edge which tail is in X and head not
				int tmpCost = A[v] + e->weigth;
				if (tmpCost < minw.second)
				{
					minw.first = e->head;
					minw.second = tmpCost;
				}
			}
		}
		// add vertice of edge with smallest cost to X
		A.insert(minw);
		X.insert(minw.first);
	}

	return A;
}



std::map<Vertice*, int> DijkstraHeap(AdjacencyList & g, Vertice * S)
{
	std::map<Vertice*, int> ret;

	return ret;
}

