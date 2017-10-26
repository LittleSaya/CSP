#include "csptest.h"
#include "commonFunc.h"
#include <iostream>
#include <vector>
#include <algorithm>

// THIS IS (NOT) A WORNG ANSWER
// this is not a wrong answer ;_;

struct WSC
{
	int w;
	int s;
	int c;
	
	WSC(): w(0), s(0), c(0) { }
};

struct TimeStamp
{
	int time;
	std::vector<int> inKey;
	std::vector<int> outKey;
	
	TimeStamp(): time(0), inKey(), outKey() { }
	TimeStamp(int t): time(t), inKey(), outKey() { }
};

int findTime(int t, const std::vector<TimeStamp> &v);
void sortIndice(int *indice, const std::vector<TimeStamp> &v);
void sortIndice_in(int *indice, int low, int high, const std::vector<TimeStamp> &v);

void f_201709_2()
{
	// input
	int keyN = 0, teacherN = 0;
	std::cin >> keyN >> teacherN;
	int *keyState = new int[keyN]();
	for (int i = 0; i < keyN; ++i)
		keyState[i] = i + 1;
	WSC *input = new WSC[teacherN]();
	for (int i = 0; i < teacherN; ++i)
		std::cin >> input[i].w >> input[i].s >> input[i].c;
	
	std::vector<TimeStamp> theList;
	int idx = 0;
	for (int i = 0; i < teacherN; ++i)
	{
		// start time
		idx = findTime(input[i].s, theList);
		if (idx < 0)
		{
			theList.push_back(TimeStamp(input[i].s));
			theList.back().outKey.push_back(input[i].w);
		}
		else
		{
			theList[idx].outKey.push_back(input[i].w);
		}
		// end time
		idx = findTime(input[i].s + input[i].c, theList);
		if (idx < 0)
		{
			theList.push_back(TimeStamp(input[i].s + input[i].c));
			theList.back().inKey.push_back(input[i].w);
		}
		else
		{
			theList[idx].inKey.push_back(input[i].w);
		}
	}
	
	int *indice = new int[theList.size()];
	for (int i = 0; i < theList.size(); ++i)
		indice[i] = i;
	
//	for (int i = 0; i < theList.size(); ++i)
//	{
//		std::cout << theList[indice[i]].time << "\t[I:";
//		for (int j = 0; j < theList[indice[i]].inKey.size(); ++j)
//			std::cout << theList[indice[i]].inKey[j] << ',';
//		std::cout << "]\t[O:";
//		for (int j = 0; j < theList[indice[i]].outKey.size(); ++j)
//			std::cout << theList[indice[i]].outKey[j] << ',';
//		std::cout << "]" << std::endl;
//	}
//	
//	std::cout << std::endl;
	
	sortIndice(indice, theList);
	for (int i = 0; i < theList.size(); ++i)
		std::sort(theList[i].inKey.begin(), theList[i].inKey.end());
	
//	for (int i = 0; i < theList.size(); ++i)
//	{
//		std::cout << theList[indice[i]].time << "\t[I:";
//		for (int j = 0; j < theList[indice[i]].inKey.size(); ++j)
//			std::cout << theList[indice[i]].inKey[j] << ',';
//		std::cout << "]\t[O:";
//		for (int j = 0; j < theList[indice[i]].outKey.size(); ++j)
//			std::cout << theList[indice[i]].outKey[j] << ',';
//		std::cout << "]" << std::endl;
//	}
	
	for (int i = 0, j = 0; i < theList.size(); ++i)
	{
		j = indice[i];
//		std::cout << "time:" << theList[j].time << std::endl;
		// in
		for (int m = 0; m < theList[j].inKey.size(); ++m)
			for (int n = 0; n < keyN; ++n)
				if (0 == keyState[n])
				{
					keyState[n] = theList[j].inKey[m];
					break;
				}
		
//		for (int i = 0; i < keyN - 1; ++i)
//			std::cout << keyState[i] << ' ';
//		std::cout << keyState[keyN - 1] << std::endl;
	
		// out
		for (int m = 0; m < theList[j].outKey.size(); ++m)
			for (int n = 0; n < keyN; ++n)
				if (keyState[n] == theList[j].outKey[m])
				{
					keyState[n] = 0;
					break;
				}
		
//		for (int i = 0; i < keyN - 1; ++i)
//			std::cout << keyState[i] << ' ';
//		std::cout << keyState[keyN - 1] << std::endl;
	}
	
	for (int i = 0; i < keyN - 1; ++i)
		std::cout << keyState[i] << ' ';
	std::cout << keyState[keyN - 1];
	
	delete[] input, keyState, indice;
}

int findTime(int t, const std::vector<TimeStamp> &v)
{
	for (int i = 0; i < v.size(); ++i)
		if (v[i].time == t) return i;
	return -1;
}

void sortIndice(int *indice, const std::vector<TimeStamp> &v)
{
	sortIndice_in(indice, 0, v.size() - 1, v);
}

void sortIndice_in(int *indice, int low, int high, const std::vector<TimeStamp> &v)
{
	if (low >= high) return;
	int first = low, last = high;
	int key = indice[low];
	while (first < last)
	{
		while (first < last && v[indice[last]].time >= v[key].time)
			--last;
		if (first >= last) break;
		swap(indice[last], indice[first]);
		while (first < last && v[indice[first]].time <= v[key].time)
			++first;
		if (first >= last) break;
		swap(indice[last], indice[first]);
	}
	indice[first] = key;
	sortIndice_in(indice, low, first - 1, v);
	sortIndice_in(indice, first + 1, high, v);
}
