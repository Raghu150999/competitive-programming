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

struct Matrix
{
    int n;
    vector<vector<int>> mat;
    Matrix(int n): n(n)
    {
        mat = vector<vector<int>>(n, vector<int>(n, 0));
    }
    Matrix operator*(const Matrix &m) const
    {
        Matrix res(n);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                for(int k = 0; k < n; k++)
                {
                    res.mat[i][j] += mat[i][k] * m.mat[k][j];
                    res.mat[i][j] %= mod;
                }
        return res;
    }
};

Matrix matexpo(Matrix &b, int p, int n)
{
    Matrix res(n);
    for(int i = 0; i < n; i++)
        res.mat[i][i] = 1;
    while(p)
    {
        if(p & 1)
            res = res * b;
        b = b * b;
        p >>= 1;
    }
    return res;
}

int32_t main()
{
    IOS;
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    
    return 0;
}