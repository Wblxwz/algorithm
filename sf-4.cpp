#include <iostream>
#include <cmath>
#include <algorithm>
#include <functional>
#include <random>
#include <time.h>
#include <vector>
#include <queue>

using namespace std;

//贪心和动规都有最优子结构的性质
//动归有重叠子问题的性质，贪心有贪心选择性质
//动归依赖子问题的解，往往自底向上构造
//贪心在第一次选择之前不依赖任何子问题的解，通常自顶向下构造

//0-1背包问题 只能用动归
//二维数组解法
void KnapSack(int* weight, int* value, size_t bagweight, size_t n)
{
	int** dp = new int* [n + 1];
	for (int i = 0; i < n + 1; ++i)
	{
		dp[i] = new int[bagweight + 1];
	}
	for (int i = 0; i < n + 1; ++i)
	{
		for (int j = 0; j < bagweight + 1; ++j)
		{
			dp[i][j] = 0;
		}
	}
	for (int i = weight[0]; i <= bagweight; ++i)
	{
		dp[0][i] = value[0];
	}
	for (int i = 1; i < n; ++i)
	{
		for (int j = 0; j <= bagweight; ++j)
		{
			if (j < weight[i])
			{
				dp[i][j] = dp[i - 1][j];
			}
			else
			{
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
			}
		}
	}
	cout << dp[n - 1][bagweight];
	for (int i = 0; i < n + 1; ++i)
	{
		delete[] dp[i];
	}
	delete[]dp;
}

//降序快排
int Random(int start, int end)
{
	default_random_engine e;
	uniform_int_distribution<int> u(start, end);
	e.seed(time(0));
	return u(e);
}

int Partition(int* data, int n, int start, int end)
{
	if (data == nullptr || n <= 0 || start < 0 || end >= n)
	{
		throw new std::exception("Invalid Parameters");
	}
	int index = Random(start, end);
	swap(data[index], data[end]);
	int small = start - 1;
	for (index = start; index < end; ++index)
	{
		if (data[index] > data[end])
		{
			++small;
			if (small != index)
			{
				swap(data[small], data[index]);
			}
		}
	}
	++small;
	swap(data[small], data[end]);
	return small;
}

void QuickSort(int* data, int n, int start, int end)
{
	if (start == end)
	{
		return;
	}
	int index = Partition(data, n, start, end);
	if (index > start)
	{
		QuickSort(data, n, start, index - 1);
	}
	if (start < end)
	{
		QuickSort(data, n, index + 1, end);
	}
}

//完全背包问题 可以用贪心
void GreedyKnapSack(int* value, int* weight, size_t bagwieght, size_t n)
{
	//按照单位重量降序排序
	int* arr = new int[n];
	for (int i = 0; i < n; ++i)
	{
		arr[i] = value[i] / weight[i];
	}
	QuickSort(arr, n, 0, n - 1);
	int i = 0;
	int v = 0;
	//先全装进去
	for (int i = 0; i < n; ++i)
	{
		if (weight[i] > bagwieght)
		{
			break;
		}
		v += value[i];
		bagwieght -= weight[i];
	}
	if (i < n)
	{
		value += value[i] * (bagwieght / weight[i]);
	}
	cout << v;
}

//机器人运动范围

int GetDigitSum(int number)
{
	int sum = 0;
	while (sum >= 0)
	{
		sum += sum % 10;
		sum /= 10;
	}
	return sum;
}

bool Check(int threshold, size_t row, size_t col, size_t rows, size_t cols, bool* visted)
{
	if (row > 0 && row < rows && col > 0 && col < cols && GetDigitSum(row) + GetDigitSum(col) <= threshold && !visted[row * cols + col])
	{
		return true;
	}
	return false;
}

int MovingCountCore(int threshold, size_t row, size_t col, size_t rows, size_t cols, bool* visted)
{
	int count = 0;
	if (Check(threshold, row, col, rows, cols, visted))
	{
		visted[row * cols + col] = true;
		count = 1 + MovingCountCore(threshold, row - 1, col, rows, cols, visted) + MovingCountCore(threshold, row + 1, col, rows, cols, visted) + MovingCountCore(threshold, row, col - 1, rows, cols, visted) + MovingCountCore(threshold, row, col + 1, rows, cols, visted);
		return count;
	}
}

