#pragma warning(disable:4996)
//��Ŀ��hdoj6610 http://acm.hdu.edu.cn/showproblem.php?pid=6610
//���⣺��һ��ʯ������Nim���ġ�����Alice����ѡ��һ������[L,R]��Bob�����������ѡ��һ��������[l,r]������Aliceѡ���[L,R]�ڴ��ڶ��ٸ�������ʹ��Alice��ʤ(Alice����)
//Bob��Ȩ����ÿ�β��Ŀ�ʼǰѡ��һ���㣬ʹ�õ��������Ǹ��㽻��ʯ��������swap(a[i],a[i+1])

//����Nim�����������Ͳ�Ϊ0��ô�Ϳ��Ա�ʤ����ô��ͳ�Ʊذܡ��ܹ���(R-L+1)*(R-L+2)/2�������䡣
//���ǵ�ÿ�ζ����������TLE������Ҫ�Ż�һ�¡��������в�ѯ[L,R]û��ǿ�����߿��Կ��������㷨��
//������Ϊ���޸Ĳ�������ʹ��Ī�����޷�ʵ�ֵġ���ϸ˼�������޸Ĳ�����ֻӰ�����������㡣
//��������Ҫ����[L,R]������Ϊ0���������������ô���԰�����ת������[L,R]��������ͬǰ׺������ͬ����������
//��Ϊʹ��ǰ׺�͵�ԭ����ʵӦ��ͳ��[L - 1,R]�����ڵĶ���
//��ô����Bob���޸���ʵֻӰ����pre[i](ǰ׺����pre)��ֵ
//�����޸Ŀ���ʹ�ô���Ī����ɣ����޸�ʱ����Ϊ����ά��

//ע��Ī�Ӷ�ÿһ��ά�ȶ���Ҫ�ֿ飬��άĪ�ӷֿ���pow(n,0.5),��άĪ�ӷֿ�Ӧ����pow(n,2/3.0)��֤����ѧϰ���ӣ�https://www.cnblogs.com/ouuan/p/MoDuiTutorial.html (��л���еĲ�������ѧ����άĪ��)
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
//sumά������[L,R]������ÿ�����ֳ��ִ������������ÿһ�ε�ans
int sum[1024 * 1024 + 5];//a[i]<=1e6�������Ϊ1024*1024-1
//����ѯ�ʣ���������
struct questions {
    int l, r, t, id, pos;
    bool operator < (const questions& a) {
        return l / unit == a.l / unit ? (r / unit == a.r / unit ? t < a.t : r < a.r) : l < a.l;
    }
}q[maxn];
vector<questions> v;//v�б�����ÿһ���޸ģ���¼Ϊ��ǰʱ�䡣
//����ָ��
inline void add(int& x, int opt) {
    if (x == 0 && opt == 1) { x++; return; }//L�ӳ�ʼ����0�ƶ���1ʱ��û�м��ٶ���(��ʵ����Ϊpre��ʼ��Ϊ0�����⣬��ʼ��Ϊ-1Ҳ��Ҫ����)
    //l++
    if (opt == 1) {
        sum[pre[x]]--;
        ans -= sum[pre[x++]];
    }
    //r++
    else {
        ans += sum[pre[++x]];
        sum[pre[x]]++;//ǰ׺��������a[x]���ִ���
    }
}
//����ָ��
inline void sub(int& x, int opt) {
    if (x == 1 && opt == 1) { x--; return; }//������ָ��ͬ���������ƺ���û����
    if (opt == 1) {
        ans += sum[pre[--x]];
        sum[pre[x]]++;
    }
    else {
        sum[pre[x]]--;
        ans -= sum[pre[x--]];
    }
}
//1��������״̬��2��ǰ����״̬
inline void modify(int& time, int opt) {
    if (opt == 1) time++;//�������״̬��Ҫ�ȱ�ɺ����ʱ��
    int pos = v[time].id;
    if (l <= pos && pos <= r) {//�޸ĵ��ڵ�ǰ[L,R]֮ǰ��Ҫ���޸�Ӱ������ȥ
        //��ȥ�޸�״̬ǰ��ֵ
        sum[pre[pos]]--;
        ans -= sum[pre[pos]];
        //�޸�״̬
        pre[pos] = pre[pos] ^ a[pos] ^ a[pos + 1];
        swap(a[pos], a[pos + 1]);
        //�����޸�״̬���ֵ
        ans += sum[pre[pos]];
        sum[pre[pos]]++;
    }
    //��Ӱ���ֱ�Ӵ���pre������
    else {
        pre[pos] = pre[pos] ^ a[pos] ^ a[pos + 1];
        swap(a[pos], a[pos + 1]);
    }
    if (opt == 2) time--;//��ǰ�ƶ�״̬��Ҫ������������ʱ��
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
        v.push_back(q[0]);//��ֵ
        unit = pow(n, 2 / 3.0);//��ʼ���ֿ��С
        upf(i, 1, n) {
            cin >> a[i];
            pre[i] = pre[i - 1] ^ a[i];//��ǰ׺��
        }
        int time = 0;
        upf(i, 1, m) {
            int op;
            cin >> op;
            //��¼pos����Ϊֻ��op=1ʱ�Ż�����𰸣���q�Ѿ����Ź���������Ҫ��¼pos
            if (op == 1) {//op=1ʱΪ��ѯ
                cin >> q[i].l >> q[i].r;
                q[i].t = time;
                q[i].id = 0;
                q[i].pos = i;
            }
            else {//op=2�����޸�
                cin >> q[i].id;//Bobѡ��ĵ�
                q[i].l = q[i].r = 0;
                q[i].t = ++time;
                q[i].pos = i;
                v.push_back(q[i]);
            }
        }
        sort(q + 1, q + 1 + m);
        //��ʼ��
        l = 0, r = 0, ans = 0, time = 0;
        upf(i, 0, m)trueans[i] = -1;
        //sum[0] = 1;
        upf(i, 1, m) {
            //ʱ��״̬��Ҫ�޸�
            while (time < q[i].t)modify(time, 1);
            while (time > q[i].t)modify(time, 2);
            if (q[i].id != 0)//��ǰѯ����Bob���޸ĵĻ�����Ҫ����l��r���ƶ�
                continue;
            while (r < q[i].r)add(r, 2);//���ƺ���
            while (r > q[i].r)sub(r, 2);//���ƺ���
            while (l < q[i].l)add(l, 1);
            while (l > q[i].l)sub(l, 1);
            ans += sum[pre[l - 1]];//������L-1�����
            trueans[q[i].pos] = (ll)(r - l + 2) * (r - l + 1) / 2 - ans;
            ans -= sum[pre[l - 1]];//��ȥL-1�����
        }
        upf(i, 1, m) {
            if (trueans[i] != -1) {//���޸���Ҫ���
                cout << trueans[i] << '\n';
            }
        }
        //��ʼ��sum
        upf(i, l, r) {
            sum[pre[i]]--;
        }
    }
}
