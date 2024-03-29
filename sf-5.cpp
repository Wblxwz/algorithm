
#include "sf-5.h"

using namespace std;


//二叉树的镜像

struct BinaryTreeNode
{
	BinaryTreeNode(int val) :value(val), left(nullptr), right(nullptr) {}
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

//对称的二叉树
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

//顺时针打印矩阵
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

//斐波那契堆
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
	template<typename T>
	void BinarySearchTree<T>::insert(const T& data)
	{
		BinaryTreeNode* node = new BinaryTreeNode;
		node->data = data;
		node->left = nullptr;
		node->right = nullptr;
		if (!root)
		{
			root = node;
			return;
		}
		BinaryTreeNode* temp = root;
		while (true)
		{
			if (data < temp->data)
			{
				if (!temp->left)
				{
					temp->left = node;
					return;
				}
				else
					temp = temp->left;
			}
			else
			{
				if (!temp->right)
				{
					temp->right = node;
					return;
				}
				else
					temp = temp->right;
			}

		}
	}
	template<typename T>
	void BinarySearchTree<T>::destroy(BinaryTreeNode* node)
	{
		if (!node)
			return;
		if (node->left)
			destroy(node->left);
		if (node->right)
			destroy(node->right);
		delete node;
		node = nullptr;
	}
	template<typename T>
	void BinarySearchTree<T>::xianXuPrint(BinaryTreeNode* node)
	{
		cout << node->data << endl;
		if (node->left)
			xianXuPrint(node->left);
		if (node->right)
			xianXuPrint(node->right);
	}
	template<typename T>
	BinaryTreeNode* BinarySearchTree<T>::getRoot()
	{
		return root;
	}
}

bool verifyPostorder(vector<int>& postorder)
{
	if (postorder.empty())
		return false;
	size_t size = postorder.size();
	size_t root = postorder.back();
	size_t i = 0;
	for (; i < size - 1; ++i)
		if (postorder[i] > root)
			break;
	size_t j = i;
	for (; j < size - 1; ++j)
		if (postorder[j] < root)
			return false;
	bool isLeft = true;
	if (i > 0)
	{
		vector<int> left(postorder.begin(), postorder.begin() + i);
		isLeft = verifyPostorder(left);
	}
	bool isRight = true;
	if (i < size - 1)
	{
		vector<int> right(postorder.begin() + i, postorder.end() - 1);
		isRight = verifyPostorder(right);
	}
	return isLeft && isRight;
}

class Node {
public:
	int val;
	Node* left;
	Node* right;

	//Node() {}

	Node(int _val) {
		val = _val;
		left = NULL;
		right = NULL;
	}

	Node(int _val, Node* _left, Node* _right) {
		val = _val;
		left = _left;
		right = _right;
	}
};

void helpPrint(char* nums)
{
	size_t n = strlen(nums);
	bool is0 = true;
	for (int i = 0; i < n; ++i)
	{
		if (nums[i] != '0' && is0)
			is0 = false;
		if (!is0)
			cout << nums[i];
	}
	cout << endl;
}

void helper(const int n, char* nums, int index)
{
	for (int i = 0; i < 10; ++i)
	{
		if (index == n - 1)
		{
			helpPrint(nums);
			return;
		}
		nums[index + 1] = i + '0';
		helper(n, nums, index + 1);
	}
}

void quanPaiLie(const int n)
{
	char* nums = new char[n + 1];
	nums[n] = '\0';
	for (int i = 0; i < 10; ++i)
	{
		nums[0] = i + '0';
		helper(n, nums, 0);
	}
}

class Solution {
public:
	vector<vector<string>> solveNQueens(int n)
	{
		vector<vector<string>> result;
		if (n <= 0)
			return vector<vector<string>>();
		vector<string> path(n, string(n, '.'));
		queen(result, path, 0, n);
		return result;
	}
private:
	bool isRight(vector<string>& path, int row, int col, int n)
	{
		for (int i = 0; i < n; ++i)
			if (path[i][col] == 'Q')
				return false;
		for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j)
			if (path[i][j] == 'Q')
				return false;
		for (int i = row - 1, j = col + 1; i >= 0 && j < n; --i, ++j)
			if (path[i][j] == 'Q')
				return false;
		return true;
	}
	void queen(vector<vector<string>>& result, vector<string>& path, int row, int n)
	{
		if (row == n)
		{
			result.push_back(path);
			return;
		}
		for (int col = 0; col < n; ++col)
		{
			if (isRight(path, row, col, n))
			{
				result[row][col] = 'Q';
				queen(result, path, row + 1, n);
				result[row][col] = '.';
			}
		}
	}
};

