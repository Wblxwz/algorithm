#include <iostream>
#include <thread>
#include <limits>
#include <Windows.h>
#include<sql.h>
#include<sqlext.h>
#include<sqltypes.h>
#include <fstream>
#include <vector>
#include <string>

using std::cout;
using std::cin;
using std::endl;

//双向链表
struct DoubleList
{
	int data;
	DoubleList* next, * prev;
};

//不带头结点的链表在处理插入/删除表头结点时要额外判断
//带头结点会使其代码更简洁，但会浪费部分空间
void initList(DoubleList* l)//尾插法(与输入顺序相同)
{
	bool flag = true;
	int n = 0;
	DoubleList* r, * head = new DoubleList;
	head->prev = l;
	head->next = nullptr;
	l->prev = nullptr;
	l->next = head;
	r = head;
	while (flag)
	{
		if (n != -1)
		{
			std::cin >> n;
			DoubleList* s = new DoubleList;
			s->data = n;
			s->next = nullptr;
			r->next = s;
			s->prev = r;
			r = r->next;
		}
		else
			flag = false;
	}
}

void insertList(DoubleList* l, const int& n, const int& x)
{
	l = l->next;
	for (int i = 0; i < n - 1; ++i)
		l = l->next;
	DoubleList* q = new DoubleList;
	q->data = x;
	q->next = l->next;
	l->next->prev = q;
	l->next = q;
	q->prev = l;
}

void deleteList(DoubleList* l, const int& n)
{
	l = l->next;
	for (int i = 0; i < n - 1; ++i)
		l = l->next;
	DoubleList* s = l->next;
	l->next = s->next;
	s->next->prev = l;
	delete s;
}

DoubleList* searchList(DoubleList* l, const int& n)
{
	while (l->next && l->data != n)
		l = l->next;
	return l;
}

void printList(DoubleList* l)
{
	l = l->next->next;
	while (l->next)
	{
		std::cout << l->data << " ";
		l = l->next;
	}
	std::cout << std::endl;
}


//直接寻址表
struct Address
{
	int key;
	int weiXingShuJu;
};

Address* directAddressSearch(Address** d, int& k)
{
	return d[k];
}

void directAddressInsert(Address** T, Address* x)
{
	T[x->key] = x;
}

void directAddressDelete(Address** T, Address* x)
{
	T[x->key] = nullptr;
}

//除法散列法
int chuHash(const int& key, const int& m)
{
	return key % m;
}
//乘法散列法
//a为依据Knuth所获得的常数,floor为向下取整
int chengHash(const size_t& key, const size_t& m, const size_t& a)
{
	return floor(m * (key * a - floor(key * a)));
}
//散列表(链接法解决冲突)

struct Data
{
	int key;
	int data;
};

void hashInsert(DoubleList** l, Data& d, int* n)
{
	int k = chuHash(d.key, 10);
	if (n[k] == 0)
	{
		l[k] = new DoubleList;
		initList(l[k]);
	}
	insertList(l[k], 1, d.key);
	++n[k];
}

DoubleList* hashSearch(DoubleList** l, const int& key)
{
	int k = chuHash(key, 10);
	return searchList(l[k], key);
}

void hashDelete(DoubleList** l, Data& d)
{
	DoubleList* s = hashSearch(l, d.key);
	s->prev->next = s->next;
	s->next->prev = s->prev;
	delete s;
}

//二叉搜索树
struct Node
{
	int key;
	Node* l, * r, * p;
};

class BiSearchTree
{
public:
	BiSearchTree();
	~BiSearchTree() = default;
	void insert(const int& key);
	void inOrder(Node* x);
	void deleteSearch(const int& key);
	//用以v为根节点的子树替换以u为根节点的子树
	void transplant(Node* u, Node* v);
	Node* search(const int& key);
	Node* maxNode(Node* x);
	Node* minNode(Node* x);
	//寻找结点前驱(中序遍历)
	Node* predecessor(Node* x);
	//寻找结点后继(中序遍历)
	Node* successor(Node* x);
	Node* getRoot();
private:
	Node* root;
};

