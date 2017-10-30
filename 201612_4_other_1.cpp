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
	// �����ά����
	// ����m[i][j]Ϊ��i��j�ϲ����������ٵ�ʯ����Ŀ 
	int m[N][N];
	for (int x = 1; x <= n; ++x)
	{
		for (int z = 1; z <= n; ++z)
		{
			m[x][z] = -1;// ��ʼ��Ϊ-1 
		}
	}
	int min = 0;
	
	// ��һ��ʯ�ӵ����ϲ�ʱ����m[i][i]Ϊ0����ʾû��ʯ���ƶ�
	for (int i = 1; i <= n; ++i)
	{	m[i][i] = 0; }
	
	// ���ڵ�����ʯ�Ӻϲ�ʱ����ʱ��m[i][i+1]�����׿���������֮��
	for (int i = 1; i <= n - 1; ++i)
	{	m[i][i + 1] = p[i] + p[i + 1]; }
	
	// �����ڵ�3���Լ�������n��ʱ��ִ������ѭ��
	for (int r = 3; r <= n; ++r)
	{
		for (int i = 1; i <= n - r + 1; ++i)// �ӵ�1�ѿ�ʼ������n - r + 1�ѽ�����3��ʱ�����һ��iӦ�ô�n-2��ʼ��
		{
			int j = i + r - 1;// j���Ǿ���i r-1�ľ��루��i��ʼ��j��һ��r��ʯ�ӣ�
			int sum = 0;// ��i��jÿ��ʯ�ӵ�ʯ����֮�� 
			for (int k = i; k <= j; ++k)
			{	sum += p[k]; }
			
			// ��ʱm[i][j]��m[i][i] + m[i+1][j] + sumΪ�������������һ�ֿ��ܣ���һ������ 
			m[i][j] = m[i+1][j] + sum;
			
			// ����һ���������������
			for (int f = i + 1; f < j; ++f)
			{
				int t = m[i][f] + m[f+1][j] + sum;
				if (t < m[i][j])
				{	m[i][j] = t; }
			}
		}
	}
	min = m[1][n];// ���Ž� 
	return min;
}

}
