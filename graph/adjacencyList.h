#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

// --- adjacency list ---

struct Vertice;

struct Edge
{
	Vertice * tail;
	Vertice * head;

	long weigth;

	struct Context { virtual ~Context() {} };
	std::shared_ptr<Context> context;

	Vertice * getOtherVertex(Vertice * v) { return v == tail ? head : tail; }
};

// edge: (u) [tail] ----> (v) [head]

struct Vertice
{
	Vertice(long i) : id(i) {}
	
	long id;
	bool marked = false;
	
	std::vector<Edge*> edges;

	std::vector<Edge*> tails;
	std::vector<Edge*> heads;
};

struct AdjacencyList
{
	std::vector<Vertice*> vertices;
	std::vector<Edge*> edges;

	AdjacencyList Copy();
	AdjacencyList Reverse();
};

// read input in format "<tail> <head> <weight>"
AdjacencyList CreateAdjacencyList(const std::string & file);

// read input in format "<tail> <head1> <head2> ..."
AdjacencyList CreateAdjacencyListMultipleHeads(const std::string & file);

// read input in format "<tail> <head1>,<weight1> <head2>,<weight2> ..."
AdjacencyList CreateAdjacencyListMultipleHeadsWithHeights(const std::string & file);

// read input in format "<A> <B>"
// construct implication graph from 2-SAT instance (vertices for both vertex and negation of vertex)
// (A OR B) AND (C OR A) = (~A -> B), (~B -> A), (~C -> A), (~A -> C)
AdjacencyList CreateAdjacency2SAT(const std::string & file);

std::vector<Vertice*> GetVerticesInDecreasingOrderById(AdjacencyList & G);

Vertice * GetVerticeById(AdjacencyList & G, long id);

using VertexMap = std::unordered_map<long, Vertice*>;
VertexMap GenerateVertexMap(AdjacencyList & G);