BiSearchTree::BiSearchTree()
{
	root = new Node;
	cout << "root:";
	cin >> root->key;
	root->p = nullptr;
	root->l = nullptr;
	root->r = nullptr;
}

void BiSearchTree::insert(const int& key)
{
	Node* n = new Node;
	n->key = key;
	n->l = nullptr;
	n->r = nullptr;
	n->p = nullptr;
	Node* x = root;
	Node* y = nullptr;
	while (x)
	{
		y = x;
		if (n->key < x->key)
		{
			x = x->l;
		}
		else
		{
			x = x->r;
		}
	}
	n->p = y;
	if (!y)
	{
		root = n;
	}
	else if (n->key < y->key)
	{
		y->l = n;
	}
	else
	{
		y->r = n;
	}
}

void BiSearchTree::inOrder(Node* x)
{
	if (x != nullptr)
	{
		inOrder(x->l);
		cout << x->key << " ";
		inOrder(x->r);
	}
}

void BiSearchTree::deleteSearch(const int& key)
{
	Node* x = search(key);
	if (!x->l)
	{
		transplant(x, x->r);
	}
	else if (!x->r)
	{
		transplant(x, x->l);
	}
	else
	{
		Node* y = minNode(x->r);
		if (y->p != x)
		{
			transplant(y, y->r);
			y->r = x->r;
			y->r->p = y;
		}
		transplant(x, y);
		y->l = x->l;
		y->l->p = y;
	}
}

Node* BiSearchTree::minNode(Node* x)
{
	while (x->l)
	{
		x = x->l;
	}
	return x;
}

Node* BiSearchTree::maxNode(Node* x)
{
	while (x->r)
	{
		x = x->r;
	}
	return x;
}

Node* BiSearchTree::predecessor(Node* x)
{
	if (x->l)
	{
		return maxNode(x->l);
	}
	Node* y = x->p;
	while (y && x == y->l)
	{
		x = y;
		y = y->p;
	}
	return y;
}

Node* BiSearchTree::successor(Node* x)
{
	if (x->r)
		return minNode(x->r);
	Node* y = x->p;
	while (y && x == y->r)
	{
		x = y;
		y = y->p;
	}
	return y;
}

void BiSearchTree::transplant(Node* u, Node* v)
{
	if (!u->p)
	{
		root = v;
	}
	else if (u == u->p->l)
	{
		u->p->l = v;
	}
	else
	{
		u->p->r = v;
	}
	if (v)
		v->p = u->p;
}

Node* BiSearchTree::search(const int& key)
{
	Node* x = root;
	while (x)
	{
		if (key < x->key)
		{
			x = x->l;
		}
		else if (key > x->key)
		{
			x = x->r;
		}
		else
		{
			return x;
		}
	}
	return x;
}

Node* BiSearchTree::getRoot()
{
	return root;
}

//字典树 基数树

//红黑树
enum colorSet {
	Red, Black
};

struct RBNode
{
	RBNode* p, * l, * r;
	int color, key;
};

class RBTree
{
public:
	RBTree();
	~RBTree() = default;
	void leftRotate(RBNode* x);
	void rightRotate(RBNode* y);
	void rbInsert(RBNode* z);
	void rbInsertFixup(RBNode* z);
	void rbDelete(RBNode* z);
	void RBDeleteFixUp(RBNode* x);
	void rbTransplant(RBNode* u, RBNode* v);
	RBNode* RBTreeMin(RBNode* x);
private:
	RBNode* root, * tnull;
};

RBTree::RBTree()
{
	root = new RBNode;
	cout << "root:";
	cin >> root->key;
	root->color = Black;
	root->p = nullptr;
	root->l = nullptr;
	root->r = nullptr;
	tnull->color = Black;
}

void RBTree::leftRotate(RBNode* x)
{
	RBNode* y = x->r;
	x->r = y->l;
	if (y->l != tnull)
	{
		y->l->p = x;
	}
	y->p = x->p;
	if (x->p == tnull)
	{
		root = y;
	}
	else if (x == x->p->l)
	{
		x->p->l = y;
	}
	else
	{
		x->p->r = y;
	}
	y->l = x;
	x->p = y;
}

