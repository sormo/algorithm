#include "graph.h"

#pragma comment(linker, "/STACK:10000000")
#include "adjacencyList.h"
#include <map>
#include <vector>

void SecondPassDFS(Vertice * v, std::multimap<long, Vertice*> & components, long leader)
{
	v->marked = true;

	for (auto e : v->tails)
	{
		if (e->head->marked)
			continue;
	   SecondPassDFS(e->head, components, leader);
	}

	components.insert(std::pair<long, Vertice*>(leader, v));
}

void GetComponents(AdjacencyList & G, std::vector<Vertice*> & order, std::multimap<long, Vertice*> & components)
{
	for ( auto v : order )
	{
		if (v->marked)
			continue;

		SecondPassDFS(v, components, v->id);
	}
}

void FirstPassDFS(Vertice * v, std::vector<Vertice*> & ordering, long & order)
{
	v->marked = true;

	//for (auto e : v->tails)
	for (auto e : v->heads)
	{
		//if (e->head->marked)
		if (e->tail->marked)
			continue;
		//firstPassDFS(e->head, ordering, order);
		FirstPassDFS(e->tail, ordering, order);
	}

	ordering[order++] = v;
}

std::vector<Vertice*> GetMagicalOrdering(AdjacencyList & G)
{
	std::vector<Vertice*> ret(G.vertices.size(), nullptr);

	long order = 0;

	std::vector<Vertice *> decr = GetVerticesInDecreasingOrderById(G);
	for (auto v : decr)
	{
		if (!v->marked)
		{
			FirstPassDFS(v, ret, order);
		}
	}

	return ret;
}

std::multimap<long, Vertice*> ComputeSCCs(AdjacencyList & G)
{
	//AdjacencyList rG = G.reverse();

	// first DFS pass on reversed graph
	//vector<Vertice*> order = getMagicalOrdering(rG);
	std::vector<Vertice*> order = GetMagicalOrdering(G);

	// prepare magical ordering for second pass
	std::reverse(std::begin(order), std::end(order));
	for (auto v : G.vertices)
		v->marked = false;
	//for (auto it = begin(order); it != end(order); it++)
	//	*it = GetVerticeById(G, (*it)->id);

	// second pass DFS
	std::multimap<long, Vertice*> components;
	GetComponents(G, order, components);

	return components;
}

