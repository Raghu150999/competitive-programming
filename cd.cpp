#include <bits/stdc++.h>

using namespace std;

#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define int long long
#define pb push_back
#define endl "\n"

const int N = 1e6 + 7;
const double PI = acos(-1);
const int INF = 1e18;
int mod = 998244353;


pair<int, int> countBits(int a)
{
    int ans = 0, cnt = 0;
    while(a > 0)
    {
        int d = a % 2;
        ans += d;
        a /= 2;
        cnt++;
    }
    return {ans, cnt};
}

int checkPos2(int a)
{
    int l2, l;
    while(a > 0)
    {
        l2 = l;
        int d = a % 2;
        l = d;
        a /= 2;
    }
    return l2;
}

int32_t main()
{
    IOS
    int q;
    cin >> q;
    while(q--)
    {
        int n;
        cin >> n;
        auto val = countBits(n);
        if(n == 1)
        {
            cout << 1 << endl;
            continue;
        }
        else
        if(n == 2)
        {
            cout << 2 << endl;
            continue;
        }
        if(val.first == val.second)
            cout << 2 * val.first - 1 << endl;
        else
        {
            int s = checkPos2(n);
            if(val.first == val.second-1 || s)
                cout << (val.second-1)*2 << endl;
            else
                cout << (val.second-1)+(val.second-2) << endl;
        }
    }
    return 0;
}