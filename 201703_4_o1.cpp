// first optimization try
// I made an graphic table!
// the graph may get more compressed
// this is worng

#include "csptest.h"
#include <iostream>
#include <climits>

namespace Q201703_4_o1
{

const unsigned char existedFlag = 0x01;
const unsigned char excludedFlag = 0x02;

struct EdgeState
{
//	bool isExist;
//	bool isExcluded;
	unsigned char flags;
	int weight;
	
	EdgeState(): flags(0x00), weight(0) { }
	
	bool getIsExisted() { return flags & existedFlag; }
	void setIsExisted() { flags |= existedFlag; }
	void unsetIsExisted() { flags &= ~existedFlag; }
	
	bool getIsExcluded() { return flags & excludedFlag; }
	void setIsExcluded() { flags |= excludedFlag; }
	void unsetIsExcluded() { flags &= ~excludedFlag; }
};

int vertexN = 0;
int edgeN = 0;
EdgeState **graph = NULL;

int *currentPath = NULL;
bool *visitedArray = NULL;
int pathIdx = 0;// current pos

void input();
void init();
void free();
void output();

void printPath();

void f_201703_4_o1()
{
	input();
	init();
	
	visitedArray[0] = true;// first node is visited at the beginning
	
	int i1 = 0;
	int minWeight = 0, nextNode = 0;
//	printPath();
	while (currentPath[pathIdx] != vertexN - 1)
	{
		// find the "lightest" vaild edge
		minWeight = INT_MAX;
		for (i1 = 0; i1 < vertexN; ++i1)
			if (graph[currentPath[pathIdx]][i1].getIsExisted() && !graph[currentPath[pathIdx]][i1].getIsExcluded() && !visitedArray[i1] &&
				graph[currentPath[pathIdx]][i1].weight < minWeight)
			{
				minWeight = graph[currentPath[pathIdx]][i1].weight;
				nextNode = i1;
			}
		if (minWeight == INT_MAX)// dead end
		{
			graph[currentPath[pathIdx]][currentPath[pathIdx - 1]].setIsExcluded();// make previous tunnel "Excluded"
			graph[currentPath[pathIdx - 1]][currentPath[pathIdx]].setIsExcluded();// mirror
			--pathIdx;// move back
			continue;
		}
		visitedArray[nextNode] = true;
		++pathIdx;
		currentPath[pathIdx] = nextNode;// we foung a way, move on
//		printPath();
	}
	output();
	free();
}

void input()
{
	using std::cin;
	
	// the iterator, 2 nodes and a weight value
	int i = 0, v1 = 0, v2 = 0, w = 0;
	// input the amount of Nodes and Alternative tunnels
	cin >> vertexN >> edgeN;
	// allocate the graphic
	graph = new EdgeState*[vertexN];
	for (i = 0; i < vertexN; ++i)
		graph[i] = new EdgeState[vertexN]();
	// fulfill the graphic
	for (i = 0; i < edgeN; ++i)
	{
		cin >> v1 >> v2 >> w;
		--v1; --v2;// internally, the node begin with 0
		graph[v1][v2].setIsExisted();
		graph[v1][v2].weight = w;
		graph[v2][v1].setIsExisted();// mirror
		graph[v2][v1].weight = w;// mirror
	}
}

void init()
{
	currentPath = new int[vertexN]();
	visitedArray = new bool[vertexN]();
}

void free()
{
	for (int i = 0; i < vertexN; ++i)
		delete[] graph[i];
	delete[] graph, currentPath, visitedArray;
}

void output()
{
	int maxWeight = 0;
	for (int i = 0; i < pathIdx; ++i)
		maxWeight = (graph[currentPath[i]][currentPath[i + 1]].weight > maxWeight ? graph[currentPath[i]][currentPath[i + 1]].weight : maxWeight);
	std::cout << maxWeight;
}

void printPath()
{
	std::cout << std::endl << "path:";
	int i = 0;
	for (i = 0; i < pathIdx; ++i)
		std::cout << currentPath[i] << "->";
	std::cout << currentPath[i] << std::endl;
}

}

