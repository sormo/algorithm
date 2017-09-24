## Algorithms  
### Notes from Introduction to Algorithms

Following algorithms and datastructures are covered:
* **data structures**  
  * **binary search tree**  
    Store items in binary tree such that all keys in left subtree are smaller and keys in right subtree are greater than key of any node.
  * **heap**  
    Store items in binary tree such that all nodes satisfies "heap property".
  * **directed/undirected graph as adjacency list**  
    Store nodes in an array where each node contains array of incoming/outgoing edges.
  * **nion-find**  
    Track set of elements partitioned into disjoint subsets.
* **graphs**  
  * **breadth first search**  
    Iterate over all nodes of graph visiting all childs first before moving to next level of childs.
  * **depth first search**  
    Iterate over all nodes of graph visiting all nodes of single branch before backtracking.
  * **dijkstra**  
    Search shortest paths in graph from single vertex. Greedy algorithm.
  * **topological sort**  
    Finds ordering of directed acyclic graph such that all childs are before parent.
  * **kosaraju's scc**  
    Partition directed graph into subgraphs that are strongly connected (all nodes are reachable from each node within subgraph)
  * **karger's contraction**  
    Randomized algorithm for finding minimum cut of graph.
  * **2SAT**  
    Solve 2-satisfiability problem using scc.
* **divide and conquer**  
  * **mergesort**  
    Sort array of numbers using merge subrutine.
  * **quicksort**  
    Randomized algorithm for sorting array of numbers by partitioning around pivot.
  * **inversions**  
    Count number of inversions of array using modified merge sort.
  * **karatsuba**  
    Multiply two numbers using Gauss's trick resulting in better asymptotically better speed then better.
* **greedy**  
  * **clustering**  
    Partition nodes of graph into k clusters given some distance function (of two nodes).
  * **huffman encoding**  
    Translate message into bit string of smaller length using prefix free binary tree.
  * **prim's**  
    Find minimum spanning tree of graph (tree spans through all nodes).
  * **scheduling**  
    Schedule jobs on shared resource minimizing objective function.
* **dynamic**  
  * **bellman-ford**  
    Search shortest paths in graph from single vertex. Works for negative paths.
  * **floyd-warshall**  
    Find shortests paths in graph for all pairs.
  * **knapsack**  
    Find subset of items maximizing value.
  * **matrix chain multiplication**  
    Find optimal order of multiplication of matrices.
  * **optimal BST**  
    Constuct BST with minimal search time.
  * **sequence alignment**  
    Align two strings minimizing cost for mismatches and gaps. 
  * **traveling salesman**  
    Find minimum cost path which visits all nodes in graph.
