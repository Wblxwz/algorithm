#ifndef SF_5_H

#define SF_5_H

#include <iostream>
#include <format>
#include <string>
#include <assert.h>
#include <vector>
#include <stack>
#include <deque>

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
		BinaryTree(){}
		BinaryTreeNode* create(BinaryTreeNode* node);
		~BinaryTree() = default;
		void print(BinaryTreeNode* node);
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
