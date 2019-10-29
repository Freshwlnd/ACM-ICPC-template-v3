typedef long long ll;
#define per(i,a,n) for (int i=a;i<n;i++)
#define w(i) T[(i)].w
#define ls(i) T[(i)].ls
#define rs(i) T[(i)].rs
const int MAXN(1e5+7);

int N, Q;
int L[MAXN], R[MAXN];

struct node{
    int ls,rs;                  //左儿子，右儿子
    ll w;                       //下面点数
    node(){ls=rs=w=0;}
}T[MAXN*20];
ll a[MAXN],b[MAXN],p[MAXN];     //原始数据，离散化后点值，离散化过程数组
int root[MAXN],sz;      //第i棵树根节点，总点数
//插入
void ins(int &i,int l,int r,int x){
    T[++sz]=T[i]; i=sz;
    w(i)++;
    if (l==r) return;
    int m=(l+r)>>1;
    if (x<=m) ins(ls(i),l,m,x);
    else ins(rs(i),m+1,r,x);
}
//查询区间[l, r] 第k小（第1小表示最小）
//query(root[l-1], root[r], 1, N, k);
int query(int i,int j,int l,int r,int k) {
    if (l==r) return l;
    int t=w(ls(j))-w(ls(i));
    int m=(l+r)>>1;
    if (t>=k) return query(ls(i),ls(j),l,m,k);
    else return query(rs(i),rs(j),m+1,r,k-t);
}

int main() {

    while(cin >> N >> Q) {      //N个点，Q个询问

        //离散化
        per(i, 1, N+1) { cin>>a[i]; p[i]=i; }
        sort(p+1, p+1+N, [](int i, int j) {return a[i]<a[j];});
        per(i, 1, N+1) { b[p[i]] = i; }
        //离散化结束

        root[0]=0;
        sz=0;
        per(i, 1, N+1) {
            root[i]=root[i-1];
            ins(root[i], 1, N, b[i]);
        }

    }

    return 0;
}
