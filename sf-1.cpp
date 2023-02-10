#include <iostream>
#include <thread>
#include <limits>
#include <Windows.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <fstream>
#include <vector>
#include <random>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

//尽量以const替换#define宏
//大写名称通常用于宏，这里不应用大写，暂时不改了
//常量定义式通常放在头文件里
const int ROWS = 3;
const int MYSIZE = 10;

template<typename T, typename U>
inline void print(T* a, const U& n)
{
	for (int i = 0; i < n; ++i)
	{
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
}

template<typename T>
inline void swap(T& a, T& b)
{
	T t = a;
	a = b;
	b = t;
}

//功能：二进制加法
void add_Bin(int* a, int* b, const size_t& n)
{
	int carry = 0;//进位初始化
	//[]运算符需要传入size_t类型(64位系统下是64位，但是int64位系统下还是32位4字节)
	//size_t是无符号整型
	int* c = new int[n + 1];
	for (size_t i = n; i > 0; --i)
	{
		c[i] = (a[i - 1] + b[i - 1] + carry) % 2;
		carry = (a[i - 1] + b[i - 1] + carry) / 2;
	}
	c[0] = carry;
	print(c, n + 1);
	delete[]c;
}

//功能：排序算法
//插入排序（类似扑克牌，分成两部分，遍历无序的向有序中插入）O(n^2)
void insert_Sort(int* a, const size_t& n)
{
	for (int i = 1; i < n; ++i)
	{
		int key = a[i];
		int j = i - 1;
		while (j >= 0 && a[j] > key)
		{
			a[j + 1] = a[j];
			--j;
		}
		a[j + 1] = key;
	}
}
//希尔排序 O(nlog2n)

void shellSort(int* a, const size_t& n)
{
	for (int gap = n / 2; gap > 0; gap /= 2)
		for (int i = 0; i < gap; ++i)
			for (int j = i + gap; j < n; j += gap)
			{
				int temp = a[j];
				int preindex = j - gap;
				while (a[preindex] > temp && preindex >= 0)
				{
					a[preindex + gap] = a[preindex];
					preindex -= gap;
				}
				a[preindex + gap] = temp;
			}
}

//选择排序 O(n^2)
void select_Sort(int* a, const size_t& n)
{
	for (int i = 0; i < n - 1; ++i)
	{
		int min = i;
		for (int j = i + 1; j < n; ++j)
			if (a[j] < a[min])
				min = j;
		swap(a[i], a[min]);
	}
}
//冒泡排序 O(n^2)
void maoPao(int* a, const size_t& n)
{
	for (int i = 0; i < n - 1; ++i)
		for (int j = 0; j < n - i - 1; ++j)
			if (a[j] > a[j + 1])
				swap(a[j], a[j + 1]);
}
//归并排序算法 O(nlog₂n)
void merge(int* a, const int start, const int end, int* b)
{
	int left_length = (end - start + 1) / 2 + 1;
	int left_index = start;
	int right_index = start + left_length;
	int result_index = start;
	while (left_index < start + left_length && right_index < end + 1)
	{
		if (a[left_index] <= a[right_index])
		{
			b[result_index++] = a[left_index++];
		}
		else
		{
			b[result_index++] = a[right_index++];
		}
	}
	while (left_index < start + left_length)
	{
		b[result_index++] = a[left_index++];
	}
	while (right_index < end + 1)
	{
		b[result_index++] = a[right_index++];
	}
}
//右值表达式不能作为递归时的引用（非常量引用只能用左值）
void merge_Sort(int* a, const int start, const int end, int* b)
{
	if (end == start)
	{
		return;
	}
	else if (end - start == 1)
	{
		if (a[start] > a[end])
			swap(a[start], a[end]);
	}
	else
	{
		merge_Sort(a, start, (end - start + 1) / 2 + start, b);
		merge_Sort(a, (end - start + 1) / 2 + 1, end, b);
		merge(a, start, end, b);
	}
}

void myMerge(int* arr, const int& start, const int& mid, const int& end)
{
	int len = (end - start) + 1;
	int left = start;
	int right = mid + 1;
	int* temp = new int[len];
	int i = 0;
	while (left <= mid && right <= end)
		temp[i++] = arr[left] <= arr[right] ? arr[left++] : arr[right++];
	while (left <= mid)
		temp[i++] = arr[left++];
	while (right <= end)
		temp[i++] = arr[right++];
	for (int j = 0; j < len; ++j)
		arr[start + j] = temp[j];
	delete[]temp;
}

void myMergeSort(int* arr, const int& start, const int& end)
{
	if (start == end)
		return;
	int mid = (start + end) / 2;
	myMergeSort(arr, start, mid);
	myMergeSort(arr, mid + 1, end);
	myMerge(arr, start, mid, end);
}

//最大子数组
class Maxarray
{
public:
	Maxarray() = default;
	Maxarray(const int& min, const int& max, const int& s) :min_index(min), max_index(max), sum(s)
	{ }
	inline int getSum() const
	{
		return this->sum;
	}
	~Maxarray() = default;
private:
	int min_index, max_index, sum;
};

Maxarray find_CrossMaxArray(int* a, const int& low, const int& mid, const int& high)
{
	int left_sum = -INT_MAX;
	int sum = 0;
	int max_left = 0;
	for (int i = mid; i >= low; --i)
	{
		sum += a[i];
		if (sum > left_sum)
		{
			left_sum = sum;
			max_left = i;
		}
	}
	int right_sum = -INT_MAX;
	sum = 0;
	int max_right = 0;
	for (int i = mid + 1; i <= high; ++i)
	{
		sum += a[i];
		if (sum > right_sum)
		{
			right_sum = sum;
			max_right = i;
		}
	}
	return Maxarray(max_left, max_right, left_sum + right_sum);
}

Maxarray find_MaxArray(int* a, const int& low, const int& high)
{
	if (low == high)
		return Maxarray(low, high, a[low]);
	else
	{
		int mid = (low + high) / 2;
		Maxarray m1 = find_MaxArray(a, low, mid);
		Maxarray m2 = find_MaxArray(a, mid + 1, high);
		Maxarray m3 = find_CrossMaxArray(a, low, mid, high);
		if (m1.getSum() > m2.getSum() && m1.getSum() > m3.getSum())
			return m1;
		else if (m2.getSum() > m1.getSum() && m2.getSum() > m3.getSum())
			return m2;
		else
			return m3;
	}
}

//矩阵乘法(假定矩阵为n*n)
class Matrix
{
public:
	Matrix()
	{
		rows = ROWS;
		matrix = new int* [rows];
		for (int i = 0; i < rows; ++i)
			matrix[i] = new int[rows];
		std::cout << "default" << std::endl;
	}
	Matrix(const int& r)//假定矩阵为n*n
	{
		rows = r;
		//cols = c;
		matrix = new int* [rows];
		for (int i = 0; i < r; ++i)
			matrix[i] = new int[rows];
		for (int i = 0; i < r; ++i)
		{
			for (int j = 0; j < r; ++j)
			{
				int x = 0;
				std::cin >> x;
				matrix[i][j] = x;
			}
		}
		std::cout << "OK" << std::endl;
	}
	void print() const
	{
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < rows; ++j)
				std::cout << matrix[i][j] << " ";
			std::cout << std::endl;
		}
	}
	const int getRows() const
	{
		return this->rows;
	}
	int** getMatrix()
	{
		return this->matrix;
	}
