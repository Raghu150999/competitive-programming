#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

int modexpo(int b, int p, int m = mod)
{
    int res = 1;
    b %= m;
    while(p)
    {
        if(p & 1)
            res *= b;
        res %= m;
        b *= b;
        b %= m;
        p >>= 1;
    }
    return res;
}

int modinv(int a, int p = mod)
{
    return modexpo(a, p - 2, p);
}

const int maxn = 1e6 + 7;

int fact[maxn], invfact[maxn];

void fac()
{
    fact[0] = 1;
    for(int i = 1; i < maxn; i++)
    {
        fact[i] = fact[i-1] * i;
        fact[i] %= mod;
    }
    invfact[maxn-1] = modinv(fact[maxn-1]);
    for(int i = maxn - 2; i >= 0; i--)
    {
        invfact[i] = invfact[i+1] * (i + 1);
        invfact[i] %= mod;
    }
}

int ncr(int n, int r)
{
    if(n < r || n == 0)
        return 0;
    r = min(r, n-r);
    if(r == 0)
        return 1;
    int res = fact[n];
    res *= invfact[r];
    res %= mod;
    res *= invfact[n-r];
    res %= mod;
    return res;
}


int phi(int n)
{
    // Source: http://cp-algorithms.com/
    int result = n;
    for(int i = 2; i * i <= n; i++)
    {
        if(n % i == 0)
        {
            while(n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if(n > 1)
        result -= result / n;
    return result;
}

int modinv_phi(int a, int m)
{
    return modexpo(a, phi(m) - 1, m);
}

// returns a * b % c, takes care even if a, b are negative numbers and large
int mulmod(int a, int b, int c) 
{
    // Source: tourist submission
    // https://codeforces.com/contest/986/submission/38743952
    int sign = 1;
    if(a < 0)
        a = -a, sign = -sign;
    if(b < 0)
        b = -b, sign = -sign;
    a %= c;
    b %= c;
    int res = 0;
    while(b > 0)
    {
        if(b & 1)
            res = (res + a) % c;
        a = (a + a) % c;
        b >>= 1;
    }
    if(sign == -1)
        res = (-res) % c;
    return res;
}


int xgcd(int a, int b, int &x, int &y)
{
    if(a == 0)
    {
        x = 0;
        y = 1;
        return b;
    }
    int p = b / a;
    int g = xgcd(b - p * a, a, y, x);
    x -= p * y;
    return g;
}

// returns any solution of linear diophantine equation in x and y
// also returns gcd in g
// eqn: ax + by = c
// works even if a, b, c are large
bool diophantine(int a, int b, int c, int &x, int &y, int &g)
{
    // Source: tourist submission
    // https://codeforces.com/contest/986/submission/38743952
    if(a == 0 && b == 0)
    {
        if(c == 0)
        {
            x = y = g = 0;
            return true;
        }
        return false;
    }
    if(a == 0)
    {
        if(c % b == 0)
        {
            x = 0;
            y = c / b;
            g = abs(b);
            return true;
        }
        return false;
    }
    if(b == 0)
    {
        if(c % a == 0)
        {
            x = c / a;
            y = 0;
            g = abs(a);
            return true;
        }
        return false;
    }
    g = xgcd(a, b, x, y);
    if(c % g != 0)
        return false;
    int dx = c / a;
    c -= dx * a;
    int dy = c / b;
    c -= dy * b;
    x = dx + mulmod(x, c / g, b);
    y = dy + mulmod(y, c / g, a);
    g = abs(g);
    return true;
}
