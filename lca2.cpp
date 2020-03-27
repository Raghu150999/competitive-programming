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
 
const int INF = 2e9;
const double PI = acos(-1);
const int N = 1e6 + 7;
int mod = 998244353;

vector<int> graph[N];
int dp[N][21], depth[N], timer, first[N], last[N];

void dfs(int u)
{
    first[u] = ++timer;
    for(int &v: graph[u])
        dfs(v);
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
    for(int i = 20; i >= 0; i--)
        if(!is_ancestor(dp[u][i], v))
            u = dp[u][i];
    return dp[u][0];
}

int lca2(int u, int v)
{
    if(depth[u] < depth[v])
        swap(u, v);
    for(int i = 20; i >= 0; i--)
        if(depth[u] - (1 << i) >= depth[v])
            u = dp[u][i];
    // Case when v is an ancestor of u
    if(u == v)
        return u;
    // Now u and v are at same depth, so we can binary lift both u and v
    // simultaneously
    for(int i = 20; i >= 0; i--)
        if(dp[u][i] != dp[v][i])
            u = dp[u][i], v = dp[v][i];
    assert(dp[u][0] == dp[v][0]);
    return dp[u][0];
}

int32_t main()
{
    IOS;
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n, q, u;
    cin >> q;
    for(int i = 2; i <= 4; i++)
        graph[1].pb(i), depth[i] = 1;
    n = 4;
    vector<int> vq;
    for(int i = 1; i <= q; i++)
    {
        cin >> u;
        graph[u].pb(n+1);
        graph[u].pb(n+2);
        n += 2;
        vq.pb(u);
    }
    dfs(1);
    for(int i = 1; i <= 4; i++)
        for(int j = 0; j <= 20; j++)
            dp[i][j] = 1;
    int l = 2, r = 3;
    n = 4;
    int diameter = 2;
    for(int i = 0; i < q; i++)
    {
        int u = vq[i], a = n + 1, b = n + 2;
        n += 2;
        dp[a][0] = u, dp[b][0] = u;
        depth[a] = depth[u] + 1, depth[b] = depth[u] + 1;
        for(int i = 1; i <= 20; i++)
        {
            dp[a][i] = dp[dp[a][i-1]][i-1];
            dp[b][i] = dp[dp[b][i-1]][i-1];
        }
        int l1 = lca(a, l), l2 = lca(a, r);
        int d1 = depth[a] + depth[l] - 2 * depth[l1];
        int d2 = depth[a] + depth[r] - 2 * depth[l2];
        if(diameter < max(d1, d2))
        {
            if(d2 > d1)
                swap(d1, d2), swap(l, r);
            r = a;
            diameter = d1;
        }
        cout << diameter << endl;
    }
    return 0;
}