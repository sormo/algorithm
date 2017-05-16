#include "graph.h"
#include "adjacencyList.h"
#include <vector>
#include <set>
#include <stack>
#include <iostream>

void Visit(Vertice * v, std::vector<Vertice*> & ret)
{
	for (auto e : v->tails)
	{
		if (!e->head->marked)
			Visit(e->head, ret);
	}

	ret.insert(ret.begin(), v);
	v->marked = true;
}

std::vector<Vertice*> Toposort(AdjacencyList & G)
{
	std::vector<Vertice*> ret;

	std::stack<Vertice*> toProcess;
	for(auto v : G.vertices)
		toProcess.push(v);

	while(!toProcess.empty())
	{
		Vertice * v = toProcess.top();
		toProcess.pop();

		if (v->marked)
			continue;

		Visit(v, ret);
	}

	return ret;
}
