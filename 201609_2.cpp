#include "csptest.h"
#include <iostream>

namespace Q201609_2
{

const int X = 5;
const int Y = 20;

bool m[X][Y];

int findConti(int tik);
int reserve(int y);
int getNum(int x, int y);

void f_201609_2()
{
	int n = 0, tik = 0;
	std::cin >> n;
	for (int i = 0; i < n; ++i)
	{
		std::cin >> tik;
		int j = findConti(tik);
		if (j != Y)
		{
			int k, l;
			for (k = 0; k < X; ++k)
			{
				if (!m[k][j])
				{	break; }
			}
			for (l = 0; l < tik; ++l)
			{
				std::cout << getNum(k + l, j) << ' ';
				m[k + l][j] = true;
			}
			std::cout << std::endl;
		}
		else
		{
			for (int y = 0; y < Y; ++y)
			{
				for (int x = 0; x < X; ++x)
				{
					if (!m[x][y])
					{
						std::cout << getNum(x, y) << ' ';
						m[x][y] = true;
						if (--tik <= 0)
						{	break; }
					}
				}
				if (tik <= 0)
				{	break; }
			}
			std::cout << std::endl;
		}
	}
			
}

int findConti(int tik)
{
	for (int i = 0; i < Y; ++i)
	{
		if (reserve(i) >= tik)
		{	return i; }
	}
	return Y;
}

int reserve(int y)
{
	for (int i = 0; i < X; ++i)
	{
		if (!m[i][y])
		{	return X - i; }
	}
	return 0;
}

int getNum(int x, int y)
{
	return y * X + x + 1;
}

}
