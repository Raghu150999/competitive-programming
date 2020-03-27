#include <bits/stdc++.h>

using namespace std;

struct DSU
{
	vector<int> parent;
	int n;
	DSU(int n) : n(n)
	{
		parent.resize(n+1);
		for(int i = 0; i <= n; i++)
			parent[i] = i;
	}

	int getParent(int x)
	{
		if(x == parent[x])
			return x;
		return parent[x] = getParent(parent[x]);
	}

	int merge(int u, int v)
	{
		int pu = getParent(u), pv = getParent(v);
		if(pu == pv)
			return 0;
		parent[pv] = pu;
		return 1;
	}
};