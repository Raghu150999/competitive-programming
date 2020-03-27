#include <bits/stdc++.h>

using namespace std;

struct Heap
{
	bool isMax;
	int size;
	vector<int> heap;
	Heap(int isMax = true) : isMax(isMax) 
	{
		size = 0;
		heap.push_back(0); // dummy value
	}
	Heap(vector<int> &v, int isMax = true) : isMax(isMax)
	{
		int n = v.size();
		heap.resize(n+1);
		size = n;
		for(int i = 1; i <= n; i++)
			heap[i] = v[i-1];
		for(int i = (n/2) + 1; i >= 1; i--)
			heapify(i);
	}
	int parent(int i)
	{
		return i/2;
	}
	int left(int i)
	{
		return 2*i;
	}
	int right(int i)
	{
		return 2*i + 1;
	}
	bool compare(int x, int y)
	{
		bool res = (x >= y);
		return res ^ isMax;
	}
	void swap(int i, int j)
	{
		int tmp = heap[i];
		heap[i] = heap[j];
		heap[j] = tmp;
	}
	void heapify(int i)
	{
		int largest = i;
		int l = left(i), r = right(i);
		if(l <= size && compare(heap[largest], heap[l]))
			largest = l;
		if(r <= size && compare(heap[largest], heap[r]))
			largest = r;
		if(largest == i)
			return;
		swap(largest, i);
		heapify(largest);
	}
	void insert(int val)
	{
		size++;
		if(heap.size() < size)
			heap.push_back(val);
		else
			heap[size] = val;
		int curr = size;
		while(curr > 1)
		{
			int p = parent(curr);
			if(compare(heap[p], heap[curr]))
			{
				swap(p, curr);
				curr = p;
			}
			else
				break;
		}
	}
	int getTop()
	{
		return heap[1];
	}
	int extractTop()
	{
		int lst = heap[size];
		size--;
		int top = heap[1];
		heap[1] = lst;
		heapify(1);
		return top;
	}
};

int main()
{
	int n;
	cin >> n;
	vector<int> v(n);
	for(int i = 0; i < n; i++)
		cin >> v[i];
	Heap mxHeap = Heap(v, false);
	cout << mxHeap.getTop() << endl;
	cout << mxHeap.extractTop() << endl;
	cout << mxHeap.getTop() << endl;
	mxHeap.insert(1e8);
	cout << mxHeap.getTop() << endl;
}