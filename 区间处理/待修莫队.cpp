#pragma warning(disable:4996)
//题目：hdoj6610 http://acm.hdu.edu.cn/showproblem.php?pid=6610
//题意：在一堆石子中玩Nim博弈。但是Alice会先选择一个区间[L,R]，Bob在这个区间内选择一个子区间[l,r]，问在Alice选择的[L,R]内存在多少个子区间使得Alice必胜(Alice先行)
//Bob有权利在每次博弈开始前选择一个点，使该点和其后面那个点交换石堆数。即swap(a[i],a[i+1])

//根据Nim博弈区间异或和不为0那么就可以必胜，那么先统计必败。总共有(R-L+1)*(R-L+2)/2个子区间。
//考虑到每次都暴力计算会TLE，就需要优化一下。对于所有查询[L,R]没有强制在线可以考虑离线算法。
//但是因为有修改操作单独使用莫队是无法实现的。仔细思考题中修改操作，只影响了这两个点。
//现在我们要求在[L,R]中异或和为0的子区间个数，那么可以把问题转化成在[L,R]区间内相同前缀异或和相同的数对数。
//因为使用前缀和的原因其实应当统计[L - 1,R]区间内的对数
//那么现在Bob的修改其实只影响了pre[i](前缀异或和pre)的值
//单点修改可以使用待修莫队完成，以修改时间作为第三维度

//注意莫队对每一个维度都需要分块，二维莫队分块是pow(n,0.5),三维莫队分块应该是pow(n,2/3.0)。证明及学习链接：https://www.cnblogs.com/ouuan/p/MoDuiTutorial.html (感谢大佬的博客让我学会三维莫队)
#include<bits/stdc++.h>
#define upf(a,b,c) for(ll a=b;a<=c;++a)
#define drf(a,b,c) for(ll a=b;a>=c;--a)
#define mem(a,b) memset(a,b,sizeof(a))
#define Tcase(n) for(int _=1;_<=n;++_)
#define ll long long
#define ull unsigned long long
#define ShaShiBuGan int woyebuzhidaogaiganmasuoyishenmedoubugan=0;

#if 1
#define endl '\n'
#endif

const ll mod(1e9);
const int maxn(1e5 + 5);
const int INF(0x3fffffff);
const double sfive(sqrt(5));
using namespace std;
ll powmod(ll a, ll b) { ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) { if (b & 1)res = res * a % mod; a = a * a % mod; }return res; }
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll S(ll x) { return x * x; }
int T;
int n, m, a[maxn], unit, pre[maxn], l, r;
ll trueans[maxn], ans;
//sum维护了在[L,R]区间内每个数字出现次数，方便计算每一次的ans
int sum[1024 * 1024 + 5];//a[i]<=1e6最大异或和为1024*1024-1
//保存询问，离线排序
struct questions {
    int l, r, t, id, pos;
    bool operator < (const questions& a) {
        return l / unit == a.l / unit ? (r / unit == a.r / unit ? t < a.t : r < a.r) : l < a.l;
    }
}q[maxn];
vector<questions> v;//v中保存了每一次修改，记录为当前时间。
//右移指针
inline void add(int& x, int opt) {
    if (x == 0 && opt == 1) { x++; return; }//L从初始化的0移动到1时并没有减少东西(其实是因为pre初始化为0有问题，初始化为-1也需要特判)
    //l++
    if (opt == 1) {
        sum[pre[x]]--;
        ans -= sum[pre[x++]];
    }
    //r++
    else {
        ans += sum[pre[++x]];
        sum[pre[x]]++;//前缀和区间内a[x]出现次数
    }
}
//左移指针
inline void sub(int& x, int opt) {
    if (x == 1 && opt == 1) { x--; return; }//与右移指针同理，但是左移好像并没有用
    if (opt == 1) {
        ans += sum[pre[--x]];
        sum[pre[x]]++;
    }
    else {
        sum[pre[x]]--;
        ans -= sum[pre[x--]];
    }
}
//1往后推移状态，2往前推移状态
inline void modify(int& time, int opt) {
    if (opt == 1) time++;//向后推移状态需要先变成后面的时间
    int pos = v[time].id;
    if (l <= pos && pos <= r) {//修改点在当前[L,R]之前需要将修改影响结果减去
        //减去修改状态前的值
        sum[pre[pos]]--;
        ans -= sum[pre[pos]];
        //修改状态
        pre[pos] = pre[pos] ^ a[pos] ^ a[pos + 1];
        swap(a[pos], a[pos + 1]);
        //加上修改状态后的值
        ans += sum[pre[pos]];
        sum[pre[pos]]++;
    }
    //不影响就直接处理pre就行了
    else {
        pre[pos] = pre[pos] ^ a[pos] ^ a[pos + 1];
        swap(a[pos], a[pos + 1]);
    }
    if (opt == 2) time--;//向前移动状态需要先运算再左移时间
}
int main() {
#ifdef ACM_LOCAL
    freopen("./ACM.in", "r", stdin);
    freopen("./ACM.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    while (cin >> n >> m) {
        v.clear();
        v.push_back(q[0]);//空值
        unit = pow(n, 2 / 3.0);//初始化分块大小
        upf(i, 1, n) {
            cin >> a[i];
            pre[i] = pre[i - 1] ^ a[i];//求前缀和
        }
        int time = 0;
        upf(i, 1, m) {
            int op;
            cin >> op;
            //记录pos是因为只有op=1时才会输出答案，而q已经被排过序所以需要记录pos
            if (op == 1) {//op=1时为查询
                cin >> q[i].l >> q[i].r;
                q[i].t = time;
                q[i].id = 0;
                q[i].pos = i;
            }
            else {//op=2单点修改
                cin >> q[i].id;//Bob选择的点
                q[i].l = q[i].r = 0;
                q[i].t = ++time;
                q[i].pos = i;
                v.push_back(q[i]);
            }
        }
        sort(q + 1, q + 1 + m);
        //初始化
        l = 0, r = 0, ans = 0, time = 0;
        upf(i, 0, m)trueans[i] = -1;
        //sum[0] = 1;
        upf(i, 1, m) {
            //时间状态需要修改
            while (time < q[i].t)modify(time, 1);
            while (time > q[i].t)modify(time, 2);
            if (q[i].id != 0)//当前询问是Bob的修改的话不需要进行l和r的移动
                continue;
            while (r < q[i].r)add(r, 2);//右移函数
            while (r > q[i].r)sub(r, 2);//左移函数
            while (l < q[i].l)add(l, 1);
            while (l > q[i].l)sub(l, 1);
            ans += sum[pre[l - 1]];//计算上L-1这个点
            trueans[q[i].pos] = (ll)(r - l + 2) * (r - l + 1) / 2 - ans;
            ans -= sum[pre[l - 1]];//除去L-1这个点
        }
        upf(i, 1, m) {
            if (trueans[i] != -1) {//非修改需要输出
                cout << trueans[i] << '\n';
            }
        }
        //初始化sum
        upf(i, l, r) {
            sum[pre[i]]--;
        }
    }
}
