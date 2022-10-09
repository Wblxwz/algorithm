#include <iostream>
#include <typeinfo>
#include <stack>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

template<typename T>
bool Swap(T& t1, T& t2)
{
	T t = t1;
	t1 = t2;
	t2 = t;
	return true;
}

//����ģ��������
template<> bool Swap(double& d1, double& d2)
{
	std::cout << "double";
	return true;
}

//�������ظ������� ����Ϊn������[0~n-1] Ѱ�������ظ�����
//ʱ�临�Ӷ�O(n),�ռ临�Ӷ�O(1)
int Duplicate(int* p, const int len)
{
	if (p == nullptr || len <= 0)
	{
		return -1;
	}
	for (int i = 0; i < len; ++i)
	{
		if (p[i] < 0 || p[i] > len - 1)
		{
			return -1;
		}
	}
	for (int i = 0; i < len; ++i)
	{
		while (p[i] != i)
		{
			if (p[i] == p[p[i]])
			{
				return p[i];
			}
			Swap(p[i], p[p[i]]);
		}
	}
	return -1;
}

//���޸������������ҳ����⣨��������!���ظ�������,��Χ��1~n-1
//����ʹ�ø������� O(n)�ĸ����洢�ռ�
//��ʹ�ø����ռ�ʱ���ƶ��ֲ���
//ʱ�临�Ӷ�O(nlogn)

int CountRange(const int* p, const int len, const int start, const int end)
{
	if (p == nullptr)
	{
		return 0;
	}
	int count = 0;
	for (int i = 0; i < len; ++i)
	{
		if (p[i] >= start && p[i] <= end)
		{
			++count;
		}
	}
	return count;
}

int GetDuplication(const int* p, const int len)
{
	if (p == nullptr || len <= 0)
	{
		return -1;
	}
	int start = 1;
	int end = len - 1;
	while (end >= start)
	{
		//����һλ������2
		int mid = ((end - start) >> 1) + start;
		int count = CountRange(p, len, start, mid);
		if (end == start)
		{
			if (count > 1)
			{
				return start;
			}
			else
			{
				break;
			}
		}
		if (count > (mid - start) + 1)
		{
			end = mid;
		}
		else
		{
			start = mid + 1;
		}
	}
	return -1;
}

//���ֲ���
template<typename T>
T BinarySerach(T* a, int start, int end, int key)
{
	int ret = -1;
	while (start <= end)
	{
		//��ֱֹ�ӳ������
		int mid = ((end - start) >> 1) + start;
		if (a[mid] < key)
		{
			start = mid + 1;
		}
		else if (a[mid] > key)
		{
			end = mid - 1;
		}
		else
		{
			ret = mid;
			break;
		}
	}
	return ret;
}

//��ά���飨���ҵ������ϵ��µ������ж��Ƿ���ָ��������
bool Find(int** matrix, int rows, int columns, int number)
{
	bool found = false;
	if (matrix != nullptr && rows > 0 && columns > 0)
	{
		int row = 0;
		int column = columns - 1;
		while (row < rows && column >= 0)
		{
			if (matrix[row][column] == number)
			{
				found = true;
				break;
			}
			else if (matrix[row][column] > number)
			{
				--column;
			}
			else
			{
				++row;
			}
		}
	}
	return found;
}


//�����������
vector<vector<int>> LcsLength(const string& x, const string& y)
{
	size_t m = x.length(), n = y.length();
	vector<vector<int>> b(m);
	for (int i = 0; i < m; ++i)
	{
		b[i].resize(n);
	}
	vector<vector<int>> c(m + 1);
	for (int i = 0; i < m + 1; ++i)
	{
		c[i].resize(n + 1);
	}
	for (int i = 1; i <= m; ++i)
	{
		c[i][0] = 0;
	}
	for (int j = 0; j <= n; ++j)
	{
		c[0][j] = 0;
	}
	for (size_t i = 1; i <= m; ++i)
	{
		for (size_t j = 1; j <= n; ++j)
		{
			if (x[i - 1] == y[j - 1])
			{
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i - 1][j - 1] = '�I';
			}
			else if (c[i - 1][j] >= c[i][j - 1])
			{
				c[i][j] = c[i - 1][j];
				b[i - 1][j - 1] = '��';
			}
			//else������������Ϊ��ʱִ��
			else
			{
				c[i][j] = c[i][j - 1];
				b[i - 1][j - 1] = '��';
			}
		}
	}
	return b;
}

