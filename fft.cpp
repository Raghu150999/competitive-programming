#include "bits/stdc++.h"
using namespace std;
//General Modulo FFT implementation
//Quite fast as it uses just 4 FFT calls
//Just call preCompute() in main() before usage

const int MAX = 1e6 + 5;            //Size of Polynomial
const int MOD = 998244353;
#define LL long long

namespace ffta {
const double PI = acos(-1);
const int LIM = 1 << 22;            //2 * 2^ceil(log2(POLY_SIZE))

//Complex class: Quite faster than in-built C++ library as it uses only functions required
template<typename T> class cmplx {
private:
    T x, y;
public:
    cmplx () : x(0.0), y(0.0) {}
    cmplx (T a) : x(a), y(0.0) {}
    cmplx (T a, T b) : x(a), y(b) {}
    T get_real() { return this->x; }
    T get_img() { return this->y; }
    cmplx conj() { return cmplx(this->x, -(this->y)); }
    cmplx operator = (const cmplx& a) { this->x = a.x; this->y = a.y; return *this; }
    cmplx operator + (const cmplx& b) { return cmplx(this->x + b.x, this->y + b.y); }
    cmplx operator - (const cmplx& b) { return cmplx(this->x - b.x, this->y - b.y); }
    cmplx operator * (const T& num) { return cmplx(this->x * num, this->y * num); }
    cmplx operator / (const T& num) { return cmplx(this->x / num, this->y / num); }
    cmplx operator * (const cmplx& b) {
        return cmplx(this->x * b.x - this->y * b.y, this->y * b.x + this->x * b.y);
    }
    cmplx operator / (const cmplx& b) {
        cmplx temp(b.x, -b.y); cmplx n = (*this) * temp;
        return n / (b.x * b.x + b.y * b.y);
    }
};

typedef cmplx<double> cd;      //change this to long double in case of error

cd W[LIM], invW[LIM];

void preCompute() {
    for(int i = 0; i < LIM/2; ++i) {
        //change this to long double in case of error
        double ang = 2 * PI * i / LIM;
        double _cos = cos(ang), _sin = sin(ang);
        W[i] = cd(_cos, _sin);
        invW[i] = cd(_cos, -_sin);
    }
}

void FFT(cd *a, int n, bool invert = false) {
    for(int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for(; j >= bit; bit >>= 1) j -= bit;
        j += bit;
        if (i < j) swap(a[i], a[j]);
    }
    for(int len = 2; len <= n; len <<= 1) {
        for(int i = 0; i < n; i += len) {
            int ind  = 0, add = LIM/len;
            for(int j = 0; j < len/2; ++j) {
                cd u = a[i+j];
                cd v = a[i+j+len/2] * (invert ? invW[ind] : W[ind]);
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                ind += add;
            }
        }
    }
    if (invert) for(int i = 0; i < n; ++i) a[i] = a[i]/n;
}

cd f[LIM], g[LIM], ff[LIM], gg[LIM];

// c[k] = sum_{i=0}^k a[i] b[k-i] % MOD
vector<int> mul(vector<int> &A, vector<int> &B) {
    int n1 = A.size(), n2 = B.size();
    int final_size = n1 + n2 - 1, N = 1;
    while(N < final_size) N <<= 1;
    vector<int> C(final_size, 0);
    int SQRTMOD = (int)sqrt(MOD) + 10;
    for(int i = 0; i < N; ++i) f[i] = cd(), g[i] = cd();
    for(int i = 0; i < n1; ++i) f[i] = cd(A[i]%SQRTMOD, A[i]/SQRTMOD);
    for(int i = 0; i < n2; ++i) g[i] = cd(B[i]%SQRTMOD, B[i]/SQRTMOD);
    FFT(f, N), FFT(g, N);
    cd X, Y, a1, a2, b1, b2;
    for(int i = 0; i < N; ++i) {
        X = f[i], Y = f[(N-i)%N].conj();
        a1 = (X + Y) * cd(0.5, 0);
        a2 = (X - Y) * cd(0, -0.5);
        X = g[i], Y = g[(N-i)%N].conj();
        b1 = (X + Y) * cd(0.5, 0);
        b2 = (X - Y) * cd(0, -0.5);
        ff[i] = a1 * b1 + a2 * b2 * cd(0, 1);
        gg[i] = a1 * b2 + a2 * b1;
    }
    FFT(ff, N, 1), FFT(gg, N, 1);
    for(int i = 0; i < final_size; ++i) {
        long long x = (LL)(ff[i].get_real() + 0.5);
        long long y = (LL)(ff[i].get_img() + 0.5) % MOD;
        long long z = (LL)(gg[i].get_real() + 0.5);
        C[i] = (x + (y * SQRTMOD + z) % MOD * SQRTMOD) % MOD;
    }
    return C;
}
};
using namespace ffta;

int n , k;
int inp;
vector < int > poly;
vector < int > res;
int main(){
    scanf("%d" , &n);
    preCompute();
    poly.resize(10 , 0);
    for(int i = 0; i < 10; i++)
        poly[i] = 1;
    res.resize(1, 0);
    res[0] = 1;
    k = n / 2;
    while(k){
        if(k & 1){
            res = ffta :: mul(res , poly);
        }
        poly = ffta :: mul(poly , poly);
        k >>= 1;
    }
    int ans = 0;
    for(auto &it:res)
    {
        ans += (1LL * it * it) % MOD;
        ans %= MOD;
    }
    printf("%d", ans);
}