#include "csptest.h"
#include <vector>
#include <iostream>

namespace Q201709_4_o1
{

/*
	参考：http://blog.csdn.net/gl486546/article/details/78232690?locationNum=5&fps=1
	
	基本思路：
	一、使用邻接表而不是邻接矩阵，在数据量最大的情况下邻接矩阵占用的空间是邻接表的100倍，同时大量的空循环会拖慢速度 
	二、遍历每一个点，对每一个点按正方向进行一次DFS，在这个过程中和它的所有下级建立一个双向的关系
		也就是说对每一个点，它知道它的所有下级，它的所有下级也都知道它
		待所有的点都遍历完成之后，每一个点都知道它的所有上级和所有下级 
*/ 
typedef unsigned short US;
typedef unsigned char UC;

std::vector<US> *graph;// 邻接矩阵 
UC **isKnow;// 存储双向关系的表格 
US N, M;

void dfsSolve(US ori, US cur, UC *visited);

void f_201709_4_o1()
{
	std::cin >> N >> M;
	graph = new std::vector<US>[N];// 邻接表 
	isKnow = new UC*[N];// 双向关系 
	for (US i = 0; i < N; ++i)
		isKnow[i] = new UC[N]();
	for (US i = 0, a = 0, b = 0; i < M; ++i)
	{
		std::cin >> a >> b;
		graph[a - 1].push_back(b - 1);
	}
	
	US remain = N;// 满足条件的点的数量 
	for (US i = 0; i < N; ++i)
	{
		UC *visited = new UC[N]();// 这里不能用isKnow的状态来代替visited，因为不能保证不会出现环状结构 
		dfsSolve(i, i, visited);
		delete[] visited;
	}
	for (US i = 0; i < N; ++i)
	{
		for (US j = 0; j < N; ++j)
		{
			if (!isKnow[i][j])
			{
				--remain;
				break;
			}
		}
	}
	std::cout << remain;
	
	delete[] graph;
	for (US i = 0; i < N; ++i)
		delete[] isKnow[i];
	delete[] isKnow;
}

void dfsSolve(US ori, US cur, UC *visited)
{
	visited[cur] = 1;
	isKnow[ori][cur] = isKnow[cur][ori] = 1;
	for (std::size_t i = 0; i < graph[cur].size(); ++i)
	{
		if (!visited[graph[cur][i]])
		{	dfsSolve(ori, graph[cur][i], visited); }
	}
}

}
