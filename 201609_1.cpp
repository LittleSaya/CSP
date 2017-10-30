#include "csptest.h"
#include <iostream>
#include <climits>
#include <cmath>

const int N = 1000;
int p[N];
int n;

void f_201609_1()
{
	std::cin >> n;
	for (int i = 0; i < n; ++i)
	{	std::cin >> p[i]; }
	
	int max = 0, t = 0;
	for (int i = 0; i < n - 1; ++i)
	{
		t = std::abs(p[i] - p[i + 1]);
		if (max < t)
		{	max = t; }
	}
	std::cout << max;
}
