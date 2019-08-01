#define per(i, a, b) for(int i=a; i<b; i++)
#define rep(i, a, b) for(int i=b-1; i>=a; i--)
#define mem(a, b) memset(a, b, sizeof(b))

const int MAXN(1e2+7);
const int MAXM(1e5+7);
const int INF(0x3f3f3f3f);
int n;

int mapp[MAXN][MAXN];
int len[MAXN];    //Dijkstra & SPFA & Bellman_Ford
int vis[MAXN];    //Dijkstra & SPFA

//Dijkstra
void Dijkstra(int u) {
    mem(vis, 0);
    mem(len, 0x3f);
    vis[u] = 1;
    len[u] = 0;

    per(i, 1, n) {
        int mp = u, mm = INF;
        per(j, 1, n + 1) {
            if (!vis[j]) {
                len[j] = min(len[j], mapp[u][j] + len[u]);
                if (len[j] < mm) {
                    mm = len[j];
                    mp = j;
                }
            }
        }
        u = mp;
        vis[u] = 1;
    }
}

//Floyd
void Floyd() {
    per(k, 1, n+1) per(i, 1, n+1) per(j, 1, n+1)
    mapp[i][j] = min(mapp[i][j], mapp[i][k] + mapp[k][j]);
}


//Bellman_Ford
//可以判断负环
int m;
int u[MAXM], v[MAXM], w[MAXM];
void Bellman_Ford(int s) {
    mem(len, 0x3f);
    len[s] = 0;

    per(i,1,n) {            //一条最短路最多经过n-1条边
        int cg=1;           //标记本轮是否有修改，无修改则说明达到最终状态(优化)
        per(j,0,m) {
            if (len[v[j]] > len[u[j]] + w[j]) {
                len[v[j]] = len[u[j]] + w[j];
                cg = 0;
            }
        }
        if(cg) break;
    }

    //判断是否存在负环
    int cg = 0;
    per(i,0,m) {
        if(len[v[i]]>len[u[i]]+w[i]) {
            cg = 1;
            break;
        }
    }
    if(cg) {
        //存在负环
    }
}

//SPFA
//跑得快(是Bellman-Ford的优化版本)
//会被恶意数据卡掉，若无负权边，优先用Dijkstra
//能计算负权图
//可以判断负环
queue<int> Q;
int SPFA(int s) {
    //初始化
    mem(len, 0x3f);
    mem(vis, 0);
    vis[s] = 1;
    len[s] = 0;
    Q.push(s);

#ifdef 判负环
    //记录更新次数
    int cntn[MAXN];
    mem(cntn, 0);
    cntn[s] = 1;
#endif

    //队列操作
    while (!Q.empty()) {
        s = Q.front();
        Q.pop();
        vis[s] = 0;
        per (i, 1, n + 1) {
            if (len[i] > len[s] + mapp[s][i]) {
                len[i] = len[s] + mapp[s][i];
                if(!vis[i]) {

#ifdef 判负环
                    if(++cntn[s]>n) { return 1; }   //存在负环
#endif

                    Q.push(i);
                    vis[i] = 1;
                }
            }
        }
    }
    return 0;
}