private:
	//代替#define宏，作用域在类内，必须用static const(应该放在头文件内)
	//当static const int(bool，char)在一起时为声明式而非定义式
	//取地址时必须有定义式
	//in-class初值设定只允许整数常量使用
	//整数常量也会被别人用指针or引用获取,#define enum都不能被取地址
	static const int ROWS = 3;
	//the enum hack补偿，用来处理static const无法使用的情况
	//enum更像#define
	enum { MYROWS = 3 };
	int rows = 0;
	//int cols = 0;
	//动态创建二维数组
	//动态内存分配指的是可以手动释放,返回第一个字节的地址
	int** matrix = new int* [rows];
};

//O(n^3)朴素算法一般够用
//矩阵乘法朴素分治和strassen算法可以以后再看，比较复杂
Matrix mulitiply(Matrix& a, Matrix& b)
{
	int n = a.getRows();
	Matrix c;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
		{
			c.getMatrix()[i][j] = 0;
			for (int k = 0; k < n; ++k)
				c.getMatrix()[i][j] += a.getMatrix()[i][k] * b.getMatrix()[k][j];
		}
	return c;
}

//多线程测试


/*寻找最大最小值，先设第一个数为最值，遍历数组，不断更新初始值*/
//至少要做n-1次比较
int maxValue(int* a, const int& n)
{
	int max = 0;
	for (int i = 0; i < n; ++i)
	{
		if (a[i] > a[max])
			max = i;
	}
	return a[max];
}

