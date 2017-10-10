// http://blog.csdn.net/u010568270/article/details/68939757
// http://blog.csdn.net/dm_vincent/article/details/7655764
// the forth try
// use optimized UnionFind

#include "csptest.h"
#include "UnionFind.h"
#include <iostream>

namespace Q201703_4_o3
{

struct Edge
{
	int v1;
	int v2;
	int w;
	
	Edge(): v1(0), v2(0), w(0) { }
};

int vertexN = 0;
int edgeN = 0;
Edge *edges = NULL;
int *edgeIdx = NULL;

myds::UnionFind *unionFind = NULL;

void input();
void sortEdge();
void initUF();
void free();

void quickSort(int *idx, int low, int high);

int compareIdx(int i1, int i2)
{
	return (edges[i1].w - edges[i2].w);
}

void swap(int *v1, int *v2)
{
	static int temp;
	temp = *v1;
	*v1 = *v2;
	*v2 = temp;
}

void f_201703_4_o3()
{
	input();
	sortEdge();
	initUF();
	
	int pairAdded = 0, maxWeight = 0;
	while (!unionFind->isConnected(0, vertexN - 1))
	{
		unionFind->connect(edges[edgeIdx[pairAdded]].v1 - 1, edges[edgeIdx[pairAdded]].v2 - 1);
		maxWeight = (maxWeight < edges[edgeIdx[pairAdded]].w ? edges[edgeIdx[pairAdded]].w : maxWeight);
		++pairAdded;
	}
	
	std::cout << maxWeight;
	
	free();
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
}

void sortEdge()
{
	quickSort(edgeIdx, 0, edgeN - 1);
}

void initUF()
{
	unionFind = new myds::UnionFind(vertexN);
}

void free()
{
	delete[] edges, edgeIdx;
	delete unionFind;
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
				break;
			}
		}
	}
	quickSort(idx, low, left - 1);
	quickSort(idx, left + 1, high);
}

}

 
