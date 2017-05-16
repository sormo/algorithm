#include "common.h"
#include <fstream>

std::vector<char> ConvertToDigits(const std::string & n)
{
	std::vector<char> ret;
	for (auto c : n)
		ret.push_back(c - '0');
	return ret;
}

std::string ConvertFromDigits(const std::vector<char> & n)
{
	std::string ret;
	for (auto c : n)
		ret.push_back(c + '0');
	return ret;
}

std::vector<char> AddNumbers(const std::vector<char> & a, const std::vector<char> & b)
{
	std::vector<char> ret;

	char c = 0;
	for (size_t i = 0; i < std::max(a.size(), b.size()); i++)
	{
		int idx = a.size() - 1 - i;
		if (idx >= 0)
			c += a[idx];
		
		idx = b.size() - 1 - i;
		if (idx >= 0)
			c += b[idx];

		ret.push_back(c % 10);
		c /= 10;
	}
	if (c)
		ret.push_back(c);

	std::reverse(ret.begin(), ret.end());

	return ret;
}

std::vector<char> SubNumbers(const std::vector<char> & a, const std::vector<char> & b)
{
	char c = 0;
	std::vector<char> ret = a;
	for (size_t i = 0; i < b.size(); i++)
	{
		int idxb = b.size() - 1 - i;
		int idxa = a.size() - 1 - i;

		if (ret[idxa] >= b[idxb])
		{
			ret[idxa] -= b[idxb];
		}
		else
		{
			int tmp = idxa - 1;
			while (!ret[tmp])
			{
				ret[tmp] = 9;
				tmp--;
			}
			ret[tmp]--;
			ret[idxa] += 10;
			ret[idxa] -= b[idxb];
		}
	}

	return ret;
}

std::vector<unsigned int> ReadNumbersToVector(const std::string & file)
{
	std::ifstream f(file);
	std::vector<unsigned int> ret;
	unsigned int n;

	while (f.good())
	{
		f >> n;

		if (f.fail())
			break;

		ret.push_back(n);
	}

	return ret;
}
