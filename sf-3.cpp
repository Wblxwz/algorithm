#include <iostream>


using std::cin;
using std::cout;
using std::endl;

template<typename T>
bool Swap(T& t1, T& t2)
{
	T t = t1;
	t1 = t2;
	t2 = t;
	return true;
}

//数组中重复的数字 长度为n的数组[0~n-1] 寻找任意重复数字
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

//最长公共子序列



int main(int argc, char* argv[])
{
	int p[7]{ 2,3,1,0,2,5,3 };
	cout << Duplicate(p, 7) << endl;

	return 0;
}