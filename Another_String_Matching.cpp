#include <bits/stdc++.h>

using namespace std;

#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define ll long long
#define pb push_back
#define endl "\n"

const ll N = 1e6 + 7;
const double PI = acos(-1);
ll mod = 1e9 + 7;

typedef complex<long double> cd;

vector<ll> res(N, 0);

void fft(vector<cd> &a, ll n, bool invert)
{
	for(int i=1, j=0;i<n;i++)
	{
		int bit = n >> 1;
		for(; j & bit; bit >>= 1)
			j ^= bit;
		j ^= bit;
		if(i < j && j < n)
		{
			cd tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
		}
	}

	for(int len=2;len<=n;len <<= 1)
	{
		long double ang = (2 * PI / len) * (invert ? -1 : 1);
		cd wlen(cos(ang), sin(ang));
		for(int i=0;i<n;i+=len)
		{
			cd w(1);
			for(int j=0;j<len/2;j++)
			{
				cd u = a[i+j], v = a[i+j+len/2] * w;
				a[i+j] = u + v;
				a[i+j+len/2] = u - v;
				w *= wlen;
			}
		}
	}
	if(invert)
	{
		for(int i=0;i<n;i++)
			a[i] /= n;
	}
}

vector<cd> p1(N, 0), p2(N, 0);

void multiply(vector<ll> &f1, ll sz1, vector<ll> &f2, ll sz2, vector<ll> &res)
{
	ll n = 1;
	for(int i=0;i<sz1;i++)
		p1[i] = f1[i];
	for(int i=0;i<sz2;i++)
		p2[i] = f2[i];
	while(n < sz1 + sz2)
		n <<= 1;
	for(int i=sz1;i<n;i++)
		p1[i] = 0;
	for(int i=sz2;i<n;i++)
		p2[i] = 0;
	fft(p1, n, false);
	fft(p2, n, false);
	for(int i=0;i<n;i++)
		p1[i] *= p2[i];
	fft(p1, n, true);
	int deg = sz1 - 1 + sz2;
	for(int i=0;i<deg;i++)
		res[i] = (ll)round(p1[i].real()); // use mod here if needed
	for(int i=deg;i<n;i++)
		res[i] = 0;
}

vector<ll> v1(N, 0), v2(N, 0), ans(N, 0);

int32_t main()
{
    
    IOS
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    
    string str;
    cin>>str;
    ll n = str.size();
    for(int j=0;j<26;j++)
    {	
    	char ch = 'a' + j;
    	for(int i=n-1;i>=0;i--)
    		v1[n-1-i] = str[i] == ch ? 1 : 0;
	    for(int i=0;i<n;i++)
	    	v2[i] = str[i] == ch ? 1 : 0;
	    multiply(v1, n, v2, n, v2);
	    for(int i=n;i<=2*n-2;i++)
	    	ans[i-n+1] += v2[i];
    }
    ll mx = -1;
    for(int i=1;i<n;i++)
    	mx = max(mx, ans[i]);
    cout<<mx<<endl;
    if(mx == 0)
    	return 0;
    for(int i=1;i<n;i++)
    {
    	if(ans[i] == mx)
    		cout<<i<<" ";
    }
    cout<<endl;
	return 0;
}
