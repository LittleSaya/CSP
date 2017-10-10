// this is worng

#include "csptest.h"
#include <iostream>
#include <climits>

// 1.excluded edges 
// 2.vertexes that have been visited
// 3.current pos

namespace Q201703_4
{

struct EdgeInfo
{
	int v1;// vertex 1
	int v2;// vertex 2
	int w;// weight
	
	EdgeInfo(): v1(0), v2(0), w(0) { }
};
	
// global variables
int n = 0, m = 0;// n: how many vertexes, m: how many edges
EdgeInfo *edgeInfos = new EdgeInfo[m];

int *excludedEdges = NULL;
int excludedEdgesN = 0;
int *visitedVertexes = NULL;
int currentPos = 0;// the index of "visitedVertexes", we are at v1 at first

// iterators
int i1 = 0, i2 = 0, i3 = 0;
int g1 = 0, g2 = 0;

void input();
bool isExcludedEdge(int e);
bool isVertexVisited(int v);
void makeExcluded();
void output();

void f_201703_4()
{
	input();// input
	
	// init array
	excludedEdges = new int[m]();// no excluded edges at first
	visitedVertexes = new int[n]();// vertexes that we have visited (in order), only v1 has been visited at first
	visitedVertexes[0] = 1;
	
	// local variables
	int nextNode = 0;// next Node
	int nextEdgeWit = 0;// the weight of next edge
	
	unsigned long ctr = 0;// loop count
	
	
	bool hasNextEdge = false, isLoop = false;
	while (visitedVertexes[currentPos] != m && ctr < 1000000)
	{
		// find next edge to go
		hasNextEdge = false;
		nextEdgeWit = INT_MAX;// before we begin to select an edge, we assume that we have had an edge and that edge is very "heavy"
		for (i1 = 0; i1 < m; ++i1)
		{
			// is this edge excluded?
			if (isExcludedEdge(i1)) { continue; }// this edge is excluded
			
			// ok, we found a non-excluded edge
			// but one of the edge's vertexes must be the "visitedVertexes[currentPos]"
			if (edgeInfos[i1].v1 == visitedVertexes[currentPos])// v1 is visitedVertexes[currentPos]
			{
				// first, we must make sure that we haven't visited v2 before
				if (isVertexVisited(edgeInfos[i1].v2)) { continue; }// ok, this new edge will make a "loop", we can not use it
				
				// now, the next edge must be as "light" as possible
				if (edgeInfos[i1].w < nextEdgeWit)
				{
					nextEdgeWit = edgeInfos[i1].w;// this can be put before the Loop Exam?
					nextNode = edgeInfos[i1].v2;
					hasNextEdge = true;
				}
			}
			else if (edgeInfos[i1].v2 == visitedVertexes[currentPos])// v2 is visitedVertexes[currentPos]
			{
				// similiar
				if (isVertexVisited(edgeInfos[i1].v1)) { continue; }
				if (edgeInfos[i1].w < nextEdgeWit)// similiar
				{
					nextEdgeWit = edgeInfos[i1].w;
					nextNode = edgeInfos[i1].v1;
					hasNextEdge = true;
				}
			}
		}
		if (!hasNextEdge)
		{
			// at this point, we found no way to go
			// we must turn back to last vertex
			// then find and make the last edge "excluded"
			makeExcluded();
		}
		else
		{
			++currentPos;
			visitedVertexes[currentPos] = nextNode;
		}
	}
	
	output();
	
	delete[] excludedEdges, visitedVertexes;
}

void input()
{
	using std::cin;
	
	cin >> n >> m;
	for (int i = 0; i < m; ++i)
	{
		cin >> edgeInfos[i].v1 >> edgeInfos[i].v2 >> edgeInfos[i].w;
	}
}

bool isExcludedEdge(int e)
{
	for (g1 = 0; g1 < excludedEdgesN; ++g1)
	{
		if (e == excludedEdges[g1])
		{
			return true;
		}
	}
	return false;
}

bool isVertexVisited(int v)
{
	for (g1 = 0; g1 < currentPos; ++g1)
	{
		if (v == visitedVertexes[g1])
		{
			return true;
		}
	}
	return false;
}

void makeExcluded()
{
	// turn back to last vertex
	--currentPos;
	// find and make the last edge "excluded"
	for (g1 = 0; g1 < m; ++g1)
	{
		if ((edgeInfos[g1].v1 == visitedVertexes[currentPos] && edgeInfos[g1].v2 == visitedVertexes[++currentPos]) ||
			(edgeInfos[g1].v2 == visitedVertexes[currentPos] && edgeInfos[g1].v1 == visitedVertexes[++currentPos]))
		{
			excludedEdges[excludedEdgesN] = g1;
			++excludedEdgesN;
		}
	}
}

void output()
{
	using std::cout;
	
	int maxW = 0;
	for (g1 = 0; g1 < currentPos; ++g1)
	{
		for (g2 = 0; g2 < m; ++g2)
		{
			if ((edgeInfos[g2].v1 == visitedVertexes[g1] && edgeInfos[g2].v2 == visitedVertexes[g1 + 1]) ||
			(edgeInfos[g2].v2 == visitedVertexes[g1] && edgeInfos[g2].v1 == visitedVertexes[g1 + 1]))
			{
				maxW = (edgeInfos[g2].w > maxW ? edgeInfos[g2].w : maxW);
			}
		}
	}
	
	cout << maxW;
}

}
