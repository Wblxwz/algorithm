#include <iostream>
#include <cmath>
#include <algorithm>
#include <functional>
#include <random>
#include <time.h>

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

int Paratiton(int* data, int n, int start, int end)
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
	int index = Paratiton(data, n, start, end);
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

int main(int argc, char* argv[])
{
	int weight[3] = { 1,3,4 };
	int value[3] = { 15,20,30 };
	int bagweight = 4;
	//KnapSack(weight, value, bagweight, 3);
	GreedyKnapSack(value, weight, bagweight, 3);
	return 0;
}