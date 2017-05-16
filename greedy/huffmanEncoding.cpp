#include <vector>
#include <memory>
#include "..\datastruct\heap.h"

struct HuffmanNode;
using HuffmanNodePtr = std::shared_ptr<HuffmanNode>;

struct HuffmanNode
{
	HuffmanNodePtr left = nullptr;
	HuffmanNodePtr right = nullptr;
	float value;

	HuffmanNode(float v) : value(v) {}
	//bool operator<(const HuffmanNode & o) { return value < o.value; }
};

bool operator<(const HuffmanNodePtr & a, const HuffmanNodePtr& b) { return a->value < b->value; }

std::vector<std::pair<float, std::string>> HuffmanEncoding(const std::vector<float> & frequencies)
{
	Heap<std::shared_ptr<HuffmanNode>> heap;
	for (auto f : frequencies)
		heap.Push(std::make_shared<HuffmanNode>(f));

	HuffmanNodePtr root;
	while (heap.Size() > 1)
	{
		HuffmanNodePtr left, right, parent;

		heap.Pop(left);
		heap.Pop(right);

		parent = std::make_shared<HuffmanNode>(left->value + right->value);

		parent->left = left;
		parent->right = right;

		if (heap.Empty())
		{
			root = parent;
			break;
		}

		heap.Push(parent);
	}

	// generate encodings from tree

	std::vector<std::pair<float, std::string>> encodings;
	std::function<void(std::string, HuffmanNodePtr)> traverse = [&encodings, &traverse](std::string c, HuffmanNodePtr node)
	{
		if (node->left == nullptr && node->right == nullptr)
		{
			encodings.push_back({ node->value, c });
			return;
		}

		if (node->left)
			traverse(c + "0", node->left);
		if (node->right)
			traverse(c + "1", node->right);
	};

	traverse("", root);

	return encodings;
}