int MovingCount(int threshold, size_t rows, size_t cols)
{
	if (threshold < 0 || rows <= 0 || cols <= 0)
	{
		return 0;
	}
	bool* visted = new bool[rows * cols];
	for (int i = 0; i < rows * cols; ++i)
	{
		visted[i] = false;
	}
	int count = MovingCountCore(threshold, 0, 0, rows, cols, visted);
	delete[] visted;
	return count;
}

//剪绳子
//动归
int DPMaxProductAfterCutting(size_t length)
{
	if (length < 2)
	{
		return 0;
	}
	if (length == 2)
	{
		return 1;
	}
	if (length == 3)
	{
		return 2;
	}
	int* products = new int[length + 1];
	products[0] = 0;
	products[1] = 0;
	products[2] = 1;
	products[3] = 2;
	int max = 0;
	for (int i = 4; i <= length; ++i)
	{
		for (int j = 1; j <= i / 2; ++j)
		{
			int product = products[j] * products[i - j];
			if (product > max)
			{
				max = product;
			}
			products[i] = max;
		}
	}
	max = products[length];
	delete[]products;
	return max;
}

//贪心算法
int GreedyMaxProductAfterCutting(size_t length)
{
	if (length < 2)
	{
		return 0;
	}
	if (length == 2)
	{
		return 1;
	}
	if (length == 3)
	{
		return 2;
	}
	size_t timesof3 = length / 3;
	if (length - 3 * timesof3 == 1)
	{
		timesof3 -= 1;
	}
	size_t timesof2 = (length - 3 * timesof3) / 2;
	return (int)pow(3, timesof3) * (int)pow(2, timesof2);
}

//正数右移补0，负数右移补1
//除法效率要比移位慢得多

//输出二进制中1的个数
int NumberOf1(int n)
{
	int count = 0;
	while (n)
	{
		++count;
		//一个整数减去1后和自己与可以将最右侧的1变为0，所以有多少个1就能运行多少次
		n = (n - 1) & n;
	}
	//这种return默认返回副本
	//return不要返回指针或引用的local变量
	return count;
}

//由于精度的问题，不能用等号判断两个小数是否相等
//不能忽略边界及异常，做好参数检查、非法输入等
//功能测试、边界测试、负面测试
//可扩展性、可维护性

//数值的整数次方

double PowerWithUnsignedExponent(double base, unsigned exponent)
{
	if (exponent == 0)
	{
		return 1;
	}
	if (exponent == 1)
	{
		return base;
	}
	double result = PowerWithUnsignedExponent(base, exponent >> 1);
	result *= result;
	if ((exponent & 0x1) == 1)
	{
		result *= base;
	}
	return result;
}

bool invalidinput = false;

double Power(double base, int exponent)
{
	invalidinput = false;
	if ((base == 0.0) && exponent < 0)
	{
		invalidinput = true;
		return 0.0;
	}
	unsigned int absexponent = (unsigned int)(exponent);
	if (exponent < 0)
	{
		absexponent = (unsigned int)(-exponent);
	}
	double result = PowerWithUnsignedExponent(base, absexponent);
	if (exponent < 0)
	{
		result = 1.0 / result;
	}
	return result;
}

//赫夫曼编码 贪心
class Huffman
{
public:
	Huffman() :name('\0'), weight(0), left(nullptr), right(nullptr) {};
	Huffman(const char name, const int weight, Huffman* left, Huffman* right) :name(name), weight(weight), left(left), right(right) {};
	Huffman(const Huffman& h) :name(h.name), weight(h.weight), left(h.left), right(h.right) {};
	char GetName()
	{
		return name;
	}
	int GetWeight()
	{
		return weight;
	}
	Huffman* GetLeft()
	{
		return left;
	}
	Huffman* GetRight()
	{
		return right;
	}
	void SetWeight(const int& weight)
	{
		this->weight = weight;
	}
	void SetLeft(Huffman* h)
	{
		this->left = h;
	}
	void SetRight(Huffman* h)
	{
		this->right = h;
	}
	~Huffman() = default;
private:
	char name;
	int weight;
	Huffman* left, * right;
};

