#include <bits/stdc++.h>

using namespace std;

#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define ll long long
#define pb push_back
#define endl "\n"

const ll N = 1e6 + 7;
const ll mod = 998244353;

vector<ll> subset;

int32_t main()
{
	
	IOS

	ll n, a, s;
	vector<ll> v;
	cin>>n>>s;
	for(int i=0;i<n;i++)
	{
		cin>>a;
		v.pb(a);
	}
	int nby2 = n / 2;
	ll ans = -1;
	for(ll i=0;i<(1LL << nby2);i++)
	{
		ll sum = 0;
		for(int j=0;j<nby2;j++)
		{
			if(i & (1LL << j))
				sum += v[j];
		}
		subset.pb(sum);
		if(sum <= s)
			ans = max(ans, sum);
	}
	sort(subset.begin(), subset.end());
	int nrest = n - nby2;
	for(ll i=0;i<(1LL << nrest);i++)
	{
		ll mask = (i << nby2);
		ll sum = 0;
		for(int j=nby2;j<n;j++)
			if(mask & (1LL << j))
				sum += v[j];
		if(sum > s)
			continue;
		ll diff = s - sum;
		int idx = upper_bound(subset.begin(), subset.end(), diff) - subset.begin();
		idx--;
		ans = max(ans, subset[idx] + sum);
	}
	cout<<ans<<endl;
	return 0;
}