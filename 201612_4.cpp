#include "csptest.h"
#include <iostream>
#include <climits>

// 有问题，有可能是超时了 

namespace Q201612_4
{

const int N = 1000;

int n = 0;
int freq[N];// frequency
int nb[N - 1];// neighbour

int dict_min_wpl(int arr[N], int low, int high);

void f_201612_4()
{
	std::cin >> n;
	for (int i = 0; i < n; ++i)
	{
		std::cin >> freq[i];
		std::cout << freq[i] << ' ';
	}
	std::cout << std::endl;
	
	for (int i = 0; i < n - 1; ++i)
	{
		nb[i] = freq[i] + freq[i + 1];
		std::cout << nb[i] << ' ';
	}
	std::cout << std::endl;
	
	int min = dict_min_wpl(freq, 0, n - 1);
	std::cout << min;
}

int dict_min_wpl(int arr[N], int low, int high)
{
	// 1
	if (low >= high)
	{	return 0; }
	// 2
	if (high - 1 == low)
	{	return nb[low]; }
	// other
	int sum = 0;
	for (int i = low; i <= high; ++i)
	{	sum += freq[i]; }
	int min = INT_MAX;
	for (int i = low; i < high; ++i)
	{
		int t = dict_min_wpl(arr, low, i) + dict_min_wpl(arr, i + 1, high) + sum;
		if (min > t)
		{	min = t; }
	}
	return min;
}

}