void RBTree::rightRotate(RBNode* y)
{
	RBNode* x = y->l;
	y->l = x->r;
	if (x->r != tnull)
	{
		x->r->p = y;
	}
	x->p = y->p;
	if (y->p == tnull)
	{
		root = x;
	}
	else if (y == y->p->l)
	{
		y->p->l = x;
	}
	else
	{
		y->p->r = x;
	}
	x->r = y;
	y->p = x;
}

//假设z的key值已经被赋值
void RBTree::rbInsert(RBNode* z)
{
	RBNode* y = tnull;
	RBNode* x = root;
	while (x != tnull)
	{
		y = x;
		if (z->key < x->key)
		{
			x = x->l;
		}
		else
		{
			x = x->r;
		}
	}
	z->p = y;
	if (y == tnull)
	{
		root = z;
	}
	else if (z->key < y->key)
	{
		y->l = z;
	}
	else
	{
		y->r = z;
	}
	//保持红黑树的结构
	z->l = tnull;
	z->r = tnull;
	z->color = Red;
	rbInsertFixup(z);
}

//保持红黑性质，因为插入点为红色结点
void RBTree::rbInsertFixup(RBNode* z)
{
	while (z->p->color == Red)
	{
		//z的父结点的父结点一定存在（5条性质）
		if (z->p == z->p->p->l)
		{
			//情况1 z的叔结点y为红色
			RBNode* y = z->p->p->r;
			if (y->color == Red)
			{
				z->p->color = Black;
				y->color = Black;
				z->p->p->color = Red;
				//一红带两黑
				z = z->p->p;
			}
			else //情况2 z的叔结点是黑色
			{
				if (z == z->p->r) //且z是右孩子
				{
					z = z->p;
					leftRotate(z);//目的将情况2转为情况3,即转到左孩子
				}
				//情况3 且z是左孩子
				z->p->color = Black;
				z->p->p->color = Red;
				rightRotate(z->p->p);
			}
		}
		//叔结点相反，但代码相同
		else
		{
			RBNode* y = z->p->p->l;
			if (y->color == Red)
			{
				z->p->color = Black;
				y->color = Black;
				z->p->p->color = Red;
				z = z->p->p;
			}
			else
			{
				if (z == z->p->l)
				{
					z = z->p;
					rightRotate(z);
				}
				z->p->color = Black;
				z->p->p->color = Red;
				leftRotate(z->p->p);
			}
		}
	}
	root->color = Black;
}

void RBTree::rbTransplant(RBNode* u, RBNode* v)
{
	if (u->p == tnull)
	{
		root = v;
	}
	else if (u == u->p->l)
	{
		u->p->l = v;
	}
	else
	{
		u->p->r = v;
	}
	v->p = u->p;
}

RBNode* RBTree::RBTreeMin(RBNode* x)
{
	while (x->l)
	{
		x = x->l;
	}
	return x;
}

void RBTree::rbDelete(RBNode* z)
{
	RBNode* y = z;
	RBNode* x = new RBNode;
	int original_color = y->color;
	if (z->l == tnull)
	{
		x = z->r;
		rbTransplant(z, z->r);
	}
	else if (z->r == tnull)
	{
		x = z->l;
		rbTransplant(z, z->l);
	}
	else
	{
		y = RBTreeMin(z->r);
		original_color = y->color;
		x = y->r;
		if (y->p == z)
		{
			x->p = y;
		}
		else
		{
			rbTransplant(y, y->r);
			y->r = z->r;
			y->r->p = y;
		}
		rbTransplant(z, y);
		y->l = z->l;
		y->l->p = y;
		y->color = z->color;
	}
	if (original_color == Black)
	{
		RBDeleteFixUp(x);
	}
}