const int binarySerach(int* nums, const int n, const int data)
{
	int left = 0, right = n;
	while (left < right)
	{
		int mid = (left + right) / 2;
		if (nums[mid] == data)
			right = mid;
		else if (nums[mid] < data)
			left = mid + 1;
		else
			right = mid;
	}
	return left;
}

void bfs(BinaryTreeNode* root)
{
	deque<BinaryTreeNode*> deque;
	deque.push_back(root);
	while (!deque.empty())
	{
		BinaryTreeNode* node = deque.front();
		cout << node->value << " ";
		deque.pop_front();
		if (node->left)
			deque.push_back(node->left);
		if (node->right)
			deque.push_back(node->right);
	}
	cout << endl;
}

void dfs(BinaryTreeNode* root)
{
	stack<BinaryTreeNode*> stack;
	stack.push(root);
	while (!stack.empty())
	{
		size_t n = stack.size();
		BinaryTreeNode* node = stack.top();
		cout << node->value << " ";
		stack.pop();
		if (node->right)
			stack.push(node->right);
		if (node->left)
			stack.push(node->left);
	}
	cout << endl;
}

template<typename K, typename V>
SkipList<K, V>::SkipList(const int maxLevel)
{
	this->maxLevel = maxLevel;
	pair<K, V> p(INT_MIN, 0);
	head = new SkipNode<K, V>(p, maxLevel);
	pair<K, V> tp(INT_MAX, 0);
	tail = new SkipNode<K, V>(tp, maxLevel);
	for (int i = 0; i < maxLevel; ++i)
		head->next[i] = tail;
}

template<typename K, typename V>
int SkipList<K, V>::randomLevel()
{
	int temp_level = 1;
	default_random_engine e;
	e.seed(time(nullptr));
	uniform_int_distribution<size_t> u(0, 1);
	while (u(e) && temp_level < maxLevel)
		++temp_level;
	return temp_level;
}

template<typename K, typename V>
int SkipList<K, V>::nodeLevel(SkipNode<K, V>** next)
{
	int node_Level = 0;
	if (next[0]->element.first == INT_MAX)
		return node_Level;
	int size = sizeof(next) / sizeof(SkipNode<K, V>*);
	for (int i = 0; i < size; ++i)
	{
		if (next[i] && next[i]->element.first != INT_MAX)
			++node_Level;
		else
			break;
	}
	return node_Level;
}

template<typename K, typename V>
SkipNode<K, V>* SkipList<K, V>::find(const K& key)
{
	SkipNode<K, V>* thead = head;
	int currMaxLevel = nodeLevel(thead->next);
	for (int i = currMaxLevel; i >= 0; --i)
	{
		while (thead->next[i] && thead->next[i]->element.first < key)
			thead = thead->next[i];
	}
	thead = thead->next[0];
	if (thead->element.first == key)
	{
		cout << "find successful" << thead->element.first << ":" << thead->element.second << endl;
		return thead;
	}
	else
	{
		cout << "not find" << endl;
		return nullptr;
	}
}

template<typename K, typename V>
bool SkipList<K, V>::insert(const pair<const K, V>& p)
{
	int level = randomLevel();
	SkipNode<K, V>* node = find(p.first);
	if (node)
	{
		node->element.second = p.second;
		cout << p.first << "已存在" << ":" << p.second << endl;
		return false;
	}
	node = new SkipNode<K, V>(p, level);
	SkipNode<K, V>* thead = head;
	for (int i = level - 1; i >= 0; --i)
	{
		while (thead->next[i] && thead->next[i]->element.first < p.first)
			thead = thead->next[i];
		node->next[i] = thead->next[i];
		thead->next[i] = node;
	}
	return true;
}

