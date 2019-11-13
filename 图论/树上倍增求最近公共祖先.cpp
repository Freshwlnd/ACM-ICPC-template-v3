const int maxn(1e5 + 5);
struct node {
    int t;//记录能到达的节点
    int nex;//记录边标号
}e[maxn << 1];//记录所有的边信息
//  深度          倍增的父节点        以2为底i的对数
int depth[maxn], father[maxn][22], lg[maxn], head[maxn];//head[i]表示以i为一个端点的最后一条边的序号
int tot;
inline void add(int x, int y)//加边,最终记录某一节点的所有父子节点
{
    e[++tot].t = y;//对于第tot条边记录信息，t信息表示能到达y节点
    e[tot].nex = head[x];//nex信息记录对于x节点能到达的所有节点的边序号。
    head[x] = tot;//修改x节点能到达的所有节点的边序号，记录一定是x节点能到的最后一个输入的节点。
}
inline void dfs(int now, int fath)
{
    depth[now] = depth[fath] + 1;//深度是父节点深度+1
    father[now][0] = fath;
    for (register int i = 1; (1 << i) <= depth[now]; ++i)
        father[now][i] = father[father[now][i - 1]][i - 1];
    for (register int i = head[now]; i; i = e[i].nex)//遍历now节点的所有父子节点
    {
        if (e[i].t != fath)dfs(e[i].t, now);//对于所有子节点进行dfs
    }
}
inline int lca(int x, int y)
{
    if (depth[x] < depth[y])//令x深度较大
        swap(x, y);
    while (depth[x] > depth[y])//将x深度处理成和y一样
        x = father[x][lg[depth[x] - depth[y]] - 1];
    if (x == y)//判断y是否是x的父节点
        return x;
    for (register int k = lg[depth[x]]; k >= 0; --k)//开始倍增，如果父节点不同就可以倍增网上走，相同不能走(可能走过头)
        if (father[x][k] != father[y][k])
            x = father[x][k], y = father[y][k];
    return father[x][0];
}
int n, m, s;
int main()
{
    scanf("%d%d%d", &n, &m, &s);//n个节点,m个询问,s为根节点
    for (register int i = 1; i <= n - 1; ++i)
    {
        int x, y; scanf("%d%d", &x, &y);
        add(x, y); add(y, x);
    }
    dfs(s, 0);
    for (register int i = 1; i <= n; ++i)
        lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
    for (register int i = 1; i <= m; ++i)
    {
        int x, y; scanf("%d%d", &x, &y);
        printf("%d\n", lca(x, y));
    }
    return 0;
}
