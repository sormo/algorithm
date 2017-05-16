#include "dynamic.h"
#include <algorithm>
#include <fstream>
#include <cassert>

// sequence alignment
//
// input: two strings A and B which should be aligned, penalty for gap and for mismatch of two letters
// output: strings A' and B' which has same length with gaps and has minimal overal penalty
//         gaps inserted on correct places into A and B

std::tuple<std::string, std::string, long, long> ReadSequenceAlignmentInput(const std::string & file)
{
	std::string str1;
	std::string str2;
	long gapPenalty;
	long mismatchPenalty;

	std::ifstream f(file);
	assert(f.is_open());

	std::string line;

	std::getline(f, line);
	gapPenalty = std::atol(line.c_str());

	std::getline(f, line);
	mismatchPenalty = std::atol(line.c_str());

	std::getline(f, str1);
	std::getline(f, str2);

	return { str1, str2, gapPenalty, mismatchPenalty };
}

std::tuple<long, std::string, std::string> SequenceAlignmentEx(const std::string & str1, const std::string & str2, long gapPenalty, std::function<long(char, char)> mismatchPenalty)
{
	// [i][j] penalty after aligning first i and j letters from str1 and str2 strings (1-based)
	std::vector<std::vector<long>> A(str1.size() + 1, std::vector<long>(str2.size() + 1, std::numeric_limits<long>::max()));

	// initialization (when 0 is allowed from either string only gaps are used)
	for (size_t i = 0; i <= str1.size(); ++i)
		A[i][0] = i*gapPenalty;
	for (size_t j = 0; j <= str2.size(); ++j)
		A[0][j] = j*gapPenalty;

	for (size_t i = 1; i <= str1.size(); ++i)
	{
		for (size_t j = 1; j <= str2.size(); ++j)
		{
			A[i][j] = std::min({ A[i-1][j-1] + mismatchPenalty(str1[i-1], str2[j-1]), A[i][j-1] + gapPenalty, A[i-1][j] + gapPenalty });
		}
	}

	// ---

	// reconstruction
	std::string str1r;
	std::string str2r;
	size_t i = str1.size(), j = str2.size();
	while(i > 0 && j > 0)
	{
		if (A[i][j] - mismatchPenalty(str1[i - 1], str2[j - 1]) == A[i - 1][j - 1])
		{
			str1r.push_back(str1[i - 1]);
			str2r.push_back(str2[j - 1]);
			i--;
			j--;
		}
		else if (A[i][j] - gapPenalty == A[i - 1][j])
		{
			str1r.push_back(str1[i - 1]);
			str2r.push_back('_');
			i--;
		}
		else if (A[i][j] - gapPenalty == A[i][j - 1])
		{
			str2r.push_back(str2[j - 1]);
			str1r.push_back('_');
			j--;
		}
	}

	while (i > 0) { str1r.push_back(str1[i - 1]); str2r.push_back('_'); i--; }
	while (j > 0) { str2r.push_back(str2[j - 1]); str1r.push_back('_'); j--; }

	std::reverse(std::begin(str1r), std::end(str1r));
	std::reverse(std::begin(str2r), std::end(str2r));

	return{ A[str1.size()][str2.size()], str1r, str2r };
}

long SequenceAlignment(const std::string & str1, const std::string & str2, long gapPenalty, long mismatchPenalty)
{
	return std::get<0>(SequenceAlignmentEx(str1, str2, gapPenalty, [mismatchPenalty](char c1, char c2) { return c1 == c2 ? 0 : mismatchPenalty; }));
}