void RBTree::RBDeleteFixUp(RBNode* x)
{
	while (x != root && x->color == Black)
	{
		if (x == x->p->l)
		{
			RBNode* w = x->p->r;
			if (w->color == Red)
			{
				w->color = Black;
				x->p->color = Red;
				leftRotate(x->p);
				w = x->p->r;
			}
			if (w->l->color == Black && w->r->color == Black)
			{
				w->color = Red;
				x = x->p;
			}
			else if (w->r->color == Black)
			{
				w->l->color = Black;
				w->color = Red;
				rightRotate(w);
				w = x->p->r;
			}
			w->color = x->p->color;
			x->p->color = Black;
			w->r->color = Black;
			leftRotate(x->p);
			x = root;
		}
		else
		{
			RBNode* w = x->p->l;
			if (w->color == Red)
			{
				w->color = Black;
				x->p->color = Red;
				rightRotate(x->p);
				w = x->p->l;
			}
			if (w->l->color == Black && w->r->color == Black)
			{
				w->color = Red;
				x = x->p;
			}
			else if (w->l->color == Black)
			{
				w->r->color = Black;
				w->color = Red;
				leftRotate(w);
				w = x->p->l;
			}
			w->color = x->p->color;
			x->p->color = Black;
			w->l->color = Black;
			rightRotate(x->p);
			x = root;
		}
	}
	x->color = Black;
}

//顺序统计树是在红黑树的基础上添加了x.size，即包含以x为根的子树在内的结点数
//要从红黑树中扩展，没加入红黑树的操作，只写了多出来的操作
//并且红黑树的插入删除左旋右旋也要做多余的操作来维护多出来的信息
//哨兵大小为0

struct OsTreeNode
{
	OsTreeNode* left, * right, * p;
	int key, size;
};

class OsTree
{
public:
	OsTreeNode* OsSelect(OsTreeNode* x, int i);
	int OsRank(OsTree* t, OsTreeNode* x);
private:
	OsTreeNode* root;
};

//中序遍历找秩（输出的位置）为i的结点，以t->root做开始结点x
//O(lgn)
OsTreeNode* OsTree::OsSelect(OsTreeNode* x, int i)
{
	int r = x->left->size + 1;//r为x的秩,因为是按中序遍历确定的秩
	if (r == i)
	{
		return x;
	}
	else if (i < r)
	{
		return OsSelect(x->left, i);
	}
	else
	{
		return OsSelect(x->right, i - r);//以x右子树为根的i-r个元素
	}
}

//给定结点x寻找其秩(中序)
//O(lgn)
int OsTree::OsRank(OsTree* t, OsTreeNode* x)
{
	//计算x为根节点的左子树结点个数
	int r = x->left->size + 1;
	OsTreeNode* y = x;
	while (y != t->root)
	{
		if (y == y->p->right)
		{
			r += y->p->left->size + 1;
		}
		y = y->p;
	}
	return r;
}

//区间树

