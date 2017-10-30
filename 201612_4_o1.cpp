#include "csptest.h"
#include <iostream>
#include <climits>

// reference 1: http://blog.csdn.net/more_ugly_less_bug/article/details/60142954
// reference 2: http://www.cnblogs.com/SCAU_que/articles/1893979.html

namespace Q201612_4_o1
{

const int N = 1000;
int m[N][N];
int f[N];
int n;

void f_201612_4_o1()
{
	std::cin >> n;
	for (int i = 0; i < n; ++i)
	{	std::cin >> f[i]; }
	for (int i = 0; i < n - 1; ++i)
	{	m[i][i + 1] = f[i] + f[i + 1]; }
	
	int sum = 0, min = 0;
	int low = 0, high = 0;
	for (int r = 3; r <= n; ++r)
	{
		for (int low = 0; low < n - r + 1; ++low)
		{
			int high = low + r - 1;
			
			sum = 0;
			for (int g = low; g <= high; ++g)
			{	sum += f[g]; }
			
			min = sum + m[low][low] + m[low + 1][high];
			
			for (int x = low + 1; x < high; ++x)
			{
				int t = sum + m[low][x] + m[x + 1][high];
				if (min > t)
				{	min = t; }
			}
			m[low][high] = min;
		}
	}
	std::cout << min;
}

}
