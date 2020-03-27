#include <bits/stdc++.h>

using namespace std;

#define int long long

const int mod = 1e9 + 7;

int modexpo(int b, int p)
{
	int res = 1;
	while(p)
	{
		if(p % 2)
			res *= b;
		res %= mod;
		b *= b;
		b %= mod;
		p >>= 1;
	}
	return res;
}

void gaussian_elimination(vector<int> &v)
{
    int len = v.size();
    int index = 0;
    for(int i=31;i>=0;i--)
    {
        int mx = -1e8, pos = -1;
        for(int j=index;j<len;j++)
        {
            if((v[j] & (1 << i)) && v[j] > mx)
            {
                mx = v[j];
                pos = j;
            }
        }
        if(pos == -1)
            continue;
        swap(v[pos], v[index]);
        pos = index;
        for(int j=0;j<len;j++)
        {
            if(j != pos && (v[j] & (1 << i)))
                v[j] ^= v[pos];
        }
        index++;
    }
}

/**
*   This probram computes how many subsets of a set of integers give a XOR sum equal to k.
*/

int32_t main() 
{
    int n, k;
    cin>>n>>k;
    vector<int> v;
    for(int i=0;i<n;i++)
    {
        int a;
        cin>>a;
        v.push_back(a);
    }
    gaussian_elimination(v); // perform gaussian elimination
    int cnt = 0;
    while(cnt < n && v[cnt] > 0)
        cnt++;
    cnt = n - cnt;
    int res = 0;
    for(int j=0;j<n;j++)
    {
    	for(int i=31;i>=0;i--)
    	{
    		if(!((1 << i) & v[j]))
    			continue;
    		if(((1 << i) & k) == (v[j] & (1 << i)))
    			res ^= v[j];
    		break;
    	}
    }
    int x = res == k ? 1 : 0;
    int prod = modexpo(2, cnt);
    cout << prod * x << endl;
	return 0;
}