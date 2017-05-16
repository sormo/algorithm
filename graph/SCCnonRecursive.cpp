#include "graph.h"
#include "adjacencyList.h"
#include <stack>
#include <map>
#include <vector>

void GetComponentsEx(AdjacencyList & g, std::vector<Vertice*> & order, std::multimap<long, Vertice*> & components)
{
	// don't know why this is needed ):
	std::reverse(order.begin(), order.end());

	VertexMap vm = GenerateVertexMap(g);

	for ( Vertice * v : order )
	{
		Vertice * rv = vm[v->id];

		if (rv->marked)
			continue;

		std::stack<Vertice*> toVisit;
		long leader = rv->id;

		toVisit.push(rv);

		while(!toVisit.empty())
		{
			Vertice * vv = toVisit.top();
			toVisit.pop();

			if (!vv->marked)
				components.insert(std::pair<long, Vertice*>(leader, vv));
			vv->marked = true;


			for ( auto e : vv->tails )
			{
				if (e->head->marked)
					continue;
				toVisit.push(e->head);
			}
		}
	}

}

std::vector<Vertice*> GetMagicalOrderingEx(AdjacencyList & g)
{
	std::vector<Vertice*> ret(g.vertices.size(), nullptr);

	std::stack<Vertice*> toVisit;
	long order = 0;

	std::vector<Vertice *> decr = GetVerticesInDecreasingOrderById(g);
	for (auto v : decr)
	{
		if (!v->marked)
			toVisit.push(v);

		while(!toVisit.empty())
		{
			Vertice * vi = toVisit.top();

			vi->marked = true;

			bool viNotFinished = false;
			for (auto e : vi->tails)
			{
				if (!e->head->marked)
				{
					toVisit.push(e->head);
					viNotFinished = true;
					break;
				}
			}

			if (!viNotFinished)
			{
				ret[order++] = vi;
				toVisit.pop();
			}
		}
	}

	return ret;
}

std::multimap<long, Vertice*> ComputeSCCsEx(AdjacencyList & g)
{
	AdjacencyList rg = g.Reverse();

	// first DFS pass on reversed graph
	std::vector<Vertice*> order = GetMagicalOrderingEx(rg);

	// second pass DFS
	std::multimap<long, Vertice*> components;
	GetComponentsEx(g, order, components);

	return components;
}
