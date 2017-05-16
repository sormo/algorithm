#include "gtest/gtest.h"
#include "datastruct\heap.h"
#include <fstream>
#include "datastruct\datastruct.h"

TEST(hash, test1)
{
	std::ifstream in("datastruct/data/hashTest.txt");
	ASSERT_TRUE(in.is_open());

	std::set<long long> values;
	std::string line;
	while (std::getline(in, line))
		values.insert(stoll(line));

	std::set<long long> sums;
	/*for (auto x : values)
	{
		set<long long>::iterator v = values.upper_bound(-10000 - x - 1);
		while (v != values.end() && *v <= 10000 - x)
		{
			sums.insert(x + *v);
			v++;
		}
	}*/
	for (auto x : values)
	{
		for (auto y : values)
		{
			long long sum = x + y;
			if (sum >= -10000 && sum <= 10000)
				sums.insert(sum);
		}
	}

	EXPECT_EQ(6, sums.size());
}

TEST(hash, homework)
{
	std::ifstream in("datastruct/data/algo1_programming_prob_2sum.txt");
	ASSERT_TRUE(in.is_open());

	std::set<long long> values;
	std::string line;
	while (std::getline(in, line))
		values.insert(stoll(line));

	std::set<long long> sums;
	for (auto x : values)
	{
		std::set<long long>::iterator v = values.upper_bound(-10000 - x - 1);
		while (v != values.end() && *v <= 10000 - x)
		{
			sums.insert(x + *v);
			v++;
		}
	}
	/*for (auto x : values)
	{
		for (auto y : values)
		{
			long long sum = x + y;
			if (sum >= -10000 && sum <= 10000)
				sums.insert(sum);
		}
	}*/

	EXPECT_EQ(427, sums.size());
}

TEST(heap, extractMin)
{
	Heap<int> t;
	std::vector<int> inputArray{5,8,1,7,4,9,2};

	for (auto v : inputArray)
		t.Push(v);

	int val = 0;

	EXPECT_TRUE(t.Pop(val));
	EXPECT_EQ(1, val);

	EXPECT_TRUE(t.Pop(val));
	EXPECT_EQ(2, val);

	EXPECT_TRUE(t.Pop(val));
	EXPECT_EQ(4, val);

	EXPECT_TRUE(t.Pop(val));
	EXPECT_EQ(5, val);

	EXPECT_TRUE(t.Pop(val));
	EXPECT_EQ(7, val);

	EXPECT_TRUE(t.Pop(val));
	EXPECT_EQ(8, val);

	EXPECT_TRUE(t.Pop(val));
	EXPECT_EQ(9, val);

	EXPECT_FALSE(t.Pop(val));
}

TEST(heap, extractMax)
{
	Heap<int, std::greater<int>> t;
	std::vector<int> inputArray{5,8,1,7,4,9,2};

	for (auto v : inputArray)
		t.Push(v);

	int val = 0;

	EXPECT_TRUE(t.Pop(val));
	EXPECT_EQ(9, val);

	EXPECT_TRUE(t.Pop(val));
	EXPECT_EQ(8, val);

	EXPECT_TRUE(t.Pop(val));
	EXPECT_EQ(7, val);

	EXPECT_TRUE(t.Pop(val));
	EXPECT_EQ(5, val);

	EXPECT_TRUE(t.Pop(val));
	EXPECT_EQ(4, val);

	EXPECT_TRUE(t.Pop(val));
	EXPECT_EQ(2, val);

	EXPECT_TRUE(t.Pop(val));
	EXPECT_EQ(1, val);

	EXPECT_FALSE(t.Pop(val));
}

TEST(heap, extractMin2)
{
	Heap<float> t;
	std::vector<float> inputArray{ 0.5f,0.8f,0.1f,0.7f,0.4f,0.9f,0.2f };

	for (auto v : inputArray)
		t.Push(v);

	float val = 0.0f;

	EXPECT_TRUE(t.Pop(val));
	EXPECT_FLOAT_EQ(0.1f, val);

	EXPECT_TRUE(t.Pop(val));
	EXPECT_FLOAT_EQ(0.2f, val);

	EXPECT_TRUE(t.Pop(val));
	EXPECT_FLOAT_EQ(0.4f, val);

	EXPECT_TRUE(t.Pop(val));
	EXPECT_FLOAT_EQ(0.5f, val);

	EXPECT_TRUE(t.Pop(val));
	EXPECT_FLOAT_EQ(0.7f, val);

	EXPECT_TRUE(t.Pop(val));
	EXPECT_FLOAT_EQ(0.8f, val);

	EXPECT_TRUE(t.Pop(val));
	EXPECT_FLOAT_EQ(0.9f, val);

	EXPECT_FALSE(t.Pop(val));
}

