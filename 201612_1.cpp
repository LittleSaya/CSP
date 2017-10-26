#include "csptest.h"
#include "commonFunc.h"
#include <iostream>
#include <vector>

void quickSort(std::vector<int> &v, int low, int high);

void f_201612_1()
{
	int N = 0;
	std::cin >> N;
	std::vector<int> v(N);
	for (size_t i = 0; i < v.size(); ++i)
	{	std::cin >> v[i]; }
	
//	printIntVector(v);
	
	quickSort(v, 0, v.size() - 1);
	
//	printIntVector(v);
	
	int mIdx = 0, smaller = 0, bigger = 0;
	int lastTime = 0;
	mIdx = v.size() / 2;
	while (true)
	{
		int i = 0;
		// 第一个比v[mIdx]小的数字的下标=>比v[mIdx]小的数字有多少个 
		for (i = mIdx - 1; i >= 0; --i)
		{
			if (v[i] < v[mIdx])
			{	break; }
		}
		smaller = i + 1;
//		std::cout << "smaller=" << smaller << std::endl;
		// 第一个比v[mIdx]大的数字的下标=>比v[mIdx]大的数字有多少个 
		for (i = mIdx + 1; i < v.size(); ++i)
		{
			if (v[i] > v[mIdx])
			{	break; }
		}
		bigger = v.size() - i;
//		std::cout << "bigger=" << bigger << std::endl;
		
		if (smaller == bigger)
		{
			std::cout << v[mIdx];
			return;
		}
		else if (smaller < bigger)
		{
			if (-1 == lastTime)
			{
				std::cout << -1;
				return;
			}
			lastTime = 1;
			for (i = mIdx + 1; i < v.size() && v[i] <= v[mIdx]; ++i)
			{ }
			if (v.size() == i)
			{
				std::cout << -1;
				return;
			}
			else
			{	mIdx = i; }
		}
		else
		{
			if (1 == lastTime)
			{
				std::cout << -1;
				return;
			}
			lastTime = -1;
			for (i = mIdx - 1; i >= 0 && v[i] >= v[mIdx]; ++i)
			{ }
			if (-1 == i)
			{
				std::cout << -1;
				return;
			}
			else
			{	mIdx = i; }
		}
	}
}

void quickSort(std::vector<int> &v, int low, int high)
{
//	static int cnt = 0;
//	std::cout << ++cnt << std::endl;
	
	if (low >= high)
	{	return; }
	int left = low, right = high;
	int k = v[low];
	while (left < right)
	{
		while (left < right && v[right] >= k)
		{	--right; }
		swap(v[left], v[right]);
//		printIntVector(v);
//		std::cout << "left=" << left << ", right=" << right << std::endl;
		while (left < right && v[left] <= k)
		{	++left; }
		swap(v[left], v[right]);
//		printIntVector(v);
//		std::cout << "left=" << left << ", right=" << right << std::endl;
	}
	quickSort(v, low, left - 1);
	quickSort(v, left + 1, high);
}
