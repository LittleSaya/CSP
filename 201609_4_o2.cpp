#include "csptest.h"
#include <iostream>
#include <vector>
#include <climits>
#include <queue>

// Dijkstra + Prim + 最小堆优化 

namespace Q201609_4_o2
{

struct AdjNode
{
	int id;
	int adjLen;
	
	AdjNode() : id(0), adjLen(0) { }
	AdjNode(int p_id, int p_adjLen) : id(p_id), adjLen(p_adjLen) { }
};

struct NodeStat
{
	int id;
	int preId;
	int preLen;
	int allLen;
	bool included;
	
	NodeStat() : id(0), preId(0), preLen(0), allLen(INT_MAX), included(false) { }
	
	bool operator<(const NodeStat &node) const { return this->allLen > node.allLen; }
};

int nodeN = 0, edgeN = 0;
std::vector<std::vector<AdjNode> > adjTable;
std::vector<NodeStat> statList;

void init();

void f_201609_4_o2()
{
	init();
	std::priority_queue<NodeStat> pQueue;
	pQueue.push(statList[1]);// the capital is the first to be included
	while (pQueue.size())
	{
		// get the most costless unincluded node
		NodeStat node = pQueue.top();
		pQueue.pop();
		if (node.included) { continue; }
		node.included = true;
		// traverse all of its adjNodes
		for (int i = 0, id = 0, adjLen = 0; i < adjTable[node.id].size(); ++i)
		{
			// refresh the statList
			id = adjTable[node.id][i].id;
			adjLen = adjTable[node.id][i].adjLen;
			if (statList[id].allLen > adjLen + node.allLen)
			{
				statList[id].allLen = adjLen + node.allLen;
				statList[id].preId = node.id;
				statList[id].preLen = adjLen;
				pQueue.push(statList[id]);// push new data into the queue
			}
			else if (statList[id].allLen == adjLen + node.allLen && statList[id].preLen > adjLen)
			{
				statList[id].preLen = adjLen;
				statList[id].preId = node.id;
			}
		}
	}
	int sumLen = 0;
	for (int i = 2; i <= nodeN; ++i)
	{
		sumLen += statList[i].preLen;
	}
	std::cout << sumLen;
}

void init()
{
	std::cin >> nodeN >> edgeN;
	// build the adjTable
	adjTable.resize(nodeN + 1);
	int a = 0, b = 0, c = 0;
	for (int i = 0; i < edgeN; ++i)
	{
		std::cin >> a >> b >> c;
		adjTable[a].push_back(AdjNode(b, c));
		adjTable[b].push_back(AdjNode(a, c));
	}
	// build the statList
	statList.resize(nodeN + 1);
	for (int i = 1; i <= nodeN; ++i)
	{
		statList[i].id= i;
	}
	statList[1].allLen = 0;// capital's len = 0
}

} 
