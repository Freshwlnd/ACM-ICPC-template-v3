#pragma warning(disable:4996)
#include<bits/stdc++.h>
#define upf(a,b,c) for(int a=b;a<=c;++a)
#define drf(a,b,c) for(int a=b;a>=c;--a)
#define mem(a,b) memset(a,b,sizeof(a))
#define Tcase(n) for(int _=1;_<=n;++_)
#define ull unsigned long long
#ifdef ONLINE_JUDGE
#define endl '\n'
#endif
typedef long long ll;
const int mod(100003);
using namespace std;
ll powmod(ll a, ll b) { ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) { if (b & 1)res = res * a % mod; a = a * a % mod; }return res; }
const int maxn = 1e5 + 5;
const double PI = 3.14159265358979323846264338327950288419716939937510582097494459230781640628;
typedef complex<double> cp;
namespace Polynomial_multiplication {
    int n, m, rev[maxn << 2];
    cp a[maxn << 2], b[maxn << 2];
    void init(int len) {
        for (n = 1, m = 0; n <= len; n <<= 1, m++);
        for (int i = 0; i < n; ++i) {
            rev[i] = rev[i >> 1] >> 1 | (i & 1) << (m - 1);
            a[i] = cp(0, 0);
            b[i] = cp(0, 0);
        }
    }
    void builda(vector<int> x, int len) { for (int i = 0; i <= len; i++) a[i] = cp(x[i], 0); }
    void builda(int x[], int len) { for (int i = 0; i <= len; i++) a[i] = cp(x[i], 0); }
    void buildb(vector<int> x, int len) { for (int i = 0; i <= len; i++) b[i] = cp(x[i], 0); }
    void buildb(int x[], int len) { for (int i = 0; i <= len; i++) b[i] = cp(x[i], 0); }

    void fft(cp* a, int dft)
    {
        for (int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
        for (int step = 1; step < n; step <<= 1)
        {
            double al = dft * PI / step;
            for (int k = 0; k < step; k++)
            {
                cp wnk = exp(cp(0, al * k));
                for (int j = k; j < n; j += step << 1)
                {
                    cp x = a[j];
                    cp y = wnk * a[j + step];
                    a[j] = x + y;
                    a[j + step] = x - y;
                }
            }
        }
        if (dft == -1) for (int i = 0; i < n; i++) a[i] /= n;
    }
    void calc(vector<int>& v, int len) {
        fft(a, 1); fft(b, 1);
        for (int i = 0; i < n; ++i)a[i] *= b[i];
        fft(a, -1);
        for (int i = 0; i <= len; i++) v.push_back(ll(a[i].real() + 0.5) % mod);
    }
}
