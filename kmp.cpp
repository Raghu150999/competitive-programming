#include<bits/stdc++.h>

using namespace std;

struct KMP
{
	string pattern;
	int n;
	vector<int> pi;
	KMP(string pattern) : pattern(pattern) 
	{
		n = pattern.size();
		pi.resize(n+1);
		computePI();
	}
	void computePI()
	{
		pi[0] = 0;
		int k = 0;
		for(int i = 1; i < n; i++)
		{
			while(k > 0 && pattern[i] != pattern[k])
				k = pi[k-1];
			if(pattern[i] == pattern[k])
				k++;
			pi[i] = k;
		}
	}
	vector<int> findMatch(string &text)
	{
		int m = text.size();
		int j = 0, i = 0;
		vector<int> idxs;
		while(i < m)
		{
			while(j < n && text[i] == pattern[j])
				i++, j++;
			if(j == n)
				idxs.push_back(i-n), j = pi[j-1];
			else
			{
				if(j)
					j = pi[j-1];
				else
					i++;
			}
		}
		return idxs;
	}

};

int main()
{
	string text = "I am great and I know that!";
	string pattern = "great";
	KMP kmp = KMP(pattern);
	vector<int> idxs = kmp.findMatch(text);
	for(auto idx: idxs)
		cout << idx << " ";
	cout << endl;
	pattern = "I";
	kmp = KMP(pattern);
	idxs = kmp.findMatch(text);
	for(auto idx: idxs)
		cout << idx << " ";
	cout << endl;
	return 0;
}