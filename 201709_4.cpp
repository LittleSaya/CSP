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
	unsigned char **graph = new unsigned char*[N];// �����ڽӾ����ʾ����Ч�ʵ��£�ռ�ÿռ�󣬿�ѭ���ࣩ 
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
			ͬ������������㷨���ҵ�������ÿ���㶼�����˿���
			��ÿһ���㣬�������������ϼ����¼���
				���ȴӵ�i�����������һ��DFS����¼���з��ʹ��ĵ㣨�ҵ������������¼��� 
				Ȼ��ӵ�i�ӷ��������һ��DFS����¼���з��ʹ��ĵ㣨�ҵ������������ϼ��� 
				����ж��ǲ��ǰ�ÿһ���㶼������һ��
				������ǵĻ���--remain
			�����ϵ������ǣ�
				��ÿһ����i�������������һ��DFS���������е��¼�����һ��˫���ϵ
				Ҳ����˵���õ�i֪�������е��¼���Ҳ�õ�i���е��¼�֪����i
				��������ִ�����֮�󣬶Ե�i��˵����֪�����Լ��������¼�������i�������ϼ�Ҳ�õ�i֪�����Լ��Ĵ���
				Ҳ����˵��i֪�����Լ��������ϼ��������¼�
				
				���ַ�����ѭ�������϶���Ҫ�����Լ��ķ���Ҫ�ٵģ��Ͼ�����һ��������ҵĲ��� 
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
