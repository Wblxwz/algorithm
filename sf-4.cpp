#include <iostream>

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

int main(int argc, char* argv[])
{
	int weight[3] = { 1,3,4 };
	int value[3] = { 15,20,30 };
	int bagweight = 4;
	KnapSack(weight, value, bagweight, 3);
	return 0;
}