void Sort(vector<Huffman*>& v)
{
	size_t n = v.size();
	for (size_t i = 0; i < n - 1; ++i)
	{
		for (size_t j = 0; j < n - 1 - i; ++j)
		{
			if (v[j]->GetWeight() > v[j + 1]->GetWeight())
			{
				Huffman* temp = v[j];
				v[j] = v[j + 1];
				v[j + 1] = temp;
			}
		}
	}
}

Huffman* Top(vector<Huffman*>& v)
{
	Sort(v);
	Huffman* h = v[0];
	v.erase(v.begin());
	return h;
}

Huffman* HuffmanTree()
{
	Huffman* f = new Huffman('f', 5, nullptr, nullptr);
	Huffman* e = new Huffman('e', 9, nullptr, nullptr);
	Huffman* c = new Huffman('c', 12, nullptr, nullptr);
	Huffman* b = new Huffman('b', 13, nullptr, nullptr);
	Huffman* d = new Huffman('d', 16, nullptr, nullptr);
	Huffman* a = new Huffman('a', 45, nullptr, nullptr);
	vector<Huffman*> v;
	v.push_back(f);
	v.push_back(e);
	v.push_back(c);
	v.push_back(b);
	v.push_back(d);
	v.push_back(a);
	size_t n = v.size();
	for (size_t i = 0; i < n - 1; ++i)
	{
		Huffman* z = new Huffman(), * x(Top(v)), * y(Top(v));
		z->SetLeft(x);
		z->SetRight(y);
		z->SetWeight(x->GetWeight() + y->GetWeight());
		v.push_back(z);
	}
	return Top(v);
}

//打印从1到最大的n位数
//考虑到大数问题使用字符串或数组解决
//其实就是全排列

void PrintNumber(char* number)
{
	bool isbeginning0 = true;
	int nlength = strlen(number);
	for (int i = 0; i < nlength; ++i)
	{
		if (isbeginning0 && number[i] != '0')
		{
			isbeginning0 = false;
		}
		if (!isbeginning0)
		{
			cout << number[i];
		}
	}
	cout << "\t";
}

void Print1ToMaxOfNDigitsRecursively(char* number, int length, int index)
{
	if (index == length - 1)
	{
		PrintNumber(number);
		return;
	}
	for (int i = 0; i < 10; ++i)
	{
		number[index + 1] = i + '0';
		Print1ToMaxOfNDigitsRecursively(number, length, index + 1);
	}
}

void Print1ToMaxOfNDigits(size_t n)
{
	if (n <= 0)
	{
		return;
	}
	//多放一个'\0'
	char* number = new char[n + 1];
	number[n] = '\0';
	for (int i = 0; i < 10; ++i)
	{
		number[0] = i + '0';
		Print1ToMaxOfNDigitsRecursively(number, n, 0);
	}
	delete[] number;
}

//在O(1)时间内删除链表节点
struct ListNode
{
	int data;
	ListNode* next;
};

void DeleteNode(ListNode** head, ListNode* deleted)
{
	if (!head || !deleted)
	{
		return;
	}
	if (deleted->next != nullptr)
	{
		ListNode* node = deleted->next;
		deleted->data = node->data;
		deleted->next = node->next;
		delete node;
		node = nullptr;
	}
	else if (*head == deleted)
	{
		delete deleted;
		deleted = nullptr;
		*head = nullptr;
	}
	else
	{
		ListNode* node = *head;
		while (node->next != deleted)
		{
			node = node->next;
		}
		node->next = nullptr;
		delete deleted;
		deleted = nullptr;
	}
}

