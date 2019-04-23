#pragma GCC optimize(3)
#include <cstdio>
#include <cmath>
#include <algorithm>
#define N 200005
#define M 4000005
#define R register
using namespace std;

int n, Q, m, cnt, a[N], b[N], x, y, k;
int T[N], ls[M], rs[M], sum[M];

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

inline void Build_new(int mark, int loc)
{
    T[mark] = ++cnt;
    sum[cnt] = sum[T[mark - 1]] + 1;
    int l =  1, r = m, now = cnt, still = T[mark - 1];
    for(; ls[still] || rs[still];)
    {
        int mid = (l + r) >> 1;
        // l ~ mid --- left    mid + 1 ~ r --- right
        if(loc > mid)
        {
            ls[now] = ls[still];rs[now] = ++cnt;
            sum[ rs[now] ] = sum[ rs[still] ] + 1;
            now = rs[now];
            still = rs[still];
            l = mid + 1;
        }
        else
        {
            rs[now] = rs[still];ls[now] = ++cnt;
            sum[ ls[now] ] = sum[ ls[still] ] + 1;
            now = ls[now];
            still = ls[still];
            r = mid;
        }
    }
}

inline int query(int a, int b, int l, int r, int k)
{
    if(l == r) return l;
    int lm = sum[ls[b]] - sum[ls[a]];
    int mid = (l + r) >> 1;
    if(k <= lm) return query(ls[a], ls[b], l, mid, k);
    return query(rs[a], rs[b], mid + 1, r, k - lm);
}

signed main()
{
    n = read(), Q = read();
    for(R int i = 1; i <= n; i++) a[i] = read(), b[i] = a[i];
    sort(b + 1, b + 1 + n);
    m = unique(b + 1, b + 1 + n) - b - 1;
    T[0] = Build(1, m);
    for(R int i = 1; i <= n; i++)
    {
        int loc = lower_bound(b + 1, b + 1 + m, a[i]) - b;
        Build_new(i, loc);
    }
    for(R int i = 1; i <= Q; i++)
    {
        x =read(), y=read(), k=read();
        printf("%d\n", b[query(T[x - 1], T[y], 1, m, k)]);
    }
    return 0;
}
