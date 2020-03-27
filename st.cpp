#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300005;
vector<pair<int, int>> sgmnt(MAXN * 4);
struct SegmentTree
{
	vector<pair<int, int>> *sgmnt; // Pair(val, idx)
	int n;
	SegmentTree(int n, vector<int> &a, vector<pair<int, int>> *sgmnt)
	{
		this->n = n;
		this->sgmnt = sgmnt;
		build(a, 0, 0, n-1);
	}
	void build(vector<int> &a, int curr, int ss, int se) 
	{
		if(ss == se)
			(*sgmnt)[curr].first = a[ss], (*sgmnt)[curr].second = ss;
		else
		{
			int mid = (ss + se) / 2;
			int left = 2 * curr + 1;
			int right = 2 * curr + 2;
			build(a, left, ss, mid);
			build(a, right, mid + 1, se);
			(*sgmnt)[curr] = func((*sgmnt)[left], (*sgmnt)[right]);
		}
	}
	pair<int, int> query(int curr, int ss, int se, int l, int r)
	{
		if(l > r)
			return {0, -1}; // Change this value accordingly
		if(l == ss && r == se)
			return (*sgmnt)[curr];
		if(l <= ss && se <= r)
			return (*sgmnt)[curr];
		int mid = (ss + se) / 2;
		int left = 2 * curr + 1;
		int right = 2 * curr + 2;
		pair<int, int> lft = query(left, ss, mid, l, min(r, mid));
		pair<int, int> rgt = query(right, mid + 1, se, max(l, mid+1), r);
		return func(lft, rgt);
	}
	void update(int curr, int ss, int se, int pos, int new_val)
	{
		if(ss == se)
			(*sgmnt)[curr].first = new_val;
		else
		{
			int mid = (ss + se) / 2;
			int left = 2 * curr + 1;
			int right = 2 * curr + 2;
			if(pos <= mid)
				update(left, ss, mid, pos, new_val);
			else
				update(right, mid+1, se, pos, new_val);
			(*sgmnt)[curr] = func((*sgmnt)[left], (*sgmnt)[right]);
		}
	}
	pair<int, int> Q(int l, int r)
	{
		return query(0, 0, n-1, l, r);
	}
	void U(int pos, int new_val)
	{
		update(0, 0, n-1, pos, new_val);
	}
	// Change function to implement different operations
	pair<int, int> func(pair<int, int> a, pair<int, int> b)
	{
		if(a.first < b.first)
			return a;
		return b;
	}
};