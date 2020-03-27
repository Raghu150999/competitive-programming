#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

// Remove GCC optimizer for codechef
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;
using namespace __gnu_pbds;

#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define mod 1000000007

const int INF = 2e18 + 8;
const double PI = acos(-1);

const int maxn = 1e5 + 7;

int n, curr_pos;
vector<int> graph[maxn];
int depth[maxn], parent[maxn], head[maxn], pos[maxn], arr[maxn], heavy[maxn], sgt[4*maxn];

int dfs(int u) {
    int size = 1, max_size = 0;
    heavy[u] = -1;
    for (int v : graph[u]) {
        if (v != parent[u]) {
            parent[v] = u;
            depth[v] = depth[u] + 1;
            int sub_size = dfs(v);
            if (sub_size > max_size) {
                heavy[u] = v;
                max_size = sub_size;
            }
            size += sub_size;
        }
    }
    return size;
}

void decompose(int u, int h) {
    head[u] = h;
    pos[u] = ++curr_pos;
    if (heavy[u] != -1) {
        decompose(heavy[u], h);
    }
    for (int v : graph[u]) {
        if (v != parent[u] && v != heavy[u]) {
            decompose(v, v);
        }
    }
}

/**
*   Segment tree implementation
*   - using 1 indexing
*   - f = 1|0 (max|min)
*   - default uses max segment tree
*/

// need to pass the array to build
// example: build(arr)
int build(int *arr, int *sgt = sgt, int f = 1, int ss = 1, int se = n, int curr = 1)
{
    if(ss == se)
        return sgt[curr] = arr[ss];
    int mid = (ss + se) >> 1;
    int left = build(arr, sgt, f, ss, mid, (curr << 1));
    int right = build(arr, sgt, f, mid+1, se, (curr << 1)|1);
    int &res = sgt[curr];
    if(f)
        res = max(left, right);
    else
        res = min(left, right);
    return res;
}

// using default args
// call: query(l, r)
int query(int l, int r, int *sgt = sgt, int f = 1, int ss = 1, int se = n, int curr = 1)
{
    if(r < ss || se < l)
    {
        if(f)
            return -INF;
        else
            return INF;
    }
    if(l <= ss && se <= r)
        return sgt[curr];
    int mid = (ss + se) >> 1;
    int left = query(l, r, sgt, f, ss, mid, (curr << 1));
    int right = query(l, r, sgt, f, mid+1, se, (curr << 1)|1);
    int res;
    if(f)
        res = max(left, right);
    else
        res = min(left, right);
    return res;
}


// call: update(pos, val)
int update(int pos, int val, int *sgt = sgt, int f = 1, int ss = 1, int se = n, int curr = 1)
{
    if(pos < ss || se < pos)
        return sgt[curr];
    if(ss == se)
    {
        sgt[curr] = val;
        return sgt[curr];
    }
    int mid = (ss + se) >> 1;
    int left = update(pos, val, sgt, f, ss, mid, (curr << 1));
    int right = update(pos, val, sgt, f, mid+1, se, (curr << 1)|1);
    int &res = sgt[curr];
    if(f)
        res = max(left, right);
    else
        res = min(left, right);
    return res;
}

// Find max edge in path a -> b
int hldquery(int a, int b) {
    int curr_max = 0;
    for(; head[a] != head[b]; b = parent[head[b]]) {
        if (depth[head[a]] > depth[head[b]]) {
            swap(a, b);
        }
        curr_max = max(curr_max, query(pos[head[b]], pos[b]));
    }
    if (depth[a] > depth[b]) {
        swap(a, b);
    }
    // Exclude edge above 'a'
    int l = pos[a] + 1, r = pos[b];
    if (l <= r) {
        curr_max = max(curr_max, query(l, r));
    }
    return curr_max;
}

int32_t main()
{
    IOS;
    // freopen("running_on_fumes_chapter_1_input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            graph[i].clear();
            depth[i] = 0;
            parent[i] = i;
            arr[i] = 0;
        }
        vector<tuple<int, int, int>> edges;
        for (int i = 1; i < n; i++) {
            int u, v, c;
            cin >> u >> v >> c;
            graph[u].push_back(v);
            graph[v].push_back(u);
            edges.push_back({u, v, c});
        }
        dfs(1);
        curr_pos = 0;
        decompose(1, 1);
        for (auto &edge : edges) {
            int u = get<0>(edge), v = get<1>(edge), c = get<2>(edge);
            if (depth[u] < depth[v]) {
                swap(u, v);
            }
            arr[pos[u]] = c;
        }
        build(arr);
        string s;
        while (true) {
            cin >> s;
            if (s == "DONE") break;
            if (s == "QUERY") {
                int a, b;
                cin >> a >> b;
                cout << hldquery(a, b) << endl;
            } else {
                int i, ti;
                cin >> i >> ti;
                i--;
                int u = get<0>(edges[i]), v = get<1>(edges[i]);
                if (depth[u] < depth[v])
                    swap(u, v);
                update(pos[u], ti);
            }
        }
    }
    return 0;
}