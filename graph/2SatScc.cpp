#include "graph.h"
#include "adjacencyList.h"

bool Check2SATSatisfiability(AdjacencyList & G)
{
	std::multimap<long, Vertice*> r = ComputeSCCsEx(G);

	std::map<long, long> components;

	for (auto it = r.begin(); it != r.end(); it++)
	{
		components.insert({ it->second->id, it->first });
	}

	for (auto it = components.begin(); it != components.end(); it++)
	{
		auto nit = components.find(-1*(it->first));
		if (nit != components.end())
		{
			if (it->second == nit->second)
				return false;
		}
	}

	return true;
}
