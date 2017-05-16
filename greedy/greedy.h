#pragma once

#include <vector>
#include <string>
#include <map>
#include "../graph/adjacencyList.h"

// *** scheduling ***

struct job
{
	int weight = 0;
	int length = 0;
};
std::vector<job> ReadJobInput(const std::string & fileName);

long long ScheduleByDifference(std::vector<job> & data);
long long ScheduleByRatio(std::vector<job> & data);

// *** prim's MST ***

std::vector<const Edge*> ComputePrimsMSTNaive(const AdjacencyList & V);
std::vector<Edge*> ComputePrimsMSTHeap(AdjacencyList & V);

long long CountEdgeWeights(const std::vector<const Edge*> & e);


// *** clustering ***

using NUM = unsigned int;
struct ClusterEdge
{
	NUM v1;
	NUM v2;
	NUM cost;
};
std::vector<ClusterEdge> ReadClusterInput(const std::string & file);
NUM Cluster(NUM k, std::vector<ClusterEdge> edges);

std::vector<NUM> ReadClusterBinInput(const std::string & file);
NUM ClusterBin(size_t bits, std::vector<NUM> nodes, NUM separation = 3);

/*
using ClusterMap = std::map<NUM, NUM>;
ClusterMap readClusterBinInput(const std::string & file);
NUM countClusters(const NUM & BITS, const ClusterMap & data);
*/

std::vector<std::pair<float, std::string>> HuffmanEncoding(const std::vector<float> & frequencies);