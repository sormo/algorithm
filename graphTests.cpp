#include "gtest/gtest.h"

#include <iostream>
#include <map>
#include <algorithm>
#include "graph\graph.h"
#include "graph\adjacencyList.h"
#include "graph\undirectedAdjacencyList.h"

TEST(graph_undirected, topological_sort)
{
	AdjacencyList g = CreateAdjacencyListMultipleHeads("graph/data/directedTest2.graph");
	std::vector<Vertice*> r = Toposort(g);

	EXPECT_EQ(5, r.at(0)->id);
	EXPECT_EQ(6, r.at(1)->id);
	EXPECT_EQ(1, r.at(2)->id);
	EXPECT_EQ(2, r.at(3)->id);
	EXPECT_EQ(4, r.at(4)->id);
	EXPECT_EQ(20, r.at(5)->id);
	EXPECT_EQ(10, r.at(6)->id);
}

TEST(graph_undirected, kargers_min_cut_1)
{
	Undirected::AdjacencyList<unsigned long long> g = Undirected::CreateAdjacencyListMultipleAdjacents("graph/data/karger1.graph");
	int ret = KargersMincut(g);
	EXPECT_EQ(2, ret);
}

TEST(graph_undirected, kargers_min_cut_2)
{
	Undirected::AdjacencyList<unsigned long long> g = Undirected::CreateAdjacencyListMultipleAdjacents("graph/data/karger2.graph");
	int ret = KargersMincut(g);
	EXPECT_EQ(3, ret);
}

TEST(graph_undirected, kargers_min_cut_3)
{
	Undirected::AdjacencyList<unsigned long long> g = Undirected::CreateAdjacencyListMultipleAdjacents("graph/data/karger3.graph");
	int ret = KargersMincut(g);
	EXPECT_EQ(1, ret);
}

TEST(graph_undirected, kargers_min_cut)
{
	Undirected::AdjacencyList<unsigned long long> g = Undirected::CreateAdjacencyListMultipleAdjacents("graph/data/kargerMinCut.graph");
	int ret = KargersMincut(g);
	EXPECT_EQ(17, ret);
}

TEST(graph_undirected, BFS)
{
	AdjacencyList g = CreateAdjacencyListMultipleHeads("graph/data/rectangle.graph");
	std::map<Vertice*, int> distances = BFS(g, GetVerticeById(g,1));

	EXPECT_EQ(0, distances[GetVerticeById(g, 1)]);
	EXPECT_EQ(1, distances[GetVerticeById(g, 2)]);
	EXPECT_EQ(1, distances[GetVerticeById(g, 3)]);
	EXPECT_EQ(2, distances[GetVerticeById(g, 4)]);
	EXPECT_EQ(2, distances[GetVerticeById(g, 5)]);
	EXPECT_EQ(3, distances[GetVerticeById(g, 6)]);
}

TEST(graph_undirected, DFS)
{
	AdjacencyList g = CreateAdjacencyListMultipleHeads("graph/data/rectangle.graph");
	DFS(g, GetVerticeById(g, 1));
}

void check_subset(const std::multimap<long, Vertice*> & r, const std::set<int> & a, int l)
{
	auto range = r.equal_range(l);
	EXPECT_TRUE(distance(range.first, range.second) == a.size());
	for (auto v = range.first; v != range.second; v++)
		EXPECT_TRUE(a.end() != a.find(v->second->id));
}

TEST(graph_directed, SCC1)
{
	AdjacencyList g = CreateAdjacencyListMultipleHeads("graph/data/kosarajuTest1.graph");
	std::multimap<long, Vertice*> r = ComputeSCCs(g);

	check_subset(r, { 4, 5, 6 }, 6);
	check_subset(r, { 7, 8, 9 }, 9);
	check_subset(r, { 1, 2, 3, 10 }, 10);
}

