#ifndef SF_5_H

#define SF_5_H

#include <iostream>
#include <format>
#include <string>
#include <assert.h>
#include <vector>
#include <stack>
#include <deque>
#include <unordered_map>
#include <random>

using namespace std;

template<typename K, typename V>
class SkipNode
{
public:
	SkipNode(const pair<const K, V>& thePair, int level) :element(thePair), next(new SkipNode<K, V>* [level])
	{
		for (int i = 0; i < level; ++i)
			next[i] = nullptr;
	}
	pair<const K, V> element;
	SkipNode<K, V>** next;
};

template<typename K, typename V>
class SkipList
{
public:
	SkipList(const int maxLevel);
	int randomLevel();
	int nodeLevel(SkipNode<K, V>** next);
	SkipNode<K, V>* find(const K& key);
	bool insert(const pair<const K, V>& p);
	bool deleteNode(const K& key);
	~SkipList()
	{
		int size = sizeof(head->next) / sizeof(SkipNode<K, V>*);
		for (int i = 0; i < size; ++i)
		{
			SkipNode<K, V>* thead = head->next[i];
			while (thead->next[i] && thead->next[i] != tail)
			{
				SkipNode<K, V>* tnode = thead;
				thead = thead->next[i];
				delete tnode;
				tnode = nullptr;
			}
		}
		delete head;
		head = nullptr;
		delete tail;
		tail = nullptr;
	}
private:
	int maxLevel;
	SkipNode<K, V>* head;
	SkipNode<K, V>* tail;
};

struct SingleList
{
	SingleList() :data(0), next(nullptr), key(INT_MIN) {}
	SingleList(const int key,const int data) :data(data),next(nullptr),key(key) {}
	~SingleList() = default;
	int key;
	int data;
	SingleList* next;
};

template<typename K,typename V>
class HashTable
{
public:
	HashTable(int length) :list(new SingleList* [length]), length(length)
	{
		for (int i = 0; i < length; ++i)
			list[i] = new SingleList();;
	}
	//采用除法散列函数
	int hash(const K& key)
	{
		return key % length;
	}
	bool insert(const pair<K, V>& p);
	bool deleteNode(const K& key);
	SingleList* find(const K& key);
	~HashTable()
	{
		for (int i = 0; i < length; ++i)
		{
			while (list[i]->next)
			{
				SingleList* temp = list[i];
				list[i] = list[i]->next;
				delete temp;
				temp = nullptr;
			}
			delete list[i];
			list[i] = nullptr;
		}
		delete[] list;
		list = nullptr;
	}
private:
	int length;
	SingleList** list;
};

namespace mystl
{
	struct BinaryTreeNode
	{
		int data;
		BinaryTreeNode* left, * right;
	};
	template<typename T>
	class BinaryTree
	{
	public:
		BinaryTree() {}
		BinaryTreeNode* create(BinaryTreeNode* node);
		~BinaryTree() = default;
		void print(BinaryTreeNode* node);
	};
	template<typename T>
	class BinarySearchTree
	{
	public:
		BinarySearchTree() :root(nullptr) {}
		void insert(const T& data);
		void destroy(BinaryTreeNode* node);
		void xianXuPrint(BinaryTreeNode* node);
		BinaryTreeNode* getRoot();
		~BinarySearchTree()
		{
			destroy(root);
		}
	private:
		BinaryTreeNode* root;
	};
}//mystl

//单链表实现的栈（头插法逆序输出）
template<typename T>
class ListStack
{
public:
	ListStack() :data(0), next(nullptr), head(nullptr) {}
	bool push(const T& data);
	T pop();
	const T& top() const;
	const size_t size();
	void deleter();
	~ListStack()
	{
		deleter();
	}
private:
	T data;
	ListStack* next, * head;
};

template<typename T>
class StackWithMin
{
public:
	StackWithMin() :d_stack(new ListStack<T>), m_stack(new ListStack<T>) {}
	void push(const T& data);
	T pop();
	const T& min() const;
	~StackWithMin() = default;
private:
	ListStack<T>* d_stack;
	ListStack<T>* m_stack;
};

#endif // !SF_5_H
