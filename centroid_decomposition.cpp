#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>

// Remove GCC optimizer for codechef
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
using namespace __gnu_pbds;

#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define pb push_back
#define endl "\n"
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>

const int INF = 1e12;
const double PI = acos(-1);
const int N = 1e6 + 7;
int mod = 998244353;

vector<int> ctree[N], graph[N];
int sz[N], parent[N];
bool dead[N];

int computeSZ(int u, int p)
{
    sz[u] = 1;
    for(auto v: graph[u])
        if(v != p && !dead[v])
            sz[u] += computeSZ(v, u);
    return sz[u];
}

int getCentroid(int u, int p, int n)
{
    for(auto v: graph[u])
        if(v != p && sz[v] > (n >> 1) && !dead[v])
            return getCentroid(v, u, n);
    return u;
}

int cd(int u)
{
    computeSZ(u, u);
    int c = getCentroid(u, u, sz[u]);
    dead[c] = true;
    for(auto v: graph[c])
    {
        if(!dead[v])
        {
            int r = cd(v);
            ctree[c].pb(r);
            ctree[r].pb(c);
            parent[r] = c;
        }
    }
    return c;
}

int level[N], visited[N];

void bfs(int root)
{
    queue<int> q;
    q.push(root);
    visited[root] = 1;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(auto v: ctree[u])
            if(!visited[v])
            {
                visited[v] = 1;
                level[v] = level[u] + 1;
                q.push(v);
            }
    }
}

int32_t main()
{
    IOS;
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n;
    cin >> n;
    for(int i = 0; i < n-1; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].pb(v);
        graph[v].pb(u);
    }
    int root = cd(1);
    parent[root] = root;
    bfs(root);
    return 0;
}