#include "greedy.h"

#include <string>
#include <vector>
#include <fstream>
#include <cassert>
#include <sstream>
#include <map>
#include <algorithm>

std::vector<job> ReadJobInput(const std::string & fileName)
{
	std::vector<job> data;
	std::ifstream f(fileName);
	assert(f.is_open());

	std::string line;
	while(std::getline(f, line))
	{
		std::stringstream ss(line);

		job b;
		ss >> b.weight;
		ss >> b.length;
		data.push_back(std::move(b));
	}

	return data;
}

long long ScheduleByDifference(std::vector<job> & data)
{
	std::sort(data.begin(), data.end(), [](const job &a, const job &b) 
	{
		int wa = a.weight - a.length;
		int wb = b.weight - b.length;

		if (wa < wb)
			return false;
		else if (wa > wb)
			return true;

		return a.weight > b.weight;
	});

	long long ret = 0;
	long long c = 0;

	for (const auto & j : data)
	{
		c += j.length;
		ret += c*j.weight;
	}

	return ret;
}

typedef float FLOATING;

long long ScheduleByRatio(std::vector<job> & data)
{
	std::sort(data.begin(), data.end(), [](const job &a, const job &b)
	{
		float ra = (float)a.weight / (float)a.length;
		float rb = (float)b.weight / (float)b.length;

		return ra > rb;
	});

	long long ret = 0;
	long long c = 0;

	for (const auto & j : data)
	{
		c += j.length;
		ret += c*j.weight;
	}

	return ret;
}

