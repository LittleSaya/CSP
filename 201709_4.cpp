#include "csptest.h"
#include <iostream>

// cost too much
namespace Q201709_4
{ 

void forwardKnow(int i, unsigned char **graph, unsigned char *know, int N); 
void backwardKnow(int i, unsigned char **graph, unsigned char *know, int N); 

void f_201709_4()
{
	int N, M;
	std::cin >> N >> M;
	unsigned char **graph = new unsigned char*[N];// 采用邻接矩阵表示法，效率低下（占用空间大，空循环多） 
	for (int i = 0; i < N; ++i)
		graph[i] = new unsigned char[N]();
	for (int i = 0, a = 0, b = 0; i < M; ++i)
	{
		std::cin >> a >> b;
		graph[a - 1][b - 1] = 1;
	}
	
//	for (int y = 0; y < N; ++y)
//	{
//		for (int x = 0; x < N; ++x)
//			std::cout << (int)graph[y][x];
//		std::cout << std::endl;
//	}
	
	int remain = N;
	for (int i = 0; i < N; ++i)
	{
		/*
			同样是深度优先算法，我的做法把每个点都割离了开来
			对每一个点，单独计算它的上级和下级：
				首先从点i从正方向进行一次DFS，记录所有访问过的点（找到这个点的所有下级） 
				然后从点i从反方向进行一次DFS，记录所有访问过的点（找到这个点的所有上级） 
				最后判断是不是把每一个点都访问了一遍
				如果不是的话就--remain
			网络上的做法是：
				对每一个点i，从正方向进行一次DFS，和它所有的下级建立一个双向关系
				也就是说，让点i知道它所有的下级，也让点i所有的下级知道点i
				整个过程执行完毕之后，对点i来说，它知道了自己的所有下级，而点i的所有上级也让点i知道了自己的存在
				也就是说点i知道了自己的所有上级和所有下级
				
				这种方法的循环次数肯定是要比我自己的方法要少的，毕竟少了一个反向查找的步骤 
		*/
//		std::cout << std::endl << "Num " << i + 1 << std::flush;
		unsigned char *know = new unsigned char[N](); 
		forwardKnow(i, graph, know, N);
		backwardKnow(i, graph, know, N);
		know[i] = 1;
		for (int j = 0; j < N; ++j)
		{
			if (!know[j])
			{
				--remain;
//				std::cout << std::endl << "Not Full" << std::endl << std::flush;
				break;
			}
		}
		delete[] know;
	}
	std::cout << remain;
	
	for (int i = 0; i < N; ++i)
		delete[] graph[i];
	delete[] graph;
}

void forwardKnow(int i, unsigned char **graph, unsigned char *know, int N)
{
	for (int j = 0; j < N; ++j)
	{
		if (graph[i][j] && !know[j])
		{
//			std::cout << std::endl << "Know " << j + 1 << std::flush;
			++know[j];
			forwardKnow(j, graph, know, N);
		}
	}
}

void backwardKnow(int i, unsigned char **graph, unsigned char *know, int N)
{
	for (int j = 0; j < N; ++j)
	{
		if (graph[j][i] && !know[j])
		{
//			std::cout << std::endl << "Know " << j + 1 << std::flush;
			++know[j];
			backwardKnow(j, graph, know, N);
		}
	}
}

}
