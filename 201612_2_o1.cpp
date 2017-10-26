#include "csptest.h"
#include <iostream>
#include <climits>

// 友情提示：别求反函数 :-) 

namespace Q201612_2_o1
{

int salary(int S);

void f_201612_2_o1()
{
	int T = 0;
	std::cin >> T;
	for (int i = 0; i < INT_MAX; i += 100)
	{
		if (salary(i) == T)
		{
			std::cout << i;
			break;
		}
	}
}

int salary(int S)
{
	static int A = 0;
	if (S >= 0 && S <= 3500)
	{	return S; }
	else
	{
		A = S - 3500;
		if (A <= 1500)// 0.97
		{	return 3500 + A * 0.97; }
		else if (A <= 4500)// 0.9
		{	return 3500 + 1500 * 0.97 + (A - 1500) * 0.9; }
		else if (A <= 9000)// 0.8
		{	return 3500 + 1500 * 0.97 + 3000 * 0.9 + (A - 4500) * 0.8; }
		else if (A <= 35000)// 0.75
		{	return 3500 + 1500 * 0.97 + 3000 * 0.9 + 4500 * 0.8 + (A - 9000) * 0.75; }
		else if (A <= 55000)// 0.7
		{	return 3500 + 1500 * 0.97 + 3000 * 0.9 + 4500 * 0.8 + 26000 * 0.75 + (A - 35000) * 0.7; }
		else if (A <= 80000)// 0.65
		{	return 3500 + 1500 * 0.97 + 3000 * 0.9 + 4500 * 0.8 + 26000 * 0.75 + 20000 * 0.7 + (A - 55000) * 0.65; }
		else
		{	return 3500 + 1500 * 0.97 + 3000 * 0.9 + 4500 * 0.8 + 26000 * 0.75 + 20000 * 0.7 + 25000 * 0.65 + (A - 80000) * 0.55; }
	}
}

}
