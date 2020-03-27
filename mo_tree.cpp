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

int block;
struct Query
{
    int l, r, idx, lc, flc;
    bool operator<(const Query &q) const
    {
        if(l / block != q.l / block)
            return l / block < q.l / block;
        return r < q.r;
    }
};

vector<int> graph[N];
vector<Query> vq;
vector<int> tour, val, ans;
vector<bool> vis;
int cnt[N];

struct LCA
{
    // Number of nodes in the tree
    int n;
    vector<int> first, last;
    vector<vector<int>> up;
    int timer, L;
    LCA(int n): n(n)
    {
        timer = 0;
        up = vector<vector<int>>(n+1, vector<int>(20, 0));
        first.resize(n+1);
        last.resize(n+1);
        L = ceil(log2(n));
        // Important ancestor of root is root
        dfs(1, 1);
    }

    void dfs(int u, int p)
    {
        first[u] = ++timer;
        tour.pb(u);
        up[u][0] = p;
        for(int i = 1; i <= L; i++)
            up[u][i] = up[up[u][i-1]][i-1];
        for(auto v: graph[u])
            if(v != p)
                dfs(v, u);
        last[u] = ++timer;
        tour.pb(u);
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
};

void check(int pos, int &res)
{
    int v = tour[pos];
    if(vis[v] && --cnt[val[v]] == 0)
        res--;
    else
    if(!vis[v] && cnt[val[v]]++ == 0)
        res++;
    vis[v] = !vis[v];
}

void process(int n)
{
    block = sqrt(n);
    sort(vq.begin(), vq.end());
    int curL = 0, curR = 0, res = 0;
    check(curL, res);
    for(auto e: vq)
    {
        while(curL < e.l)
        {
            check(curL, res);
            curL++;
        }
        while(curL > e.l)
        {
            curL--;
            check(curL, res);
        }
        while(curR < e.r)
        {
            curR++;
            check(curR, res);
        }
        while(curR > e.r)
        {
            check(curR, res);
            curR--;
        }
        int u = tour[curL];
        if(e.lc != u)
            check(e.flc, res);
        ans[e.idx] = res;
        if(e.lc != u)
            check(e.flc, res);
    }
}

int32_t main()
{
    IOS;
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n >> m;
    val.resize(n+1);
    vector<pair<int, int>> vp(n+1);
    vp[0].first = -1;
    for(int i = 1; i <= n; i++)
    {
        cin >> vp[i].first;
        vp[i].second = i;
    }
    sort(vp.begin() + 1, vp.end());
    int cnt = 0;
    for(int i = 1; i <= n; i++)
    {
        if(vp[i].first != vp[i-1].first)
            cnt++;
        val[vp[i].second] = cnt;
    }
    for(int i = 0; i < n-1; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].pb(v);
        graph[v].pb(u);
    }
    tour.pb(0);
    LCA lca(n);
    ans.resize(m);
    for(int i = 0; i < m; i++)
    {
        int u, v;
        Query q;
        cin >> u >> v;
        int lc = lca.lca(u, v);
        if(lca.first[u] > lca.first[v])
        {
            int tmp = u;
            u = v;
            v = tmp;
        }
        q.idx = i;
        q.lc = lc;
        q.flc = lca.first[lc];
        // Case 1
        if(u == lc)
            q.l = lca.first[u], q.r = lca.first[v];
        else
            q.l = lca.last[u], q.r = lca.first[v];
        vq.pb(q);
    }
    vis.resize(n+1);
    process(n);
    for(auto e: ans)
        cout << e << endl;
    return 0;
}