#pragma warning(disable:4996)
//~����~
//A ������ n �����У���Щ������ n-1 ����·������ʹ�������������п��Ի����·��Ψһ��
//ÿ�����ж���һ�� �������֣��Լ������ʽ�������������е������ģ���Ϊ���е�������
//һЩ������ϣ������ A ���������߼ƻ� �˷ɻ������� x �ų��У�
//���� x �ų��е� y �ų���֮������Ψһ��·�����������մ� y ��������뿪 A ���� 
//�ھ���ÿһ������ʱ�������߾ͻ��л������������е������������գ��Ӷ���������˱��浽�Լ����ϡ�
//Ȼ���������ǲ��ܼ򵥵��ӵģ���һ��������Ҳʮ��������������������������������ķ�ʽ�������Լ����ϵġ�
//���磬 ���������� 3 ����Ƭ������ֵ�ֱ��� 5��7��11����ô���ձ������Լ����ϵ�����ֵ���� 9��5 xor 7 xor 11���� 
//��Щ�����������߷��֣�ֻҪѡ���Եؽ������գ����ܻ�ø��������ֵ��
//������������������ֵ�У�ֻѡ�� 5  �� 11 �����Ա���������ֵΪ 14 ��
//���ڣ�һЩ�������ҵ��˴������㣬ϣ��������Ǽ���������ǵ��г̰����� ���Ա������������ֵ�Ƕ��١�
//~����~
//��һ�а��� 2 �������� n ��q���ֱ��ʾ���е�������������������
//�ڶ��а��� n ���Ǹ����������е� i ������ Gi ��ʾ i �ų��е�����ֵ��
//��� n - 1 �У�ÿ�а������������� x ��y����ʾ x �ų��к� y �ų���֮����һ����·������
//��� q �У�ÿ�а������������� x ��y����ʾ���������ߵ����мƻ��Ǵ� x �ų��е� y �ų��С�
//N �� 20000, Q �� 200000, Gi �� 2 ^ 60
//~���~
//�����Ҫ���� q �У�ÿ�а��� 1 ���Ǹ���������ʾ���������߿��Ա������������ֵ��
#include<bits/stdc++.h>
#define upf(a,b,c) for(ll a=b;a<=c;++a)
#define drf(a,b,c) for(ll a=b;a>=c;--a)
#define ll long long
#define mod MOD
const int MOD(998244353);
const double esp(1e-6);
const int maxn(2e4 + 5);
using namespace std;
ll powmod(ll a, ll b) { ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) { if (b & 1)res = res * a % mod; a = a * a % mod; }return res; }
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll n, q, g[maxn];
struct Linear_Basis {
    long long d[61];  //d[]�ع�ǰ�����Ի���p[]�ع�������Ի�
    int cnt;                //��¼���Ի�����
    Linear_Basis()              //��ʼ��
    {
        memset(d, 0, sizeof(d));
        cnt = 0;
    }
    bool insert(long long val)  //�������Ի�
    {
        for (int i = 60; i >= 0; i--)
            if (val & (1LL << i))
            {
                if (!d[i])
                {
                    d[i] = val;
                    break;
                }
                val ^= d[i];
            }
        return val > 0;
    }
    //������0�ͷ���true
    bool check(long long val) {
        for (int i = 32; i >= 0; i--)
            if (val & (1LL << i)) {
                if (!d[i])
                    return false;
                val ^= d[i];
            }
        return true;
    }
    //�������Ի������ռ������ֵ
    long long query_max()
    {
        long long ret = 0;
        for (int i = 60; i >= 0; i--)
            if ((ret ^ d[i]) > ret)
                ret ^= d[i];
        return ret;
    }
};
//�ϲ��������Ի�
Linear_Basis merge(const Linear_Basis& n1, const Linear_Basis& n2)
{
    Linear_Basis ret = n1;
    for (int i = 60; i >= 0; i--)
        if (n2.d[i])
            ret.insert(n2.d[i]);
    return ret;
}
struct node {
    int t, nex;
}e[500001 << 1];
ll depth[maxn], father[maxn][16], lg[maxn], head[maxn];
Linear_Basis LB[maxn][16];
ll tot;
inline void add(int x, int y)
{
    e[++tot].t = y;
    e[tot].nex = head[x];
    head[x] = tot;
}
inline void dfs(int now, int fath)
{
    depth[now] = depth[fath] + 1;
    father[now][0] = fath;
    LB[now][0].insert(g[now]);
    for (register int i = 1; (1 << i) <= depth[now]; ++i) {
        father[now][i] = father[father[now][i - 1]][i - 1];
        LB[now][i] = merge(LB[now][i - 1], LB[father[now][i - 1]][i - 1]);
    }
    for (register int i = head[now]; i; i = e[i].nex)
    {
        if (e[i].t != fath)dfs(e[i].t, now);
    }
}
Linear_Basis lca(int x, int y)
{
    Linear_Basis L;
    if (depth[x] < depth[y])
        swap(x, y);
    while (depth[x] > depth[y]) {
        L = merge(L, LB[x][lg[depth[x] - depth[y]] - 1]);
        x = father[x][lg[depth[x] - depth[y]] - 1];
    }
    if (x == y) {
        L = merge(L, LB[x][0]);
        return L;
    }
    for (register int k = lg[depth[x]]; k >= 0; --k)
        if (father[x][k] != father[y][k]) {
            L = merge(L, LB[x][k]);
            L = merge(L, LB[y][k]);
            x = father[x][k];
            y = father[y][k];
        }
    L = merge(L, LB[x][0]);
    L = merge(L, LB[y][0]);
    L = merge(L, LB[father[x][0]][0]);
    return L;
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

    cin >> n >> q;
    upf(i, 1, n) {
        cin >> g[i];
    }
    upf(i, 1, n - 1)
    {
        int x, y;
        cin >> x >> y;
        add(x, y);
        add(y, x);
    }
    dfs(1, 0);
    upf(i, 1, n)
        lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
    ll x, y;
    upf(i, 1, q) {
        cin >> x >> y;
        Linear_Basis B = lca(x, y);
        ll ans = B.query_max();
        cout << ans << endl;
    }
    return 0;
}