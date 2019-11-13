// 题目
// https://codeforces.com/contest/1192/problem/B
//
// 题目简述：
//    给定一棵N≤10^5个节点的树，边上带权，维护以下两个操作：
//    1. 修改一条边的边权
//    2. 询问当前树的直径长度
//
// 树的直径有以下性质：
// 定理：令farthest(𝑥)表示与节点𝑥距离最远的节点的集合。
// 则对任意节点𝑥，都有任意𝑎∈farthest(𝑥)与𝑏∈farthest(𝑎)，𝑎与𝑏的距离即为直径。
// 
// 我们任选一个节点𝑟作为树的根，任意边(𝑥,𝑦)，
// 若𝑥为𝑦的父节点，则把边权置于节点𝑦上，视作点权，记作𝑤[𝑦]，则修改边权都可以视作修改点权。
//
// 我们考虑询问树的直径，可以分成两个步骤：1. 找到离𝑟距离最远的叶子节点𝑥。2. 找到离𝑥距离最远的节点𝑦。
// 1. 找到离𝑟距离最远的叶子节点𝑥。我们在树的DFS序𝑝1,𝑝2,…,𝑝𝑛上查找dis(𝑟,𝑝𝑖)的最大值及其下标𝑖，则𝑥=𝑝𝑖。
//    可在𝑂(log𝑛)时间复杂度内解决。
// 2. 找到离𝑥距离最远的节点𝑦。设LCA(𝑥,𝑦)=𝑢，则dis(𝑥,𝑦)=dis(𝑟,𝑥)+dis(𝑟,𝑦)−2dis(𝑟,𝑢)。
//    考虑树链剖分，在𝑥到𝑟的路径中的所有重链中，找到最大的节点𝑢，使得dis(𝑟,light(𝑢))−2dis(𝑟,𝑢)最大，
//    其中light(𝑢)表示节点𝑢的轻链连接出去的后代节点集合（包括𝑢本身）。可在𝑂(log2𝑛)时间复杂度内解决。
// 
// 接下来考虑修改操作，我们只需要维护
// 1. 步骤1 的 dis(𝑟,𝑝𝑖)。只需要用线段树维护区间整体加减，以及区间最值即可。时间复杂度𝑂(log𝑛)。
// 2. 步骤2 的 dis(𝑟,light(𝑢))−2dis(𝑟,𝑢)。同样需要用线段树维护区间整体加减，以及区间最值。
//    此外，对于每一个节点𝑥，我们都需要一个multiset来维护light(𝑥)中节点𝑦的最大值dis(𝑟,𝑦)。
//    时间复杂度为𝑂(log2𝑛)。
// 
// 于是，我们可以在时间复杂度𝑂(𝑛+𝑞log2𝑛)内解决。

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;

#define X first
#define Y second

using i32 = int;
using i64 = long long;
using u8 = unsigned char;
using u32 = unsigned;
using u64 = unsigned long long;
using f64 = double;
using f80 = long double;
//using i128 = __int128_t;
//using u128 = __uint128_t;
using i128 = i64;
using u128 = u64;

ll power(ll a, ll b, ll p) {
    if (!b) return 1;
    ll t = power(a, b/2, p);
    t = t*t%p;
    if (b&1) t = t*a%p;
    return t;
}

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    ll px, py;
    ll d = exgcd(b, a%b, px, py);
    x = py;
    y = px-a/b*py;
    return d;
}

template<class T>
inline void freshmin(T &a, const T &b) {
    if (a > b) a = b;
}

template<class T>
inline void freshmax(T &a, const T &b) {
    if (a < b) a = b;
}

//#define getchar getchar_unlocked
//#define putchar putchar_unlocked

