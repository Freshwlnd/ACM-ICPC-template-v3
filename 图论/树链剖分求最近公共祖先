const int maxn=1e5+10;
struct edge{
    int next,to;
}e[maxn*2];
struct node{
    int l,r,ls,rs,sum,lazy;
}a[maxn*2];
int n,m,r,rt,mod,v[maxn],head[maxn],cnt,f[maxn],d[maxn],son[maxn],size[maxn],top[maxn],id[maxn],rk[maxn];

void dfs1(int u,int fa,int depth)    //当前节点、父节点、层次深度
{
    f[u]=fa;
    d[u]=depth;
    size[u]=1;    //这个点本身size=1
    for(int i=head[u];i;i=e[i].next)
    {
        int v=e[i].to;
        if(v==fa)
            continue;
        dfs1(v,u,depth+1);    //层次深度+1
        size[u]+=size[v];    //子节点的size已被处理，用它来更新父节点的size
        if(size[v]>size[son[u]])
            son[u]=v;    //选取size最大的作为重儿子
    }
}
void dfs2(int u,int t)    //当前节点、重链顶端
{
    top[u]=t;
    id[u]=++cnt;    //标记dfs序
    rk[cnt]=u;    //序号cnt对应节点u
    if(!son[u])
        return;
    dfs2(son[u],t);
/*我们选择优先进入重儿子来保证一条重链上各个节点dfs序连续，
一个点和它的重儿子处于同一条重链，所以重儿子所在重链的顶端还是t*/
    for(int i=head[u];i;i=e[i].next)
    {
        int v=e[i].to;
        if(v!=son[u]&&v!=f[u])
            dfs2(v,v);    //一个点位于轻链底端，那么它的top必然是它本身
    }
}
int sum(int x,int y)
{
    int ans=0,fx=top[x],fy=top[y];
    while(fx!=fy)    //两点不在同一条重链
    {
        if(d[fx]>=d[fy])
        {
            ans+=query(id[fx],id[x],rt);    //线段树区间求和，处理这条重链的贡献
            x=f[fx],fx=top[x];    //将x设置成原链头的父亲结点，走轻边，继续循环
        }
        else
        {
            ans+=query(id[fy],id[y],rt);
            y=f[fy],fy=top[y];
        }
    }
    //循环结束，两点位于同一重链上，但两点不一定为同一点，所以我们还要统计这两点之间的贡献
    if(id[x]<=id[y])
        ans+=query(id[x],id[y],rt);
    else
        ans+=query(id[y],id[x],rt);
    return ans;
}

int main() {
    //进入
    dfs1(root,0,1);
}
