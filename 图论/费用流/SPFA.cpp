#define per(i, a, b) for(int i=a; i<b; i++)
#define rep(i, a, b) for(int i=b-1; i>=a; i--)
using namespace std;
typedef long long ll;

//网络流_费用流_SPFA
const int INF(0x3f3f3f3f);
const int MAXN(5e3+7);
const int MAXM(5e4+7);

class MCMS_SPFA {
public:
    int N, S, T;
    int head[MAXN], nxt[2*MAXM], To[2*MAXM];    //存每个点最后一条边, 每条边的前一条边,每条边连接的另一个点
    ll Val[2*MAXM], Fee[2*MAXM];                //存每条边的权重,每条边的费用
    int cntedg;                                 //边数
    ll dis[MAXN], floww[MAXN];              //SPFA中 点的距离，该点的流量
    int vis[MAXN], pre[MAXN], last[MAXN];   //SPFA中 是否被访问，指向该点的边，上一个点
    queue<int> qq;                  //SPFA中 队列
    ll maxflow, mincost;    //存最大流，最小费

public:
    MCMS_SPFA(int _N=0, int _S=0, int _T=0): N(_N), S(_S), T(_T) {
        cntedg = 1;
        per(i, 1, N+1) {
            vis[i] = head[i] = 0;
        }
    }
    inline void _Add(int u, int v, ll w, ll f) {
        nxt[++cntedg] = head[u];
        To[cntedg] = v;
        Val[cntedg] = w;
        Fee[cntedg] = f;
        head[u] = cntedg;
    }
    inline void addEdge(int u, int v, ll w, ll f) {
        _Add(u, v, w, f);
        _Add(v, u, 0, -f);
    }
    inline int SPFA() {
        per(i, 1, N+1) dis[i] = INF;
        qq.push(S);
        floww[S] = INF; vis[S] = 1; dis[S] = 0; pre[T] = -1;

        int tmp;
        while(!qq.empty()) {
            tmp = qq.front();qq.pop();vis[tmp]=0;
            for(int i=head[tmp]; i; i=nxt[i]) {
                if(Val[i] && dis[To[i]]>dis[tmp]+Fee[i]) {
                    floww[To[i]] = min(floww[tmp], Val[i]);
                    dis[To[i]]=dis[tmp]+Fee[i];
                    pre[To[i]] = i;
                    last[To[i]] = tmp;
                    if(!vis[To[i]]) {
                        vis[To[i]] = 1;
                        qq.push(To[i]);
                    }
                }
            }
        }
        return pre[T]!=-1;
    }
    inline void mcms() {
        maxflow = mincost = 0;
        while(SPFA()) {                 //判断是否有边能走
            int noww=T;
            maxflow += floww[T];
            mincost += floww[T]*dis[T];
            while(noww!=S) {            //从T一直到S
                Val[pre[noww]^1] += floww[T];
                Val[pre[noww]] -= floww[T];
                noww = last[noww];
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
    MCMS_SPFA MS(N, S, T);

    int u, v;
    ll w, f;
    for(int i=0; i<M; i++) {
        cin >> u >> v >> w >> f;
        MS.addEdge(u, v, w, f);
    }

    MS.mcms();

    cout << MS.maxflow << ' ' << MS.mincost << endl;

    return 0;
}
