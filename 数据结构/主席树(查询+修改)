#pragma GCC optimize(3)
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
#define N 60005
#define M 2000005
#define R register
using namespace std;

int n, Q, m, cnt, a[N], b[N], x, y, k;
int T[N], S[N], ls[M], rs[M], sum[M];
int cntE, use[3][N];

struct ques
{
    char s[1];
    int l, r, kth;
}q[N >> 2];
inline int read()
{
    int x = 0;
    char c = getchar();
    bool flag = 0;
    while(c < '0' || c > '9'){if(c == '-')flag = 1;c = getchar();}
    while(c >= '0' && c <= '9'){x = (x << 3) + (x << 1) + (c ^ 48);c = getchar();}
    return flag ? -x : x;
}

int Build(int l, int r)
{
    int now = ++cnt;
    if(l < r)
    {
        int mid = (l + r) >> 1;
        ls[now] = Build(l, mid);
        rs[now] = Build(mid + 1, r);
    }
    return now;
}

inline int Build_new(int flag, int mark, int loc, int val)
{
    int rt = ++cnt; 
    int before;
    if(mark == 1) before = T[0];
    else before = flag ? T[mark - 1] : S[mark - 1];
    if(!flag && val) before = S[mark];
    sum[rt] = sum[before] + val;
    int l =  1, r = m, now = rt, still = before;
    for(; ls[still] || rs[still];)
    {
        int mid = (l + r) >> 1;
        // l ~ mid --- left    mid + 1 ~ r --- right
        if(loc > mid)
        {
            ls[now] = ls[still];
            rs[now] = ++cnt, sum[ rs[now] ] = sum[ rs[still] ] + val;
            now = rs[now];
            still = rs[still];
            l = mid + 1;
        }
        else
        {
            rs[now] = rs[still];
            ls[now] = ++cnt, sum[ ls[now] ] = sum[ ls[still] ] + val;
            now = ls[now];
            still = ls[still];
            r = mid;
        }
    }
    return rt;
}

inline int lowbit(int x) { return x & (-x); }
inline int Sum(int y, int x)
{
    int res = 0;
    for(R int i = x; i >= 1; i -= lowbit(i))
        res += sum[ls[use[y][i]]];
    return res;
}
inline int query(int u, int v, int a, int b, int l, int r, int k)
{
    if(l == r) return l;
    int lm = Sum(2, v) + sum[ls[b]] - sum[ls[a]] - Sum(1, u);
    int mid = (l + r) >> 1;
    if(k <= lm) 
    {
        for(R int i = u; i >= 1; i -= lowbit(i))
            use[1][i] = ls[use[1][i]];
        for(R int i = v; i >= 1; i -= lowbit(i))
            use[2][i] = ls[use[2][i]];
        return query(u, v, ls[a], ls[b], l, mid, k);
    }
    for(R int i = u; i >= 1; i -= lowbit(i))
            use[1][i] = rs[use[1][i]];
    for(R int i = v; i >= 1; i -= lowbit(i))
            use[2][i] = rs[use[2][i]];
    return query(u, v, rs[a], rs[b], mid + 1, r, k - lm);
    return 0;
}

inline void update(int loc,int num)
{
    int where;
    where = lower_bound(b + 1, b + 1 + m, a[loc]) - b;
    for(R int i = loc; i <= n; i += lowbit(i))
        S[i] = Build_new(0, i, where, -1);
    where = lower_bound(b + 1, b + 1 + m, num) - b;
    for(R int i = loc; i <= n; i +=lowbit(i))
        S[i] = Build_new(0, i, where, 1);
    a[loc] = num;
}

signed main()
{
    n = read(), Q = read();
    for(R int i = 1; i <= n; i++) a[i] = read(), b[i] = a[i];
    cntE = n;
    for(R int i = 1; i <= Q; i++)
    {
        scanf("%s%d%d", q[i].s, &q[i].l, &q[i].r);
        if(q[i].s[0] == 'Q')
            scanf("%d", &q[i].kth);
        else 
            b[++cntE] = q[i].r;
    }
    sort(b + 1, b + 1 + cntE);
    m = unique(b + 1, b + 1 + cntE) - b - 1;
    T[0] = Build(1, m);
    for(R int i = 1; i <= n; i++)
    {
        int loc = lower_bound(b + 1, b + 1 + m, a[i]) - b;
        T[i] = Build_new(1, i, loc, 1);
    }
    for(R int i = 1; i <= n; i++)
        S[i] = Build_new(0, i, 1, 0);
    for(R int i = 1; i <= Q; ++i)
    {
        if(q[i].s[0] == 'Q')
        {
            int x = q[i].l, y = q[i].r;
            for(R int j = x - 1; j >= 1; j -= lowbit(j))
                use[1][j] = S[j];
            for(R int j = y; j >= 1; j -= lowbit(j))
                use[2][j] = S[j];
            printf("%d\n", b[query(x - 1, y, T[x - 1], T[y], 1, m, q[i].kth)]);
        }
        else
            update(q[i].l, q[i].r);
    }
    return 0;
}
