#include <bits/stdc++.h>
using namespace std;

void toposort(int u, stack<int>& st, vector<int> graph[], vector<int>& visited)
{
	visited[u] = 1;
	for(int i = 0; i < graph[u].size(); i++)
	{
		int dest = graph[u][i];
		if(visited[dest])
			continue;
		toposort(dest, st, graph, visited);
	}
	st.push(u);
}

int isAcyclic(int u, vector<int> graph[], vector<int>& visited, vector<int>& inStack)
{
	visited[u] = 1;
	inStack[u] = 1;
	for(int i = 0; i < graph[u].size(); i++)
	{
		int dest = graph[u][i];
		if(inStack[dest])
			return 0;
		if(visited[dest])
			continue;
		if(!isAcyclic(dest, graph, visited, inStack))
			return 0;
	}
	inStack[u] = 0;
	return 1;
}

int main()
{
	int n, m;
	cin >> n >> m;
	vector<int> graph[n+1], visited(n+1, 0), inStack(n+1, 0);
	for(int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
	}
	for(int i = 1; i <= n; i++)
		if(graph[i].size())
			sort(graph[i].begin(), graph[i].end(), greater<int>());
	int acyclic = 1;
	for(int i = 1; i <= n; i++)
	{
		if(visited[i])
			continue;
		acyclic &= isAcyclic(i, graph, visited, inStack);
	}
	if(!acyclic)
		return cout<<"Sandro fails.", 0;
	for(int i = 1; i <= n; i++)
		visited[i] = 0;
	stack<int> st;
	for(int i = n; i >= 1; i--)
	{
		if(visited[i])
			continue;
		toposort(i, st, graph, visited);
	}
	while(!st.empty())
	{
		cout<<st.top()<<" ";
		st.pop();
	}
	return 0;
}