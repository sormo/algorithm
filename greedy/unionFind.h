#pragma once
#include <vector>
#include <cassert>
#include <algorithm>

// TODO T must be cheap to copy

template <class T>
class UnionFind
{
public:
	struct Node
	{
		T value;
		int rank;
		size_t index;

		bool operator==(const Node & o) { return value == o.value; }
		bool operator!=(const Node & o) { return value != o.value; }
	};


	Node Insert(const T & v)
	{
		size_t index = m_nodes.size();

		m_nodes.push_back({ v, 0, index });
		m_parents.push_back(m_nodes.size() - 1);

		assert(m_nodes.size() == m_parents.size());

		return m_nodes.back();
	}

	Node Find(const Node & v)
	{
		Node ret = v;
		while (m_parents[ret.index] != ret.index)
			ret = m_nodes[m_parents[ret.index]];

		// TODO path compression

		return ret;
	}

	Node Union(const Node & a, const Node & b)
	{
		Node na = Find(a);
		Node nb = Find(b);

		if (na == nb)
			return na;

		if (na.rank != nb.rank)
		{
			const Node * smaller = na.rank > nb.rank ? &nb : &na;
			const Node * bigger = na.rank > nb.rank ? &na : &nb;

			m_parents[smaller->index] = bigger->index;

			return *bigger;
		}
		else
		{
			m_parents[na.index] = nb.index;
			m_nodes[nb.index].rank++;

			return b;
		}
	}

	size_t CountClusters()
	{
		std::set<size_t> count;
		for (auto c : m_parents)
			count.insert(c);
		return count.size();
	}

private:
	std::vector<Node> m_nodes;
	std::vector<size_t> m_parents;

};
