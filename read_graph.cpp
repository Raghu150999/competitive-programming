#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e6;

void dfs(int u, vector<bool> &vis, vector<int> *graph)
{
	vis[u] = 1;
	for(int &v: graph[u])
		if(!vis[v])
			dfs(v, vis, graph);
}


int main()
{
	int n, m;
	cin >> n >> m;
	vector<int> graph[n+2], grapht[n+2];
	vector<bool> vis(n+2, 0);
	for(int i = 0; i < n; i++)
	{
		int u, v;
		cin >> u >> v;
		u++, v++;
		graph[u].push_back(v);
		grapht[v].push_back(u);
	}
	dfs(1, vis, graph);
	cout << "OK" << endl;
	return 0;
}