TEST(heap, extractMax2)
{
	Heap<float, std::greater<float>> t;
	std::vector<float> inputArray{ 0.5f,0.8f,0.1f,0.7f,0.4f,0.9f,0.2f };

	for (auto v : inputArray)
		t.Push(v);

	float val = 0.0f;

	EXPECT_TRUE(t.Pop(val));
	EXPECT_FLOAT_EQ(0.9f, val);

	EXPECT_TRUE(t.Pop(val));
	EXPECT_FLOAT_EQ(0.8f, val);

	EXPECT_TRUE(t.Pop(val));
	EXPECT_FLOAT_EQ(0.7f, val);

	EXPECT_TRUE(t.Pop(val));
	EXPECT_FLOAT_EQ(0.5f, val);

	EXPECT_TRUE(t.Pop(val));
	EXPECT_FLOAT_EQ(0.4f, val);

	EXPECT_TRUE(t.Pop(val));
	EXPECT_FLOAT_EQ(0.2f, val);

	EXPECT_TRUE(t.Pop(val));
	EXPECT_FLOAT_EQ(0.1f, val);

	EXPECT_FALSE(t.Pop(val));
}

/*TEST(heap, vertices)
{
	HeapWithCall<WVertice*, decltype(mem_fn(&WVertice::id)), heapType::min> heapver(&WVertice::id);
	WGraph wg;
	wg.initFromFileEx("graph/data/djikstra1.graph");

	for (auto v : wg.vertices())
		heapver.insert(v);

	WVertice * val;

	EXPECT_TRUE(heapver.Pop(val));
	EXPECT_EQ(1, val->id());
}*/

TEST(heap, medianMaintenance1)
{
	std::ifstream in("datastruct/data/median1.txt");
	if (!in.is_open())
		return;

	std::vector<int> values;

	std::string line;
	while (std::getline(in, line))
	{
		int num = std::stoi(line);
		values.push_back(num);
	}

	std::vector<int> medians = MedianMaintenance<int>(values);

	int sum = 0;
	for (auto v : medians)
		sum += v;
	EXPECT_EQ(23, sum);
}

TEST(heap, medianMaintenance2)
{
	std::ifstream in("datastruct/data/median2.txt");
	if (!in.is_open())
		return;

	std::vector<int> values;

	std::string line;
	while (getline(in, line))
	{
		int num = std::stoi(line);
		values.push_back(num);
	}

	std::vector<int> medians = MedianMaintenance<int>(values);

	int sum = 0;
	for (auto v : medians)
		sum += v;
	EXPECT_EQ(55, sum);
}

TEST(heap, medianMaintenance3)
{
	std::ifstream in("datastruct/data/median3.txt");
	if (!in.is_open())
		return;

	std::vector<int> values;

	std::string line;
	while (std::getline(in, line))
	{
		int num = stoi(line);
		values.push_back(num);
	}

	std::vector<int> medians = MedianMaintenance<int>(values);

	int sum = 0;
	for (auto v : medians)
		sum = sum + v;
	EXPECT_EQ(148, sum);
}

TEST(heap, medianMaintenanceHomeWork)
{
	std::ifstream in("datastruct/data/Median.txt");
	if (!in.is_open())
		return;

	std::vector<int> values;

	std::string line;
	while (std::getline(in, line))
	{
		int num = stoi(line);
		values.push_back(num);
	}

	std::vector<int> medians = MedianMaintenance<int>(values);

	unsigned long long sum = 0;
	for (auto m : medians)
		sum += m;

	std::cout << "Medians: " << sum << std::endl;
	std::cout << "Modulo: " << (sum % 10000) << std::endl;

}
