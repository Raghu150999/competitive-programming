#include <bits/stdc++.h>

using namespace std;

#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define pb push_back
#define endl "\n"

const int INF = 1e9;
int mod = 1e9 + 7;

const int maxn = 1e5 + 7;

/**
*   START HERE
*/

/**
*   Segment tree implementation
*   - using 1 indexing
*   - f = 1|0 (max|min)
*   - default uses max segment tree
*/

// Define n for segment tree here
int n;
int sgt[4*maxn], arr[maxn];

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


/**
*   ENDS HERE
*/

int32_t main()
{
    IOS;
    
    // sample segment tree usage
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> arr[i];
    build(arr);
    int q;
    cin >> q;
    for(int i = 1; i <= q; i++)
    {
        int l, r;
        cin >> l >> r;
        // print max in [l, r]
        cout << query(l, r) << endl;
    }
    update(n, 6);
    cout << query(n-1, n) << endl;
    return 0;
}