struct Value
{
	int max, min;
};

/*同时寻找最大值和最小值*/
/*最大比较次数为3⌊n/2⌋*/
inline Value minMaxValue(int* a, const int& n)
{
	int max = 0, min = 0;
	Value v;
	if (n % 2 == 0)
	{
		max = a[0] > a[1] ? a[0] : a[1];
		min = a[0] > a[1] ? a[1] : a[0];
	}
	else
	{
		max = a[0];
		min = a[0];
	}
	for (int i = 1; i < n - 1; i += 2)
	{
		if (a[i] >= a[i + 1])
		{
			if (a[i] > max)
			{
				max = a[i];
			}
			if (a[i + 1] < min)
			{
				min = a[i + 1];
			}
		}
		else
		{
			if (a[i + 1] > max)
			{
				max = a[i + 1];
			}
			if (a[i] < min)
			{
				min = a[i];
			}
		}
	}
	if (a[n - 1] < min)
		min = a[n - 1];
	if (a[n - 1] > max)
		max = a[n - 1];
	v.max = max;
	v.min = min;
	return v;
}


/*随机算法*/
//按优先级随机排列数组
void randomArray(int* a, const int& n)
{
	srand(unsigned(time(0)));
	int* p = new int[n];
	for (int i = 0; i < n; ++i)
	{
		p[i] = rand() % 100;
	}
	print(p, 6);
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = 0; j < n - 1 - i; ++j)
			if (p[j] > p[j + 1])
			{
				swap(a[j], a[j + 1]);
				swap(p[j], p[j + 1]);
			}
	}
	delete[]p;
}
//原址随机排列数组
void randomInPlace(int* a, const size_t& n)
{
	srand(unsigned(time(0)));
	for (int i = 0; i < n; ++i)
	{
		swap(a[i], a[rand() % n]);
	}
}

//在线雇用问题（平衡最小化面试次数和最大化雇用质量）
//k = n/e时至少有1/e的概率取得最好值(e = 2.7)
int onLine(int* score, const int& n, const int& k)
{
	int best = INT_MIN;
	for (int i = 0; i < k; ++i)
	{
		if (score[i] > best)
			best = score[i];
	}
	for (int i = k; i < n; ++i)
	{
		if (score[i] > best)
			return i;
	}
	return n;
}


/*树的父结点、左孩子和右孩子
给定结点为i，父结点为i/2（向下取整），左孩子为2i，右孩子为2i+1
*/
inline int Parent(int& i)
{
	return i / 2;
}

inline int Left(int& i)
{
	return i * 2;
}

inline int Right(int& i)
{
	return i * 2 + 1;
}

/*包含n个元素的堆的高度为lgn*/
//堆近似完全二叉树
struct Heap
{
	int n = 6;
	int* a;
};

