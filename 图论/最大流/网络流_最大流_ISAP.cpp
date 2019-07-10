//网络流_最大流_ISAP(Improved Shortest Augumenting Path）
const ll INF(0x3f3f3f3f3f3f3f3f);

class ISAP {
public:
    int N, S, T;
    vector<int> head;   //存每个点最后一条边
    vector<int> depth;  //存每次bfs后每个点的深度
    vector<int> gap;
    vector<int> nxt;    //存每条边的前一条边
    vector<int> To;     //存每条边连接的另一个点
    vector<ll> Val;    //存每条边的权重
    ll outt;           //存最大流

public:
    ISAP(int Nn=0, int Ss=0, int Tt=0): N(Nn), S(Ss), T(Tt) {
        head.assign(N+1, 0);
        depth.assign(N+1, 0);
        gap.assign(N+3, 0); //depth[S]被置为N+1后还可能被+1，故最大为N+2
        Val.resize(2);
        To.resize(2);
        nxt.resize(2);
    }
    void _Add(int u, int v, ll w) {
        nxt.push_back(head[u]);
        head[u] = To.size();
        To.push_back(v);
        Val.push_back(w);
    }
    void addEdge(int u, int v, ll w) {
        _Add(u, v, w);
        _Add(v, u, 0);
    }
    void bfs() {    //标记每个点到T的最短距离
        queue<int> qq;
        qq.push(T);
        depth[T] = 1;
        int tmp;

        while(!qq.empty()) {
            tmp = qq.front();
            qq.pop();
            gap[depth[tmp]]++;
            for(int i=head[tmp]; i; i=nxt[i]) {
                if(!depth[To[i]]) {
                    depth[To[i]] = depth[tmp]+1;
                    qq.push(To[i]);
                }
            }
        }
    }
    int dfs(int pos, ll val) {
        if(pos==T) {
            outt += val;
            return val;
        }
        int dv = 0;
        for(int i=head[pos]; i; i=nxt[i]) {
            if(Val[i] && depth[To[i]]==depth[pos]-1) {
                ll valu = dfs(To[i], min(val, Val[i]));
                if(valu) {
                    Val[i] -= valu;
                    Val[i^1] += valu;
                    dv += valu;
                    val -= valu;
                }
                if(!val) return dv;
            }
        }
        //若还没return，说明还剩流量用不完
        //此时修改depth
        if(!--gap[depth[pos]]) {  //若该深度点不存在，即出现断层，则终止遍历
            depth[S] = N+1;     //设置终止标志
        }
        ++gap[++depth[pos]];
        return dv;
    }
    void isap() {
        outt = 0;
        bfs();
        while (depth[S]<=N) {
            dfs(S, INF);
        }
    }
};

int N, M, S, T;
int u, v;
ll w;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> S >> T;
    ISAP dd(N, S, T);

    for (int i = 0; i < M; i++) {
        cin >> u >> v >> w;
        dd.addEdge(u, v, w);
    }

    dd.isap();
    cout << dd.outt << endl;


    return 0;
}