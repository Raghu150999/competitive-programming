#include <bits/stdc++.h>
 
using namespace std;
 
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define int long long
#define pb push_back
#define endl "\n"
#define INF 1e18

const int N = 1e6 + 7;
const double PI = acos(-1);
int mod = 1e9 + 7;


vector<int> graph[N];
vector<int> color[3];
map<pair<int, int>, vector<pair<int, int>>> mp;
vector<int> as(N, 0);

vector<int> dfs(int pc, int p, int u)
{
	int children = 0;
	vector<vector<int>> cc;
	vector<int> child;
	for(int i = 0; i < graph[u].size(); i++)
	{
		int v = graph[u][i];
		if(v == p)
			continue;
		children++;
		for(int k = 0; k < 3; k++)
			cc.pb(dfs(k, u, v));
		child.pb(v);
	}
	vector<int> colors(3, INF);
	if(children > 2)
		return colors;
	if(children == 1)
	{
		for(int i = 0; i < 3; i++)
		{
			int mn = 1e18, mnd;
			for(int k = 0; k < 3; k++)
			{
				mnd = mn;
				if(k == pc || k == i)
					continue;
				mn = min(mn, cc[i][k] + color[i][u-1]);
				if(mn != mnd)
				{
					mp[{u, i}].clear();
					mp[{u, i}].pb({child[0], k});
				}
				mnd = mn;
			}
			colors[i] = mn;
		}
	}
	else
	if(children == 2)
	{
		for(int i = 0; i < 3; i++)
		{
			int mnd;
			for(int k1 = 0; k1 < 3; k1++)
			{
				for(int k2 = 0; k2 < 3; k2++)
				{
					mnd = colors[i];
					if(k1 == k2 || k1 == i || k2 == i || k1 == pc || k2 == pc)
						continue;
					colors[i] = min({colors[i], cc[i][k1] + cc[i+3][k2] + color[i][u-1]});
					if(colors[i] != mnd)
					{
						mp[{u, i}].clear();
						mp[{u, i}].pb({child[0], k1});
						mp[{u, i}].pb({child[1], k2});
					}
				}
			}
		}
	}
	else
	{
		for(int i = 0; i < 3; i++)
			colors[i] = color[i][u-1];
	}
	return colors;
}

void path_reconstruct(int u, int c)
{
	for(int i = 0; i < mp[{u, c}].size(); i++)
	{
		pair<int, int> p = mp[{u, c}][i];
		path_reconstruct(p.first, p.second);
	}
	as[u] = c + 1;
}

int32_t main()
{
    
    IOS
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    
    int n, a;
    cin >> n;
    
    for(int i = 0; i < 3; i++)
    	for(int j = 0; j < n; j++)
    		cin >> a, color[i].pb(a);
    for(int i = 0; i < n-1; i++)
    {
    	int u, v;
    	cin >> u >> v;
    	graph[u].pb(v);
    	graph[v].pb(u);
    }
    vector<int> costs = dfs(-1, -1, 1);
    int mn = 1e18;
    for(int &c : costs)
    	mn = min(mn, c);
    for(int i = 0; i < 3; i++)
    {
    	if(costs[i] == mn)
    	{
    		path_reconstruct(1, i);
    		break;
    	}
    }
    if(mn >= 1e18)
    {
    	cout << -1;
    	return 0;
    }
    else
    	cout << mn;
    cout << endl;
    for(int i = 1; i <= n; i++)
    	cout << as[i] << " ";
    cout << endl;
	return 0;
}