/*维护最大堆的性质,i为根结点的下标*/
void max_Heapify(Heap& h, int i)
{
	int largest = i;
	int l = Left(i);
	int r = Right(i);
	if (l < h.n && h.a[l] > h.a[i])
		largest = l;
	else
		largest = i;
	if (r < h.n && h.a[r] > h.a[largest])
		largest = r;
	if (largest != i)
	{
		swap(h.a[i], h.a[largest]);
		max_Heapify(h, largest);
	}
}

/*建最大堆*/
/*堆数组的子数组[n/2,n/2+1,...,n-1]都是叶子结点*/
void buildMaxHeap(Heap& h)
{
	//都是根节点
	for (int i = h.n / 2 - 1; i >= 0; --i)
	{
		max_Heapify(h, i);
	}
}

/*堆排序 O(nlogn)*/
size_t heapSort(Heap& h)
{
	buildMaxHeap(h);
	for (int i = h.n - 1; i > 0; --i)
	{
		swap(h.a[0], h.a[i]);
		--h.n;
		max_Heapify(h, 0);

	}
	return h.n;
}

/*最大优先队列*/
int heapMax(Heap& h)//返回队列中最大键字的元素
{
	return h.a[0];
}

int heapExtractMax(Heap& h)//去掉并返回具有最大键字的元素
{
	if (h.n < 1)
	{
		std::cout << "error" << std::endl;
		return 0;
	}
	int max = h.a[0];
	h.a[0] = h.a[h.n - 1];
	--h.n;
	max_Heapify(h, 0);
	return max;
}

void heapIncreaseKey(Heap& h, int x, int k)//将元素x的关键字值增加到k(赋值)
{
	if (k < h.a[x])
	{
		std::cout << "error";
		return;
	}
	h.a[x] = k;
	while (x > 0 && h.a[Parent(x)] < h.a[x])
	{
		swap(h.a[x], h.a[Parent(x)]);
		x = Parent(x);
	}
}

void maxHeapInsert(Heap& h, int key)//插入一个新元素
{
	++h.n;
	h.a[h.n - 1] = INT_MIN;
	heapIncreaseKey(h, h.n - 1, key);
}

/*快速排序，实际排序中最好的选择，因为平均性能非常好 O(nlgn)*/
int Partition(int* a, int p, int r)
{
	int x = a[r];
	int i = p - 1;
	for (int j = p; j <= r - 1; ++j)
	{
		if (a[j] <= x)
		{
			++i;
			swap(a[i], a[j]);
		}
	}
	swap(a[i + 1], a[r]);
	return i + 1;
}

void quickSort(int* a, int p, int r)
{
	if (p < r)
	{
		int q = Partition(a, p, r);
		quickSort(a, p, q - 1);
		quickSort(a, q + 1, r);
	}
}

/*随机化版本的快速排序，在处理大数据输入时效果更好*/
int Random(const int& a, const int& b)
{
	std::default_random_engine e;
	e.seed(time(nullptr));
	std::uniform_int_distribution<size_t> u(a, b);
	return u(e);
}

int randomPartition(int* a, int p, int r)
{
	int i = Random(p, r);
	swap(a[i], a[r]);
	return Partition(a, p, r);
}

void randomQuickSort(int* a, int p, int r)
{
	if (p < r)
	{
		int q = randomPartition(a, p, r);
		randomQuickSort(a, p, q - 1);
		randomQuickSort(a, q + 1, r);
	}
}

int myPartition(int* a, int p, int r)
{
	int index = Random(p, r);
	swap(a[index], a[r]);
	int first = p - 1;
	for (index = p; index < r; ++index)
		if (a[index] < a[r])
		{
			++first;
			if (index != first)
				swap(a[index], a[first]);
		}
	++first;
	swap(a[first], a[r]);
	return first;
}

void myQuickSort(int* a, const int& start, const int& end)
{
	if (start == end)
		return;
	int index = myPartition(a, start, end);
	if (index > start)
		myQuickSort(a, start, index - 1);
	if (index < end)
		myQuickSort(a, index + 1, end);
}

