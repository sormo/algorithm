#include "undirectedAdjacencyList.h"

#include <fstream>
#include <cassert>
#include <sstream>
#include <vector>
#include <tuple>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <regex>

namespace Undirected
{
	AdjacencyList<float> CreateAdjacencyListFromPoints(std::string file)
	{
		AdjacencyList<float> ret;

		std::ifstream infile(file);
		assert(infile.is_open());

		int idCounter = 1;
		std::string line;
		std::vector<std::tuple<float, float, Vertice<float>*>> verts;
		while (std::getline(infile, line))
		{
			std::stringstream sline(line);
			float x, y;

			sline >> x;
			sline >> y;

			Vertice<float> * v = new Vertice<float>(idCounter++);
			ret.vertices.push_back(v);

			for (auto & vt : verts)
			{
				Edge<float> * e = new Edge<float>;
				e->vertex1 = v;
				e->vertex2 = std::get<2>(vt);
				e->weigth = sqrt(pow(x - std::get<0>(vt), 2) + pow(y - std::get<1>(vt), 2));

				std::get<2>(vt)->edges.push_back(e);
				v->edges.push_back(e);
				ret.edges.push_back(e);
			}

			verts.push_back(std::make_tuple(x, y, v));
		}

		return ret;
	}

	AdjacencyList<unsigned long long> CreateAdjacencyListMultipleHeadsWithHeights(std::string file)
	{
		AdjacencyList<unsigned long long> ret;
		std::map<int, Vertice<unsigned long long>*> mapv;

		std::ifstream f(file);
		assert(f.is_open());

		std::string line;
		while (std::getline(f, line))
		{
			std::istringstream iss(line);

			std::regex ws_re("[\\s*,]");
			std::vector<std::string> tokens;
			std::copy(std::sregex_token_iterator(line.begin(), line.end(), ws_re, -1),
				std::sregex_token_iterator(),
				std::back_inserter(tokens));

			tokens.erase(
				std::remove_if(
				tokens.begin(),
				tokens.end(),
				[](std::string const& s) { return s.size() == 0; }),
				tokens.end());

			if (tokens.empty())
				continue;

			int tailid = stoi(tokens[0]);
			Vertice<unsigned long long> * tail = GetVertex<unsigned long long>(mapv, ret, tailid);

			for (size_t i = 1; i < tokens.size(); i = i + 2)
			{
				Edge<unsigned long long> * e = new Edge<unsigned long long>;
				int headid = stoi(tokens[i + 0]);
				e->vertex1 = GetVertex<unsigned long long>(mapv, ret, headid);
				e->vertex2 = tail;
				e->weigth = stoi(tokens[i + 1]);

				ret.edges.push_back(e);

				e->vertex2->edges.push_back(e);
				e->vertex1->edges.push_back(e);
			}

		}

		return ret;
	}

	AdjacencyList<unsigned long long> CreateAdjacencyListMultipleAdjacents(std::string file)
	{
		AdjacencyList<unsigned long long> ret;
		std::map<int, Vertice<unsigned long long>*> mapv;

		std::ifstream f(file);
		assert(f.is_open());

		std::string line;
		while (std::getline(f, line))
		{
			std::istringstream iss(line);

			int currentNodeId;
			if (iss >> currentNodeId)
			{
				Vertice<unsigned long long> * currentNode = GetVertex<unsigned long long>(mapv, ret, currentNodeId);

				while (iss.good())
				{
					unsigned long adjacentNodeId;
					if (iss >> adjacentNodeId)
					{
						// check if this edge already exists
						auto adjacentNode = GetVertex<unsigned long long>(mapv, ret, adjacentNodeId);
						bool found = false;
						for (auto e : adjacentNode->edges)
						{
							if ((e->vertex1->id == currentNodeId && e->vertex2->id == adjacentNodeId) || 
								((e->vertex1->id == adjacentNodeId && e->vertex2->id == currentNodeId)))
							{
								currentNode->edges.push_back(e);
								found = true;
								break;
							}
						}
						if (found)
							continue;

						Edge<unsigned long long> * e = new Edge < unsigned long long > ;
						
						e->vertex1 = currentNode;
						e->vertex2 = adjacentNode;
						e->weigth = 0;

						ret.edges.push_back(e);

						e->vertex1->edges.push_back(e);
						e->vertex2->edges.push_back(e);
					}
				}
			}
		}
		return ret;
	}
}
