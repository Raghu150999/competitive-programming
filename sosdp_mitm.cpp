#include <bits/stdc++.h>

using namespace std;

#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define ll long long
#define pb push_back
#define endl "\n"

const ll N = 1e6 + 7;
const ll mod = 998244353;

const int maxn = 2e6 + 2;

map<ll, ll> mp[42];

ll graph[42], n;
ll b[maxn], f[maxn];

void primeFactorize(ll a, ll idx)
{
	for(int i=2;i*i<=a;i++)
	{
		while(a % i == 0)
		{
			a /= i;
			mp[idx][i]++;
		}
	}
	if(a != 1)
		mp[idx][a]++;
}

int isClique(ll mask)
{
	for(int i=0;i<n;i++)
		if((mask & (1LL << i)) && ((mask & graph[i]) != mask))
			return 0;
	return 1;
}

int32_t main()
{
	
	IOS

	ll t;
	cin>>t;
	while(t--)
	{
		ll a;
		cin>>n;
		for(int i=0;i<n;i++)
			mp[i].clear();
		for(int i=0;i<n;i++)
		{
			cin>>a;
			primeFactorize(a, i);
		}
		for(int i=0;i<n;i++)
			graph[i] = (1LL << i);
		
		// Constructing graph
		for(int i=0;i<n;i++)
		{
			for(int j=i+1;j<n;j++)
			{
				int flag = 0;
				for(auto it: mp[i])
				{
					if(it.second + mp[j][it.first] > 2)
					{
						flag = 1;
						break;
					}
				}
				if(!flag)
				{
					for(auto it: mp[j])
					{
						if(it.second > 2)
						{
							flag = 1;
							break;
						}
					}
				}
				if(!flag)
				{
					graph[i] |= (1LL << j);
					graph[j] |= (1LL << i);
				}
			}
		}
		int nby2 = n / 2;
		for(ll i=0;i<(1LL << nby2);i++)
		{
			b[i] = isClique(i);
			f[i] = b[i];
		}
		
		// SOS dp
		for(int i = 0;i < nby2; ++i) 
			for(ll mask = 0; mask < (1LL << nby2); ++mask)
				if(mask & (1<<i))
					f[mask] += f[mask^(1<<i)];

		int nrest = n - nby2;
		ll ans = 0;
		for(ll i=0;i<(1LL << nrest);i++)
		{
			ll mask = (i << nby2);
			ll res = (1LL << nby2) - 1;
			int flag = 0;
			if(!isClique(mask))
				continue;
			for(int j=nby2;j<n;j++)
				if(mask & (1LL << j))
					res &= graph[j];
			ans += f[res];
		}
		cout<<ans<<endl;
	}

	return 0;
}