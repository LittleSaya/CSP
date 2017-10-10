// http://blog.csdn.net/u010568270/article/details/68939757
// the third try
// do not use "Tree" to organize vertexes

#include "csptest.h"
#include <iostream>

namespace Q201703_4_o2
{

struct Edge
{
	int v1;
	int v2;
	int w;
	
	Edge(): v1(0), v2(0), w(0) { }
};

int vertexN = 0;
Edge *edges = NULL;
int edgeN = 0;
int *edgeIdx = NULL;

int *union_find = NULL;
int findGroup(int idx) { return union_find[idx]; }
void addPair(int v1, int v2); 

void input();
void sortEdge();
void free();

void quickSort(int *idx, int low, int high);
int compareIdx(int i1, int i2) { return (edges[i1].w - edges[i2].w); }
void swap(int *v1, int *v2) { static int temp; temp = *v1; *v1 = *v2; *v2 = temp; }

void idxAndWeight();
void printUF();

void f_201703_4_o2()
{
	input();
	sortEdge();
//	idxAndWeight();
	
	int pairAdded = 0, maxWeight = 0;
	while (findGroup(1) != findGroup(vertexN))
	{
		addPair(edges[edgeIdx[pairAdded]].v1, edges[edgeIdx[pairAdded]].v2);
		maxWeight = (maxWeight < edges[edgeIdx[pairAdded]].w ? edges[edgeIdx[pairAdded]].w : maxWeight);
		++pairAdded;
//		std::cout << "union find state:" << std::endl;
//		printUF();
//		std::cout << "max weight = " << maxWeight << std::endl;
	}
	
	std::cout << maxWeight;
	
	free();
}

void addPair(int v1, int v2)
{
	static int temp = 0;
	temp = union_find[v1];
//	std::cout << "pair added: (" << v1 << ", " << v2 << ")" << std::endl;
	if (union_find[v1] == union_find[v2]) { return; }
	for (int i = 1; i < vertexN; ++i)
		if (union_find[i] == temp) { union_find[i] = union_find[v2]; }
}

void input()
{
	std::cin >> vertexN >> edgeN;
	edges = new Edge[edgeN]();
	edgeIdx = new int[edgeN]();
	for (int i = 0; i < edgeN; ++i)
	{
		std::cin >> edges[i].v1 >> edges[i].v2 >> edges[i].w;
		edgeIdx[i] = i;
	}
	// initialize the UF, we make it's index starts with 1
	union_find = new int[vertexN + 1]();
	for (int i = 1; i <= vertexN; ++i)
		union_find[i] = i;
}

void sortEdge()
{
	quickSort(edgeIdx, 0, edgeN - 1);
}

void quickSort(int *idx, int low, int high)
{
	if (low >= high) { return; }
	int left = low, right = high;
	int key = idx[low];
	while (left != right)
	{
		while (left != right)
		{
			if (compareIdx(idx[right], key) >= 0)
				--right;
			else
			{
				swap(idx + right, idx + left);
//				idxAndWeight();
				break;
			}
		}
		while (left != right)
		{
			if (compareIdx(idx[left], key) <= 0)
				++left;
			else
			{
				swap(idx + left, idx + right);
//				idxAndWeight();
				break;
			}
		}
	}
	quickSort(idx, low, left - 1);
	quickSort(idx, left + 1, high);
}

void free()
{
	delete[] edges, edgeIdx, union_find;
}

void idxAndWeight()
{
	std::cout << "\n=======begin=======\n";
	std::cout << "i\tw" << std::endl;
	for (int i = 0; i < edgeN; ++i)
		std::cout << edgeIdx[i] << '\t' << edges[edgeIdx[i]].w << std::endl;
	std::cout << "=======end=======\n";
}

void printUF()
{
	std::cout << "V:";
	for (int i = 0; i < vertexN + 1; ++i)
		std::cout << i << ' ';
	std::cout << "\nG:";
	for (int i = 0; i < vertexN + 1; ++i)
		std::cout << union_find[i] << ' ';
	std::cout << std::endl;
}

} 
