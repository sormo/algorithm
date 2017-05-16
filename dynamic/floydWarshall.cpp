#include "dynamic.h"
#include <vector>
#include <map>
#include <algorithm>
#include <limits>

// [i][j][k] = minimum cost of i->j path using k vertices between i,j (indexing 1-based)
using Vector3d = std::vector<std::vector<std::vector<long>>>;

long FloydWarshall(const AdjacencyList & G)
{
	Vector3d A(G.vertices.size()+1, 
		std::vector<std::vector<long>>(G.vertices.size()+1, 
		std::vector<long>(G.vertices.size() + 1, 
			std::numeric_limits<long>::max())));

	// init step
	// shortest path using 0 vertices
	for (size_t i = 1; i <= G.vertices.size(); i++)
	{
		for (size_t j = 1; j <= G.vertices.size(); j++)
		{
			if (i == j)
			{
				// zero for same vertex
				A[i][j][0] = 0;
			}
			else
			{
				// cost of edge if direct connection
				long minCost = std::numeric_limits<long>::max();
				for (Edge * e : G.vertices.at(i-1)->tails)
				{
					if (e->head == G.vertices.at(j-1))
						minCost = std::min(minCost, e->weigth);
				}
				A[i][j][0] = minCost;
			}
		}
	}

	// for i->j paths try to use k vertex as intermediate
	for (size_t k = 1; k <= G.vertices.size(); k++)
	{
		for (size_t i = 1; i <= G.vertices.size(); i++)
		{
			for (size_t j = 1; j <= G.vertices.size(); j++)
			{
				if (A[i][k][k-1] == std::numeric_limits<long>::max() || A[k][j][k-1] == std::numeric_limits<long>::max())
				{
					A[i][j][k] = A[i][j][k-1];
					continue;
				}

				A[i][j][k] = std::min(A[i][j][k-1], A[i][k][k-1] + A[k][j][k-1]);
			}
		}
	}

	// output shortest path
	long minpath = std::numeric_limits<long>::max();
	for (size_t i = 1; i <= G.vertices.size(); i++)
	{
		for (size_t j = 1; j <= G.vertices.size(); j++)
		{
			minpath = std::min(minpath, A[i][j][G.vertices.size()]);
		}
	}

	return minpath;
}
