#include <iostream>

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

//��ȫ�������� ������̰��

int main(int argc, char* argv[])
{
	int weight[3] = { 1,3,4 };
	int value[3] = { 15,20,30 };
	int bagweight = 4;
	KnapSack(weight, value, bagweight, 3);
	return 0;
}