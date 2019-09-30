const int maxn = 1e5 + 5;
ll powmod(ll a, ll b) { ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) { if (b & 1)res = res * a % mod; a = a * a % mod; }return res; }
ll fac[maxn];
ll invfac[maxn];
//预处理阶乘和阶乘的逆元
void init()
{
    fac[0] = 1;
    for (int i = 1; i < maxn; i++)
        fac[i] = fac[i - 1] * i % mod;
    invfac[maxn - 1] = powmod(fac[maxn - 1], mod - 2);
    for (int i = maxn - 2; i >= 0; i--)
        invfac[i] = invfac[i + 1] * (i + 1) % mod;
}

inline ll combi(int k, int n) { return k > n ? 0 : 1LL * fac[n] * invfac[k] % mod * invfac[n - k] % mod; }
