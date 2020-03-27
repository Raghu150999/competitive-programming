#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>

// Remove GCC optimizer for codechef
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;
using namespace __gnu_pbds;

#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define pb push_back
#define endl "\n"
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define mod 998244353

const int INF = 2e18 + 8;
const double PI = acos(-1);

const int maxn = 2e5 + 7;
vector<int> graph[maxn], graphr[maxn], cgraph[maxn];
int parent[maxn], vis[maxn];
stack<int> order;
int leader = -1;

void toposort(int u) {
    vis[u] = 1;
    for (int v : graph[u]) {
        if (vis[v]) continue;
        toposort(v);
    }
    order.push(u);
}

void dfs(int u) {
    parent[u] = leader;
    vis[u] = 1;
    for (int v : graphr[u]) {
        if (vis[v]) continue;
        dfs(v);
    }
}

int32_t main()
{
    IOS;
    // freopen("running_on_fumes_chapter_1_input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graphr[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            toposort(i);
        }
    }
    for (int i = 1; i <= n; i++) {
        vis[i] = 0;
    }
    while (!order.empty()) {
        int u = order.top();
        order.pop();
        if (vis[u]) continue;
        leader = u;
        dfs(u);
    }
    for (int i = 1; i <= n; i++) {
        for (int v : graph[i]) {
            if (parent[i] != parent[v]) {
                cgraph[parent[i]].push_back(parent[v]);
            }
        }
    }
    return 0;
}
