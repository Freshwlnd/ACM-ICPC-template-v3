//网络流_最大流_Dinic
const ll INF(0x3f3f3f3f3f3f3f3f);

class Dinic {
public:
    int N, S, T;
    vector<int> head;   //存每个点最后一条边
    vector<int> cur;    //当前弧优化，进一步加速
    vector<int> depth;  //存每次bfs后每个点的深度
    vector<int> nxt;    //存每条边的前一条边
    vector<int> To;     //存每条边连接的另一个点
    vector<ll> Val;    //存每条边的权重
    ll outt;           //存最大流

public:
    Dinic(int Nn=0, int Ss=0, int Tt=0): N(Nn), S(Ss), T(Tt) {
        head.assign(N+1, 0);
        depth.resize(N+1);
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
    int bfs() {
        queue<int> qq;
        qq.push(S);
        vector<int> marked;
        marked.assign(N+1, 0);
        marked[S] = 1;
        marked[T] = depth[S] = 0;
        int tmp;

        while(!qq.empty()) {
            tmp = qq.front();
            qq.pop();
            for(int i=head[tmp]; i; i=nxt[i]) {
                if(Val[i] && !marked[To[i]]) {
                    marked[To[i]] = 1;
                    depth[To[i]] = depth[tmp]+1;
                    qq.push(To[i]);
                }
            }
        }
        if(marked[T]) {
            return 1;
        }
        return 0;
    }
    int dfs(int pos, ll val) {
        if(pos==T) {
            return val;
        }
        for(int& i=cur[pos]; i; i=nxt[i]) {     //利用当前弧，&饮用保证当前弧能被修改
            if(Val[i] && depth[To[i]]==depth[pos]+1) {
                ll valu = dfs(To[i], min(val, Val[i]));
                if(valu) {
                    Val[i] -= valu;
                    Val[i^1] += valu;
                    return valu;
                }
            }
        }
        return 0;
    }
    void dinic() {
        outt = 0;
        while(bfs()) {
            cur = head;     //赋值当前弧
            ll val;
            while((val=dfs(S, INF))) {
                outt += val;
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int N, M, S, T;
    cin >> N >> M >> S >> T;
    Dinic DD(N, S, T);

    int u, v;
    ll w;
    for(int i=0; i<M; i++) {
        cin >> u >> v >> w;
        DD.addEdge(u, v, w);
    }

    DD.dinic();

    cout << DD.outt << endl;

    return 0;
}
