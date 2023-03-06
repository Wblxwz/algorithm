
#include "sf-5.h"

using namespace std;


//∂˛≤Ê ˜µƒæµœÒ

struct BinaryTreeNode
{
	int value;
	BinaryTreeNode* left, * right;
};

void MirrorRecursively(BinaryTreeNode* head)
{
	if (head == nullptr)
	{
		return;
	}
	if (head->left == nullptr && head->right == nullptr)
	{
		return;
	}
	BinaryTreeNode* temp = head->left;
	head->left = head->right;
	head->right = temp;
	if (head->left)
	{
		MirrorRecursively(head->left);
	}
	if (head->right)
	{
		MirrorRecursively(head->right);
	}
}

//∂‘≥∆µƒ∂˛≤Ê ˜
bool IsSymmetrical(BinaryTreeNode* root1, BinaryTreeNode* root2);

bool IsSymmetrical(BinaryTreeNode* root)
{
	return IsSymmetrical(root, root);
}

bool IsSymmetrical(BinaryTreeNode* root1, BinaryTreeNode* root2)
{
	if (root1 == nullptr && root2 == nullptr)
	{
		return true;
	}
	if (root1 == nullptr || root2 == nullptr)
	{
		return false;
	}
	if (root1->value != root2->value)
	{
		return false;
	}
	return IsSymmetrical(root1->left, root2->right) && IsSymmetrical(root1->right, root2->left);
}

//À≥ ±’Î¥Ú”°æÿ’Û
void PrintMatrixInCircle(int** numbers, int columns, int rows, int start)
{
	int endX = columns - 1 - start;
	int endY = rows - 1 - start;
	for (int i = start; i <= endX; ++i)
	{
		cout << numbers[start][i];
	}
	if (start < endY)
	{
		for (int i = start + 1; i <= endY; ++i)
		{
			cout << numbers[i][endX];
		}
	}
	if (start < endX && start < endY)
	{
		for (int i = endX - 1; i >= start; --i)
		{
			cout << numbers[endY][i];
		}
	}
	if (start < endX && start < endY - 1)
	{
		for (int i = endY - 1; i >= start + 1; --i)
		{
			cout << numbers[i][start];
		}
	}
}

void PrintMatrixClockwisely(int** numbers, int columns, int rows)
{
	if (numbers == nullptr || columns <= 0 || rows <= 0)
	{
		return;
	}
	int start = 0;
	while (columns > start * 2 && rows > start * 2)
	{
		PrintMatrixInCircle(numbers, columns, rows, start);
		++start;
	}
}

//Ï≥≤®ƒ«∆ı∂—
struct FibNode;

struct FibHeap
{
	int n;
	FibNode* min;
};

struct FibNode
{
	int degree;
	FibNode* p, * child, * left, * right;
	bool mark;
	int key;
};

FibHeap* MakeFibHeap()
{
	FibHeap* h = new FibHeap;
	h->min = nullptr;
	h->n = 0;
	return h;
}

void FibHeapInsertRootList(FibHeap* h, FibNode* x)
{
	h->min->left->right = x;
	x->left = h->min->left;
	h->min->left = x;
	x->right = h->min;
}

void FibHeapInsert(FibHeap* h, FibNode* x)
{
	x->degree = 0;
	x->p = nullptr;
	x->child = nullptr;
	x->mark = false;
	if (h->min == nullptr)
	{
		x->left = x;
		x->right = x;
		h->min = x;
	}
	else
	{
		if (x->key < h->min->key)
		{
			FibHeapInsertRootList(h, x);
			if (h->min->key > x->key)
				h->min = x;
		}
	}
	h->n += 1;
}

template<typename T>
bool ListStack<T>::push(const T& data)
{
	ListStack* node = new ListStack;
	assert(node);
	node->data = data;
	node->next = head;
	head = node;
	return true;
}

template<typename T>
T ListStack<T>::pop()
{
	if (!head)
		return INT_MIN;
	ListStack* temp = head;
	head = head->next;
	int n = temp->data;
	delete temp;
	return n;
}

template<typename T>
const T& ListStack<T>::top() const
{
	return head ? head->data : INT_MIN;
}

template<typename T>
const size_t ListStack<T>::size()
{
	size_t cnt = 0;
	ListStack<T>* tmp = head;
	while (tmp)
	{
		tmp = tmp->next;
		++cnt;
	}
	return cnt;
}

template<typename T>
void ListStack<T>::deleter()
{
	while (head)
	{
		ListStack<T>* temp = head;
		head = head->next;
		delete temp;
	}
}

template<typename T>
void StackWithMin<T>::push(const T& data)
{
	d_stack->push(data);
	if (m_stack->size() == 0 || data < m_stack->top())
		m_stack->push(data);
	else
		m_stack->push(m_stack->top());
}

template<typename T>
T StackWithMin<T>::pop()
{
	d_stack->pop();
	m_stack->pop();
}

template<typename T>
const T& StackWithMin<T>::min() const
{
	assert(m_stack->size() > 0 && d_stack->size() > 0);
	return m_stack->top();
}

bool isPopOrder(vector<int>& pushed, vector<int>& popped)
{
	if (pushed.empty() || popped.empty())
		return true;
	auto p1 = pushed.begin();
	auto p2 = popped.begin();
	stack<int> a_stack;
	while (p2 != popped.cend())
	{
		while (a_stack.empty() || a_stack.top() != *p2)
		{
			if (p1 == pushed.cend())
				break;
			a_stack.push(*p1);
			++p1;
		}
		if (a_stack.top() != *p2)
			break;
		a_stack.pop();
		++p2;
	}
	if (a_stack.empty())
		return true;
	return false;
}


namespace mystl
{
	template<typename T>
	BinaryTreeNode* BinaryTree<T>::create(BinaryTreeNode* node)
	{
		int tmp = INT_MIN;
		cin >> tmp;
		if (tmp == -1)
			node = nullptr;
		else
		{
			node = new BinaryTreeNode;
			node->data = tmp;
			node->left = create(node->left);
			node->right = create(node->right);
		}
		return node;
	}
	template<typename T>
	void BinaryTree<T>::print(BinaryTreeNode* node)
	{
		if (node)
		{
			cout << node->data << " ";
			print(node->left);
			print(node->right);
		}
	}
	template<typename T>
	void printBinaryTreeRows(BinaryTreeNode* root)
	{
		if (!root)
			return;
		std::deque<T> deque;
		deque.push_back(root);
		while (!deque.empty())
		{
			BinaryTreeNode* node = deque.front();
			deque.pop_front();
			cout << node->data << " ";
			if (node->left)
				deque.push_back(node->left);
			if (node->right)
				deque.push_back(node->right);
		}
	}
}



int main(int argc, char* argv[])
{
	/*StackWithMin<int> min_stack;
	min_stack.push(3);
	cout << min_stack.min() << endl;
	min_stack.push(2);
	cout << min_stack.min() << endl;
	min_stack.push(3);
	cout << min_stack.min() << endl;*/

	/*vector<int> pushed{ 1,2,3,4,5 };
	vector<int> popped{ 4,3,5,1,2 };
	cout << isPopOrder(pushed, popped);*/

	mystl::BinaryTree<int> tree;
	mystl::BinaryTreeNode* root = new mystl::BinaryTreeNode;
	root = tree.create(root);
	mystl::printBinaryTreeRows<mystl::BinaryTreeNode*>(root);

	return 0;
}