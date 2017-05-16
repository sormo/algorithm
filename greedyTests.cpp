#include "gtest/gtest.h"

#include "greedy/greedy.h"
#include <iostream>

// *** scheduling ***

TEST(scheduling, homework1)
{
	auto data = ReadJobInput("greedy\\data\\schedule1.txt");

	EXPECT_EQ(11336, ScheduleByDifference(data));
	EXPECT_EQ(10548, ScheduleByRatio(data));
}

TEST(scheduling, homework2)
{
	auto data = ReadJobInput("greedy\\data\\schedule2.txt");

	EXPECT_EQ(145924, ScheduleByDifference(data));
	EXPECT_EQ(138232, ScheduleByRatio(data));
}

TEST(scheduling, homework3)
{
	auto data = ReadJobInput("greedy\\data\\schedule3.txt");

	EXPECT_EQ(23, ScheduleByDifference(data));
	EXPECT_EQ(22, ScheduleByRatio(data));
}

TEST(scheduling, homeworkReal)
{
	auto data = ReadJobInput("greedy\\data\\jobs1.txt");
	std::cout << "hw1: " << ScheduleByDifference(data) << std::endl;
	std::cout << "hw2: " << ScheduleByRatio(data) << std::endl;
}

// *** Prims ***

TEST(MST, primsNaive)
{
	EXPECT_EQ(2624, CountEdgeWeights(ComputePrimsMSTNaive(CreateAdjacencyList("greedy\\data\\prims1.txt"))));
	EXPECT_EQ(-351, CountEdgeWeights(ComputePrimsMSTNaive(CreateAdjacencyList("greedy\\data\\prims3.txt"))));
}

TEST(MST, primsHomework)
{
	std::cout << "prims hw: " << CountEdgeWeights(ComputePrimsMSTNaive(CreateAdjacencyList("greedy\\data\\edges.txt"))) << std::endl;
}

// *** clustering ***

TEST(clustering, test1)
{
	EXPECT_EQ(134365, Cluster(4, ReadClusterInput("greedy\\data\\clustering1.txt")));
}

TEST(clustering, test2)
{
	EXPECT_EQ(7, Cluster(4, ReadClusterInput("greedy\\data\\clustering2.txt")));
}

TEST(clustering, test3)
{
	EXPECT_EQ(5, Cluster(4, ReadClusterInput("greedy\\data\\clustering3.txt")));
}

TEST(clustering, test4)
{
	EXPECT_EQ(27, Cluster(4, ReadClusterInput("greedy\\data\\clustering4.txt")));
}

TEST(clustering, test5)
{
	EXPECT_EQ(2, Cluster(4, ReadClusterInput("greedy\\data\\clustering5.txt")));
}

TEST(clustering, test6)
{
	EXPECT_EQ(161, Cluster(3, ReadClusterInput("greedy\\data\\clustering6.txt")));
}

TEST(clustering, test7)
{
	EXPECT_EQ(5, Cluster(2, ReadClusterInput("greedy\\data\\clustering7.txt")));
}

TEST(clustering, clusterHW1)
{
	EXPECT_EQ(106, Cluster(4, ReadClusterInput("greedy\\data\\clustering_HW.txt")));
}

/*
TEST(clustering, clusterBin1)
{
	clusterBin(3, readClusterBinInput("greedy\\data\\clusteringBin_1.txt"));
}
*/

TEST(clustering, clusterBin2)
{
	EXPECT_EQ(1, ClusterBin(5, ReadClusterBinInput("greedy\\data\\clusteringBin_2.txt")));
}

TEST(clustering, clusterBin3)
{
	EXPECT_EQ(1, ClusterBin(6, ReadClusterBinInput("greedy\\data\\clusteringBin_3.txt")));
}

TEST(clustering, clusterBin4)
{
	EXPECT_EQ(2, ClusterBin(9, ReadClusterBinInput("greedy\\data\\clusteringBin_4.txt")));
}

TEST(clustering, clusterBin5)
{
	EXPECT_EQ(2, ClusterBin(7, ReadClusterBinInput("greedy\\data\\clusteringBin_5.txt")));
}

TEST(clustering, clusterBin6)
{
	EXPECT_EQ(11, ClusterBin(9, ReadClusterBinInput("greedy\\data\\clusteringBin_6.txt")));
}

TEST(clustering, clusterBin7)
{
	EXPECT_EQ(4, ClusterBin(8, ReadClusterBinInput("greedy\\data\\clusteringBin_7.txt")));
}

TEST(clustering, clusterBin8)
{
	EXPECT_EQ(6, ClusterBin(8, ReadClusterBinInput("greedy\\data\\clusteringBin_8.txt")));
}

TEST(clustering, clusterBinHW)
{
	EXPECT_EQ(6118, ClusterBin(24, ReadClusterBinInput("greedy\\data\\clusteringBin_big.txt")));
}

TEST(huffman, huffman1)
{
	auto t = HuffmanEncoding({0.28f,0.27f,0.2f,0.15f,0.1f});
}