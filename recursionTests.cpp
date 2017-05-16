#include "gtest\gtest.h"
#include "recursion\recursion.h"
#include "common\common.h"

TEST(recursion, mergesort1)
{
	std::vector<int> test = { 10,3,4,7,1,2,8,9,6,5 };

	Mergesort<int>(test);

	EXPECT_EQ(1, test[0]);
	EXPECT_EQ(2, test[1]);
	EXPECT_EQ(3, test[2]);
	EXPECT_EQ(4, test[3]);
	EXPECT_EQ(5, test[4]);
	EXPECT_EQ(6, test[5]);
	EXPECT_EQ(7, test[6]);
	EXPECT_EQ(8, test[7]);
	EXPECT_EQ(9, test[8]);
}

TEST(recursion, quicksort1)
{
	std::vector<int> test = { 10,3,4,7,1,2,8,9,6,5 };

	Quicksort<int>(test);

	EXPECT_EQ(1, test[0]);
	EXPECT_EQ(2, test[1]);
	EXPECT_EQ(3, test[2]);
	EXPECT_EQ(4, test[3]);
	EXPECT_EQ(5, test[4]);
	EXPECT_EQ(6, test[5]);
	EXPECT_EQ(7, test[6]);
	EXPECT_EQ(8, test[7]);
	EXPECT_EQ(9, test[8]);
}

TEST(recursion, quicksortHW1)
{
	std::vector<unsigned int> arr = ReadNumbersToVector("recursion\\data\\QuickSort1.txt");

	Quicksort<unsigned int>(arr);
}

TEST(recursion, karatsuba)
{
	// TODO
	auto a = KaratsubaMultiply("46", "134");
	//auto a = KaratsubaMultiply("1234","5678");
}

TEST(recursion, inversions1)
{
	std::vector<unsigned int> arr1 = { 8, 7, 6 ,5, 4, 3, 2, 1 };
	// there shoudl be n choose 2 inversions (number of different pairs) = n*(n-1)/2 = 28
	EXPECT_EQ(28, CountNumberOfInversions(arr1));

	std::vector<unsigned int> arr2 = { 1, 3, 5, 2, 4, 6 };
	EXPECT_EQ(3, CountNumberOfInversions(arr2));

	std::vector<unsigned int> arr3 = { 1, 5, 3, 2, 4 };
	EXPECT_EQ(4, CountNumberOfInversions(arr3));

	std::vector<unsigned int> arr4 = { 1, 6, 3, 2, 4, 5 };
	EXPECT_EQ(5, CountNumberOfInversions(arr4));

	std::vector<unsigned int> arr5 = { 4, 80, 70, 23, 9, 60, 68, 27, 66, 78, 12, 40, 52, 53, 44, 8, 49, 28, 18, 46, 21, 39, 51, 7, 87, 99, 69, 62, 84, 6, 79, 67, 14, 98, 83, 0, 96, 5, 82, 10, 26, 48, 3, 2, 15, 92, 11, 55, 63, 97, 43, 45, 81, 42, 95, 20, 25, 74, 24, 72, 91, 35, 86, 19, 75, 58, 71, 47, 76, 59, 64, 93, 17, 50, 56, 94, 90, 89, 32, 37, 34, 65, 1, 73, 41, 36, 57, 77, 30, 22, 13, 29, 38, 16, 88, 61, 31, 85, 33, 54 };
	EXPECT_EQ(2372, CountNumberOfInversions(arr5));

	auto arr_hw = ReadNumbersToVector("recursion\\data\\inversions-homework.txt");
	EXPECT_EQ(2407905288, CountNumberOfInversions(arr_hw));
}
