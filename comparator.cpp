#include <bits/stdc++.h>
using namespace std;

struct Compare
{
	// function for '()' call
	bool operator()(const int& a, const int& b) const
	{
		return (a > b);
	}
};

int main() 
{
	priority_queue<int, vector<int>, Compare> pq; // min heap '>', max heap '<'
	pq.push(1);
	pq.push(3);
	pq.push(2);
	while(!pq.empty())
	{
		cout<<pq.top()<<endl;
		pq.pop();
	}
	set<int, Compare> s;
	s.insert(1);
	s.insert(3);
	s.insert(2);
	s.erase(2);
	for(auto it: s)
		cout<<it<<" ";
	cout<<endl;
	return 0;
}