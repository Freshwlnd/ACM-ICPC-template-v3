//在本地编译会出现数组太大的问题，交上去倒是没问题
typedef long long ll;
#define per(i,a,n) for (int i=a;i<n;i++)
#define rep(i,a,n) for (int i=n-1;i>=a;i--)

const int MAXN(3e5+7);
const int CharSetNum(26);   //字符集大小
const char ShouZiMu('a');   //首字母

struct Palindromic_Tree {
    int next[MAXN][CharSetNum];     //类似字典树的指向儿子的指针
    int fail[MAXN];                 //类似AC自动机的失配指针
    int cnt[MAXN];                  //Str中该回文串出现的次数
    int num[MAXN];                  //该字符串的后缀回文串个数
    int len[MAXN];                  //该回文串长度
    int S[MAXN];                    //第i次添加的字符
    int last;                       //当前最长回文串表示的节点
    int n;                          //已添加的字符个数
    int p;                          //已添加的节点个数
    inline int newnode(int _len) {  //新加一个长度为_len的节点，返回该节点位置
        per(i, 0, CharSetNum) next[p][i] = 0;
        cnt[p] = num[p] = 0;
        len[p] = _len;
        return p++;
    }
    inline void init() {    //初始化
        last=p=n=0;
        newnode(0);     //代表偶数回文串根节点
        newnode(-1);    //代表奇数回文串根节点
        S[0]=-1;            //令第一个字符为特殊字符，减少特判
        fail[0]=1;
    }
    inline int get_fail(int x) {     //寻找当前字符应当插入的位置
        while(S[n-len[x]-1] != S[n]) x=fail[x];     //若不能形成回文串则沿fail指针回退
        return x;
    }
    inline void add(int c) {
        c -= ShouZiMu;
        S[++n] = c;
        int cur = get_fail(last);   //寻找插入位置
        if(!next[cur][c]) {     //如果是新的本质不同的回文串
            int now = newnode(len[cur]+2);            //新建节点
            fail[now] = next[get_fail(fail[cur])][c];   //和AC自动机一样建立fail指针
            next[cur][c] = now;
            num[now] = num[fail[now]]+1;    //该字符串的后缀回文字符串个数
        }
        last = next[cur][c];
        cnt[last]++;    //该回文串出现次数+1
    }
    inline void count() {  //更新回文串cnt
        rep(i, 0, p) cnt[fail[i]] += cnt[i];    //父节点出现则一定有后缀回文串出现
    }
};

int main() {

    Palindromic_Tree PT;
    PT.init();                      //初始化
    string str;
    cin >> str;                     //读入字符串
    for(auto it: str) PT.add(it);   //建树
    PT.count();                     //处理cnt
    
    return 0;
}
