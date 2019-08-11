#pragma warning(disable:4996)
//题面参见https://ac.nowcoder.com/acm/problem/14532
#include<bits/stdc++.h>
#define upf(a,b,c) for(ll a=b;a<=c;++a)
#define drf(a,b,c) for(ll a=b;a>=c;--a)
#define mem(a,b) memset(a,b,sizeof(a))
#define Tcase(n) for(int _=1;_<=n;++_)
#define ll long long
#define mod MOD
const int MOD(1e9 + 7);
const double esp(1e-6);
const int maxn(205);
using namespace std;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
int n, T, k;
ll m;
ll a[maxn], A[maxn], B[maxn], C[maxn];
ll powmod(ll a, ll b) {
    ll res = 1;
    a %= mod;
    assert(b >= 0);
    for (; b; b >>= 1) {
        if (b & 1)res = res * a % mod;
        a = a * a % mod;
    }
    return res;
}
void qpow(ll m) {
    while (m) {
        if (m & 1) {//类似快速幂，当m&1==1时需要将这部分A加到B上而
            mem(C, 0);
            upf(i, 0, n - 1)upf(j, 0, n - 1)C[i] = (C[i] + A[(j - i + n) % n] * B[j]) % mod;//此处是把A加到B上的过程
            upf(i, 0, n - 1) B[i] = C[i];
        }
        //将A'倍增'
        mem(C, 0);
        upf(i, 0, n - 1)upf(j, 0, n - 1)C[i] = (C[i] + A[(j - i + n) % n] * A[j]) % mod;
        upf(i, 0, n - 1)A[i] = C[i];
        m >>= 1;
    }
}
inline int dis(int a, int b) {
    if (a < b)
        swap(a, b);
    return min(a - b, b - a + n);
}
int main()
{
#ifdef ACM_LOCAL
    freopen("./ACM.in", "r", stdin);
    freopen("./ACM.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> T;
    Tcase(T) {
        cin >> n >> m >> k;
        upf(i, 0, n - 1) {
            cin >> a[i];
            A[i] = dis(i, 0) >= k ? 0 : k - dis(i, 0);//记录每个点到0点的距离
            B[i] = a[i];//初始B数组保存了初始的数据
        }
        A[0] = 0;//自己不能传播自己
        qpow(m);
        upf(i, 0, n - 1)cout << B[i] << " \n"[i == n - 1];//B数组保存了m次循环后的结果
    }
    return 0;
}
