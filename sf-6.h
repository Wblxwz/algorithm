#ifndef SF_6_H

#define SF_6_H

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <fstream>
#include <unordered_map>
#include <stack>

struct GraphListNode
{
	GraphListNode();
	GraphListNode(const int data):data(data),next(nullptr){}
	int data;
	GraphListNode* next;
};

class GraphList
{
public:
	GraphList(const int size, bool isAuto = true);
	~GraphList()
	{
		for (auto& i : nodes)
		{
			GraphListNode* node = i;
			GraphListNode* toBeDeleted = nullptr;
			while (node->next)
			{
				toBeDeleted = node;
				node = node->next;
				delete toBeDeleted;
				toBeDeleted = nullptr;
			}
			delete node;
		}
	}
	std::vector<GraphListNode*> nodes;
};

#endif // !SF_6_H