#include "csptest.h"
#include <vector>
#include <cstdio>
#include <climits>

// Dijkstra + Prim 
// δʹ����С���Ż�
// 80fen
 
namespace Q201609_4_o1
{

struct AdjNode
{
	int nodeId;
	int len;
	
	AdjNode() : nodeId(0), len(0) { }
	AdjNode(int p_nodeId, int p_len) : nodeId(p_nodeId), len(p_len) { }
};

struct NodeStat
{
	int pre;
	int preLen;
	int len;
	bool isIncluded;
	
	NodeStat() : pre(0), preLen(0), len(INT_MAX), isIncluded(false) { }
	NodeStat(int p_pre, int p_preLen, int p_len, bool p_isIncluded) : pre(p_pre), preLen(p_preLen), len(p_len), isIncluded(p_isIncluded) { }
};

int nodeN = 0, edgeN = 0;
std::vector<std::vector<AdjNode> > adjTable;
std::vector<NodeStat> statTable;

void input();

void f_201609_4_o1()
{
	input();
	
	int includeN = 1;// capital is included at the beginning
	int lenSum = 0;
	int expandNode = 1;// expand from the capital 
	while (includeN < nodeN)
	{
		// ��expandNode��ʼ��չ�������ýڵ�������ڽ� 
		for (int i = 0; i < adjTable[expandNode].size(); ++i)
		{
			if (statTable[adjTable[expandNode][i].nodeId].len > (adjTable[expandNode][i].len + statTable[expandNode].len))
			{
				// Ŀ��ڵ�Ŀǰ�����·������ > expandNode��ǰ�����·������ + ���ڵ���ڽ�·���ĳ��� 
				// ����Ŀ��ڵ��ǰ��ΪexpandNode������Ŀ��ڵ�����·������ΪexpandNode��ǰ�����·������ + ���ڵ���ڽ�·���ĳ���
				statTable[adjTable[expandNode][i].nodeId].pre = expandNode;
				statTable[adjTable[expandNode][i].nodeId].preLen = adjTable[expandNode][i].len;
				statTable[adjTable[expandNode][i].nodeId].len = adjTable[expandNode][i].len + statTable[expandNode].len;
			}
			else if (statTable[adjTable[expandNode][i].nodeId].len == (adjTable[expandNode][i].len + statTable[expandNode].len))
			{
				// Ŀ��ڵ�Ŀǰ�����·������ == expandNode��ǰ�����·������ + ���ڵ���ڽ�·���ĳ���
				// �Ƚ�Ŀ��ڵ����䵱ǰǰ��֮����ڽӳ��ȣ���Ŀ��ڵ���expandNode֮����ڽӳ���
				// ѡ���ڽӳ��Ƚ϶̵���Ϊ�µ�ǰ��
				if (statTable[adjTable[expandNode][i].nodeId].preLen > adjTable[expandNode][i].len)
				{
					statTable[adjTable[expandNode][i].nodeId].pre = expandNode;
					statTable[adjTable[expandNode][i].nodeId].preLen = adjTable[expandNode][i].len;
				}
			}
		}
		// ������δ�����벢���ѱ����ֵĽڵ㣨��ǰ���Ľڵ㣩�У��ҳ���ǰ����С·����С���Ǹ�
		// ������룬������Ϊ��һ����չ����
		int minLen = INT_MAX;
		for (int i = 1; i <= nodeN; ++i)
		{
			if (!statTable[i].isIncluded && 0 != statTable[i].pre && statTable[i].len < minLen)
			{
				minLen = statTable[i].len;
				expandNode = i;
			}
		}
		++includeN;
		statTable[expandNode].isIncluded = true;
	}
	for (int i = 2; i <= nodeN; ++i)
	{
		lenSum += statTable[i].preLen;
	}
//	std::cout << lenSum;
	std::printf("%d", lenSum);
}

void input()
{
	int a = 0, b = 0, w = 0;
//	std::cin >> nodeN >> edgeN;
	std::scanf("%d %d", &nodeN, &edgeN);
	adjTable.resize(nodeN + 1);
	for (int i = 0; i < edgeN; ++i)
	{
//		std::cin >> a >> b >> w;
		std::scanf("%d %d %d", &a, &b, &w);
		adjTable[a].push_back(AdjNode(b, w));
		adjTable[b].push_back(AdjNode(a, w));
	}
	statTable.resize(nodeN + 1);
	statTable[1].isIncluded = true;
	statTable[1].len = 0;
//	for (int i = 2; i <= nodeN; ++i)
//	{
//		statTable[i].len = INT_MAX;// infinity
//	}
}

}
