#include "gtest/gtest.h"

#include "dynamic/dynamic.h"
#include <iostream>
#include "common\common.h"

TEST(dynamic, weightedIS1)
{
	std::vector<DNUM> in{5,1,5,1,5};
	std::vector<DNUM> ret = IndependentSets(in);

	EXPECT_EQ(3, ret.size());
	for (DNUM n : ret)
		EXPECT_EQ(5,n);
}

TEST(dynamic, weightedIS2)
{
	std::vector<DNUM> in{5,4,3,2,1};
	std::vector<DNUM> ret = IndependentSets(in);

	ASSERT_EQ(3, ret.size());
	EXPECT_EQ(5,ret[0]);
	EXPECT_EQ(3,ret[1]);
	EXPECT_EQ(1,ret[2]);
}

TEST(dynamic, weightedIS3)
{
	std::vector<DNUM> in{5,100,3,2,1};
	std::vector<DNUM> ret = IndependentSets(in);
	
	ASSERT_EQ(2, ret.size());
	EXPECT_EQ(100, ret[0]);
	EXPECT_EQ(2, ret[1]);
}

TEST(dynamic, weightedIS4)
{
	std::vector<DNUM> in{ 5,5,5,100,99,2,99 };
	std::vector<DNUM> ret = IndependentSets(in);

	ASSERT_EQ(4, ret.size());
	EXPECT_EQ(5, ret[0]);
	EXPECT_EQ(5, ret[1]);
	EXPECT_EQ(99, ret[2]);
	EXPECT_EQ(99, ret[3]);
}

#define computeKnapsack ComputeKnapsackOpt

TEST(dynamic, knapsack1)
{
	EXPECT_EQ(4, computeKnapsack(5, ReadKnapsackInput("dynamic\\data\\knap1.txt")));
}

TEST(dynamic, knapsack2)
{
	EXPECT_EQ(8, computeKnapsack(6, ReadKnapsackInput("dynamic\\data\\knap2.txt")));
}

TEST(dynamic, knapsack3)
{
	EXPECT_EQ(60, computeKnapsack(100, ReadKnapsackInput("dynamic\\data\\knap3.txt")));
}

TEST(dynamic, knapsack4)
{
	EXPECT_EQ(27000, computeKnapsack(6, ReadKnapsackInput("dynamic\\data\\knap4.txt")));
}

TEST(dynamic, knapsackHW1)
{
	std::cout << std::endl << "HW1: " << computeKnapsack(10000, ReadKnapsackInput("dynamic\\data\\knapsackHW.txt")) << std::endl;
}

TEST(dynamic, knapsackHW2)
{
	std::cout << std::endl << "HW2: " << computeKnapsack(2000000, ReadKnapsackInput("dynamic\\data\\knapsackHW2.txt")) << std::endl;
}

#undef computeKnapsack

TEST(dynamic, FloydWarshall)
{
	FloydWarshall(CreateAdjacencyList("dynamic\\data\\floydWarshall1.txt"));
}

TEST(dynamic, bellmanFord1)
{
	AdjacencyList G = CreateAdjacencyList("dynamic\\data\\bellmanFord1.txt");
	Vertice * S = GetVerticeById(G, 1);
	Vertice * D = GetVerticeById(G, 5);

	BellmanFordVariation(G, S, D);
	// 1 -> 2 -> 4 -> 5
}

TEST(dynamic, allPair1)
{
	EXPECT_EQ(-2, FloydWarshall(CreateAdjacencyList("dynamic\\data\\allpair1.txt")));
	EXPECT_EQ(-2, AllPairBellmanFord(CreateAdjacencyList("dynamic\\data\\allpair1.txt")));
}

TEST(dynamic, allPair2)
{
	EXPECT_EQ(-4, FloydWarshall(CreateAdjacencyList("dynamic\\data\\allpair2.txt")));
	EXPECT_EQ(-4, AllPairBellmanFord(CreateAdjacencyList("dynamic\\data\\allpair2.txt")));
}

TEST(dynamic, allPair3)
{
	//EXPECT_EQ(std::numeric_limits<int>::max(), floydWarshall(CreateAdjacencyList("dynamic\\data\\allpair3.txt")));
	EXPECT_EQ(std::numeric_limits<int>::max(), AllPairBellmanFord(CreateAdjacencyList("dynamic\\data\\allpair3.txt")));
}

TEST(dynamic, allPair4)
{
	EXPECT_EQ(-6, FloydWarshall(CreateAdjacencyList("dynamic\\data\\allpair4.txt")));
	EXPECT_EQ(-6, AllPairBellmanFord(CreateAdjacencyList("dynamic\\data\\allpair4.txt")));
}

TEST(dynamic, allPair5)
{
	EXPECT_EQ(-5, FloydWarshall(CreateAdjacencyList("dynamic\\data\\allpair5.txt")));
	EXPECT_EQ(-5, AllPairBellmanFord(CreateAdjacencyList("dynamic\\data\\allpair5.txt")));
}

TEST(dynamic, allPair6)
{
	EXPECT_EQ(-9, FloydWarshall(CreateAdjacencyList("dynamic\\data\\allpair6.txt")));
	EXPECT_EQ(-9, AllPairBellmanFord(CreateAdjacencyList("dynamic\\data\\allpair6.txt")));
}

