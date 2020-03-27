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

struct Query
{
    int l, r, idx, ans;
};

vector<Query> vq;
int block;
int cnt[N];
vector<int> v;
int ans;

bool compare(Query &q1, Query &q2)
{
    if(q1.l / block != q2.l / block)
        return q1.l / block < q2.l / block;
    return q1.r < q2.r;
}

void add(int pos)
{
    if(cnt[v[pos]] == 0)
        ans++;
    cnt[v[pos]]++;
}

void remove(int pos)
{
    if(cnt[v[pos]] == 1)
        ans--;
    cnt[v[pos]]--;
}

void process(int n)
{
    block = sqrt(n);
    sort(vq.begin(), vq.end(), compare);
    int currL = 0, currR = 0;
    ans = 0;
    add(currL);
    for(int i = 0; i < vq.size(); i++)
    {
        while(currL < vq[i].l)
        {
            remove(currL);
            currL++;
        }
        while(currL > vq[i].l)
        {
            currL--;
            add(currL);
        }
        while(currR < vq[i].r)
        {
            currR++;
            add(currR);
        }
        while(currR > vq[i].r)
        {
            remove(currR);
            currR--;
        }
        vq[i].ans = ans;
    }
}

int32_t main()
{
    IOS;
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        v.pb(a);
    }
    int q;
    cin >> q;
    for(int i = 0; i < q; i++)
    {
        int l, r;
        cin >> l >> r;
        l--, r--;
        vq.pb({l, r, i, 0});
    }
    process(n);
    vector<int> ans(q);
    for(auto e: vq)
        ans[e.idx] = e.ans;
    for(auto e: ans)
        cout << e << endl;
    return 0;
}