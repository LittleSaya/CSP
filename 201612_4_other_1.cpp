#include "csptest.h"
#include <iostream>

#define N 100

namespace Q201612_4_other_1
{

int MatrixChain_min(int p[N], int n);

void f_201612_4_other_1()
{
	int p[N] = {0, 1, 3, 4, 2, 5};
	int n = 5;
	int min = MatrixChain_min(p, n);
	std::cout << "min=" << min << std::endl;
}

int MatrixChain_min(int p[N], int n)
{
	// 定义二维数组
	// 定义m[i][j]为从i到j合并过程中最少的石子数目 
	int m[N][N];
	for (int x = 1; x <= n; ++x)
	{
		for (int z = 1; z <= n; ++z)
		{
			m[x][z] = -1;// 初始化为-1 
		}
	}
	int min = 0;
	
	// 当一堆石子单独合并时，设m[i][i]为0，表示没有石子移动
	for (int i = 1; i <= n; ++i)
	{	m[i][i] = 0; }
	
	// 相邻的两堆石子合并时，此时的m[i][i+1]很容易看出是两者之和
	for (int i = 1; i <= n - 1; ++i)
	{	m[i][i + 1] = p[i] + p[i + 1]; }
	
	// 当相邻的3堆以及到最后的n堆时，执行以下循环
	for (int r = 3; r <= n; ++r)
	{
		for (int i = 1; i <= n - r + 1; ++i)// 从第1堆开始，到第n - r + 1堆结束（3堆时，最后一个i应该从n-2开始）
		{
			int j = i + r - 1;// j总是距离i r-1的距离（从i开始到j，一共r堆石子）
			int sum = 0;// 从i到j每堆石子的石子数之和 
			for (int k = i; k <= j; ++k)
			{	sum += p[k]; }
			
			// 此时m[i][j]以m[i][i] + m[i+1][j] + sum为结果，这是其中一种可能，不一定最优 
			m[i][j] = m[i+1][j] + sum;
			
			// 除上一种组合外的其他情况
			for (int f = i + 1; f < j; ++f)
			{
				int t = m[i][f] + m[f+1][j] + sum;
				if (t < m[i][j])
				{	m[i][j] = t; }
			}
		}
	}
	min = m[1][n];// 最优解 
	return min;
}

}
