#pragma warning(disable:4996)
//��Ŀ��hdoj6651
//n�⣬m��֪ʶ�㣬����(�ȸ���֪ʶ�������1��)k��
//��ϰ��������֪ʶ��

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
//���ڸ�ϰ֪ʶ�����ٵ�n-k+1�������Ҫͨ����������Ҫ����Щ�������ٸ�ϰm+1��֪ʶ��
//����ʣ���k-1��������Ҫ��ϰ���ٵ�n-k+1����֪ʶ��������
//��ô��������֪ʶ�㸴ϰ����Ҫ��ϰm/(n-k+1)+1��֪ʶ��
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
