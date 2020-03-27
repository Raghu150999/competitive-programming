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

const int INF = 1e18 + 8;
const double PI = acos(-1);
const int N = 1e6 + 7;
int mod = 1e9 + 7;

vector<pair<int, int>> graph[N];

int dis[N];
bool vis[N];

void bfs01(int root)
{
    deque<int> d;
    d.push_front(root);
    vis[root] = 1;
    while(!d.empty())
    {
        int u = d.front();
        d.pop_front();

        for(auto &p: graph[u])
        {
            if(vis[p.first])
                continue;
            // 0 edge
            if(p.second == 0)
            {
                d.push_front(p.first);
                dis[p.first] = dis[u];
            }
            else
            // 1 edge
            {
                d.push_back(p.first);
                dis[p.first] = dis[u] + 1;
            }
            vis[p.first] = 1;
        }
    }
}

int32_t main()
{
    IOS;
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    

    return 0;
}