//删除排序的链表中重复的节点
//因为head也可能被删除，所以使用**head
void DeleteDuplication(ListNode** head)
{
	if (head == nullptr || *head == nullptr)
	{
		return;
	}
	ListNode* prenode = nullptr;
	ListNode* node = *head;
	while (node != nullptr)
	{
		ListNode* next = node->next;
		bool needdelete = false;
		if (next != nullptr && next->data == node->data)
		{
			needdelete = true;
		}
		if (!needdelete)
		{
			prenode = node;
			node = node->next;
		}
		else
		{
			int data = node->data;
			ListNode* tobedelete = node;
			while (tobedelete != nullptr && tobedelete->data == data)
			{
				next = tobedelete->next;
				delete tobedelete;
				tobedelete = nullptr;
				tobedelete = next;
			}
			if (prenode == nullptr)
			{
				*head = next;
			}
			else
			{
				prenode->next = next;
			}
			node = next;
		}
	}
}

//正则表达式匹配
bool MatchCore(char* str, char* pattern)
{
	if (*str == '\0' && *pattern == '\0')
	{
		return true;
	}
	if (*str != '\0' && *pattern == '\0')
	{
		return false;
	}
	if (*(pattern + 1) == '*')
	{
		if (*pattern == *str || (*pattern == '.' && *str != '\0'))
		{
			return MatchCore(str + 1, pattern + 2) || MatchCore(str + 1, pattern) || MatchCore(str, pattern + 2);
		}
		else
		{
			return MatchCore(str, pattern + 2);
		}
	}
	if (*str == *pattern || (*pattern == '.' && *str != '\0'))
	{
		return MatchCore(str + 1, pattern + 1);
	}
}

bool Match(char* str, char* pattern)
{
	if (str == nullptr || pattern == nullptr)
	{
		return false;
	}
	return MatchCore(str, pattern);
}

//表示数值的字符串

bool ScanUnsignedInteger(const char** str)
{
	const char* before = *str;
	while (**str != '\0' && **str >= '0' && **str <= '9')
	{
		++(*str);
	}
	return *str > before;
}

bool ScanInteger(const char** str)
{
	if (**str == '+' || **str == '-')
	{
		++(*str);
	}
	return ScanUnsignedInteger(str);
}

bool IsNumber(const char* str)
{
	if (str == nullptr)
	{
		return false;
	}
	bool numeric = ScanInteger(&str);
	if (*str == '.')
	{
		++str;
		numeric = ScanUnsignedInteger(&str) || numeric;
	}
	if (*str == 'e' || *str == 'E')
	{
		++str;
		numeric = numeric || ScanInteger(&str);
	}
	return numeric && *str == '\0';
}

//摊还分析使用摊还代价，确定不同操作组成的集合“平均”代价
//聚合分析 核算法 聚能法

//内存(RAM)用红黑树，磁盘(辅存)用B树
//B树类似红黑树，是一种平衡搜索树
//不同点在于B树可以有很多孩子，红黑树是二叉树
//B树就是把所以孩子数据及指向它们的指针都存在一起，检索一个结点关键字即可检索其所有孩子
//省去了大量磁盘访问，因为每次检索一个结点都是一次磁盘访问

struct BTreeNode
{
	int* keys;
	BTreeNode** childs;
	bool leaf;
	int n;
	int t;
};

class BTree
{
public:
	BTree(int t) :root(nullptr), t(t) {}
	void SetRoot(BTreeNode* x)
	{
		this->root = x;
	}
	BTreeNode* GetRoot()
	{
		return root;
	}
private:
	BTreeNode* root;
	int t;
};

void BTreeCreate(BTree* t)
{
	BTreeNode* x = new BTreeNode();
	x->leaf = true;
	x->n = 0;
	t->SetRoot(x);
}

BTreeNode* BTreeSerach(BTreeNode* r, int x)
{
	int i = 0;
	while (i < r->n && x > r->keys[i])
	{
		++i;
	}
	if (r->keys[i] == x)
		return r;
	if (r->leaf)
		return nullptr;
	return BTreeSerach(r->childs[i], x);
}

