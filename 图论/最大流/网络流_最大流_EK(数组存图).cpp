//网络流_最大流_EK
const int MAXN(1e3+7);
const int INF(0x3fff);

int N, M, S, T;
int mapp[MAXN][MAXN];
int outt;

struct Point {
    int pos, value;
    Point(int pp=0, int vv=0): pos(pp), value(vv) {}
};

int bfs() {
    queue<Point> qqq;
    Point tmp;
    int flag1 = 0;

    int marked[MAXN] = {};
    marked[S] = S;

    qqq.push(Point(S, INF));
    while(!qqq.empty()) {
        tmp = qqq.front();
        qqq.pop();
        if(tmp.pos==T) {
            outt += tmp.value;
            flag1 = tmp.value;
            break;
        }
        for (int i = 1; i<=N; i++) {
            if(mapp[tmp.pos][i] && !marked[i]) {
                marked[i] = tmp.pos;
                int dw = min(tmp.value, mapp[tmp.pos][i]);
                qqq.push(Point(i, dw));
            }
        }
    }
    if(flag1) {
        for(int it=T; it!=S;) {
            mapp[it][marked[it]] += flag1;
            mapp[marked[it]][it] -= flag1;
            it = marked[it];
        }
    }

    return flag1;
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
        mapp[u][v] += w;
    }

    //solve
    while(bfs());

    cout << outt << endl;

    return 0;
}
