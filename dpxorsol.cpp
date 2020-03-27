// arr dynamic programming solution to finding the number 
// of subsets having xor of their elements as k 
#include<bits/stdc++.h> 
using namespace std; 

#define int long long

const int mod = 1e9 + 7;

// Returns count of subsets of arr[] with XOR value equals 
// to k. 
int subsetXOR(int arr[], int n, int k) 
{ 
	// Find maximum element in arr[] 
	int max_ele = arr[0]; 
	for (int i=1; i<n; i++) 
	if (arr[i] > max_ele) 
		max_ele = arr[i]; 

	// Maximum possible XOR value 
	int m = (1 << (int)(log2(max_ele) + 1) ) - 1; 
	if(k > m)
		return 0;
	// The value of dp[i][j] is the number of subsets having 
	// XOR of their elements as j from the set arr[0...i-1] 
	int dp[n+1][m+1]; 

	// Initializing all the values of dp[i][j] as 0 
	for (int i=0; i<=n; i++) 
		for (int j=0; j<=m; j++) 
			dp[i][j] = 0; 

	// The xor of empty subset is 0 
	dp[0][0] = 1; 

	// Fill the dp table 
	for (int i=1; i<=n; i++) 
		for (int j=0; j<=m; j++) 
			dp[i][j] = dp[i-1][j] + dp[i-1][j^arr[i-1]], dp[i][j] %= mod; 

	// The answer is the number of subset from set 
	// arr[0..n-1] having XOR of elements as k 
	return dp[n][k]; 
} 

// Driver program to test above function 
int32_t main() 
{ 
	int n, k;
	cin >> n >> k;
	int arr[n+1];
	for(int i = 0; i < n; i++)
		cin >> arr[i];
	cout << subsetXOR(arr, n, k);
	return 0; 
} 