TEST(dynamic, allPair7)
{
	//EXPECT_EQ(numeric_limits<int>::max(), floydWarshall(CreateAdjacencyList("dynamic\\data\\allpair7.txt")));
	EXPECT_EQ(std::numeric_limits<int>::max(), AllPairBellmanFord(CreateAdjacencyList("dynamic\\data\\allpair7.txt")));
}

TEST(dynamic, allPairHW)
{
	std::cout << "g1: " << AllPairBellmanFord(CreateAdjacencyList("dynamic\\data\\g1hw.txt")) << std::endl;
	std::cout << "g2: " << AllPairBellmanFord(CreateAdjacencyList("dynamic\\data\\g2hw.txt")) << std::endl;
	std::cout << "g3: " << AllPairBellmanFord(CreateAdjacencyList("dynamic\\data\\g3hw.txt")) << std::endl;
}

const float g_error = 0.1f;

TEST(dynamic, tsp0)
{
	ASSERT_NEAR(2.618f, TravelingSalesman(Undirected::CreateAdjacencyListFromPoints("dynamic\\data\\tsp0.txt")), g_error);
}

TEST(dynamic, tsp1)
{

	ASSERT_NEAR(6.17986f, TravelingSalesman(Undirected::CreateAdjacencyListFromPoints("dynamic\\data\\tsp1.txt")), g_error);
}

TEST(dynamic, tsp2)
{
	ASSERT_NEAR(6.26533f, TravelingSalesman(Undirected::CreateAdjacencyListFromPoints("dynamic\\data\\tsp2.txt")), g_error);
}

TEST(dynamic, tsp3)
{
	ASSERT_NEAR(std::round(124.966f), std::round(TravelingSalesman(Undirected::CreateAdjacencyListFromPoints("dynamic\\data\\tsp3.txt"))), g_error);
}

TEST(dynamic, tsp4)
{
	ASSERT_NEAR(16898.1f, TravelingSalesman(Undirected::CreateAdjacencyListFromPoints("dynamic\\data\\tsp4.txt")), g_error);
}

TEST(dynamic, tsp5)
{
	ASSERT_NEAR(26714.9f, TravelingSalesman(Undirected::CreateAdjacencyListFromPoints("dynamic\\data\\tsp5.txt")), g_error);
}

TEST(dynamic, tspHWex)
{
	float val = TravelingSalesman(Undirected::CreateAdjacencyListFromPoints("dynamic\\data\\tspHWex.txt"));

	val -= 1202.91f;
	val += 1173.08f;
	val += 1330.83f;
	val += 620.26f;
	val += 1243.87f;
	val += 2073.38f;

	ASSERT_NEAR(26442.7, val, g_error);
}

TEST(dynamic, DISABLED_tspHW)
{
	ASSERT_NEAR(26442.7, TravelingSalesman(Undirected::CreateAdjacencyListFromPoints("dynamic\\data\\tspHW.txt")), g_error);
}

TEST(dynamic, sequence0)
{
	ASSERT_EQ(0, apply_from_tuple(SequenceAlignment, ReadSequenceAlignmentInput("dynamic\\data\\sequence0.txt")));
}

TEST(dynamic, sequence1)
{
	ASSERT_EQ(10, apply_from_tuple(SequenceAlignment, ReadSequenceAlignmentInput("dynamic\\data\\sequence1.txt")));
}

TEST(dynamic, sequence2)
{
	ASSERT_EQ(80, apply_from_tuple(SequenceAlignment, ReadSequenceAlignmentInput("dynamic\\data\\sequence2.txt")));
}

TEST(dynamic, sequence3)
{
	ASSERT_EQ(30, apply_from_tuple(SequenceAlignment, ReadSequenceAlignmentInput("dynamic\\data\\sequence3.txt")));
}

TEST(dynamic, sequence4)
{
	ASSERT_EQ(5, apply_from_tuple(SequenceAlignment, ReadSequenceAlignmentInput("dynamic\\data\\sequence4.txt")));
}

TEST(dynamic, optimalBST0)
{
	/*
	    0       1       2       3       4       5       6
	0 00.2(0) 00.3(0) 0.69(0) 0.92(2) 1.42(2) 1.51(2) 2.23(4)
	1 0000(0) 0.05(1) 0.27(2) 0.47(2) 0.97(2) 1.05(4) 1.58(4)
	2 0000(0) 0000(0) 0.17(2) 0.37(2) 0.84(3) 00.9(4) 1.43(4)
	3 0000(0) 0000(0) 0000(0) 00.1(3) 00.4(4) 0.46(4) 0.99(4)
	4 0000(0) 0000(0) 0000(0) 0000(0) 00.2(4) 0.26(4) 0.74(6)
	5 0000(0) 0000(0) 0000(0) 0000(0) 0000(0) 0.03(5) 0.31(6)
	6 0000(0) 0000(0) 0000(0) 0000(0) 0000(0) 0000(0) 0.25(6)

	0->6 root is 4
	0->4 root is 2 5->6 root is 6

						(4)
					   /   \
					(2)     (6)
					/ \     /
				  (0) (3) (5)
					\
					(1)

	1*0.2 + 2*0.17 + 2*0.25 + 3*0.2 + 3*0.1 + 3*0.03 + 4*0.05 = 2.23
	*/
	ASSERT_NEAR(2.23f, std::get<0>(OptimalBSTEx(ReadOptimalBSTInput("dynamic\\data\\optimalBST0.txt"))), 0.01f);
}

TEST(dynamic, matrixChain0)
{
	ASSERT_EQ(124, std::get<0>(MatrixChainMultiplication({2,3,6,4,5})));
}