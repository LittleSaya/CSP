#include "csptest.h"
#include <vector>
#include <iostream>

namespace Q201709_4_o1
{

/*
	�ο���http://blog.csdn.net/gl486546/article/details/78232690?locationNum=5&fps=1
	
	����˼·��
	һ��ʹ���ڽӱ�������ڽӾ���������������������ڽӾ���ռ�õĿռ����ڽӱ��100����ͬʱ�����Ŀ�ѭ���������ٶ� 
	��������ÿһ���㣬��ÿһ���㰴���������һ��DFS������������к����������¼�����һ��˫��Ĺ�ϵ
		Ҳ����˵��ÿһ���㣬��֪�����������¼������������¼�Ҳ��֪����
		�����еĵ㶼�������֮��ÿһ���㶼֪�����������ϼ��������¼� 
*/ 
typedef unsigned short US;
typedef unsigned char UC;

std::vector<US> *graph;// �ڽӾ��� 
UC **isKnow;// �洢˫���ϵ�ı�� 
US N, M;

void dfsSolve(US ori, US cur, UC *visited);

void f_201709_4_o1()
{
	std::cin >> N >> M;
	graph = new std::vector<US>[N];// �ڽӱ� 
	isKnow = new UC*[N];// ˫���ϵ 
	for (US i = 0; i < N; ++i)
		isKnow[i] = new UC[N]();
	for (US i = 0, a = 0, b = 0; i < M; ++i)
	{
		std::cin >> a >> b;
		graph[a - 1].push_back(b - 1);
	}
	
	US remain = N;// ���������ĵ������ 
	for (US i = 0; i < N; ++i)
	{
		UC *visited = new UC[N]();// ���ﲻ����isKnow��״̬������visited����Ϊ���ܱ�֤������ֻ�״�ṹ 
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
