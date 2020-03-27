#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 5;

// {dest, weight} in graph
void djikstras(int n, int dist[], int src, vector<pair<int, int>> graph[], vector<int> &path)
{
    set<pair<int, int>> spt;
    vector<int> inSet(n + 1, 0);
    for (int i = 1; i <= n; i++)
        dist[i] = INF;
    spt.insert({0, src});
    dist[src] = 0;
    path[src] = src;
    while (!spt.empty())
    {
        auto p = *spt.begin();
        int u = p.second;
        inSet[u] = 1;
        spt.erase({dist[u], u});
        for (int i = 0; i < graph[u].size(); i++)
        {
            int v = graph[u][i].first, w = graph[u][i].second;
            if (inSet[v])
                continue;
            if (dist[v] == INF)
            {
                dist[v] = dist[u] + w;
                spt.insert({dist[v], v});
                path[v] = u;
            }
            else if (dist[v] > dist[u] + w)
            {
                spt.erase({dist[v], v});
                dist[v] = dist[u] + w;
                spt.insert({dist[v], v});
                path[v] = u;
            }
        }
    }
}

int main()
{
    vector<pair<int, int>> graph[4];
    graph[1].push_back({2, 3});
    graph[2].push_back({1, 3});

    graph[1].push_back({3, 15});
    graph[3].push_back({1, 15});

    graph[2].push_back({3, 2});
    graph[3].push_back({2, 2});

    vector<int> path(4);
    int dist[4];
    djikstras(3, dist, 1, graph, path);
    return 0;
}