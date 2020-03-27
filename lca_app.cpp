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

vector<pair<int, int>> graph[N];

struct Data
{
    int p, mx, mn;
};

struct LCA
{
    int n, L, timer;
    vector<int> first, last;
    vector<vector<Data>> up;
    LCA(int n) : n(n)
    {
        timer = 0;
        first.resize(n+1);
        last.resize(n+1);
        up = vector<vector<Data>>(n+1, vector<Data>(20));
        L = ceil(log2(n));
        dfs(1, 1, 0);
    }

    void dfs(int u, int p, int w)
    {
        first[u] = ++timer;
        up[u][0].p = p;
        up[u][0].mn = w;
        up[u][0].mx = w;
        for(int i = 1; i <= L; i++)
        {
            up[u][i].p = up[up[u][i-1].p][i-1].p;
            up[u][i].mn = min(up[up[u][i-1].p][i-1].mn, up[u][i-1].mn);
            up[u][i].mx = max(up[up[u][i-1].p][i-1].mx, up[u][i-1].mx);
        }
        for(auto e: graph[u])
            if(e.first != p)
                dfs(e.first, u, e.second);
        last[u] = ++timer;
    }

    bool is_ancestor(int u, int v)
    {
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
            if(!is_ancestor(up[u][i].p, v))
                u = up[u][i].p;
        }
        return up[u][0].p;
    }

    pair<int, int> find_ans(int u, int v)
    {
        int l = lca(u, v);
        int mn = INF;
        int mx = -INF;
        for(int i = L; i >= 0; i--)
        {
            if(!is_ancestor(up[u][i].p, l))
            {
                mn = min(mn, up[u][i].mn);
                mx = max(mx, up[u][i].mx);
                u = up[u][i].p;
            }
        }
        if(u != l)
        {
            mn = min(mn, up[u][0].mn);
            mx = max(mx, up[u][0].mx);
        }
        for(int i = L; i >= 0; i--)
        {
            if(!is_ancestor(up[v][i].p, l))
            {
                mn = min(mn, up[v][i].mn);
                mx = max(mx, up[v][i].mx);
                v = up[v][i].p;
            }
        }
        if(v != l)
        {
            mn = min(mn, up[v][0].mn);
            mx = max(mx, up[v][0].mx);
        }
        return {mn, mx};
    }
};

int32_t main()
{
    IOS;
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n;
    cin >> n;
    for(int i = 0; i < n - 1; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].pb({v, w});
        graph[v].pb({u, w});
    }
    int q;
    LCA lca(n);
    cin >> q;
    for(int i = 0; i < q; i++)
    {
        int u, v;
        cin >> u >> v;
        auto ans = lca.find_ans(u, v);
        cout << ans.first << " " << ans.second << endl;
    }
    return 0;
}