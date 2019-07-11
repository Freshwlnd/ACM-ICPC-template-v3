#define per(i, a, b) for(int i=a; i<b; i++)
#define rep(i, a, b) for(int i=b-1; i>=a; i--)
#define mem(a, b) memset(a, b, sizeof(a))

const int MAXN(107);
const int INF(0x3f3f3f3f);


int mapp[MAXN][MAXN];
int n;                  //点数
int outt;               //记录路径权值和

int prim(int s) {
    int vis[MAXN];      //记录是否已在点集中
    int len[MAXN];      //记录到当前点集距离
    mem(vis, 0);
    mem(len, 0x3f);
    vis[s] = 1;

    per(i, 1, n) {
        int mm=INF, mp;
        per(j, 1, n+1) {
            if(!vis[j] && mm>(len[j]=min(len[j],mapp[s][j]))) {
                mm = len[j];
                mp = j;
            }
        }
        if(mm==INF) {
            return 0;       //非联通图
        }
        outt += mm;
        s = mp;
        vis[s] = 1;
    }
    return 1;

}