void PrintLcs(const vector<vector<int>>& b, const string& x, const size_t& i, const size_t& j)
{
	if (i == 0 || j == 0)
	{
		return;
	}
	if (b[i - 1][j - 1] == '�I')
	{
		PrintLcs(b, x, i - 1, j - 1);
		cout << x[i - 1];
	}
	else if (b[i - 1][j - 1] == '��')
	{
		PrintLcs(b, x, i - 1, j);
	}
	else
	{
		PrintLcs(b, x, i, j - 1);
	}
}

//���ַ����еĿո��Ϊ%20
void ReplaceBlank(char* s, int length)
{
	if (s == nullptr || length <= 0)
	{
		return;
	}
	int originallength = 0;
	int numberofblank = 0;
	int i = 0;
	while (s[i] != '\0')
	{
		++originallength;
		if (s[i] == ' ')
		{
			++numberofblank;
		}
		++i;
	}
	int newlength = originallength + 2 * numberofblank;
	//length������������[���]
	if (newlength > length)
	{
		return;
	}
	int indexoforiginal = originallength;
	int indexofnew = newlength;
	while (indexoforiginal >= 0 && indexofnew > indexoforiginal)
	{
		if (s[indexoforiginal] == ' ')
		{
			s[indexofnew--] = '0';
			s[indexofnew--] = '2';
			s[indexofnew--] = '%';
		}
		else
		{
			s[indexofnew--] = s[indexoforiginal];
		}
		--indexoforiginal;
	}
}

struct ListNode
{
	int data;
	ListNode* next;
};


void AddToTail(ListNode** head, const int& value)
{
	//�Զ�����new��ü�����
	ListNode* node = new ListNode();
	node->data = value;
	node->next = nullptr;
	if (*head == nullptr)
	{
		*head = node;
	}
	else
	{
		ListNode* phead = *head;
		while (phead->next != nullptr)
		{
			phead = phead->next;
		}
		phead->next = node;
	}
}

void RemoveNode(ListNode** head, const int& value)
{
	if (*head == nullptr || head == nullptr)
	{
		return;
	}
	ListNode* node = *head;
	if (node->data == value)
	{
		*head = node->next;
		delete node;
	}
	else
	{
		while (node->next != nullptr)
		{
			if (node->next->data == value)
			{
				ListNode* p = node->next;
				node->next = p->next;
				delete p;
				break;
			}
			node = node->next;
		}
	}
}

void PrintListNode(ListNode** head)
{
	if (head == nullptr || *head == nullptr)
	{
		return;
	}
	ListNode* node = *head;
	while (node != nullptr)
	{
		cout << node->data << " ";
		node = node->next;
	}
}

//��β��ͷ��ӡ����,���Ըı�����ָ��˳��Ҳ����������ջ������
ListNode* Reversal(ListNode* head)
{
	if (head == nullptr || head->next == nullptr)
	{
		return head;
	}
	else
	{
		ListNode* begin = nullptr, * mid = head, * end = head->next;
		while (true)
		{
			mid->next = begin;
			if (end == nullptr)
			{
				break;
			}
			begin = mid;
			mid = end;
			end = end->next;
		}
		head = mid;
		return head;
	}
}

void PrintTailToHead(ListNode** head)
{
	if (*head == nullptr)
	{
		return;
	}
	std::stack<ListNode*> stack;
	ListNode* node = *head;
	while (node != nullptr)
	{
		stack.push(node);
		node = node->next;
	}
	while (!stack.empty())
	{
		ListNode* node = stack.top();
		cout << node->data << " ";
		stack.pop();
	}
}
//��β��ͷ��ӡ����ݹ��,���ܵ��º�������ջ�����(�����û�ջ������)
void PrintTailToHeadRecursion(ListNode** head)
{
	if (*head != nullptr)
	{
		if ((*head)->next != nullptr)
		{
			PrintTailToHeadRecursion(&(*head)->next);
		}
		cout << (*head)->data << " ";
	}
}

