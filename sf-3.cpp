#include <iostream>
#include <typeinfo>

using std::cin;
using std::cout;
using std::endl;
using std::string;

template<typename T>
bool Swap(T& t1, T& t2)
{
	T t = t1;
	t1 = t2;
	t2 = t;
	return true;
}

//函数模板特例化
template<> bool Swap(double& d1, double& d2)
{
	std::cout << "double";
	return true;
}

//数组中重复的数字 长度为n的数组[0~n-1] 寻找任意重复数字
//时间复杂度O(n),空间复杂度O(1)
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

//不修改数组的情况下找出任意（并非所有!）重复的数字,范围是1~n-1
//可以使用辅助数组 O(n)的辅助存储空间
//不使用辅助空间时类似二分查找
//时间复杂度O(nlogn)

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
		//右移一位，即除2
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

//二分查找
template<typename T>
T BinarySerach(T* a, int start, int end, int key)
{
	int ret = -1;
	while (start <= end)
	{
		//防止直接除溢出？
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

//二维数组（左到右递增，上到下递增）判断是否含有指定的整数
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


//最长公共子序列
std::pair<int**, int**> LcsLength(string x, string y)
{
	size_t m = x.length();
	size_t n = y.length();
	++m;
	++n;
	x = " " + x;
	y = " " + y;
	int** b = new int* [m];
	for (int i = 0; i < m; ++i)
	{
		b[i] = new int[n];
	}
	int** c = new int* [m];
	for (int i = 0; i < n; ++i)
	{
		c[i] = new int[n];
	}
	for (int i = 0; i < m; ++i)
	{
		c[i][0] = 0;
	}
	for (int i = 1; i < m; ++i)
	{
		c[0][i] = 0;
	}
	for (int i = 1; i < m; ++i)
	{
		for (int j = 1; j < n; ++j)
		{
			if (x[i] == y[j])
			{
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = '↖';
			}
			else if (c[i - 1][j] >= c[i][j - 1])
			{
				c[i][j] = c[i - 1][j];
				b[i][j] = '↑';
			}
			else
			{
				c[i][j] = c[i][j - 1];
				b[i][j] = '←';
			}
		}
	}
	return std::pair<int**, int**>(b, c);
}

void PrintLcs(int** b, string x, const int i, const int j)
{
	if (i == 0 || j == 0)
	{
		return;
	}
	if (b[i][j] == '↖')
	{
		PrintLcs(b, x, i - 1, j - 1);
		cout << x[size_t(i) - 1];
	}
	else if (b[i][j] == '↑')
	{
		PrintLcs(b, x, i - 1, j);
	}
	else
	{
		PrintLcs(b, x, i, j - 1);
	}
}

//将字符串中的空格改为%20
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
	//length是数组总容量[最大]
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

int main(int argc, char* argv[])
{
	/*int p[7]{ 2,3,1,0,2,5,3 };
	cout << Duplicate(p, 7) << endl;
	double d1 = 1.1, d2 = 2.2;
	Swap(d1, d2);*/

	/*string x = "abcd";
	string y = "abce";
	PrintLcs(LcsLength(x, y).first, x, 4, 4);*/

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

	//s[]是初始化在栈上的数组，是可写的，*s指向字面值常量必须是const的，字面值常量是常量
	//多余的char被初始化为'\0'
	char s[50] = "hello world!";
	ReplaceBlank(s, 50);
	/*for (int i = 0; i < 50; ++i)
	{
		cout << s[i];
	}*/
	int i = 0;
	while (s[i] != '\0')
	{
		cout << s[i];
		++i;
	}

	return 0;
}