class IntervalTreeNode
{
private:
	IntervalTreeNode* left, * right, * p, * tnull;
	int max, low, high;
public:
	friend class IntervalTree;
	bool operator!=(IntervalTreeNode* t)
	{
		if (max != t->max && low != t->low && high != t->high)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

class IntervalTree
{
public:
	friend class IntervalTree;
	IntervalTreeNode* IntervalSerarch(IntervalTree t, IntervalTreeNode i);
	bool Overlap(IntervalTreeNode i);
private:
	IntervalTreeNode* root;
};

bool IntervalTree::Overlap(IntervalTreeNode i)
{
	//不重叠
	return false;
	//重叠
	return true;
}

//寻找与i重叠的区间x
IntervalTreeNode* IntervalTree::IntervalSerarch(IntervalTree t, IntervalTreeNode i)
{
	IntervalTreeNode* x = t.root;
	while (x != t.root->tnull && !Overlap(i))
	{
		if (x->left != t.root->tnull && x->left->max >= i.low)
		{
			x = x->left;
		}
		else
		{
			x = x->right;
		}
	}
	return x;
}

//动态规划
//钢条切割问题
//递归自顶向下解法(效率很差，因为反复求解相同的子问题)
//T(2^n)
int CutRod(const int* p, const int n)
{
	if (n == 0)
	{
		return 0;
	}
	int q = INT_MIN;
	for (int i = 0; i < n; ++i)
	{
		q = max(q, p[i] + CutRod(p, n - i - 1));
	}
	return q;
}

//动态规划的钢条切割问题
//自顶向下加入“备忘”的解法

int MemoizedCutRodAux(const int* p, const int n, int* r)
{
	int q = 0;
	if (r[n - 1] >= 0)
	{
		return r[n - 1];
	}
	if (n == 0)
	{
		q = 0;
	}
	else
	{
		q = INT_MIN;
		for (int i = 0; i < n; ++i)
		{
			q = max(q, p[i] + MemoizedCutRodAux(p, n - i - 1, r));
		}
	}
	r[n - 1] = q;
	return q;
}

int MemoizedCutRod(const int* p, const int n)
{
	int* r = new int[n];
	for (int i = 0; i < n; ++i)
	{
		r[i] = -1;
	}
	return MemoizedCutRodAux(p, n, r);
}

//自底向上解法
int BottomUpCutRod(const int* p, int n)
{
	++n;
	int* r = new int[n];
	r[0] = 0;
	int q = 0;
	for (int j = 1; j < n; ++j)
	{
		q = INT_MIN;
		for (int i = 0; i < j; ++i)
		{
			q = max(q, p[i] + r[j - i - 1]);
		}
		r[j] = q;
	}
	return r[n - 1];
}

//钢条切割问题不仅给出最优解，也给出构成方式
std::pair<int*, int*> ExtendedBottomUpCutRod(int* p, int n)
{
	++n;
	int* r = new int[n];
	int* s = new int[n];
	s[0] = 0;
	int q = 0;
	r[0] = 0;
	for (int i = 1; i < n; ++i)
	{
		q = INT_MIN;
		for (int j = 0; j < i; ++j)
		{
			if (q < p[j] + r[i - j - 1])
			{
				q = p[j] + r[i - j - 1];
				s[i] = j + 1;
			}
		}
		r[i] = q;
	}
	std::pair<int*, int*> pp{ r,s };
	return pp;
}

void PrintCutRodSolution(int* p, int n)
{
	int* r = ExtendedBottomUpCutRod(p, n).first;
	int* s = ExtendedBottomUpCutRod(p, n).second;
	std::cout << "收益:" << r[n] << std::endl;
	while (n > 0)
	{
		std::cout << s[n];
		n = n - s[n];
		std::cout << std::endl;
	}
}

int main(int argc, char* argv[])
{
	/*DoubleList* l = new DoubleList;
	initList(l);
	printList(l);
	insertList(l, 3, 100);
	printList(l);
	deleteList(l, 3);
	printList(l);
	DoubleList* sl = searchList(l, 5);
	std::cout << sl->data;*/

	/*DoubleList** l = new DoubleList * [10];
	Data d1, d2, d3;
	int list[10] = { 0 };
	d1.key = 3;
	d2.key = 13;
	d3.key = 7;
	hashInsert(l, d1,list);
	hashInsert(l, d2, list);
	hashInsert(l, d3, list);
	cout << hashSearch(l, 13)->data << endl;
	printList(l[3]);
	hashDelete(l, d2);
	cout << hashSearch(l, 13)->data << endl;*/

	/*BiSearchTree b;
	b.insert(6);
	b.insert(18);
	b.insert(3);
	b.insert(7);
	b.insert(17);
	b.inOrder(b.getRoot());
	cout << endl << b.search(7)->key << endl;
	cout << b.predecessor(b.search(7))->key << endl;
	cout << b.successor(b.search(7))->key << endl;
	cout << b.minNode(b.getRoot())->key << " " << b.maxNode(b.getRoot())->key << endl;
	b.deleteSearch(6);
	b.inOrder(b.getRoot());*/

	int p[10]{ 1,5,8,9,10,17,17,20,24,30 };
	std::cout << CutRod(p, 7);
	std::cout << MemoizedCutRod(p, 4);
	std::cout << BottomUpCutRod(p, 10);
	PrintCutRodSolution(p, 7);



	return 0;
}