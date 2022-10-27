#include <iostream>
#include <cmath>
#include <algorithm>
#include <functional>
#include <random>
#include <time.h>
#include <vector>
#include <queue>

using namespace std;

//̰�ĺͶ��涼�������ӽṹ������
//�������ص�����������ʣ�̰����̰��ѡ������
//��������������Ľ⣬�����Ե����Ϲ���
//̰���ڵ�һ��ѡ��֮ǰ�������κ�������Ľ⣬ͨ���Զ����¹���

//0-1�������� ֻ���ö���
//��ά����ⷨ
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

//�������
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

//��ȫ�������� ������̰��
void GreedyKnapSack(int* value, int* weight, size_t bagwieght, size_t n)
{
	//���յ�λ������������
	int* arr = new int[n];
	for (int i = 0; i < n; ++i)
	{
		arr[i] = value[i] / weight[i];
	}
	QuickSort(arr, n, 0, n - 1);
	int i = 0;
	int v = 0;
	//��ȫװ��ȥ
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

//�������˶���Χ

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

//������
//����
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

//̰���㷨
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

//�������Ʋ�0���������Ʋ�1
//����Ч��Ҫ����λ���ö�

//�����������1�ĸ���
int NumberOf1(int n)
{
	int count = 0;
	while (n)
	{
		++count;
		//һ��������ȥ1����Լ�����Խ����Ҳ��1��Ϊ0�������ж��ٸ�1�������ж��ٴ�
		n = (n - 1) & n;
	}
	//����returnĬ�Ϸ��ظ���
	//return��Ҫ����ָ������õ�local����
	return count;
}

//���ھ��ȵ����⣬�����õȺ��ж�����С���Ƿ����
//���ܺ��Ա߽缰�쳣�����ò�����顢�Ƿ������
//���ܲ��ԡ��߽���ԡ��������
//����չ�ԡ���ά����

//��ֵ�������η�

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

//�շ������� ̰��
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

//��ӡ��1������nλ��
//���ǵ���������ʹ���ַ�����������
//��ʵ����ȫ����

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
	//���һ��'\0'
	char* number = new char[n + 1];
	number[n] = '\0';
	for (int i = 0; i < 10; ++i)
	{
		number[0] = i + '0';
		Print1ToMaxOfNDigitsRecursively(number, n, 0);
	}
	delete[] number;
}

//��O(1)ʱ����ɾ������ڵ�
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

//ɾ��������������ظ��Ľڵ�
//��ΪheadҲ���ܱ�ɾ��������ʹ��**head
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

//������ʽƥ��
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

//��ʾ��ֵ���ַ���

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

//̯������ʹ��̯�����ۣ�ȷ����ͬ������ɵļ��ϡ�ƽ��������
//�ۺϷ��� ���㷨 ���ܷ�

//�ڴ�(RAM)�ú����������(����)��B��
//B�����ƺ��������һ��ƽ��������
//��ͬ������B�������кܶຢ�ӣ�������Ƕ�����
//

//��������˳��ʹ����λ��ż��ǰ��
//���Ʋ���ģʽ�ĺ���д��

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


	return 0;
}