//B树的插入需要按照中间关键字进行分裂
void BTreeSplitChild(BTreeNode* x, int i)
{
	int t = x->t;
	BTreeNode* z = new BTreeNode();
	BTreeNode* y = x->childs[i];
	z->leaf = y->leaf;
	z->n = t;
	for (int j = 0; i < j - 1; ++j)
	{
		z->keys[j] = y->keys[j + t];
	}
	if (!y->leaf)
	{
		for (int j = 0; j < t; ++j)
		{
			z->childs[j] = y->childs[j + t];
		}
	}
	y->n = x->t - 1;
	for (int j = x->n; j >= i + 1; --j)
	{
		x->childs[j + 1] = x->childs[j];
	}
	x->childs[i + 1] = z;
	for (int j = x->n; j >= i; --j)
	{
		x->keys[j + 1] = x->keys[j];
	}
	x->keys[i] = y->keys[i];
	x->n = x->n + 1;
}

void BTreeInsertNonFull(BTreeNode* x, int k)
{
	int i = x->n - 1;
	if (x->leaf)
	{
		while (i >= 0 && k < x->keys[i])
		{
			x->keys[i + 1] = x->keys[i];
			--i;
		}
		x->keys[i + 1] = k;
		x->n = x->n + 1;
	}
	else
	{
		while (i >= 0 && k < x->keys[i])
		{
			--i;
		}
		++i;
		if (x->childs[i]->n == 2 * x->t - 1)
		{
			BTreeSplitChild(x, i);
		}
		if (k > x->keys[i])
		{
			++i;
		}
		BTreeInsertNonFull(x->childs[i], k);
	}
}

void Insert(BTree* t, int k)
{
	BTreeNode* r = t->GetRoot();
	if (r->n == r->t * 2 - 1)
	{
		BTreeNode* s = new BTreeNode();
		t->SetRoot(s);
		s->leaf = false;
		s->n = 0;
		s->childs[0] = r;
		BTreeSplitChild(s, 1);
		BTreeInsertNonFull(s, k);
	}
	else
	{
		BTreeInsertNonFull(r, k);
	}
}

//调整数组顺序使奇数位于偶数前面
//类似策略模式的函数写法

bool IsEvent(int n)
{
	return (n % 2 == 0);
}

void Reorder(int* data, size_t n, bool(*func)(int))
{
	if (data == nullptr || n == 0)
	{
		return;
	}
	int* begin = new int;
	begin = data;
	int* end = new int;
	end = data + n - 1;
	while (begin < end)
	{
		while ((begin < end) && !func(*begin))
		{
			++begin;
		}
		while ((begin < end) && func(*end))
		{
			--end;
		}
		if (begin < end)
		{
			int temp = *begin;
			*begin = *end;
			*end = temp;
		}
	}
}

void ReorderOddEvent(int* data, size_t n)
{
	Reorder(data, n, IsEvent);
}

//链表中倒数第k个结点
ListNode* FindKthToTail(ListNode* head, size_t k)
{
	if (head == nullptr || k <= 0)
	{
		return nullptr;
	}
	else
	{
		ListNode* first = head;
		for (int i = 0; i < k - 1; ++i)
		{
			if (first->next != nullptr)
			{
				first = first->next;
			}
			else
			{
				return nullptr;
			}
		}
		ListNode* last = head;
		while (first->next)
		{
			first = first->next;
			last = last->next;
		}
		return last;
	}
}

//链表中环的入口结点
ListNode* MeetingNode(ListNode* head)
{
	if (head == nullptr)
	{
		return nullptr;
	}
	ListNode* slow = head->next;
	if (slow == nullptr)
	{
		return nullptr;
	}
	ListNode* fast = slow->next;
	while (fast != nullptr && slow != nullptr)
	{
		if (fast == slow)
		{
			return fast;
		}
		slow = slow->next;
		fast = fast->next;
		if (fast != nullptr)
		{
			fast = fast->next;
		}
	}
	return nullptr;
}

ListNode* EntryNodeOfLoop(ListNode* head)
{
	ListNode* meeting = MeetingNode(head);
	if (meeting == nullptr)
	{
		return nullptr;
	}
	int nodesinloop = 1;
	ListNode* pnode = meeting;
	while (pnode->next != meeting)
	{
		pnode = pnode->next;
		++nodesinloop;
	}
	pnode = head;
	for (int i = 0; i < nodesinloop; ++i)
	{
		pnode = pnode->next;
	}
	ListNode* pnode1 = head;
	while (pnode != pnode1)
	{
		pnode = pnode->next;
		pnode1 = pnode1->next;
	}
	return pnode;
}

