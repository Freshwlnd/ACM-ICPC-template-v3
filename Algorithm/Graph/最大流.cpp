//最大流.cpp

//EK算法模板（s为源点，t为汇点，函数返回值为最大流）
//e为邻接矩阵
//p储存路径，a用来计算路径
int EK(int s,int t)  
{  
    queue<int> q;  
    int p[MAXN*2],a[MAXN*2];  
    int f=0;  
    while(1)  
    {  
        memset(a,0,sizeof(a));  
        a[s]=inf;  
        q.push(s);  
        while(!q.empty())  
        {  
            int u=q.front();  
            q.pop();  
            for(int v=0; v<=t; ++v)  
                if(!a[v]&&flow[u][v])  
                {  
                    p[v]=u,q.push(v);  
                    a[v]=min(a[u],flow[u][v]);  
                    if(v==t) break;  
                }  
        }  
        if(a[t]==0) break;  
        for(int u=t; u!=s; u=p[u])  
        {  
            flow[p[u]][u]-=a[t];  
            flow[u][p[u]]+=a[t];  
        }  
        f+=a[t];  
    }  
    return f;  
}  
