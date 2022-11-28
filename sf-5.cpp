#include <iostream>

using namespace std;

//¶ş²æÊ÷µÄ¾µÏñ

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

//¶Ô³ÆµÄ¶ş²æÊ÷
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

//Ë³Ê±Õë´òÓ¡¾ØÕó
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

//ì³²¨ÄÇÆõ¶Ñ
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

void FibHeapInsert(FibHeap* h, FibNode* x)
{
	x->degree = 0;
	x->p = nullptr;
	x->child = nullptr;
	x->mark = false;
	if (h->min == nullptr)
	{
		h->min = x;
	}
	else
	{
		if (x->key < h->min->key)
		{
			h->min = x;
		}
	}
	h->n += 1;
}

int main(int argc, char* argv[])
{

	return 0;
}