//反转链表
ListNode* ReverseList(ListNode* head) {
	ListNode* pre = nullptr;
	ListNode* curr = head;
	while (curr)
	{
		ListNode* post = curr->next;
		curr->next = pre;
		pre = curr;
		curr = post;
	}
	return pre;
}

//合并两个递增链表
ListNode* Merge(ListNode* list1, ListNode* list2)
{
	ListNode* list = nullptr;
	if (list1 == nullptr && list2 == nullptr)
	{
		return nullptr;
	}
	else if (list1 == nullptr)
	{
		list = list2;
		return list;
	}
	else if (list2 == nullptr)
	{
		list = list1;
		return list;
	}
	else
	{
		list = new ListNode();
		ListNode* listhead = list, * listhead1 = list1, * listhead2 = list2;
		while (listhead1 != nullptr && listhead2 != nullptr)
		{
			ListNode* node = new ListNode();
			if (listhead1->data <= listhead2->data)
			{
				node->data = listhead1->data;
				listhead1 = listhead1->next;
			}
			else
			{
				node->data = listhead2->data;
				listhead2 = listhead2->next;
			}
			listhead->next = node;
			listhead = listhead->next;
		}
		while (listhead1 != nullptr)
		{
			listhead->next = listhead1;
			listhead = listhead->next;
			listhead1 = listhead1->next;
		}
		while (listhead2 != nullptr)
		{
			listhead->next = listhead2;
			listhead = listhead->next;
			listhead2 = listhead2->next;
		}
		return list->next;
	}
}

//树的子结构

struct BinaryTreeNode
{
	double value;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
};

bool Equal(const double& n1, const double& n2)
{
	//只要相差很小就可以认定相同，这就是为什么自定义Equal函数
	if ((n1 - n2 > -0.0000001) && (n1 - n2) < 0.0000001)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool DoesTree1HaveTree2(BinaryTreeNode* p1, BinaryTreeNode* p2)
{
	if (p2 == nullptr)
	{
		return true;
	}
	if (p1 == nullptr)
	{
		return false;
	}
	if (!Equal(p1->value, p2->value))
	{
		return false;
	}
	return DoesTree1HaveTree2(p1->left, p2->left) && DoesTree1HaveTree2(p1->right, p2->right);
}

bool HasSubtree(BinaryTreeNode* r1, BinaryTreeNode* r2)
{
	bool result = false;
	if (r1 != nullptr && r2 != nullptr)
	{
		if (Equal(r1->value, r2->value))
		{
			result = DoesTree1HaveTree2(r1, r2);
		}
		if (!result)
		{
			result = DoesTree1HaveTree2(r1->left, r2);
		}
		if (!result)
		{
			result = DoesTree1HaveTree2(r1->right, r2);
		}
	}
	return result;
}

int main(int argc, char* argv[])
{
	//int weight[3] = { 1,3,4 };
	//int value[3] = { 15,20,30 };
	//int bagweight = 4;
	////KnapSack(weight, value, bagweight, 3);
	//GreedyKnapSack(value, weight, bagweight, 3);
	//Print1ToMaxOfNDigits(3);
	/*Huffman *h = HuffmanTree();
	cout << h->GetRight()->GetRight()->GetLeft()->GetWeight();*/
	ListNode* h1 = new ListNode();
	h1->data = 1;
	ListNode* h2 = new ListNode();
	h2->data = 2;
	ListNode* h3 = new ListNode();
	h3->data = 4;
	h1->next = h2;
	h2->next = h3;
	h3->next = nullptr;
	ListNode* h4 = new ListNode();
	h4->data = 1;
	ListNode* h5 = new ListNode();
	h5->data = 3;
	ListNode* h6 = new ListNode();
	h6->data = 4;
	h4->next = h5;
	h5->next = h6;
	h6->next = nullptr;
	ListNode* h = Merge(h1, h4);
	while (h != nullptr)
	{
		cout << h->data;
		h = h->next;
	}

	return 0;
}