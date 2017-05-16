#include "graph.h"
#include "adjacencyList.h"
#include <map>
#include <queue>

std::map<Vertice*, int> BFS(AdjacencyList & G, Vertice * S)
{
	// initialization
	std::queue<Vertice*> verticesToVisit;

	std::map<Vertice*, int> distances;
	distances.insert(std::pair<Vertice*, int>(S, 0));

	verticesToVisit.push(S);

	while (!verticesToVisit.empty())
	{
		Vertice * cv = verticesToVisit.front();
		verticesToVisit.pop();

		for (Edge * e : cv->tails)
		{

			if (e->head->marked)
				continue;
			e->head->marked = true;
			verticesToVisit.push(e->head);

			distances.insert(std::pair<Vertice*, int>(e->head, distances[cv] + 1));
		}
	}

	return distances;
}
