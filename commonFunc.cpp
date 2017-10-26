#include "csptest.h"
#include <iostream>
#include <vector>

void swap(int &a, int &b)
{
	static int c = 0;
	c = a;
	a = b;
	b = c;
}

void printArray(int *array, int n)
{
	for (int i = 0; i < n - 1; ++i)
		std::cout << array[i] << " ";
	if (n > 0)
		std::cout << array[n - 1];
}

void printArray_p(int *array, int n)
{
	for (int i = 0; i < n - 1; ++i)
		std::cout << array[i] + 1 << " ";
	if (n > 0)
		std::cout << array[n - 1] + 1;
}

void printIntVector(const std::vector<int> &v)
{
	for (size_t i = 0; i < v.size(); ++i)
		std::cout << v[i] << " ";
	std::cout << std::endl;
}
