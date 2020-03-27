#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
using namespace __gnu_pbds;

#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define pb push_back
#define endl "\n"
#define int long long

const int INF = 1e12;
const double PI = acos(-1);
const int N = 1e6 + 7;
int mod = 1e9 + 7;

char editor[N];

struct MaxStack
{
    stack<int> st;
    void push(int x)
    {
        if(st.empty())
            st.push(x);
        else
        {
            if(st.top() <= x)
                st.push(x);
        }
    }
    void pop(int x)
    {
        if(x == st.top())
            st.pop();
    }
    int gettop()
    {
        return st.top();
    }
};

int32_t main()
{
    IOS;
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n;
    cin >> n;
    string str;
    cin >> str;
    int pos = 0;
    int left = 0, right = 0, lpos = -1, rpos = -1;
    MaxStack sl, sr;
    sl.push(0);
    sr.push(0);
    for(int i = 0; i < n; i++)
    {
        if(str[i] == 'L')
        {
            if(pos != 0 && (editor[pos] == '(' || editor[pos] == ')'))
            {
                sl.pop(left);
                if(editor[pos] == '(')
                    left--, right++;
                if(editor[pos] == ')')
                    left++, right--;
                sr.push(-right);
                if(right > 0)
                    if(rpos == -1)
                        rpos = pos;
                if(pos <= lpos)
                    lpos = -1;
            }
            if(pos)
                pos--;
        }
        else
        if(str[i] == 'R')
        {
            pos++;
            if(editor[pos] == '(' || editor[pos] == ')')
            {
                sr.pop(-right);
                if(editor[pos] == '(')
                    left++, right--;
                if(editor[pos] == ')')
                    left--, right++;
                sl.push(left);
                if(left < 0)
                    if(lpos == -1)
                        lpos = pos;
                if(pos >= rpos)
                    rpos = -1;
            }
        }
        else
        {
            if(editor[pos] == '(' || editor[pos] == ')')
                sl.pop(left);
            if(editor[pos] == '(')
                left--;
            else
            if(editor[pos] == ')')
                left++;
            if(str[i] == '(')
                left++;
            else
            if(str[i] == ')')
                left--;
            editor[pos] = str[i];
            if(str[i] == ')' || str[i] == '(')
                sl.push(left);
            if(left < 0)
                if(lpos == -1)
                    lpos = pos;
            if(pos == lpos)
                if(left >= 0)
                    lpos = -1;
        }
        // cout << lpos << " " << rpos << " ";
        if(lpos == -1 && rpos == -1 && (left + right == 0))
        {
            int ans = sl.gettop();
            ans = max(ans, sr.gettop());
            cout << ans << " ";
        }
        else
             cout << -1 << " ";
         // cout << endl;
    }
    return 0;
}