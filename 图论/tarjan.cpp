int dfn[MAXN], low[MAXN];               //新点号/子树最小节点号
int color[MAXN], stk[MAXN], vis[MAXN];  //颜色/栈/访问标记
int cnt, t, colorNm;                    //新点号/栈顶/颜色号
vector<int> ve[MAXN];                   //边

void tarjan(int now) {
    dfn[now] = low[now] = ++cnt;  //初始化
    stk[++t] = now; //入栈操作
    vis[now] = 1;    //v[]代表该点是否已入栈
    for (auto it: ve[now]) {  //邻接表存图
        if (!dfn[it]) { //判断该点是否被搜索过
            tarjan(it);
            low[now] = min(low[now], low[it]);
        } else if (vis[it])
            low[now] = min(low[now], dfn[it]);  //一旦遇到已入栈的点，就将该点作为连通量的根
                                                //这里用dfn[e[i].v]更新的原因是：这个点可能
                                                //已经在另一个强连通分量中了但暂时尚未出栈，所
                                                //以now不一定能到达low[e[i].v]但一定能到达
                                                // dfn[e[i].v].
    }
    if (low[now] == dfn[now]) {
        int cur;
        colorNm++;
        do {
            cur = stk[t--];
            color[cur] = colorNm;               //同一环标相同颜色
            vis[cur] = 0;                       //不要忘记出栈
        } while (now != cur);
    }
}
