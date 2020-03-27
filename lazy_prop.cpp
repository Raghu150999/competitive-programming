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

const int INF = 1e16;
const double PI = acos(-1);
const int N = 1e6 + 7;
int mod = 1e9 + 7;

const int maxn = 2e4 + 7;
int mat[57][maxn], dp[57][maxn];
int sgt[4*maxn], lazy[4*maxn];

int build(int ss, int se, int curr, int *arr)
{
    lazy[curr] = 0;
    if(ss == se)
        return sgt[curr] = arr[ss];
    int mid = (ss + se) >> 1;
    int left = build(ss, mid, (curr << 1), arr);
    int right = build(mid+1, se, (curr << 1)|1, arr);
    return sgt[curr] = max(left, right);
}

int query(int ss, int se, int curr, int l, int r)
{
    if(r < ss || se < l)
        return -INF;
    if(l <= ss && se <= r)
        return sgt[curr];
    int mid = (ss + se) >> 1;
    int left = query(ss, mid, (curr << 1), l, r);
    int right = query(mid+1, se, (curr << 1)|1, l, r);
    return sgt[curr] = max(left, right);
}

int update(int ss, int se, int curr, int l, int r, int val)
{
    if(lazy[curr])
    {
        sgt[curr] += lazy[curr];
        if(ss != se)
        {
            lazy[(curr << 1)] += lazy[curr];
            lazy[(curr << 1)|1] += lazy[curr];
        }
        lazy[curr] = 0;
    }
    if(r < ss || se < l)
        return sgt[curr];
    if(l <= ss && se <= r)
    {
        sgt[curr] += val;
        if(ss != se)
        {
            lazy[(curr << 1)] += val;
            lazy[(curr << 1)|1] += val;
        }
        return sgt[curr];
    }
    int mid = (ss + se) >> 1;
    int left = update(ss, mid, (curr << 1), l, r, val);
    int right = update(mid+1, se, (curr << 1)|1, l, r, val);
    return sgt[curr] = max(left, right);
}

int32_t main()
{
    IOS;
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    
    int n, m, k;
    cin >> n >> m >> k;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            cin >> mat[i][j];
    int l = m - k + 1, sum = 0;
    for(int i = 1; i <= m; i++)
    {
        if(i <= k)
            sum += mat[1][i] + mat[2][i];
        else
        {
            dp[1][i-k] = sum;
            sum += mat[1][i] + mat[2][i];
            sum -= mat[1][i-k] + mat[2][i-k];
        }
    }
    dp[1][l] = sum;
    for(int i = 2; i <= n; i++)
    {
        build(1, l, 1, dp[i-1]);
        sum = 0;
        int ws = 0;
        for(int j = 1; j <= k; j++)
        {
            sum += mat[i][j];
            ws += mat[i][j];
            ws += mat[i+1][j];
        }
        for(int j = 1; j <= k; j++)
        {
            update(1, l, 1, j, j, -sum);
            sum -= mat[i][j];
        }
        for(int j = k; j <= m;)
        {
            dp[i][j-k+1] = sgt[1] + ws;
            j++;
            if(j > m)
                break;
            int start = max(1LL, j-2*k+1), end = j-k;
            update(1, l, 1, start, end, mat[i][j-k]);
            start = j - k + 1, end = min(j, l);
            update(1, l, 1, start, end, -mat[i][j]);
            ws -= (mat[i][j-k] + mat[i+1][j-k]);
            ws += (mat[i][j] + mat[i+1][j]);
        }
    }
    int mx = 0;
    for(int i = 1; i <= l; i++)
        mx = max(mx, dp[n][i]);
    cout << mx << endl;
    return 0;
}
