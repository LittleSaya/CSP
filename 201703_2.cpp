#include "csptest.h"
#include "commonFunc.h"
#include <iostream>

void f_201703_2()
{
	using std::cin;
	using std::cout;
	using std::endl;
	int n = 0, m = 0;//n:how many students, m:how many adjustment
	cin >> n >> m;
	int *num2pos = new int[n], *pos2num = new int[n];
	int *adjust = new int[m * 2];
	for (int i = 0; i < n; ++i)
		num2pos[i] = pos2num[i] = i;
	for (int i = 0; i < m; ++i)
	{
		cin >> adjust[2 * i] >> adjust[2 * i + 1];
		adjust[2 * i] -= 1;
	}
	int direction = 1, steps = 0;
	int swapTargetNum = 0;
	for (int i = 0; i < m; ++i)
	{
		if (adjust[2 * i + 1] == 0)			{ continue; }
		else if (adjust[2 * i + 1] > 0)		{ direction = 1; steps = adjust[2 * i + 1];}
		else								{ direction = -1; steps = -adjust[2 * i + 1];}
		for (int j = 0; j < steps; ++j)
		{
			if (num2pos[adjust[2 * i]] == 0 && direction < 0) break;
			if (num2pos[adjust[2 * i]] == n - 1 && direction > 0) break;
			swapTargetNum = pos2num[num2pos[adjust[2 * i]] + direction];
			swap(pos2num[num2pos[adjust[2 * i]]], pos2num[num2pos[adjust[2 * i]] + direction]);
			swap(num2pos[adjust[2 * i]], num2pos[swapTargetNum]);
		}
	}
	printArray_p(pos2num, n);
	delete [] num2pos, pos2num, adjust;
}
