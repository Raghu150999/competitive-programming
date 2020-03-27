#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
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
int root;

struct LCA
{
    vector<int> euler, depth, segtree, first;
    int n;
    LCA(int n) : n(n)
    {
        depth.resize(n+1);
        first.resize(n+1);
        dfs(root, -1, 0);
        segtree.resize(4*euler.size());
        build(0, euler.size() - 1, 0);
    }
    void dfs(int u, int p, int dis)
    {
        first[u] = euler.size();
        euler.pb(u);
        depth[u] = dis;
        for(int i = 0; i < graph[u].size(); i++)
        {
            int v = graph[u][i];
            if(v == p)
                continue;
            dfs(v, u, dis+1);
            euler.pb(u);
        }
    }
    int build(int ss, int se, int curr)
    {
        if(ss == se)
        {
            segtree[curr] = euler[ss];
            return segtree[curr];
        }
        int mid = (ss + se) / 2;
        int l = build(ss, mid, 2*curr+1);
        int r = build(mid+1, se, 2*curr+2);
        if(depth[l] < depth[r])
            return segtree[curr] = l;
        else
            return segtree[curr] = r;
    }
    int query(int ss, int se, int curr, int qs, int qe)
    {
        if(se < qs || qe < ss)
            return -1;
        if(qs <= ss && se <= qe)
            return segtree[curr];
        int mid = (ss + se) / 2;
        int l = query(ss, mid, 2*curr+1, qs, qe);
        int r = query(mid+1, se, 2*curr+2, qs, qe);
        if(l == -1)
            return r;
        if(r == -1)
            return l;
        if(depth[l] < depth[r])
            return l;
        else
            return r;
    }
    int lca(int a, int b)
    {
        int left = first[a], right = first[b];
        if(left > right)
        {
            int tmp = left;
            left = right;
            right = tmp;
        }
        return query(0, euler.size() - 1, 0, left, right);
    }
};

int32_t main()
{
    IOS;
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int t;
    cin >> t;
    for(int h = 1; h <= t; h++)
    {
        int n;
        cin >> n;
        set<int> s;
        for(int i = 1; i <= n; i++)
            s.insert(i), graph[i].clear();
        for(int i = 1; i <= n; i++)
        {
            int k;
            cin >> k;
            for(int j = 0; j < k; j++)
            {
                int v;
                cin >> v;
                graph[i].pb(v);
                s.erase(v);
            }
        }
        root = *s.begin();
        int q;
        LCA lca(n);
        cin >> q;
        cout << "Case " << h << ":" << endl;
        for(int i = 0; i < q; i++)
        {
            int u, v;
            cin >> u >> v;
            cout << lca.lca(u, v) << endl;
        }
    }
    return 0;
}