//���Ŷ���������(��������������С�Ķ�����)
std::pair<vector<vector<int>>, vector<vector<int>>> Optimalbst(int* p, int* q, size_t length)
{
	vector<vector<int>> e(length + 1);
	for (auto i : e)
	{
		i.resize(length + 1);
	}
	vector<vector<int>> w(length + 1);
	for (auto i : w)
	{
		i.resize(length + 1);
	}
	vector<vector<int>> root(length);
	for (auto i : root)
	{
		i.resize(length);
	}
	for (size_t i = 1; i <= length; ++i)
	{
		e[i][i - 1] = q[i - 1];
		w[i][i - 1] = q[i - 1];
	}
	for (size_t l = 1; l <= length; ++l)
	{
		for (size_t i = 1; i <= length - l + 1; ++i)
		{
			size_t j = i + l - 1;
			e[i][j] = INT_MAX;
			w[i][j] = w[i][j - 1] + p[j] + q[j];
			for (size_t r = i; r <= j; ++r)
			{
				size_t t = (size_t)e[i][r - 1] + e[r + 1][j] + w[i][j];
				if (t < e[i][j])
				{
					e[i][j] = t;
					root[i][j] = r;
				}
			}
		}
	}
	return std::make_pair(e, root);
}

//�ؽ�������(����ǰ������������������������)
struct BinaryTreeNode
{
	int value;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
	BinaryTreeNode* parent;
};

BinaryTreeNode* ConstructCore(int* startpreorder, int* endpreorder, int* startinorder, int* endinorder)
{
	int rootvalue = startpreorder[0];
	BinaryTreeNode* root = new BinaryTreeNode();
	root->value = rootvalue;
	root->left = root->right = nullptr;
	if (startpreorder == endpreorder)
	{
		if (startinorder == endinorder && *startpreorder == *startinorder)
		{
			return root;
		}
		else
		{
			throw "Invalid input";
		}
	}
	int* rootinorder = startinorder;
	while (rootinorder <= endinorder && *rootinorder != rootvalue)
	{
		++rootinorder;
	}
	if (rootinorder == endinorder && *rootinorder != rootvalue)
	{
		throw "Invalid input";
	}
	int leftlength = rootinorder - startinorder;
	int* leftpreorderend = startpreorder + leftlength;
	if (leftlength > 0)
	{
		root->left = ConstructCore(startpreorder + 1, leftpreorderend, startinorder, rootinorder - 1);
	}
	if (leftlength < endpreorder - startpreorder)
	{
		root->right = ConstructCore(leftpreorderend + 1, endpreorder, rootinorder + 1, endinorder);
	}
	return root;
}

BinaryTreeNode* Construct(int* preorder, int* inorder, int length)
{
	if (preorder == nullptr || inorder == nullptr || length == 0)
	{
		return nullptr;
	}
	return ConstructCore(preorder, preorder + length - 1, inorder, inorder + length - 1);
}

//����������һ�����
BinaryTreeNode* GetNext(BinaryTreeNode* pnode)
{
	if (pnode == nullptr)
	{
		return nullptr;
	}
	BinaryTreeNode* pnext = nullptr;
	if (pnode->right != nullptr)
	{
		BinaryTreeNode* pright = pnode->right;
		while (pright->left != nullptr)
		{
			pright = pright->left;
		}
		pnext = pright;
	}
	else if (pnode->parent != nullptr)
	{
		BinaryTreeNode* pparent = pnode->parent;
		BinaryTreeNode* pcurrent = pnode;
		while (pparent != nullptr && pcurrent == pparent->right)
		{
			pcurrent = pparent;
			pparent = pparent->parent;
		}
		pnext = pparent;
	}
	return pnext;
}

