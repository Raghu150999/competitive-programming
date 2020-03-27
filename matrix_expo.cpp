#include <bits/stdc++.h>

using namespace std;

#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define ll long long
#define pb push_back
// #define endl "\n"

const ll N = 1e6 + 7;
const ll mod = 1e9 + 7;

struct Matrix
{
	ll arr[5][5];
};

Matrix *matrixMultiply(Matrix *mat, Matrix *mat2, int size, ll m)
{
	Matrix *mat3 = new Matrix;
	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
			mat3->arr[i][j] = 0;
	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
			for(int k=0;k<size;k++)
			{
				mat3->arr[i][j] += mat->arr[i][k] * mat2->arr[k][j];
				mat3->arr[i][j] %= m;
			}
	return mat3;
}

Matrix *matrixMod(Matrix *mat, ll m, int size)
{
	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
			mat->arr[i][j] %= mod;
	return mat;
}

Matrix *matrixExpo(Matrix *mat, ll pow, ll m, int size)
{
	Matrix *res = new Matrix;
	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
			res->arr[i][j] = 0;
	for(int i=0;i<size;i++)
		res->arr[i][i] = 1;
	while(pow)
	{
		if(pow & 1)
			res = matrixMultiply(res, mat, size, m);
		pow >>= 1;
		res = matrixMod(res, m, size);
		mat = matrixMultiply(mat, mat, size, m);
		mat = matrixMod(mat, m, size);
	}
	return res;
}

ll modexpo(ll b, ll p, ll m)
{
	ll res = 1;
	b %= m;
	while(p)
	{
		if(p & 1)
			res = res * b;
		p >>= 1;
		res %= m;
		b = (b*b)%m;
	}
	return res;
}

int32_t main()
{
	
	IOS

	vector<ll> v;
	ll n, f1, f2, f3, c;
	cin>>n>>f1>>f2>>f3>>c;
	Matrix *coeffc = new Matrix;
	coeffc->arr[0][0] = 1;
	coeffc->arr[0][1] = 0;
	coeffc->arr[0][2] = 0;
	coeffc->arr[0][3] = 0;
	coeffc->arr[0][4] = 1;

	coeffc->arr[1][0] = 2;
	coeffc->arr[1][1] = 1;
	coeffc->arr[1][2] = 1;
	coeffc->arr[1][3] = 1;
	coeffc->arr[1][4] = -6;

	coeffc->arr[2][0] = 0;
	coeffc->arr[2][1] = 1;
	coeffc->arr[2][2] = 0;
	coeffc->arr[2][3] = 0;
	coeffc->arr[2][4] = 0;

	coeffc->arr[3][0] = 0;
	coeffc->arr[3][1] = 0;
	coeffc->arr[3][2] = 1;
	coeffc->arr[3][3] = 0;
	coeffc->arr[3][4] = 0;

	coeffc->arr[4][0] = 0;
	coeffc->arr[4][1] = 0;
	coeffc->arr[4][2] = 0;
	coeffc->arr[4][3] = 0;
	coeffc->arr[4][4] = 1;

	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
			coeffc->arr[i][j] = (coeffc->arr[i][j] + (mod - 1))%(mod-1);
	
	Matrix *coefff = new Matrix;
	coefff->arr[0][0] = 1;
	coefff->arr[0][1] = 1;
	coefff->arr[0][2] = 1;

	coefff->arr[1][0] = 1;
	coefff->arr[1][1] = 0;
	coefff->arr[1][2] = 0;

	coefff->arr[2][0] = 0;
	coefff->arr[2][1] = 1;
	coefff->arr[2][2] = 0;

	coeffc = matrixExpo(coeffc, n-3, mod-1, 5);
	coefff = matrixExpo(coefff, n-3, mod-1, 3);

	ll powc = 0, p1 = 0, p2 = 0, p3 = 0;
	vector<ll> vc, v1, v2, v3;
	vc.pb(4);
	vc.pb(0);
	vc.pb(0);
	vc.pb(0);
	vc.pb(1);

	for(int i=0;i<5;i++)
		powc += coeffc->arr[1][i] * vc[i];

	v3.pb(1);
	v3.pb(0);
	v3.pb(0);

	v2.pb(0);
	v2.pb(1);
	v2.pb(0);

	v1.pb(0);
	v1.pb(0);
	v1.pb(1);

	for(int i=0;i<3;i++)
	{
		p3 += coefff->arr[0][i] * v3[i];
		p2 += coefff->arr[0][i] * v2[i];
		p1 += coefff->arr[0][i] * v1[i];
	}
	ll ans = 1;
	ans *= modexpo(c, powc, mod);
	ans %= mod;
	ans *= modexpo(f3, p3, mod);
	ans %= mod;
	ans *= modexpo(f2, p2, mod);
	ans %= mod;
	ans *= modexpo(f1, p1, mod);
	ans %= mod;
	cout<<ans<<endl;
	return 0;
}