TEST(graph_directed, SCC2)
{
	AdjacencyList g = CreateAdjacencyListMultipleHeads("graph/data/scc2.txt");
	std::multimap<long, Vertice*> r = ComputeSCCs(g);

	check_subset(r, { 7, 4, 1 }, 7);
	check_subset(r, { 8, 5, 2 }, 8);
	check_subset(r, { 9, 6, 3 }, 9);
}

TEST(graph_directed, SCC3)
{
	AdjacencyList g = CreateAdjacencyListMultipleHeads("graph/data/scc3.txt");
	std::multimap<long, Vertice*> r = ComputeSCCs(g);

	check_subset(r, {1}, 1);
	check_subset(r, {2,4,5}, 4);
	check_subset(r, {3,6}, 6);
	check_subset(r, {7,8,9,10,11,12}, 12);
}

TEST(graph_directed, SCC4)
{
	AdjacencyList g = CreateAdjacencyListMultipleHeads("graph/data/scc4.txt");
	std::multimap<long, Vertice*> r = ComputeSCCs(g);

	check_subset(r, { 2 }, 2);
	check_subset(r, { 1,3,4,6,7,9 }, 9);
	check_subset(r, { 14 }, 14);
}

TEST(graph_directed, SCC_homework)
{
	AdjacencyList g = CreateAdjacencyListMultipleHeads("graph/data/SCC.txt");
	std::multimap<long, Vertice*> components = ComputeSCCs(g);

	std::map<int, int> leaders;
	for (auto p : components)
	{
		std::map<int, int>::iterator it = leaders.find(p.first);
		if (it == leaders.end())
			leaders[p.first] = 1;
		else
			it->second++;
	}

	std::vector<std::pair<int, int> > vecLeaders;
	copy(leaders.begin(), leaders.end(), back_inserter(vecLeaders));

	sort(vecLeaders.begin(), vecLeaders.end(), [](const std::pair<int, int> & p1, const std::pair<int, int> & p2){ return p1.second > p2.second; });

	int iterCount = vecLeaders.size() > 5 ? 5 : vecLeaders.size();
	for (int i = 0; i < iterCount; i++)
	{
		std::cout << vecLeaders[i].first << " " << vecLeaders[i].second << std::endl;
	}
}

TEST(graph_weightened, Djikstra1)
{
	AdjacencyList g = CreateAdjacencyListMultipleHeadsWithHeights("graph/data/djikstra1.txt");
	std::map<Vertice*, int> paths = DijkstraNaive(g, GetVerticeById(g, 1));

	EXPECT_EQ(2, paths[GetVerticeById(g, 4)]);
}

TEST(graph_weightened, Djikstra2)
{
	AdjacencyList g = CreateAdjacencyListMultipleHeadsWithHeights("graph/data/djikstra2.txt");
	std::map<Vertice*, int> paths = DijkstraNaive(g, GetVerticeById(g, 1));

	EXPECT_EQ(5, paths[GetVerticeById(g, 7)]);
}

TEST(graph_weightened, Djikstra3)
{
	AdjacencyList g = CreateAdjacencyListMultipleHeadsWithHeights("graph/data/djikstra3.txt");
	std::map<Vertice*, int> paths = DijkstraNaive(g, GetVerticeById(g, 13));

	EXPECT_EQ(26, paths[GetVerticeById(g, 5)]);
}

TEST(graph_weightened, Djikstra4)
{
	AdjacencyList g = CreateAdjacencyListMultipleHeadsWithHeights("graph/data/djikstra4.txt");
	std::map<Vertice*, int> paths = DijkstraNaive(g, GetVerticeById(g, 28));

	EXPECT_EQ(9, paths[GetVerticeById(g, 6)]);
}

