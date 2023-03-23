#include "sf-6.h"

using namespace std;

GraphListNode::GraphListNode()
{
	int data = 0;
	cout << "请输入顶点值:";
	cin >> data;
	this->data = data;
	this->next = nullptr;
}

GraphList::GraphList(const int size, bool isAuto)
{
	if (!isAuto)
	{
		char c = ' ';
		for (int i = 0; i < size; ++i)
		{
			nodes.push_back(new GraphListNode(i));
			GraphListNode* node = nodes[i];
			while (true)
			{
				node->next = new GraphListNode;
				node = node->next;
				cout << "是否终止(y/n)";
				cin >> c;
				if (c == 'y')
					break;
			}
		}
	}
	else
	{
		ifstream in;
		in.open("graph.txt", ifstream::in);
		char ch[20]{ '0' };
		for (int i = 0; i < size; ++i)
		{
			nodes.push_back(new GraphListNode(i));
			in.getline(ch, 20);
			int j = 0;
			GraphListNode* node = nodes[i];
			while (ch[j] != '\0')
			{
				if (ch[j] != ' ')
				{
					node->next = new GraphListNode(ch[j] - '0');
					node = node->next;
				}
				++j;
			}
		}
		in.close();
	}
}

void print(GraphList* graph)
{
	int size = graph->nodes.size();
	for (int i = 0; i < size; ++i)
	{
		GraphListNode* node = graph->nodes[i];
		while (node)
		{
			cout << node->data << "->";
			node = node->next;
		}
		cout << "/" << endl;
	}
}

void bfs(GraphList* graph, const int s)
{
	cout << "bfs:" << endl;
	unordered_map<int, bool> visited;
	deque<GraphListNode*> deque;
	deque.push_back(graph->nodes[s]);
	visited[graph->nodes[s]->data] = true;
	while (!deque.empty())
	{
		GraphListNode* node = deque.front();
		deque.pop_front();
		cout << node->data << " ";
		while (node->next)
		{
			if (!visited[node->next->data])
			{
				deque.push_back(graph->nodes[node->next->data]);
				visited[node->next->data] = true;
			}
			node = node->next;
		}
	}
	cout << endl;
}

void dfs(GraphList* graph, const int s)
{
	cout << "dfs:" << endl;
	stack<GraphListNode*> stack;
	unordered_map<int, bool> visited;
	visited[graph->nodes[s]->data] = true;
	stack.push(graph->nodes[s]);
	while (!stack.empty())
	{
		GraphListNode* node = stack.top();
		stack.pop();
		cout << node->data << " ";
		while (node->next)
		{
			if (!visited[node->next->data])
			{
				visited[node->next->data] = true;
				stack.push(graph->nodes[node->next->data]);
			}
			node = node->next;
		}
	}
	cout << endl;
}

deque<GraphListNode*> topologicalSort(GraphList* graph)
{
	unordered_map<int, int> dgree;
	int size = graph->nodes.size();
	for (int i = 0; i < size; ++i)
	{
		GraphListNode* node = graph->nodes[i];
		while (node->next)
		{
			++dgree[node->next->data];
			node = node->next;
		}
	}
	deque<GraphListNode*> temp;
	deque<GraphListNode*> result;
	for (int i = 0; i < size; ++i)
		if (dgree[i] == 0)
			temp.push_back(graph->nodes[i]);
	while (!temp.empty())
	{
		GraphListNode* node = temp.front();
		temp.pop_front();
		result.push_back(node);
		while (node->next)
		{
			--dgree[node->next->data];
			if (dgree[node->next->data] == 0)
				temp.push_back(graph->nodes[node->next->data]);
			node = node->next;
		}
	}
	return result;
}

int main(int argc, char* argv[])
{
	//使用邻接链表表示图的结构
	GraphList* graph = new GraphList(7);
	print(graph);
	//bfs(graph, 1);
	//dfs(graph, 2);
	deque<GraphListNode*> deque = topologicalSort(graph);
	for (auto i = deque.begin(); i != deque.cend(); ++i)
		cout << (*i)->data << " ";
	cout << endl;

	return 0;
}