/*选择第i个顺序统计量（即数组中第i个最小值）*/
/*假设所有元素是互异的，O(n)*/
int randomSelect(int* a, int p, int r, int i, const int& n)
{
	--i;
	if (p == r)
		return a[p];
	int q = randomPartition(a, p, r);
	int k = q - p + 1;
	if (i == k)
		return a[q];
	else if (i < k)
		return randomSelect(a, p, q - 1, i, n);
	else
		return randomSelect(a, q + 1, r, i, n);
}

template<typename T>
T myMax(T* a, const T& n)
{
	T maxnum = a[0];
	for (int i = 1; i < n; ++i)
	{
		if (a[i] > maxnum)
			maxnum = a[i];
	}
	return maxnum;
}

template<typename T>
T myMin(T* a, const T& n)
{
	T minnum = a[0];
	for (int i = 1; i < n; ++i)
	{
		if (a[i] < minnum)
			minnum = a[i];
	}
	return minnum;
}

//计数排序 O(k+n)
//有条件 输入的所有数小于等于k 对输入元素做假设
//是稳定的排序（相等的数排序完成后不改变其顺序，比如a2 a4都是3，排完后a2还在a4前面）
void countSort(int* a, const int n)
{
	int minnum = myMin(a, n);
	int maxnum = myMax(a, n);
	int len = maxnum - minnum + 1;
	vector<int> v(len);
	vector<int> output(n);
	for (int i = 0; i < n; ++i)
		++v[a[i] - minnum];
	for (int i = 1; i < len; ++i)
		v[i] += v[i - 1];
	for (int i = n - 1; i >= 0; --i)
	{
		output[v[a[i] - minnum] - 1] = a[i];
		--v[a[i] - minnum];
	}
	for (int i = 0; i < n; ++i)
		a[i] = output[i];
}


//基数排序 最大值小于等于9 按位排序 O(n+k) [因为用的计数排序是稳定排序]
void radixSort(int* a, const int& n)
{
	int maxnum = myMax(a,n);
	int mod = 10, div = 1;
	int maxdiv = 0;
	while (maxnum != 0)
	{
		maxnum /= 10;
		++maxdiv;
	}
	vector<int> v[10];
	for (int i = 0; i < maxdiv; mod *= 10, div *= 10, ++i)
	{
		for (int j = 0; j < n; ++j)
			v[(a[j] % mod) / div].push_back(a[j]);
		int index = 0;
		for (int k = 0; k < 10; ++k)
		{
			int size = v[k].size();
			for (int l = 0; l < size; ++l)
			{
				a[index++] = v[k][l];
			}
			v[k].clear();
		}
	}
}

//桶排序 O(n)
void bucketSort(int* arr, const int& bucketsize, const int& n)
{
	if (n < 2)
		return;
	int minnum = arr[0];
	int maxnum = arr[0];
	minnum = myMin(arr, n);
	maxnum = myMax(arr, n);
	int bucketcount = (maxnum - minnum) / bucketsize + 1;
	vector<int>* buckets = new vector<int>[bucketcount];
	for (int i = 0; i < n; ++i)
		buckets[(arr[i] - minnum) / bucketsize].push_back(arr[i]);
	int k = 0;
	for (int i = 0; i < bucketcount; ++i)
	{
		int size = buckets[i].size();
		bucketSort(buckets[i].data(), bucketsize, size);
		for (int j = 0; j < size; ++j)
			arr[k++] = buckets[i][j];
	}
	delete[] buckets;
}

/*最坏情况为O(n)的选择算法*/
//P123
void Select()
{

}

//基于数组实现的栈
struct Stack
{
	int* data;
	int top;
	int maxSize;
};

void initStack(Stack& s)
{
	s.data = new int[MYSIZE];
	s.top = -1;
	s.maxSize = MYSIZE;
}

bool stackEmpty(Stack& s)
{
	return s.top < 0 ? true : false;
}

bool stackFull(Stack& s)
{
	return s.top == s.maxSize ? true : false;
}

