#include "csptest.h"
#include <vector>
#include <climits>
#include <iostream>

namespace Q201609_4
{
// 最小生成树
// prim

// it's wrong
// it's wrong
// it's wrong
// it's wrong

struct AdjNode
{
	int id;
	int w;
	
	AdjNode(int p_id, int p_w) : id(p_id), w(p_w)
	{
	}
};

struct NodeStat
{
	int adj;
	int len;
	
	NodeStat() : adj(1), len(INT_MAX)
	{
	}
	
	NodeStat(int p_adj, int p_len) : adj(p_adj), len(p_len)
	{
	}
};

int cityN = 0;
int roadN = 0;

std::vector<std::vector<AdjNode> > adjTable;
std::vector<NodeStat> nodeStat;

void f_201609_4()
{
	// input
	std::cin >> cityN >> roadN;
	// build the adjTable
	adjTable.resize(cityN + 1);
	for (int i = 0; i < roadN; ++i)
	{
		int a = 0, b = 0, c = 0;
		std::cin >> a >> b >> c;
		adjTable[a].push_back(AdjNode(b, c));
		adjTable[b].push_back(AdjNode(a, c));
	}
	// build the first nodeStat
	nodeStat.resize(cityN + 1, NodeStat());
	nodeStat[0].adj = nodeStat[1].adj = 0;// capital is included at the beginning
	nodeStat[0].len = nodeStat[1].len = 0;
	for (int i = 0; i < adjTable[1].size(); ++i)
	{
		nodeStat[adjTable[1][i].id].len = adjTable[1][i].w;
	}
	// loop to include other nodes
	int sum = 0;
	for (int i = 0; i < cityN - 1; ++i)
	{
		int nodeToConnect = 0;
		int minW = INT_MAX;
		for (int j = 2; j <= cityN; ++j)
		{
			// find the next node
			if (0 != nodeStat[j].adj && nodeStat[j].len < minW)
			{
				minW = nodeStat[j].len;
				nodeToConnect = j;
			}
		}
		// add the node to the net
		nodeStat[nodeToConnect].adj = nodeStat[nodeToConnect].len = 0;
		sum += minW;
		// refresh
		for (int j = 0; j < adjTable[nodeToConnect].size(); ++j)
		{
			if (adjTable[nodeToConnect][j].w < nodeStat[adjTable[nodeToConnect][j].id].len)
			{
				nodeStat[adjTable[nodeToConnect][j].id].adj = nodeToConnect;
				nodeStat[adjTable[nodeToConnect][j].id].len = adjTable[nodeToConnect][j].w;
			}
		}
	}
	std::cout << sum;
}

}
