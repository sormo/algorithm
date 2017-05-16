#include "graph.h"
#include "adjacencyList.h"
#include <stack>

void DFS(AdjacencyList & G, Vertice * S)
{
    for (auto e : S->tails)
    {
        if (e->head->marked)
            continue;

        DFS(G, e->head);
    }
}
