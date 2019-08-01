//网络流_最大流_EK
const int MAXN(2e5+7);  //两倍边数
const int INF(0x3fff);

int N, M, S, T;		//bfs用到N，需设为点总数
int marked[MAXN];   //若未访问则记为0，访问过则记为其上一个点
int path[MAXN];
int flow[MAXN];     //记录到第i个点的水流量
int outt;           //答案
struct Edge {
    int v, w, nxt; //连接点、容量、反向边编号
} edge[MAXN];   //记录所有边
int cnt = 2;    //必须从偶数开始
int head[MAXN]; //记录每个点第一条边

void addEdge(int u, int v, int w) {
    //正向边
    edge[cnt].v = v; edge[cnt].w = w; edge[cnt].nxt = head[u]; head[u] = cnt++;
    //反向边，正向边与反向边的编号只有最后一位不同（二进制下）
    edge[cnt].v = u; edge[cnt].w = 0; edge[cnt].nxt = head[v]; head[v] = cnt++;
}

int bfs() {
    queue<int> qqq;
    int tmp;

    for(int i=1; i<=N; i++) {
        marked[i] = 0;
    }
    marked[S] = S;
    flow[S] = INF;
    flow[T] = 0;
    qqq.push(S);

    while(!qqq.empty()) {
        tmp = qqq.front();
        qqq.pop();
        if(tmp==T) {
            outt += flow[tmp];
            break;
        }
        for (int i = head[tmp]; i; i=edge[i].nxt) { //i为边号
            if(edge[i].w && !marked[edge[i].v]) {
                marked[edge[i].v] = tmp;
                path[edge[i].v] = i;
                flow[edge[i].v] = min(flow[tmp], edge[i].w);
                qqq.push(edge[i].v);                //push点号
            }
        }
    }
    if(marked[T]) {
        for(int it=T; it!=S; it=marked[it]) {   //it为点号
            edge[path[it]].w -= flow[T];
            edge[path[it]^1].w += flow[T];
        }
    }

    return flow[T];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    //input
    cin >> N >> M >> S >> T;
    int u, v, w;
    for(int i=0; i<M; i++) {
        cin >> u >> v >> w;
        addEdge(u, v, w);
    }

    //solve
    while(bfs());

    cout << outt << endl;

    return 0;
}