template<typename K, typename V>
bool SkipList<K, V>::deleteNode(const K& key)
{
	SkipNode<K, V>* toBeDeleted = find(key);
	if (!toBeDeleted)
	{
		cout << "删除失败，不存在该节点" << endl;
		return false;
	}
	SkipNode<K, V>* thead = head;
	int tlevel = sizeof(toBeDeleted->next) / sizeof(SkipNode<K, V>*);
	for (int i = tlevel - 1; i >= 0; --i)
	{
		while (thead->next[i] && thead->next[i]->element.first < key)
			thead = thead->next[i];
		SkipNode<K, V>* node = thead->next[i];
		thead->next[i] = node->next[i];
		delete node;
		node = nullptr;
	}
	return true;
}

template<typename K, typename V>
bool HashTable<K, V>::insert(const pair<K, V>& p)
{
	SingleList* first = find(p.first);
	if (first)
	{
		first->data = p.second;
		return false;
	}
	int pos = hash(p.first);
	SingleList* node = new SingleList(p.first, p.second);
	node->next = nullptr;
	if (!list[pos]->next)
		list[pos]->next = node;
	else
	{
		SingleList* temp = list[pos]->next;
		SingleList* last = list[pos];
		while (temp && temp->key < p.first)
		{
			last = temp;
			temp = temp->next;
		}
		node->next = temp;
		last->next = node;
	}
	return true;
}

template<typename K, typename V>
bool HashTable<K, V>::deleteNode(const K& key)
{
	SingleList* node = find(key);
	if (!node)
	{
		cout << "不存在该元素，无法删除" << endl;
		return false;
	}
	SingleList* toBeDeleted = node->next;
	node->next = toBeDeleted->next;
	delete toBeDeleted;
	toBeDeleted = nullptr;
	return true;
}

template<typename K, typename V>
SingleList* HashTable<K, V>::find(const K& key)
{
	int pos = hash(key);
	SingleList* temp = list[pos]->next;
	SingleList* last = temp;
	while (temp && temp->key < key)
	{
		last = temp;
		temp = temp->next;
	}
	if (!temp || temp->key != key)
	{
		cout << "未找到" << endl;
		return nullptr;
	}
	cout << "Key:" << key << "Value:" << temp->data << endl;
	return last;
}

