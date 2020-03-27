const int mod = 1e9 + 7;

long long modexpo(long long b, long long p)
{
    long long res = 1;
    while(p)
    {
        if(p % 2)
            res *= b;
        b *= b;
        b %= mod;
        res %= mod;
        p >>= 1;
    }
    return res;
}

long long modinv(long long b)
{
    return modexpo(b, mod-2);
}

long long ncr(long long n, long long r)
{
    r = min(r, n - r);
    long long ans = 1;
    for(int i = n; i >= n-r+1; i--)
    {
        ans *= i;
        ans %= mod;
        ans *= modinv(i+r-n);
        ans %= mod;
    }
    return ans;
}