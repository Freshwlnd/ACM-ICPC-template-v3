//构建[L,R]区间的最大根笛卡尔树

int numm[MAXN];
int stk[MAXN], topp;
int ls[MAXN], rs[MAXN], fa[MAXN];
inline void build(int L, int R) {   //构建[L,R]区间的最大根笛卡尔树
    topp = 0;
    per(i, L, R+1) {
        fa[i] = ls[i] = rs[i] = 0;
        while(numm[stk[topp]] < numm[i]) ls[i] = stk[topp--];
        fa[i] = stk[topp];
        fa[ls[i]] = i;
        rs[fa[i]] = i;
        stk[++topp] = i;
    }
}