template<typename T>
int AVLTree<T>::getHeight(AVLTreeNode<T>* node)
{
	if (node)
		return node->height;
	return 0;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::find(const T& key)
{
	AVLTreeNode<T>* node = root;
	while (node)
	{
		if (node->key == key)
		{
			cout << "已找到" << endl;
			return node;
		}
		if (key < node->key)
			node = node->left;
		else
			node = node->right;
	}
	cout << "未找到" << endl;
	return nullptr;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::llRotation(AVLTreeNode<T>* node)
{
	AVLTreeNode<T>* n_left = node->left;
	node->left = n_left->right;
	n_left->right = node;
	node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
	n_left->height = max(getHeight(n_left->left), getHeight(node)) + 1;
	return n_left;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::rrRotation(AVLTreeNode<T>* node)
{
	AVLTreeNode<T>* n_right = node->right;
	node->right = n_right->left;
	n_right->left = node;
	node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
	n_right->height = max(getHeight(node->right), getHeight(node)) + 1;
	return n_right;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::lrRotation(AVLTreeNode<T>* node)
{
	node->left = rrRotation(node->left);
	return llRotation(node);
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::rlRotation(AVLTreeNode<T>* node)
{
	node->right = llRotation(node->right); 
	return rrRotation(node);
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::myMin(AVLTreeNode<T>* node)
{
	if (!node)
		return nullptr;
	AVLTreeNode<T>* tnode = node;
	while (tnode->left)
		tnode = tnode->left;
	return tnode;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::myMax(AVLTreeNode<T>* node)
{
	if (!node)
		return nullptr;
	AVLTreeNode<T>* tnode = node;
	while (tnode->right)
		tnode = tnode->right;
	return tnode;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>* node, const T& key)
{
	if (!node)
		node = new AVLTreeNode<T>(key, nullptr, nullptr);
	else if (key < node->key)
	{
		node->left = insert(node->left, key);
		if (getHeight(node->left) - getHeight(node->right) == 2)
		{
			if (key < node->left->key)
				node = llRotation(node);
			else
				node = lrRotation(node);
		}
	}
	else if (key > node->key)
	{
		node->right = insert(node->right, key);
		if (getHeight(node->left) - getHeight(node->right) == -2)
		{
			if (key > node->right->key)
				node = rrRotation(node);
			else
				node = rlRotation(node);
		}
	}
	else
	{
		cout << "不允许添加相同的节点" << endl;
		return nullptr;
	}
	node->height = max(getHeight(node->left), getHeight(node->right));
	return node;
}

template<typename T>
void AVLTree<T>::remove(const T& key)
{
	AVLTreeNode<T>* node = find(key);
	if (node)
		root = deleteNode(root, node);
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::deleteNode(AVLTreeNode<T>* node, AVLTreeNode<T>* z)
{
	if (!node || !z)
		return nullptr;
	if (z->key < node->key)
	{
		node->left = deleteNode(node->left, z);
		if (getHeight(node->left) - getHeight(node->right) == -2)
		{
			AVLTreeNode<T>* tnode = node->right;
			if (getHeight(tnode->left) > getHeight(tnode->right))
				node = rlRotation(tnode);
			else
				node = rrRotation(tnode);
		}
	}
	else if (z->key > node->key)
	{
		node->right = deleteNode(node->right, z);
		if (getHeight(node->left) - getHeight(node->right) == 2)
		{
			AVLTreeNode<T>* tnode = node->left;
			if (getHeight(tnode->left) > getHeight(tnode->right))
				node = llRotation(node);
			else
				node = lrRotation(node);
		}
	}
	else
	{
		if (node->left && node->right)
		{
			if (getHeight(node->left) > getHeight(node->right))
			{
				AVLTreeNode<T>* max = myMax(node->left);
				node->key = max->key;
				node->left = deleteNode(node->left, max);
			}
			else
			{
				AVLTreeNode<T>* min = myMin(node->right);
				node->key = min->key;
				node->right = deleteNode(node->right, min);
			}
		}
		else
		{
			AVLTreeNode<T>* tnode = node;
			node = node->left ? node->left : node->right;
			delete tnode;
		}
	}
	return node;
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

	/*mystl::BinaryTree<int> tree;
	mystl::BinaryTreeNode* root = new mystl::BinaryTreeNode;
	root = tree.create(root);
	mystl::printBinaryTreeRows<mystl::BinaryTreeNode*>(root);*/

	/*mystl::BinarySearchTree<int> tree;
	tree.insert(5);
	tree.insert(3);
	tree.insert(1);
	tree.insert(2);
	tree.insert(6);
	tree.xianXuPrint(tree.getRoot());*/

	/*vector<int> sequence1 = { 5, 7, 6, 9, 11, 10, 8 };
	vector<int> sequence2 = { 7, 4, 6, 5 };
	cout << verifyPostorder(sequence1) << endl;
	cout << verifyPostorder(sequence2) << endl;*/

	/*Node* head = new Node(4);
	head->left = new Node(2);
	head->left->left = new Node(1);
	head->right = new Node(5);
	head->left->right = new Node(3);
	treeToDoublyList(head);
	cout << head->right->val;*/

	/*int data[7]{ 1,1,1,4,4,5,5 };
	cout << binarySerach(data, 7, 1);*/

	/*BinaryTreeNode* root = new BinaryTreeNode(1);
	root->left = new BinaryTreeNode(2);
	root->right = new BinaryTreeNode(3);
	root->left->left = new BinaryTreeNode(4);
	root->left->right = new BinaryTreeNode(5);
	root->right->left = new BinaryTreeNode(6);
	root->right->right = new BinaryTreeNode(7);
	bfs(root);
	dfs(root);*/

	/*SkipList<int, int> s(7);
	pair<int, int> p(1, 1);
	s.insert(p);
	s.find(1);
	p.second = 2;
	s.insert(p);
	s.find(1);
	s.deleteNode(1);
	s.find(1);*/

	/*HashTable<int, int> my_hash_table(5);
	my_hash_table.insert(pair<int, int>(1, 1));
	my_hash_table.insert(pair<int, int>(1, 2));
	my_hash_table.insert(pair<int, int>(16, 5));
	my_hash_table.find(1);*/

	AVLTree<int>* tree = new AVLTree<int>;
	tree->setRoot(tree->insert(tree->getRoot(), 1));
	tree->insert(tree->getRoot(), 2);
	tree->insert(tree->getRoot(), 3);
	
	tree->find(2);
	tree->remove(2);
	tree->find(2);

	return 0;
}