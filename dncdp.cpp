#include <bits/stdc++.h>

using namespace std;

#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define ll long long
#define pb push_back
#define endl "\n"

const ll N = 1e6 + 7;
const double PI = acos(-1);
ll mod = 1e9 + 7;

const int maxn = 4002;
const int INF = 1e9 + 7;

int arr[maxn][maxn], pref[maxn][maxn], dp[maxn][maxn], c[maxn][maxn];

void compute(int idx, int l, int r, int optl, int optr)
{
	if(l > r)
		return;
	int mid = (l + r) >> 1;
	pair<int, int> best = {INF, -1};
	for(int k=optl;k<=min(mid-1, optr);k++)
		best = min(best, {dp[k][idx-1] + c[k+1][mid], k});
	dp[mid][idx] = best.first;
	int opt = best.second;
	compute(idx, l, mid - 1, optl, opt);
	compute(idx, mid + 1, r, opt, optr);
}

int32_t main()
{
	
	// IOS
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
	
	ll n, k;
	cin>>n>>k;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			char ch='#';	// Fast IO
			while(!isdigit(ch))
				ch=getchar();
			arr[i][j]=ch-'0';
			pref[i][j] = (j > 0 ? pref[i][j-1] : 0) + arr[i][j];
		}
	}
	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++)
			c[i][j] = c[i][j-1] + pref[j][j] - (i > 0 ? pref[j][i-1] : 0);
	for(int i=0;i<n;i++)
		dp[i][1] = c[0][i];
	for(int j=2;j<=k;j++)
		compute(j, 0, n-1, 0, n-2);
	cout<<dp[n-1][k]<<endl;
	return 0;
}	