TEST(graph_weightened, DjikstraHomework)
{
	AdjacencyList g = CreateAdjacencyListMultipleHeadsWithHeights("graph/data/dijkstraData.txt");
	std::map<Vertice*, int> paths = DijkstraNaive(g, GetVerticeById(g, 1));

	std::cout << paths[GetVerticeById(g, 7)] << ",";
	std::cout << paths[GetVerticeById(g, 37)] << ",";
	std::cout << paths[GetVerticeById(g, 59)] << ",";
	std::cout << paths[GetVerticeById(g, 82)] << ",";
	std::cout << paths[GetVerticeById(g, 99)] << ",";
	std::cout << paths[GetVerticeById(g, 115)] << ",";
	std::cout << paths[GetVerticeById(g, 133)] << ",";
	std::cout << paths[GetVerticeById(g, 165)] << ",";
	std::cout << paths[GetVerticeById(g, 188)] << ",";
	std::cout << paths[GetVerticeById(g, 197)] << std::endl;
}

TEST(graph_directed, 2Sat1)
{
	EXPECT_TRUE(Check2SATSatisfiability(CreateAdjacency2SAT("graph/data/2satt1.txt")));
}

TEST(graph_directed, 2Sat2)
{
	EXPECT_TRUE(Check2SATSatisfiability(CreateAdjacency2SAT("graph/data/2satt2.txt")));
}

TEST(graph_directed, 2Sat3)
{
	EXPECT_FALSE(Check2SATSatisfiability(CreateAdjacency2SAT("graph/data/2satt3.txt")));
}

TEST(graph_directed, 2Sat4)
{
	EXPECT_TRUE(Check2SATSatisfiability(CreateAdjacency2SAT("graph/data/2satt4.txt")));
}

TEST(graph_directed, 2Sat5)
{
	EXPECT_TRUE(Check2SATSatisfiability(CreateAdjacency2SAT("graph/data/2satt5.txt")));
}

TEST(graph_directed, 2Sat6)
{
	EXPECT_TRUE(Check2SATSatisfiability(CreateAdjacency2SAT("graph/data/2satt6.txt")));
}

TEST(graph_directed, 2Sat7)
{
	EXPECT_TRUE(Check2SATSatisfiability(CreateAdjacency2SAT("graph/data/2satt7.txt")));
}

TEST(graph_directed, 2Sat8)
{
	EXPECT_TRUE(Check2SATSatisfiability(CreateAdjacency2SAT("graph/data/2satt8.txt")));
}

TEST(graph_directed, 2Sat9)
{
	EXPECT_FALSE(Check2SATSatisfiability(CreateAdjacency2SAT("graph/data/2satt9.txt")));
}

TEST(graph_directed, 2Sat10)
{
	EXPECT_TRUE(Check2SATSatisfiability(CreateAdjacency2SAT("graph/data/2satt10.txt")));
}

TEST(graph_directed, 2Sat11)
{
	EXPECT_FALSE(Check2SATSatisfiability(CreateAdjacency2SAT("graph/data/2satt11.txt")));
}

TEST(graph_directed, 2Sat12)
{
	EXPECT_TRUE(Check2SATSatisfiability(CreateAdjacency2SAT("graph/data/2satt12.txt")));
}

TEST(graph_directed, 2SatHW)
{
	AdjacencyList g1 = CreateAdjacency2SAT("graph/data/2sat1.txt");
	AdjacencyList g2 = CreateAdjacency2SAT("graph/data/2sat2.txt");
	AdjacencyList g3 = CreateAdjacency2SAT("graph/data/2sat3.txt");
	AdjacencyList g4 = CreateAdjacency2SAT("graph/data/2sat4.txt");
	AdjacencyList g5 = CreateAdjacency2SAT("graph/data/2sat5.txt");
	AdjacencyList g6 = CreateAdjacency2SAT("graph/data/2sat6.txt");
	
	bool bg1 = Check2SATSatisfiability(g1);
	bool bg2 = Check2SATSatisfiability(g2);
	bool bg3 = Check2SATSatisfiability(g3);
	bool bg4 = Check2SATSatisfiability(g4);
	bool bg5 = Check2SATSatisfiability(g5);
	bool bg6 = Check2SATSatisfiability(g6);

	std::cout << "HW 2sat scc: " << bg1 << " " << bg2 << " " << bg3 << " " << bg4 << " " << bg5 << " " << bg6 << std::endl;
	// 101100
}