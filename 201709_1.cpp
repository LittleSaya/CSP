#include "csptest.h"
#include <iostream>

namespace Q201709_1
{

const int SINGLE = 10;

void f_201709_1()
{
	int N = 0, res = 0, temp = 0;
	std::cin >> N;
	
	// 5
	temp = N / (SINGLE * 5);
	N -= temp * SINGLE * 5;
	res = temp * 5 + temp * 2;
	
	// 3
	temp = N / (SINGLE * 3);
	N -= temp * SINGLE * 3;
	res += temp * 3 + temp;
	
	res += N / SINGLE;
	
	std::cout << res;
}

}
