#include <iostream>
#include <cmath>

using namespace std;

//贪心和动规都有最优子结构的性质
//动归有重叠子问题的性质，贪心有贪心选择性质
//动归依赖子问题的解，往往自底向上构造
//贪心在第一次选择之前不依赖任何子问题的解，通常自顶向下构造

//0-1背包问题 只能用动归
//二维数组解法
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

//完全背包问题 可以用贪心

//机器人运动范围

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

//剪绳子
//动归
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

//贪心算法
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

int main(int argc, char* argv[])
{
	int weight[3] = { 1,3,4 };
	int value[3] = { 15,20,30 };
	int bagweight = 4;
	KnapSack(weight, value, bagweight, 3);
	return 0;
}