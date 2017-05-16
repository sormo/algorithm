#pragma once

#include <vector>
#include <string>
#include <map>

// --- adjacency list ---

namespace Undirected
{
	template <class T>
	struct Vertice;

	template <class T>
	struct Edge
	{
		Vertice<T> * vertex1;
		Vertice<T> * vertex2;
		T weigth;
	};

	template <class T>
	struct Vertice
	{
		Vertice(int i) : id(i), marked(false) {}
		int id;
		std::vector<Edge<T> *> edges;

		bool marked;

		bool IsIncident(Vertice<T> * v)
		{
			for (auto e : edges)
				if (e->vertex1 == v || e->vertex2 == v)
					return true;
			return false;
		}
		Vertice<T> * GetAdjacent(Edge<T> * e)
		{
			return e->vertex1 == this ? e->vertex2 : e->vertex1;
		}
	};

	template <class T>
	struct AdjacencyList
	{
		std::vector<Vertice<T> *> vertices;
		std::vector<Edge<T> *> edges;

		AdjacencyList<T> Copy()
		{
			AdjacencyList<T> ret;
			std::map<int, Vertice<T>*> vertsMap;

			for (Edge<T> * e : edges)
			{
				Vertice<T> * v1 = GetVertex(vertsMap, ret, e->vertex1->id);
				Vertice<T> * v2 = GetVertex(vertsMap, ret, e->vertex2->id);

				Edge<T> * ne = new Edge<T>;
				ne->vertex1 = v1;
				ne->vertex2 = v2;
				ne->weigth = e->weigth;

				ret.edges.push_back(ne);

				v1->edges.push_back(ne);
				v2->edges.push_back(ne);
			}

			return ret;
		}
	};
	// read input in format "<x coordinate of node> <y coordinate of node>"
	AdjacencyList<float> CreateAdjacencyListFromPoints(std::string file);
	// read input in format "<tail> <head1>,<weight1> <head2>,<weight2> ..."
	AdjacencyList<unsigned long long> CreateAdjacencyListMultipleHeadsWithHeights(std::string file);
	// read input in format "<vertex> <adjacent vertex> <adjacent vertex> ..."
	AdjacencyList<unsigned long long> CreateAdjacencyListMultipleAdjacents(std::string file);

	// --- helper ---

	template <class T>
	static Vertice<T> * GetVertex(std::map<int, Vertice<T>*> & data, AdjacencyList<T> & list, int id)
	{
		std::map<int, Vertice<T>*>::iterator it = data.find(id);
		if (it != data.end())
			return it->second;

		Vertice<T> * ret = new Vertice<T>(id);
		data.insert({ id, ret });
		list.vertices.push_back(ret);

		return ret;
	}
}
