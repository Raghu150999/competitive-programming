#include <bits/stdc++.h>
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define pb push_back
#define endl "\n"
#define long long long

const long INF = 1e18;
const double PI = acos(-1);
int mod = 1e9 + 7;

struct DP
{
	int up, left, ans;
};
const int MAXN = 2001;
int mr[MAXN][MAXN], mc[MAXN][MAXN];
int cr[MAXN], cc[MAXN], rt[MAXN], ct[MAXN];
DP dp[MAXN][MAXN];
string mat[MAXN];

inline void fastmod(int &a)
{
	if(a >= mod)
		a -= mod;
}

int32_t main()
{
	IOS
	freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
	
	int n, m;
	cin >> n >> m;
	
	for(int i = 0; i < n; i++)
	{
		cin >> mat[i];
		int cnt = 0;
		for(int j = m-1; j >= 0; j--)
		{
			if(mat[i][j] == 'R')
				cnt++;
		}
		cr[i+1] = cnt;
	}
	for(int j = 0; j < m; j++)
	{
		int cnt = 0;
		for(int i = n-1; i >= 0; i--)
		{
			if(mat[i][j] == 'R')
				cnt++;
		}
		cc[j+1] = cnt;
	}
	
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			int rd = m - j + 1;
			int v1 = mr[i][rd];
			int cd = n - i + 1;
			int v2 = mc[j][cd];
			dp[i][j].up = dp[i-1][j].ans - v2 + mod;
			dp[i][j].left = dp[i][j-1].ans - v1 + mod;
			fastmod(dp[i][j].up);
			fastmod(dp[i][j].left);
			dp[i][j].ans = dp[i][j].up + dp[i][j].left;
			fastmod(dp[i][j].ans);
			if(i == 1 && j == 1)
				dp[i][j] = {1, 1, 1};
			if(mat[i-1][j-1] == 'R')
				rt[i]++, ct[j]++;
			mr[i][cr[i]-rt[i]] += dp[i][j].up;
			fastmod(mr[i][cr[i]-rt[i]]);
			mc[j][cc[j]-ct[j]] += dp[i][j].left;
			fastmod(mc[j][cc[j]-ct[j]]);
		}
	}
	cout << dp[n][m].ans << endl;
	return 0;
}

