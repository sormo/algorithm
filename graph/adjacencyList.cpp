#include "adjacencyList.h"

#include <cassert>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <regex>

Vertice * GetVertex(VertexMap & data, AdjacencyList & list, long id)
{
	auto it = data.find(id);
	if (it != data.end())
		return it->second;

	Vertice * ret = new Vertice(id);
	
	data.insert({ id, ret });
	list.vertices.push_back(ret);
	
	return ret;
}

AdjacencyList AdjacencyList::Copy()
{
	AdjacencyList ret;
	VertexMap vertexMap;

	for (Edge * e : edges)
	{
		Vertice * vhead = GetVertex(vertexMap, ret, e->head->id);
		Vertice * vtail = GetVertex(vertexMap, ret, e->tail->id);

		Edge * ne = new Edge;

		ne->tail = vtail;
		ne->head = vhead;
		ne->weigth = e->weigth;

		ret.edges.push_back(ne);

		vtail->edges.push_back(ne);
		vtail->tails.push_back(ne);

		vhead->edges.push_back(ne);
		vhead->heads.push_back(ne);
	}

	return ret;
}

AdjacencyList AdjacencyList::Reverse()
{
	AdjacencyList ret = Copy();

	for (Edge * e : ret.edges)
	{
		Vertice * tmp = e->head;
		e->head = e->tail;
		e->tail = tmp;
	}

	for (Vertice * v : ret.vertices)
	{
		std::vector<Edge*> tmp = v->heads;
		v->heads = v->tails;
		v->tails = tmp;
	}

	return ret;
}

std::vector<Vertice*> GetVerticesInDecreasingOrderById(AdjacencyList & G)
{
	std::vector<Vertice*> ret = G.vertices;

	sort(ret.begin(), ret.end(), [](Vertice * v1, Vertice * v2) { return v1->id > v2->id; });

	return ret;
}

Vertice * GetVerticeById(AdjacencyList & G, long id)
{
	auto v = find_if(begin(G.vertices), end(G.vertices), [id](const Vertice * a){ return a->id == id; });
	if (v == end(G.vertices))
		return nullptr;
	return *v;
}

VertexMap GenerateVertexMap(AdjacencyList & G)
{
	VertexMap ret;

	for (auto v : G.vertices)
		ret.insert({ v->id, v });

	return ret;
}

AdjacencyList CreateAdjacencyList(const std::string & file)
{
	AdjacencyList ret;
	VertexMap vertexMap;

	std::ifstream f(file);
	assert(f.is_open());

	std::string line;
	while (std::getline(f, line))
	{
		std::stringstream ss(line);
		long tail;
		long head;
		long cost;

		ss >> tail;
		ss >> head;
		ss >> cost;

		Vertice * v1 = GetVertex(vertexMap, ret, tail);
		Vertice * v2 = GetVertex(vertexMap, ret, head);

		Edge * e = new Edge;

		e->tail = v1;
		e->head = v2;
		e->weigth = cost;

		ret.edges.push_back(e);

		v1->edges.push_back(e);
		v1->tails.push_back(e);

		v2->edges.push_back(e);
		v2->heads.push_back(e);
	}

	return ret;
}

AdjacencyList CreateAdjacencyListMultipleHeads(const std::string & file)
{
	AdjacencyList ret;
	VertexMap vertexMap;

	std::ifstream f(file);
	assert(f.is_open());

	std::string line;
	while (std::getline(f, line))
	{
		std::stringstream ss(line);
		long tailid;

		ss >> tailid;

		Vertice * tail = GetVertex(vertexMap, ret, tailid);

		long headid;
		ss >> headid;
		
		do {
			Edge * e = new Edge;

			e->tail = tail;
			e->head = GetVertex(vertexMap, ret, headid);
			e->weigth = 1;

			ret.edges.push_back(e);

			e->tail->edges.push_back(e);
			e->tail->tails.push_back(e);

			e->head->edges.push_back(e);
			e->head->heads.push_back(e);

			ss >> headid;

		} while (ss.good());

	}

	return ret;
}

AdjacencyList CreateAdjacencyListMultipleHeadsWithHeights(const std::string & file)
{
	AdjacencyList ret;
	VertexMap vertexMap;

	std::ifstream f(file);
	assert(f.is_open());

	std::string line;
	while (getline(f, line))
	{
		std::regex ws_re("[\\s*,]");
		std::vector<std::string> tokens;

		std::copy(std::sregex_token_iterator(line.begin(), line.end(), ws_re, -1),
			std::sregex_token_iterator(),
			std::back_inserter(tokens));

		tokens.erase(
			std::remove_if(
			tokens.begin(),
			tokens.end(),
			[](std::string const& s) { return s.size() == 0; }),
			tokens.end());

		if (tokens.empty())
			continue;

		long tailid = std::stol(tokens[0]);
		Vertice * tail = GetVertex(vertexMap, ret, tailid);

		for (size_t i = 1; i < tokens.size(); i = i + 2)
		{
			Edge * e = new Edge;
			long headid = std::stol(tokens[i + 0]);
			
			e->head = GetVertex(vertexMap, ret, headid);
			e->tail = tail;
			e->weigth = std::stol(tokens[i + 1]);

			ret.edges.push_back(e);

			e->tail->edges.push_back(e);
			e->tail->tails.push_back(e);

			e->head->edges.push_back(e);
			e->head->heads.push_back(e);
		}
	}

	return ret;
}

AdjacencyList CreateAdjacency2SAT(const std::string & file)
{
	AdjacencyList ret;
	VertexMap vertexMap;

	std::ifstream f(file);
	assert(f.is_open());

	std::string line;
	while (std::getline(f, line))
	{
		std::stringstream ss(line);
		long a,   b;
		long na, nb;

		ss >> a;
		ss >> b;

		na = -a;
		nb = -b;

		Vertice * va = GetVertex(vertexMap, ret, a);
		Vertice * vb = GetVertex(vertexMap, ret, b);
		Vertice * nva = GetVertex(vertexMap, ret, na);
		Vertice * nvb = GetVertex(vertexMap, ret, nb);

		// two implications of disjunction
		Edge * e1 = new Edge;
		e1->tail = nva;
		e1->head = vb;

		Edge * e2 = new Edge;
		e2->tail = nvb;
		e2->head = va;

		nva->tails.push_back(e1);
		vb->heads.push_back(e1);

		nvb->tails.push_back(e2);
		va->heads.push_back(e2);

		ret.edges.push_back(e1);
		ret.edges.push_back(e2);
	}

	return ret;
}
