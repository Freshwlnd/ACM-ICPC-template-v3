const int maxn(1e5 + 5);
struct node {
    int t;//��¼�ܵ���Ľڵ�
    int nex;//��¼�߱��
}e[maxn << 1];//��¼���еı���Ϣ
//  ���          �����ĸ��ڵ�        ��2Ϊ��i�Ķ���
int depth[maxn], father[maxn][22], lg[maxn], head[maxn];//head[i]��ʾ��iΪһ���˵�����һ���ߵ����
int tot;
inline void add(int x, int y)//�ӱ�,���ռ�¼ĳһ�ڵ�����и��ӽڵ�
{
    e[++tot].t = y;//���ڵ�tot���߼�¼��Ϣ��t��Ϣ��ʾ�ܵ���y�ڵ�
    e[tot].nex = head[x];//nex��Ϣ��¼����x�ڵ��ܵ�������нڵ�ı���š�
    head[x] = tot;//�޸�x�ڵ��ܵ�������нڵ�ı���ţ���¼һ����x�ڵ��ܵ������һ������Ľڵ㡣
}
inline void dfs(int now, int fath)
{
    depth[now] = depth[fath] + 1;//����Ǹ��ڵ����+1
    father[now][0] = fath;
    for (register int i = 1; (1 << i) <= depth[now]; ++i)
        father[now][i] = father[father[now][i - 1]][i - 1];
    for (register int i = head[now]; i; i = e[i].nex)//����now�ڵ�����и��ӽڵ�
    {
        if (e[i].t != fath)dfs(e[i].t, now);//���������ӽڵ����dfs
    }
}
inline int lca(int x, int y)
{
    if (depth[x] < depth[y])//��x��Ƚϴ�
        swap(x, y);
    while (depth[x] > depth[y])//��x��ȴ���ɺ�yһ��
        x = father[x][lg[depth[x] - depth[y]] - 1];
    if (x == y)//�ж�y�Ƿ���x�ĸ��ڵ�
        return x;
    for (register int k = lg[depth[x]]; k >= 0; --k)//��ʼ������������ڵ㲻ͬ�Ϳ��Ա��������ߣ���ͬ������(�����߹�ͷ)
        if (father[x][k] != father[y][k])
            x = father[x][k], y = father[y][k];
    return father[x][0];
}
int n, m, s;
int main()
{
    scanf("%d%d%d", &n, &m, &s);//n���ڵ�,m��ѯ��,sΪ���ڵ�
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