int inp() {
    int x = 0, f = 0; char ch;
    for(ch = getchar(); !isdigit(ch); ch = getchar())
        if(ch == '-') f = 1;
    for(; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
    return f ? -x : x;
}

ll inp_ll() {
    ll x = 0; int f = 0; char ch;
    for(ch = getchar(); !isdigit(ch); ch = getchar())
        if(ch == '-') f = 1;
    for(; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
    return f ? -x : x;
}

template<class T>
bool read(T &x) {
    x = 0;
    char ch = getchar();
    if (ch == EOF) return 0;
    for(; !isdigit(ch); )
    {
        ch = getchar();
        if (ch == EOF) return 0;
    }
    for(; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
    return 1;
}

template<class T>
void write(T x) {
    static char s[22];
    static char *it = s+20;
    static char *end = s+20;
    if (!x)
        *-- it = '0';
    while (x)
    {
        *-- it = x%10+'0';
        x /= 10;
    }
    for (; it < end; ++ it)
        putchar(*it);
}

template<class T>
void writeln(T x) {
    write(x);
    putchar('\n');
}

const int MAXN(100010);
const int INF(1000000000);
const int MOD(998244353);

template<class T>
struct segment {
    struct {
        T val;
        T tag;
    }a[MAXN*4];
    int n;
    function<T(int)> set_value;

    void clear(int k) {
        if (a[k].tag) {
            a[k<<1].tag += a[k].tag;
            a[k<<1].val += a[k].tag;
            a[k<<1|1].tag += a[k].tag;
            a[k<<1|1].val += a[k].tag;
            a[k].tag = 0;
        }
    }

    void update(int k) {
        a[k].val = max(a[k<<1].val, a[k<<1|1].val);
    }

    void build(int k, int L, int R) {
        if (L == R) {
            a[k].val = set_value(L);
            a[k].tag = 0;
            return;
        }
        int m = (L+R)>>1;
        build(k<<1, L, m);
        build(k<<1|1, m+1, R);
        update(k);
    }
    void add(int k, int L, int R, int x, int y, T d) {
        if (L == x && R == y) {
            a[k].tag += d;
            a[k].val += d;
            return;
        }
        clear(k);
        int m = (L+R)>>1;
        if (y <= m)
            add(k<<1, L, m, x, y, d);
        else if (x > m)
            add(k<<1|1, m+1, R, x, y, d);
        else {
            add(k<<1, L, m, x, m, d);
            add(k<<1|1, m+1, R, m+1, y, d);
        }
        update(k);
    }
    T get(int k, int L, int R, int x, int y) {
        if (L == x && R == y)
            return a[k].val;
        clear(k);
        int m = (L+R)>>1;
        if (y <= m)
            return get(k<<1, L, m, x, y);
        if (x > m)
            return get(k<<1|1, m+1, R, x, y);
        return max(get(k<<1, L, m, x, m), get(k<<1|1, m+1, R, m+1, y));
    }
    void modify(int k, int L, int R, int x, T p) {
        if (L == R) {
            a[k].val = p;
            return;
        }
        clear(k);
        int m = (L+R)>>1;
        if (x <= m)
            modify(k<<1, L, m, x, p);
        else
            modify(k<<1|1, m+1, R, x, p);
        update(k);
    }
    int get_pos(int k, int L, int R, T tmp) {
        if (L == R)
            return L;
        clear(k);
        int m = (L+R)>>1;
        if (a[k<<1].val == tmp)
            return get_pos(k<<1, L, m, tmp);
        else
            return get_pos(k<<1|1, m+1, R, tmp);
    }

    void build(int n, const function<T(int)> &set_value) {
        this->n = n;
        this->set_value = set_value;
        build(1, 1, n);
    }
    void add(int x, int y, T d) {
        add(1, 1, n, x, y, d);
    }
    T get(int x, int y) {
        return get(1, 1, n, x, y);
    }
    T get(int x) {
        return get(x, x);
    }
    void modify(int x, T p) {
        modify(1, 1, n, x, p);
    }
    pair<T, int> get_max() {
        T ret = a[1].val;
        int pos = get_pos(1, 1, n, ret);
        return {ret, pos};
    }
};

segment<i64> Td, Tw;

int n;
pii e[MAXN];
vector<pair<int, i64>> v[MAXN];
vector<int> son[MAXN];

int pre[MAXN], size[MAXN];
i64 weight[MAXN];
i64 dis[MAXN];

void dfs1(int x) {
    size[x] = 1;
    for (auto p : v[x]) {
        int y = p.X;
        i64 z = p.Y;
        if (y == pre[x]) continue;
        pre[y] = x;
        son[x].push_back(y);
        dis[y] = dis[x]+z;
        weight[y] = z;
        dfs1(y);
        size[x] += size[y];
    }
}

int times, X[MAXN], Y[MAXN], Z[MAXN], r[MAXN];
int from[MAXN];
i64 mdis[MAXN], vdis[MAXN];

void dfs2(int x) {
    X[x] = ++ times;
    r[times] = x;
    sort(son[x].begin(), son[x].end(), [&](int a, int b)
    {
        return size[a] > size[b];
    });
    mdis[x] = vdis[x] = dis[x];
    for (auto y : son[x]) {
        from[y] = y == son[x][0] ? from[x] : y;
        dfs2(y);
        freshmax(vdis[x], vdis[y]);
        if (y == son[x][0])
            Z[x] = times;
        else
            freshmax(mdis[x], vdis[y]);
    }
    Y[x] = times;
}

void modify(int x, i64 w) {
    Td.add(X[x], Y[x], w-weight[x]);
    Tw.add(X[x], Y[x], weight[x]-w);
    weight[x] = w;

    while (x) {
        int y = from[x];
        x = pre[y];
        if (x) {
            i64 maxdis = Td.get(Z[x]+1, Y[x]);
            i64 pdis = Td.get(X[x]);
            Tw.modify(X[x], maxdis-2*pdis);
        }
    }
}

i64 diameter() {
    auto p = Td.get_max();
    i64 maxdis = p.X;
    int id = p.Y;
    int x = r[id];
    i64 ret = maxdis;
    while (x) {
        int y = from[x];
        if (X[y] < X[x]) {
            i64 most = Tw.get(X[y], X[x]-1);
            freshmax(ret, maxdis+most);
        }
        x = pre[y];
        if (x) {
            i64 most = Td.get(X[x], X[y]-1);
            if (Y[y]+1 <= Y[x])
                freshmax(most, Td.get(Y[y]+1, Y[x]));
            freshmax(ret, maxdis+most-2*Td.get(X[x]));
        }
    }
    return ret;
}

int main() {

    n = inp();
    int q = inp();
    i64 W = inp_ll();

    for (int i = 1; i < n; ++ i) {
        int x = inp();
        int y = inp();
        i64 z = inp_ll();
        v[x].push_back({y, z});
        v[y].push_back({x, z});
        e[i] = {x, y};
    }

    dfs1(1);
    from[1] = 1;
    dfs2(1);

    Td.build(n, [&](int x) -> i64 {
        return dis[r[x]];
    });
    Tw.build(n, [&](int x) -> i64 {
        return mdis[r[x]]-2*dis[r[x]];
    });

    i64 ans = 0;
    while (q --) {
        int a = (inp()+ans)%(n-1)+1;
        i64 b = (inp_ll()+ans)%W;
        int x = pre[e[a].X] == e[a].Y ? e[a].X : e[a].Y;
        modify(x, b);
        ans = diameter();
        writeln(ans);
    }

    return 0;
}
