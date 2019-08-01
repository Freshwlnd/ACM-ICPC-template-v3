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

const int MAXL(1e6+7);
char s[MAXL];
int tr[2*MAXL][26] , par[2*MAXL] , mx[2*MAXL] , cnt , last;
ll ans[2*MAXL], R[2*MAXL];
int len;

void extand(int x) {    //节点[1,cnt]
    int np = ++cnt , p = last;R[np] = 1;
    mx[np] = mx[p] + 1;last = np;
    while(p && !tr[p][x]) tr[p][x] = np , p = par[p];
    if(!p) par[np] = 1;
    else {
        int q = tr[p][x];
        if(mx[q] == mx[p] + 1) par[np] = q;
        else {
            int nq = ++cnt;mx[nq] = mx[p] + 1;
            per(i,0,26) tr[nq][i] = tr[q][i];
            par[nq] = par[q];par[q] = par[np] = nq;
            while(p && tr[p][x] == q) tr[p][x] = nq , p = par[p];
        }
    }
    return;
}

int tmp[MAXL] , id[2*MAXL];
void topsort() {
    per(i,1,cnt+1) tmp[mx[i]]++;
    per(i,1,len) tmp[i] += tmp[i-1];
    per(i,1,cnt+1) id[tmp[mx[i]]--] = i;
    rep(i,1,cnt+1) R[par[id[i]]] += R[id[i]];
}

int main() {
    scanf("%s",s+1);
    len = strlen(s+1)+1;cnt = last = 1; //字符串[1,len)
    per(i,1,len) extand(s[i]-'a');
    //计算每个长度的子串出现最多的次数
    topsort();  //拓扑排序
    per(i,1,cnt+1) ans[mx[i]] = max(ans[mx[i]],R[i]);
    rep(i,1,len-1) ans[i] = max(ans[i],ans[i+1]);
    per(i,1,len) printf("%lld\n",ans[i]);
    return 0;
}
