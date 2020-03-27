#include <bits/stdc++.h>
using namespace std;

struct Edge
{
	int u, v, w, idx;
	bool operator<(const Edge& e) const
	{
		return w < e.w;
	}
};

struct DSU
{
	vector<int> parent;
	int n; // No of individual sets
	DSU(int n) : n(n)
	{
		parent.resize(n+1);
		for(int i = 1; i <= n; i++)
			parent[i] = i;
	}
	int getSet(int u)
	{
		return parent[u] = (u == parent[u] ? u : getSet(parent[u]));
	}
	void merge(int u, int v)
	{
		int su = getSet(u), sv = getSet(v);
		parent[sv] = su;
	}
};

int main()
{
	// TODO using tarjan's bridge detection algorithm
	int n, m;
	cin >> n >> m;
	vector<Edge> edges;
	vector<int> ans(m+1, 0);
	map<int, int> freqWeights;
	for(int i = 0; i < m; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		edges.push_back({u, v, w, i});
		freqWeights[w]++;
	}
	sort(edges.begin(), edges.end());
	edges.push_back({0, 0, 0}); // Dummy node for loop termination
	DSU dsu(n);
	Edge prev = edges[0];
	int prevIdx = 0;
	for(int i = 0; i <= m; i++)
	{
		if(prev.w == edges[i].w)
		{
			int u = edges[i].u, v = edges[i].v;
			if(dsu.getSet(u) != dsu.getSet(v)) // Doesn't form a cycle
				ans[edges[i].idx] = 1;
		}
		else
		{
			int count = 0;
			for(int j = prevIdx; j < i; j++)
			{
				int u = edges[j].u, v = edges[j].v;
				if(dsu.getSet(u) != dsu.getSet(v))
				{
					count++;
					dsu.merge(u, v);
				}
			}
			if(count == i - prevIdx)
			{
				for(int j = prevIdx; j < i; j++)
					ans[edges[j].idx] = 2;
			}
			prevIdx = i;
			prev = edges[i];
			i--;
		}
	}
	map<int, string> printAns;
	printAns[0] = "none";
	printAns[1] = "at least one";
	printAns[2] = "any";
	for(int i = 0; i < m; i++)
		cout<<printAns[ans[i]]<<endl;
	return 0;
}