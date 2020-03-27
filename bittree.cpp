#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> BITree;

vector<int> getSum(int x)
{
	x++;
	vector<int> sum(26, 0);
	while(x > 0)
	{
		for(int i = 0; i < 26; i++)
			sum[i] += BITree[x][i];
		x -= x & (-x);
	}
	return sum;
}
 
void updateAdd(int n, int x, vector<int> &val)
{
	x++;
	while(x <= n)
	{
		for(int i = 0; i < 26; i++)
			BITree[x][i] += val[i];
		x += x & (-x);
	}
}