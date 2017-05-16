#pragma once

#include <vector>
#include <string>
#include <functional>
#include "..\graph\adjacencyList.h"
#include "..\graph\undirectedAdjacencyList.h"

using DNUM = unsigned int;

std::vector<DNUM> IndependentSets(const std::vector<DNUM> & seq);

struct knapelem
{
	knapelem(DNUM v, DNUM w) : value(v), weight(w) {}
	DNUM value;
	DNUM weight;
};
std::vector<knapelem> ReadKnapsackInput(const std::string & file);
long ComputeKnapsack(DNUM W, const std::vector<knapelem> & D);
// knapsack with space optimization
long ComputeKnapsackOpt(DNUM W, const std::vector<knapelem> & D);

// output smallest path from S to any other vertice
long BellmanFord(const AdjacencyList &G, Vertice * S);
std::vector<Vertice*> BellmanFordVariation(const AdjacencyList & G, Vertice * S, Vertice * D);

// output smallest path in graph
long AllPairBellmanFord(const AdjacencyList &G);
long FloydWarshall(const AdjacencyList &G);

float TravelingSalesman(const Undirected::AdjacencyList<float> & G);

std::tuple<std::string, std::string, long, long> ReadSequenceAlignmentInput(const std::string & file);
// return smallest penalty for aligning A and B
std::tuple<long, std::string, std::string> SequenceAlignmentEx(const std::string & str1, const std::string & str2, long gapPenalty, std::function<long(char, char)> mismatchPenalty);
long SequenceAlignment(const std::string & str1, const std::string & str2, long gapPenalty, long mismatchPenalty);

std::vector<float> ReadOptimalBSTInput(const std::string & file);
// return minimum average search time in BST with frequencies and search tree
std::tuple<float, AdjacencyList> OptimalBSTEx(const std::vector<float> & frequencies);

std::tuple<size_t, std::string> MatrixChainMultiplication(const std::vector<size_t> & dimensions);