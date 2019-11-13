#pragma warning(disable:4996)

#include<bits/stdc++.h>
using namespace std;
#define upf(a,b,c) for(int a=b;a<=c;++a)
#define drf(a,b,c) for(int a=b;a>=c;--a)
#define ll long long
const int maxn(2e6 + 5);
const int mod(998244353);
const int G(3);
ll rev[maxn], a[maxn];
ll m, l;
ll n;
ll powmod(ll a, ll b) { ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) { if (b & 1)res = res * a % mod; a = a * a % mod; }return res; }

void work(int l) {
    upf(i, 0, (1 << l) - 1)rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (l - 1));
}
void ntt(ll* a, ll n, int opt) {
    upf(i, 0, n - 1)if (i < rev[i])swap(a[i], a[rev[i]]);
    for (int base = 1; base < n; base <<= 1) {
        ll wn = powmod(G, (mod - 1) / base / 2);
        for (int block = 0; block < n; block += base << 1) {
            ll w = 1;
            for (int step = 0; step < base; step++) {
                ll x, y;
                x = a[block + step];
                y = a[block + step + base] * w % mod;
                a[block + step] = (x + y) % mod;
                a[block + step + base] = (x - y + mod) % mod;
                w = w * wn % mod;
            }
        }
    }
    if (opt == -1) {
        reverse(a + 1, a + n);
        int invn = powmod(n, mod - 2);
        upf(i, 0, n - 1)a[i] = a[i] * invn % mod;
    }
}