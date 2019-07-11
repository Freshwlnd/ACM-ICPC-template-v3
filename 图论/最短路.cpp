const int MAXN(1e4+7);
const int INF(0x3f3f3f3f);
int n;

int mapp[MAXN][MAXN];
int len[MAXN];    //Dijkstra & SPFA

//Dijkstra
bool vis[MAXN];
void Dijkstra(int u) {
    mem(vis, 0);
    mem(len, 0x3f);
    vis[u] = 1;
    len[u] = 0;

    per(i, 1, n) {
        per(j, 1, n + 1) {
            if (len[j] > mapp[u][j] + len[u]) {
                len[j] = mapp[u][j] + len[u];
            }
        }
        int mp = u, mm = INF;
        per(j, 1, n + 1) {
            if (!vis[j] && len[j] < mm) {
                mm = len[j];
                mp = j;
            }
        }
        u = mp;
        vis[u] = 1;
    }
}

//Floyd
void Floyd() {
    per(k, 1, n+1) per(i, 1, n+1) per(j, 1, n+1)
    if (mapp[i][j] > mapp[i][k] + mapp[k][j])
        mapp[i][j] = mapp[i][k] + mapp[k][j];
}

//SPFA
queue<int> Q;

void SPFA(int pos) {
    //初始化
    mem(len, 0x3f);
    len[pos] = 0;
    Q.push(pos);
    //队列操作
    int v;
    while (!Q.empty()) {
        v = Q.front();
        Q.pop();
        per (i, 1, n + 1) {
            if (len[i] > mapp[v][i] + len[v]) {
                len[i] = mapp[v][i] + len[v];
                Q.push(i);
            }
        }
    }
}
