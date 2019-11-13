#pragma warning(disable:4996)
//~题面~
//A 国共有 n 座城市，这些城市由 n-1 条道路相连，使得任意两座城市可以互达，且路径唯一。
//每座城市都有一个 幸运数字，以纪念碑的形式矗立在这座城市的正中心，作为城市的象征。
//一些旅行者希望游览 A 国。旅行者计划 乘飞机降落在 x 号城市，
//沿着 x 号城市到 y 号城市之间那条唯一的路径游览，最终从 y 城市起飞离开 A 国。 
//在经过每一座城市时，游览者就会有机会与这座城市的幸运数字拍照，从而将这份幸运保存到自己身上。
//然而，幸运是不能简单叠加的，这一点游览者也十分清楚。他们迷信着幸运数字是以异或的方式保留在自己身上的。
//例如， 游览者拍了 3 张照片，幸运值分别是 5，7，11，那么最终保留在自己身上的幸运值就是 9（5 xor 7 xor 11）。 
//有些聪明的游览者发现，只要选择性地进行拍照，便能获得更大的幸运值。
//例如在上述三个幸运值中，只选择 5  和 11 ，可以保留的幸运值为 14 。
//现在，一些游览者找到了聪明的你，希望你帮他们计算出在他们的行程安排中 可以保留的最大幸运值是多少。
//~输入~
//第一行包含 2 个正整数 n ，q，分别表示城市的数量和旅行者数量。
//第二行包含 n 个非负整数，其中第 i 个整数 Gi 表示 i 号城市的幸运值。
//随后 n - 1 行，每行包含两个正整数 x ，y，表示 x 号城市和 y 号城市之间有一条道路相连。
//随后 q 行，每行包含两个正整数 x ，y，表示这名旅行者的旅行计划是从 x 号城市到 y 号城市。
//N ≤ 20000, Q ≤ 200000, Gi ≤ 2 ^ 60
//~输出~
//输出需要包含 q 行，每行包含 1 个非负整数，表示这名旅行者可以保留的最大幸运值。
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
    long long d[61];  //d[]重构前的线性基，p[]重构后的线性基
    int cnt;                //记录线性基的秩
    Linear_Basis()              //初始化
    {
        memset(d, 0, sizeof(d));
        cnt = 0;
    }
    bool insert(long long val)  //插入线性基
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
    //可生成0就返回true
    bool check(long long val) {
        for (int i = 32; i >= 0; i--)
            if (val & (1LL << i)) {
                if (!d[i])
                    return false;
                val ^= d[i];
            }
        return true;
    }
    //计算线性基向量空间内最大值
    long long query_max()
    {
        long long ret = 0;
        for (int i = 60; i >= 0; i--)
            if ((ret ^ d[i]) > ret)
                ret ^= d[i];
        return ret;
    }
};
//合并两个线性基
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