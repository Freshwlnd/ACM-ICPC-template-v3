#if 0
//美妙袜子
·述大意：

     进行区间询问[l,r]，输出该区间内随机抽两次抽到相同颜色袜子的概率。

·分析：

     首先考虑对于一个长度为n区间内的答案如何求解。题目要求Ans使用最简分数表示：那么分母就是n*n(表示两两袜子之间的随机组合)，分子是一个累加和，累加的内容是该区间内每种颜色i出现次数sum[i]的平方。

     莫队算法的思路是，离线情况下对所有的询问进行一个美妙的SORT()，然后两个指针l,r（本题是两个，其他的题可能会更多）不断以看似暴力的方式在区间内跳来跳去，最终输出答案。

     掌握一个思想基础：两个询问之间的状态跳转。如图，当前完成的询问的区间为[a,b],下一个询问的区间为[p,q],现在保存[a,b]区间内的每个颜色出现次数的sum[]数组已经准备好，[a,b]区间询问的答案Ans1已经准备好，怎样用这些条件求出[p,q]区间询问的Ans2？

    [图片](https://images2015.cnblogs.com/blog/1101338/201706/1101338-20170602160314727-1451291019.png)

    l指针向右移动一个单位，所造成的后果就是：我们损失了一个绿色方块。那么怎样维护？美妙地，sum[绿色]减去1。那Ans如何维护？先看分母，分母从n2变成(n-1)2，分子中的其他颜色对应的部分是不会变的，绿色却从sum[绿色]2变成(sum[绿色]-1)2 ，为了方便计算我们可以直接向给Ans减去以前该颜色的答案贡献(即sum[绿色]2)再加上现在的答案贡献(即(sum[绿色]-1)2 )。

    ·回归正题地，我们美妙的发现，知道一个区间的信息，要求出旁边区间的信息（旁边区间指的是当前区间的一个指针通过加一减一得到的区间），竟只需要O(1)的时间。

    ·就算是这样，到这里为止的话莫队算法依旧无法焕发其光彩，原因是：如果我们以读入的顺序来枚举每个询问，每个询问到下一个询问时都用上述方法维护信息，那么在你脑海中会浮现出l,r跳来跳去的疯狂景象，疯狂之处在于最坏情况下时间复杂度为：O(n2)————如果要这样玩，那不如写一个暴力程序。

    ·“莫队算法巧妙地将询问离线排序，使得其复杂度无比美妙……”在一般做题时我们时常遇到使用排序来优化枚举时间消耗的例子。莫队的优化基于分块思想：对于两个询问，若在其l在同块，那么将其r作为排序关键字，若l不在同块，就将l作为关键字排序（这就是双关键字）。大米饼使用Be[i]数组表示i所属的块是谁。
    
    
    
#endif

#include <bits/stdc++.h>
#define per(i,a,n) for (int i=a;i<n;i++)
#define rep(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mem(a, b) memset(a, b, sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pI;
typedef vector<ll> vI;
const ll mod(1e9 + 7);
const ll INF(0x3f3f3f3f);
ll powmod(ll a, ll b) { ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) { if (b & 1)res = res * a%mod; a = a * a%mod; }return res; }
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
// head

const int N = 50003;
struct Mo {
    int l, r, ID;
    ll A, B;
}q[N];
ll S(ll x) { return x * x; }

int n, m, col[N], unit, Be[N];
ll sum[N], ans;
bool cmp(Mo a, Mo b) { return Be[a.l] == Be[b.l] ? a.r<b.r : a.l<b.l; }
bool CMP(Mo a, Mo b) { return a.ID<b.ID; }
void revise(int x, int add) {
    ans -= S(sum[col[x]]);
    sum[col[x]] += add;
    ans += S(sum[col[x]]); }

int main() {
     //读入+分块
    scanf("%d%d", &n, &m);
    unit = sqrt(n);
    per(i, 1, n+1) {
        scanf("%d", &col[i]);
        Be[i] = i / unit + 1;
    }
     //离线读入查询
    per(i, 1, m+1) {
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].ID = i;
    }
     //排序查询
    sort(q + 1, q + m + 1, cmp);
     //遍历查询
    int l = 1, r = 0;
    per(i, 1, m+1) {
         //莫队指针移动
        while (l<q[i].l) {revise(l, -1); l++;}
        while (l>q[i].l) {revise(l - 1, 1); l--;}
        while (r<q[i].r) {revise(r + 1, 1); r++;}
        while (r>q[i].r) {revise(r, -1); r--;}
         //查询的答案设置
        if (q[i].l == q[i].r) { q[i].A = 0; q[i].B = 1; continue; }
        q[i].A = ans - (q[i].r - q[i].l + 1);
        q[i].B = 1LL * (q[i].r - q[i].l + 1)*(q[i].r - q[i].l);
        ll GCD = gcd(q[i].A, q[i].B);
        q[i].A /= GCD;
        q[i].B /= GCD;
    }
    //复原查询顺序并输出
    sort(q + 1, q + m + 1, CMP);
    per(i, 1, m) { printf("%lld/%lld\n", q[i].A, q[i].B); }
    return 0;
}
