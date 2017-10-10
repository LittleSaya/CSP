#ifndef _UNIONFIND_H_
#define _UNIONFIND_H_

namespace myds
{
	class UnionFind
	{
	private:
		int *forest;
		int *treeSizes;
		int nodeN;// how many nodes
	public:
		// build a forest with "p_nodeN" trees, every tree only has 1 node
		// so every node is root node, and the value of the node is the index of themself
		// "treeSizes" records the size of each tree it has the same size as "forest"
		UnionFind(int p_nodeN);

		// free the resources
		~UnionFind();

		// give the index of the target node, return the index of the root node of the target node
		// while running, this function will optimize the structure of the forest
		// return a negative value when fail
		int findRoot(int idx);

		// give the indice of 2 nodes, return whether they are connected
		// return true if they are connected, otherwise return false
		bool isConnected(int idx1, int idx2);

		// give the indice of 2 nodes, make them connected if they are not connected
		// return true if they are successfully connected with each other, otherwise return false
		bool connect(int idx1, int idx2);
	};
}

#endif
