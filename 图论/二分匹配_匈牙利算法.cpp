const int N(100);       //人数
const int M(10000);     //边数

int match[N];
bool vis[N];

int head[N];        //某点的第一条边
int vp[M], nxt[M];  //vp指向的点  nxt下一条边
int top;

inline void add(int u, int v) {
    vp[top] = v;
    nxt[top] = head[u];
    head[u] = top++;
}

int maxmatch(int u) {
    int v;
    for (int j = head[u]; j; j = nxt[j]) {//找u的所有邻接边
        v = vp[j];//u的邻接点v
        if (!vis[v]) {
            vis[v] = 1;
            if (!match[v] || maxmatch(match[v])) {
                match[u] = v;
                match[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    int n1, n2, num = 0;
    int u, v;

    //init
    mem(head, -1);
    mem(match, 0);
    top = 0;

    //输入女推销员人数n1和男推销员人数n2
    cin >> n1 >> n2;
    //输入可以配合的女推销员编号u和男推销员编号v(两个都为-1结束)
    while (cin >> u >> v && u + v != -2) {
        add(u, v);
        add(v, u);
    }
    per (i, 1, n1+1) {
        mem(vis, 0);
        if (maxmatch(i))
            num++;
    }
    //最大配对数: num
    cout << num << endl;
    //配对方案：第i个人匹配情况存在match[i]中

    return 0;
}