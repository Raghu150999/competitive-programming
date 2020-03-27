string Solution::longestPalindrome(string A) {
    
    int n = A.size();
    if (n == 0) {
        return 0;
    }
    // d1[i]: Longest odd distance from center i. For ex: abaa d1[1] = 2, d1[3] = 1
    vector<int> d1(n);
    int l = 0, r = -1;
    for (int i = 0; i < n; i++) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && A[i - k] == A[i + k]) {
            k++;
        }
        d1[i] = k;
        if (i + k - 1 > r) {
            r = i + k - 1;
            l = i - k + 1;
        }
    }
    l = 0, r = -1;
    // d2[i]: Longest even distance from center i. For ex: abaa d2[1] = 0, d2[3] = 1, d2[2] = 0
    vector<int> d2(n);
    for (int i = 0; i < n; i++) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && A[i - k - 1] == A[i + k]) {
            k++;
        }
        d2[i] = k;
        if (i + k - 1 > r) {
            r = i + k - 1;
            l = i - k;
        }
    }
    int L = 0, R = 0;
    int longestPalindromeLen = 1;
    for (int i = 0; i < n; i++) {
        if ((d1[i] * 2 - 1) > longestPalindromeLen) {
            longestPalindromeLen = d1[i] * 2 - 1;
            L = i - d1[i] + 1;
            R = i + d1[i] - 1;
        }
        if ((d2[i] * 2) > longestPalindromeLen) {
            longestPalindromeLen = d2[i] * 2;
            L = i - d2[i];
            R = i + d2[i] - 1;
        }
    }
    string longestPalindrome = "";
    for (int i = L; i <= R; i++) {
        longestPalindrome += A[i];
    }
    return longestPalindrome;
}