//������ջʵ�ֶ���
template<typename T>
class CQueue
{
public:
	CQueue(void);
	~CQueue(void);
	void appendTail(const T& node);
	T deleteHead();
private:
	std::stack<T> stack1;
	std::stack<T> stack2;
};

template<typename T>
void CQueue<T>::appendTail(const T& node)
{
	stack1.push(node);
}
template<typename T>
T CQueue<T>::deleteHead()
{
	if (stack2.size() <= 0)
	{
		while (stack1.size() > 0)
		{
			T& data = stack1.top();
			//pop������ջ��ֵ
			stack1.pop();
			stack2.push(data);
		}
	}
	if (stack2.size() == 0)
	{
		throw new std::exception("queue is empty");
	}
	T head = stack2.pop();
	stack2.pop();
	return head;
}

//����ʹ�õݹ��ѭ������
int AddFrom1ToN(int n)
{
	return n <= 0 ? 0 : AddFrom1ToN(n - 1);
}

//�ݹ��ٶ����Ҵ���ջ�������
//���ö�̬�滮��̰���㷨
//��̬�滮��쳲��������� O(n)
long long Fibonacci(unsigned n)
{
	int result[2] = { 0,1 };
	if (n < 2)
	{
		return result[n];
	}
	long long fibNMinusOne = 1;
	long long fibNMinusTwo = 0;
	long long fibN = 0;
	for (unsigned int i = 2; i <= n; ++i)
	{
		fibN = fibNMinusOne + fibNMinusTwo;
		fibNMinusTwo = fibNMinusOne;
		fibNMinusOne = fibN;
	}
	return fibN;
}

//������̨��
long long Jump(int n)
{
	int result[3] = { 0,1,2 };
	if (n < 3)
	{
		return result[n];
	}
	long long Min = 1;
	long long Max = 2;
	long long Return = 0;
	for (unsigned i = 3; i <= n; ++i)
	{
		Return = Min + Max;
		Min = Max;
		Max = Return;
	}
	return Return;
}

int main(int argc, char* argv[])
{
	/*int p[7]{ 2,3,1,0,2,5,3 };
	cout << Duplicate(p, 7) << endl;
	double d1 = 1.1, d2 = 2.2;
	Swap(d1, d2);*/

	/*string x = "ABCBDAB";
	string y = "BDCABA";
	vector<vector<int>> b = LcsLength(x, y);
	PrintLcs(b, x, x.length(), y.length());*/

	/*int* a = new int[10];
	for (int i = 0; i < 10; ++i)
	{
		a[i] = i + 1;
	}
	std::cout << BinarySerach(a, 0, 9, 1);
	delete[]a;*/

	/*int** a = new int* [4];
	for (int i = 0; i < 4; ++i)
	{
		a[i] = new int[4];
	}
	int cnt = 1;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			a[i][j] = cnt++;
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			cout << a[i][j] << "\t";
		}
		cout << endl;
	}
	cout << Find(a, 4, 4, 15);
	for (int i = 0; i < 4; ++i)
	{
		delete []a[i];
	}
	delete[]a;*/

	//s[]�ǳ�ʼ����ջ�ϵ����飬�ǿ�д�ģ�*sָ������ֵ����������const�ģ�����ֵ�����ǳ���
	//�����char����ʼ��Ϊ'\0'
	//char s[50] = "hello world!";
	//ReplaceBlank(s, 50);
	///*for (int i = 0; i < 50; ++i)
	//{
	//	cout << s[i];
	//}*/
	//int i = 0;
	//while (s[i] != '\0')
	//{
	//	cout << s[i];
	//	++i;
	//}

	//ListNode* p = new ListNode();
	//p->data = 1;
	//ListNode** head = &p;
	//AddToTail(head, 2);
	//AddToTail(head, 3);
	//AddToTail(head, 4);
	//AddToTail(head, 5);
	///*PrintListNode(head);
	//RemoveNode(head, 3);
	//PrintListNode(head);*/
	////PrintTailToHead(head);
	////PrintTailToHeadRecursion(head);
	//ListNode* l = Reversal(*head);
	//PrintListNode(&l);



	return 0;
}