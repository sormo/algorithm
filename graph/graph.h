#pragma once
#include <map>
#include "adjacencyList.h"
#include "undirectedAdjacencyList.h"

int KargersMincut(Undirected::AdjacencyList<unsigned long long> & G);

std::map<Vertice*, int> BFS(AdjacencyList &G, Vertice * S);

void DFS(AdjacencyList &G, Vertice * S);

std::vector<Vertice*> Toposort(AdjacencyList & G);

std::multimap<long, Vertice*> ComputeSCCs(AdjacencyList & G);

std::multimap<long, Vertice*> ComputeSCCsEx(AdjacencyList & G);

std::map<Vertice*, int> DijkstraNaive(AdjacencyList & G, Vertice * S);

bool Check2SATSatisfiability(AdjacencyList & G);
