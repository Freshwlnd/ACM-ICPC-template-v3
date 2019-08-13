#pragma warning(disable:4996)
//题目：hdoj6651
//n题，m个知识点，需答对(比该题知识点高至少1分)k题
//复习所需最少知识点

#include<bits/stdc++.h>
#define upf(a,b,c) for(ll a=b;a<=c;++a)
#define drf(a,b,c) for(ll a=b;a>=c;--a)
#define mem(a,b) memset(a,b,sizeof(a))
#define Tcase(n) for(int _=1;_<=n;++_)
#define ll long long
#define int long long
#define mod MOD
const int MOD(1e9 + 7);
const int maxn(5e5 + 5);
const int INF(0x3fffffffffffffff);
const double esp(1e-6);
using namespace std;
ll powmod(ll a, ll b) { ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) { if (b & 1)res = res * a % mod; a = a * a % mod; }return res; }
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll n, m, k, t;
//对于复习知识点最少的n-k+1题如果需要通过考试则需要在这些题上至少复习m+1个知识点
//对于剩余的k-1题至少需要复习最少的n-k+1题中知识点最多的题
//那么对于最少知识点复习则需要复习m/(n-k+1)+1个知识点
ll hanshu() {
    return (m + 1 + (k - 1) * (m / (n - k + 1) + 1));
}
void acm() {
    cin >> t;
    Tcase(t) {
        cin >> n >> m >> k;
        cout << hanshu() << '\n';
    }
}

signed main()
{
#ifdef ACM_LOCAL
    freopen("./ACM.in", "r", stdin);
    freopen("./ACM.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    acm();
}
