#include "csptest.h"
#include <iostream>

namespace Q201703_1
{

void f_201703_1()
{
	using std::cin;
	using std::cout;
	int n = 0, k = 0;//n:how many cakes, k:min weight per person
	cin >> n >> k;
	int* cakes = new int[n];
	for (int i = 0; i < n; ++i)
		cin >> cakes[i];
	int complete = 0;
	int accumulated = 0;
	for (int i = 0; i < n; ++i)
	{
		accumulated += cakes[i];
		if (accumulated >= k)
		{
			accumulated = 0;
			++complete;
		} 
	}
	if (accumulated > 0)
		++complete;
	cout << complete;
	delete [] cakes;
}

}
