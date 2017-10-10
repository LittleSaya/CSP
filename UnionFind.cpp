#include "UnionFind.h"

myds::UnionFind::UnionFind(int p_nodeN): nodeN(p_nodeN)
{
	int i(0);
	forest = new int[nodeN]();
	for (; i < nodeN; ++i)
		forest[i] = i;
	treeSizes = new int[nodeN]();
	for (i = 0; i < nodeN; ++i)
		treeSizes[i] = 1;
}

myds::UnionFind::~UnionFind()
{
	delete[] forest, treeSizes;
}

int myds::UnionFind::findRoot(int idx)
{
	static int fatherOfIdx;
	// bound check
	if (idx < 0 || idx >= nodeN)
	{
		return -1;
	}
	fatherOfIdx = forest[idx];
	// climb to the root, the value of root is itself
	while (forest[fatherOfIdx] != fatherOfIdx)
	{
		fatherOfIdx = forest[fatherOfIdx];
	}
	// now "fatherOfIdx" is the root of idx
	forest[idx] = fatherOfIdx;
	return fatherOfIdx;
}

bool myds::UnionFind::isConnected(int idx1, int idx2)
{
	static int rootOfIdx1, rootOfIdx2;
	rootOfIdx1 = findRoot(idx1);
	rootOfIdx2 = findRoot(idx2);
	return rootOfIdx1 == rootOfIdx2;
}

bool myds::UnionFind::connect(int idx1, int idx2)
{
	// bound check
	if (idx1 < 0 || idx2 < 0 || idx1 >= nodeN || idx2 >= nodeN)
	{
		return false;
	}
	int rootOfIdx1 = findRoot(idx1);
	int rootOfIdx2 = findRoot(idx2);
	// if they are already connected
	if (rootOfIdx1 == rootOfIdx2)
	{
		return true;
	}
	// the make the "lighter" one as the child tree of the "heavier" one
	// if tree 1 is lighter than tree 2
	if (treeSizes[rootOfIdx1] < treeSizes[rootOfIdx2])
	{
		forest[rootOfIdx1] = rootOfIdx2;
		treeSizes[rootOfIdx2] += treeSizes[rootOfIdx1];
	}
	// if tree 1 is heavier than (or equal with) tree 2
	else
	{
		forest[rootOfIdx2] = rootOfIdx1;
		treeSizes[rootOfIdx1] += treeSizes[rootOfIdx2];
	}
	return true;
}


