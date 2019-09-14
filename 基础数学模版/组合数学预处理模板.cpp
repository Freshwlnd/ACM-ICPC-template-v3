#pragma warning(disable:4996)
#include<bits/stdc++.h>
#define upf(a,b,c) for(int a=b;a<=c;++a)
#define drf(a,b,c) for(int a=b;a>=c;--a)
#define ll long long
#ifdef ONLINE_JUDGE
#define end '\n'
#endif
const double esp(1e-6);
const int mod(1e9 + 7);
const int maxn(1e6 + 5);
using namespace std;
ll fac[maxn], invfac[maxn];
ll powmod(ll a, ll b) { ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) { if (b & 1)res = res * a % mod; a = a * a % mod; }return res; }
inline ll combi(int k, int n) { return k > n ? 0 : fac[n] * invfac[k] % mod * invfac[n - k] % mod; }
int main() {
#ifndef ONLINE_JUDGE
    freopen("./ACM.in", "r", stdin);
    freopen("./ACM.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    fac[0] = 1;
    upf(i, 1, 1000000) {
        fac[i] = fac[i - 1] * i % mod;
    }
    invfac[1000000] = powmod(fac[1000000], mod - 2);
    drf(i, 999999, 0)invfac[i] = invfac[i + 1] * (i + 1) % mod;
}