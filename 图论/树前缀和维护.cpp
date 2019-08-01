//使用树链剖分将树切割为链之后，用前缀和的思想更新
//更新操作
inline void Update(int u, int v, ll w) {
    //保证u<v
    summ[u] += w;
    summ[v+1] -= w;
}
//最终操作
for(int i=1; i<=N; i++) {
    summ[i] += summ[i-1];
}
//sum[i]即为：剖分序第i个点/边的权值
