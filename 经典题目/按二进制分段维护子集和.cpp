// 题面：
//    N个数字，Q个询问，每个询问为以下两种操作：
//        1. 将x改为y
//        2. 查询[x, y]中 最小的 不与[x,y]的任一子集的和相等的 整数

//    考虑某一个数字K是否是答案时，有以下两个定理：
//        1. [1,K)每个数字必然都是子集和，否则考虑不到K
//        2. 令（小于该数字的每个集合中的数字）的和为sm，x为min(sm,K-1), 则[1,x]都是子集和（由于任意y<=x都能取到,故x-y的答案集为[1,x]的全集）

//    因此对[L,R]中的排好序后的数字，令i从1到len，当 前缀和sm[i-1]+1<num[i] 时，sm[i-1]+1即为答案

//    本题的巧妙之处在于 按二进制最高位所在位数 将数字分段，当考虑到第i段时，只要该段中存在任一数字x，则[x,1<<i)都必然可行

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN(2e5+7);
const int INF(0x3f3f3f3f);
#define per(i, a, b) for(int i=a; i<b; i++)

#ifdef ONLINE_JUDGE
#define endl '\n'
#endif

int N, Q;
int a[MAXN];
int mn[MAXN<<2][25];
ll sm[MAXN<<2][25];

inline void PushUp(int rt) {
    per(i, 0, 20) {
        mn[rt][i] = min(mn[rt<<1][i], mn[rt<<1|1][i]);
        sm[rt][i] = sm[rt<<1][i]+sm[rt<<1|1][i];
    }
}

inline void Build(int l, int r, int rt) {
    if(l==r) {
        int tmp=a[l], len=-1;
        while(tmp) {len++, tmp>>=1;}
        per(i, 0, 20) mn[rt][i]=INF, sm[rt][i]=0;
        mn[rt][len]=a[l];
        per(i, len, 20) sm[rt][i] = a[l];
        return;
    }
    int mid = (l+r)>>1;
    Build(l, mid, rt<<1);
    Build(mid+1, r, rt<<1|1);
    PushUp(rt);
}

inline void Modify(int L, int C, int l, int r, int rt) {
    if(l==r) {
        a[l] = C;
        int tmp=a[l], len=-1;
        while(tmp) { len++, tmp>>=1; }
        per(i, 0, 20) mn[rt][i]=INF, sm[rt][i]=0;
        mn[rt][len]=a[l];
        per(i, len, 20) sm[rt][i] = a[l];
        return;
    }
    int mid = (l+r)>>1;
    if(L<=mid) Modify(L, C, l, mid, rt<<1);
    else Modify(L, C, mid+1, r, rt<<1|1);
    PushUp(rt);
}

int ansmn[20];
ll anssm[20];

inline void Query(int L, int R, int l, int r, int rt) {
    if(L<=l && r<=R) {
        per(i, 0, 20) {
            ansmn[i] = min(ansmn[i], mn[rt][i]);
            anssm[i] += sm[rt][i];
        }
        return;
    }
    int mid = (l+r)>>1;
    if(L<=mid) Query(L, R, l, mid, rt<<1);
    if(R>mid) Query(L, R, mid+1, r, rt<<1|1);
}

inline int Query(int L, int R) {
    per(i, 0, 20) {
        ansmn[i] = INF;
        anssm[i] = 0;
    }
    Query(L, R, 1, N, 1);
    if(ansmn[0]!=1) return 1;
    per(i, 1, 21) {
        if(ansmn[i]>anssm[i-1]+1) {
            return anssm[i-1]+1;
        }
    }
    return 0;
}

int main() {

    freopen("../1.in", "r", stdin);

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> Q;
    per(i, 1, N+1) { cin >> a[i]; }

    Build(1, N, 1);
    while(Q--) {
        int op, x, y;
        cin >> op >> x >> y;
        if(op==1) {
            Modify(x, y, 1, N, 1);
        } else {
            cout << Query(x, y) << endl;
        }
    }

    return 0;
}