void push(Stack& s, const int& n)
{
	if (stackFull(s))
	{
		exit(1);
	}
	else
	{
		s.data[++s.top] = n;
	}
}

int pop(Stack& s)
{
	if (stackEmpty(s))
	{
		exit(2);
	}
	else
	{
		return s.data[s.top--];
	}
}

//基于单链表实现的栈
//分成两个结构体，单个太浪费空间
struct ListStack
{
public:
	bool isEmptyListStack()
	{
		if (!top)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//链栈不必判满，只要能分配内存空间就可以
	//入栈用头插法，因为出栈逆序
	void pushListStack(const int& n)
	{
		ListStack* p = new ListStack;
		p->data = n;
		p->next = top;
		top = p;
	}
	int popListStack()
	{
		if (!isEmptyListStack())
		{
			ListStack* r = top;
			int n = top->data;
			top = top->next;
			delete r;
			return n;
		}
		else
		{
			exit(2);
		}
	}
private:
	int data = 0;
	ListStack* next = nullptr;
	ListStack* top = nullptr;
};

//基于数组实现的循环队列
//循环队列空出一个位置
//循环队列满了后不能用值覆盖
struct Queue
{
	int* data;
	int head;
	int tail;
	int maxSize;
	int length;
};

void initQueue(Queue& q)
{
	q.data = new int[MYSIZE];
	q.maxSize = MYSIZE;
	q.head = 0;
	q.tail = 0;
}

bool queueEmpty(Queue& q)
{
	return q.head == q.tail ? true : false;
}

bool queueFull(Queue& q)
{
	return (q.tail + 1) % q.maxSize == q.head ? true : false;
}

void enQueue(Queue& q, const int& n)
{
	if (!queueFull(q))
	{
		q.data[q.tail] = n;
		q.tail = (q.tail + 1) % q.maxSize;
	}
	else
	{
		exit(1);
	}
}

int deQueue(Queue& q)
{
	if (!queueEmpty(q))
	{
		int x = q.data[q.head];
		q.head = (q.head + 1) % q.maxSize;
		return x;
	}
	else
	{
		exit(2);
	}
}

//基于单链表实现的队列
//分成两个结构体，单个太浪费空间
struct ListQueue
{
	int data = 0, size = 0;
	ListQueue* next = nullptr, * head = nullptr, * tail = nullptr;
};

bool isListQueueEmpty(ListQueue* l)
{
	return l->size == 0 ? true : false;
}

void enListQueue(ListQueue* l, const int& n)
{
	if (l->size == 0)
	{
		ListQueue* q = new ListQueue;
		q->data = n;
		l->head = q;
		l->tail = q;
		++l->size;
	}
	else
	{
		ListQueue* q = new ListQueue;
		q->data = n;
		q->next = nullptr;
		l->tail->next = q;
		l->tail = q;
		++l->size;
	}
}

int deListQueue(ListQueue* l)
{
	if (!isListQueueEmpty(l))
	{
		int n = l->head->data;
		ListQueue* r = l->head;
		l->head = l->head->next;
		delete r;
		--l->size;
		return n;
	}
	else
	{
		exit(1);
	}
}

//二叉树
struct BiTree
{
	int data;
	BiTree* left, * right;
};

void initBiTree(BiTree* t, const int& n)
{
	t->data = n;
	t->left = nullptr;
	t->right = nullptr;
}
BiTree* createBiTree(BiTree* t)
{
	int c;
	cin >> c;
	if (c == -1)
	{
		t = nullptr;
	}
	else
	{
		t = new BiTree;
		t->data = c;
		t->left = nullptr;
		t->right = nullptr;
		t->left = createBiTree(t->left);
		t->right = createBiTree(t->right);
	}
	return t;
}

void xianXuPrint(BiTree* t)
{
	if (t != nullptr)
	{
		cout << t->data << " ";
		xianXuPrint(t->left);
		xianXuPrint(t->right);
	}
}

int main(int argc, char* argv[])
{
	/*int a[2] = { 0 }, b[2] = { 1 };
	cs(a, b);*/

	//排序
	/*int a[6] = { 5,2,4,6,1,3 };
	int b[6] = { 0 };
	int c[9] = { -2,1,-3,4,-1,2,1,-5,4 };
	Maxarray m = find_MaxArray(c, 0, 8);
	cout << m.getSum();*/
	//print(a, 6);
	/*int a[6] = { 5,2,4,6,1,3 };
	myMergeSort(a, 0, 5);
	print(a, 6);*/
	/*print(a,6);
	insert_Sort(a, 6);
	select_Sort(a, 6);
	maoPao(a, 6);
	merge_Sort(a, 0, 5, b);
	print(b, 6);*/

	//int a[4] = { 1,1,0,1 };
	//int b[4] = { 0,1,0,1 };
	//add_Bin(a, b, 4);

	/*Matrix a(3), b(3), c;
	c = mulitiply(a, b);
	c.print();*/

	/*int a[6] = { 1,2,3,4,5,6 };
	randomArray(a, 6);?
	randomInPlace(a,6);?
	print(a, 6);*/

	/*Heap h;
	h.a = new int [SIZE] { 5, 2, 4, 6, 1, 3 };
	heapSort(h);
	print(h.a, 6);*/

	/*Heap h;
	h.a = new int[SIZE] { 5, 2, 4, 6, 1, 3 };
	buildMaxHeap(h);
	cout << heapMax(h) << endl;
	heapIncreaseKey(h, 2, 20);
	cout << heapMax(h) << endl;
	cout << heapExtractMax(h) << endl;
	cout << heapMax(h) << endl;
	maxHeapInsert(h, 4);
	print(h.a, 7);
	delete[]h.a;*/

	/*int a[6] = { 5, 2, 4, 6, 1, 3 };
	quickSort(a, 0, 5);
	print(a, 6);*/

	/*int a[6] = { 5, 2, 4, 6, 1, 3 };
	randomQuickSort(a, 0, 5);
	print(a, 6);*/

	//int a[6] = { 5, 2, 4, 6, 1, 3 };
	////bucketSort(a, 1, 6);
	//////countSort(a, 6);
	//radixSort(a, 6);
	//print(a, 6);

	/*int a[6] = { 329, 457, 657, 839, 436, 720 };
	radixSort(a,3,6);
	print(a, 6);*/

	//int a[5] = { 1, 3, 6, 6, 1};
	//cout << minMaxValue(a, 5).min << " " << minMaxValue(a, 5).max << endl;

	/*int a[6] = {5, 2, 4, 6, 1, 3};
	myQuickSort(a, 0, 5);
	print(a, 6);*/
	//cout << randomSelect(a, 1, 5, 6, 6);

	/*shellSort(a, 6);
	print(a, 6);*/

	/*Stack s;
	initStack(s);
	push(s, 1);
	push(s, 2);
	push(s, 3);
	int a = pop(s);
	int b = pop(s);
	int c = pop(s);
	std::cout << a << " " << b << " " << c << std::endl;*/

	/*Queue q;
	initQueue(q);
	for (int i = 0; i < q.maxSize - 1; ++i)
	{
		enQueue(q, i);
	}
	for (int i = 0; i < q.maxSize - 1; ++i)
	{
		std::cout << deQueue(q) << " ";
	}*/

	/*ListStack l;
	l.pushListStack(1);
	l.pushListStack(2);
	l.pushListStack(3);
	std::cout << l.popListStack() << " " << l.popListStack() << " " << l.popListStack();*/

	//连续输出倒序？
	/*ListQueue* l = new ListQueue;
	enListQueue(l, 1);
	enListQueue(l, 2);
	enListQueue(l, 3);
	int a = deListQueue(l);
	int b = deListQueue(l);
	int c = deListQueue(l);
	std::cout << a << " " << b << " " << c << std::endl;*/

	/*BiTree* root = new BiTree;
	root = createBiTree(root);
	xianXuPrint(root);*/
}