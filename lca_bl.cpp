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

vector<int> graph[N];

struct LCA
{
    // Number of nodes in the tree
    int n;
    vector<int> first, last, depth;
    vector<vector<int>> up;
    int timer, L;
    LCA(int n): n(n)
    {
        timer = 0;
        up = vector<vector<int>>(n+1, vector<int>(20, 0));
        first.resize(n+1);
        last.resize(n+1);
        depth.resize(n+1);
        L = ceil(log2(n));
        // Important ancestor of root is root
        dfs(1, 1, 0);
    }

    void dfs(int u, int p, int dis)
    {
        first[u] = ++timer;
        depth[u] = dis;
        up[u][0] = p;
        for(int i = 1; i <= L; i++)
            up[u][i] = up[up[u][i-1]][i-1];
        for(auto v: graph[u])
            if(v != p)
                dfs(v, u, dis + 1);
        last[u] = ++timer;
    }

    bool is_ancestor(int u, int v)
    {
        // Returns u is u == v
        return first[u] <= first[v] && last[u] >= last[v];
    }

    int lca(int u, int v)
    {
        if(is_ancestor(u, v))
            return u;
        if(is_ancestor(v, u))
            return v;
        for(int i = L; i >= 0; i--)
        {
            if(!is_ancestor(up[u][i], v))
                u = up[u][i];
        }
        return up[u][0];
    }

    int dis(int u, int v)
    {
        int l = lca(u, v);
        return depth[u] + depth[v] - 2 * depth[l];
    }
};

int32_t main()
{
    IOS;
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    return 0;
}