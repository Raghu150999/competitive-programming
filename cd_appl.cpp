#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
 
// Remove GCC optimizer for codechef
// #pragma comment(linker, "/stack:200000000")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
 
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
const int maxn = 5e4 + 11;
 
vector<int> graph[maxn];
int sz[maxn];
bool dead[maxn];
int cnt[20][maxn];

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

void dfs_update(int u, int p, int dis, int lvl, int add)
{
    cnt[lvl][dis] += add;
    for(auto v: graph[u])
        if(v != p && !dead[v])
            dfs_update(v, u, dis+1, lvl, add);
}

int ans, k;

int dfs_get(int u, int p, int dis, int lvl)
{
    int res = 0;
    if(dis <= k)
        res += cnt[lvl][k-dis];
    else
        return res;
    for(auto v: graph[u])
        if(v != p && !dead[v])
            res += dfs_get(v, u, dis+1, lvl);
    return res;
}


int cd(int u, int lvl)
{
    computeSZ(u, u);
    int c = getCentroid(u, u, sz[u]);
    dfs_update(c, c, 0, lvl, 1);
    cnt[lvl][0]++;
    dead[c] = true;
    int sum = 0;
    for(auto v: graph[c])
    {
        if(!dead[v])
        {
            dfs_update(v, c, 1, lvl, -1);
            sum += dfs_get(v, c, 1, lvl);
            dfs_update(v, c, 1, lvl, 1);
        }
    }
    assert(sum % 2 == 0);
    ans += sum / 2;
    for(auto v: graph[c])
        if(!dead[v])
            cd(v, lvl + 1);
    for(int i = 0; i < maxn && cnt[lvl][i]; i++)
        cnt[lvl][i] = 0;
    return c;
}

int32_t main()
{
    IOS;
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
 
    int n, m;
    cin >> n >> k;
    for(int i = 0; i < n-1; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].pb(v);
        graph[v].pb(u);
    }
    cd(1, 0);
    cout << ans << endl;
    return 0;
}