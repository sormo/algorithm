#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

template <class T>
struct BSTNode
{
	BSTNode(T v) : parent(nullptr), left(nullptr), right(nullptr), value(v) {}

	BSTNode * parent;
	BSTNode * left;
	BSTNode * right;

	T value;
};

template <class T>
class BinarySearchTree
{
public:
	bool Search(const T & value)
	{
		return searchForValue(value, m_root);
	}

	// TODO
	void Insert(const T & value);
	bool Remove(const T & value);
	std::vector<T> GetSorted();

private:
	BSTNode * m_root;

	bool SearchForValue(const T & value, BSTNode * node)
	{
		if (node->value == value)
			return true;
		// using invariant of BST
		// left are smaller, right are bigger
		if (node->value > value)
			return SearchForValue(value, node->left);
		return SearchForValue(value, node->right);
	}

	void InsertToTree(const T & value, BSTNode *& node)
	{
		if (!node )
			node = new BSTNode(value);
		else if (value < node->value)
			InsertToTree(value, node->left);
		else if (value > node->value)
			InsertToTree(value, node->right) ;
	}
};

#endif // BINARYSEARCHTREE_H
