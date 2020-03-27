#include <bits/stdc++.h>

using namespace std;

#define IOS                  \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0);
#define ll long long
#define pb push_back
#define endl "\n"

const ll N = 1e6 + 7;
const long double PI = acos(-1);
ll mod = 998244353;

// Always use long double in fft problems
typedef complex<long double> cd;

vector<ll> res(N, 0);

void fft(vector<cd> &a, ll n, bool invert)
{
    for (int i = 1, j = 0; i < n; i++)
    {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j && j < n)
        {
            cd tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
        }
    }

    for (int len = 2; len <= n; len <<= 1)
    {
        long double ang = (2 * PI / len) * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len)
        {
            cd w(1);
            for (int j = 0; j < len / 2; j++)
            {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert)
    {
        for (int i = 0; i < n; i++)
            a[i] /= n;
    }
}

vector<cd> p1(N, 0), p2(N, 0);

void multiply(vector<ll> &f1, ll sz1, vector<ll> &f2, ll sz2, vector<ll> &res)
{
    ll n = 1;
    for (int i = 0; i < sz1; i++)
        p1[i] = f1[i];
    for (int i = 0; i < sz2; i++)
        p2[i] = f2[i];
    while (n < sz1 + sz2)
        n <<= 1;
    for (int i = sz1; i < n; i++)
        p1[i] = 0;
    for (int i = sz2; i < n; i++)
        p2[i] = 0;
    fft(p1, n, false);
    fft(p2, n, false);
    for (int i = 0; i < n; i++)
        p1[i] *= p2[i];
    fft(p1, n, true);
    int deg = sz1 - 1 + sz2;
    for (int i = 0; i < deg; i++)
        res[i] = (ll)round(p1[i].real()); // Use mod here if needed
    for (int i = deg; i < n; i++)
        res[i] = 0;
}

vector<ll> tmpres(N, 0), tmpb(N, 0);

// exponentiation of a polynomial
void expo(vector<ll> &f1, ll sz, ll p, vector<ll> &res)
{
    tmpres[0] = 1;
    for (int i = 0; i < sz; i++)
        tmpb[i] = f1[i];
    ll ressz = 1;
    while (p)
    {
        if (p & 1)
        {
            multiply(tmpb, sz, tmpres, ressz, tmpres);
            ressz = ressz + sz - 1;
        }
        multiply(tmpb, sz, tmpb, sz, tmpb);
        sz = 2 * sz - 1;
        p >>= 1;
    }
    for (int i = 0; i < ressz; i++)
        res[i] = tmpres[i];
}

vector<ll> input, r1(N, 0), r2(N, 0), t1(N, 0), r11(N, 0), r22(N, 0);

void dnc(ll l, ll r, ll sz, vector<ll> &res)
{
    if (r == l)
    {
        // base case will be different according to the problem
        for (int i = 0; i <= sz; i++)
            res[i] = 1;
        return;
    }
    ll sum = 0;
    ll i = l;
    for (i = l; i <= r; i++)
    {
        sum += input[i];
        if (sum > sz / 2)
            break;
    }
    ll idx = max(i - 1, l);
    sum -= input[i];
    vector<ll> tmp;
    dnc(l, max(i - 1, l), sum, r1);
    for (int i = 0; i <= sum; i++)
        tmp.pb(r1[i]);
    dnc(max(i - 1, l) + 1, r, sz - sum, r2);
    for (int i = 0; i <= sum; i++)
        r1[i] = tmp[i];
    multiply(r1, sum + 1, r2, sz - sum + 1, t1);
    for (int i = 0; i <= sz; i++)
        res[i] = t1[i];
}

int32_t main()
{

    IOS;

    ll n, m, k, a;
    vector<ll> v;
    map<ll, ll> mp, ff;
    cin >> n >> m >> k;
    mod = 1009;
    for (int i = 0; i < n; i++)
    {
        cin >> a;
        mp[a]++;
    }
    ll sum = 0;
    for (auto it : mp)
    {
        if (it.second == 0)
            continue;
        input.pb(it.second);
        sum += it.second;
    }
    sort(input.begin(), input.end());

    dnc(0, input.size() - 1, sum, res);

    cout << res[k] % mod << endl;
    multiply(t1, 4, res, 3, res);
    return 0;
}