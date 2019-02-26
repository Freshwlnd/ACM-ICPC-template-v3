//矩阵快速幂（待修改）.cpp

#include <bits/stdc++.h>
using namespace std;
#define per(i,a,n) for (int i=a;i<n;i++)
#define rep(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mmp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mem(a, b) memset(a, b, sizeof(a))
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> VI;
typedef pair<ll, ll> PI;
const ll mod(1e9 + 7);
ll powmod(ll a, ll b) { ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) { if (b & 1)res = res * a%mod; a = a * a%mod; }return res; }
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
// head

const int maxn(10);
const  double eps(1e-5);
int _, dex = 9;
ll N, out1;

struct mat
{
	ll a[maxn][maxn];
	void init() {    //初始化为单位矩阵 
		mem(a, 0);
		for (int i = 0; i<dex; ++i) {
			a[i][i] = 1;
		}
	}
};
mat operator*(mat s, mat t) {
	mat r;
	r.init();
	ll x;
	per(i,0,dex) {
		per(j,0,dex) {
			x = 0;
			per(k, 0, dex) {
				x += (s.a[i][k] * t.a[k][j]) % mod;
			}
			r.a[i][j] = x % mod;
		}
	}
	return r;
}
mat qpow(mat r, ll m) {
	mat ans;
	ans.init();
	while (m) {
		if (m & 1)
			ans = ans * r;
		r = r * r;
		m >>= 1;
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(false);
	for (cin >> _; _;_--) {
		cin >> N;
		if (N == 1) { out1 = 3; }
		else if (N == 2) { out1 = 9; }
		else if (N == 3) { out1 = 20; }
		else {
			mat inn, outt;
			out1 = 0;
			mem(inn.a, 0);
			outt.init();
			inn.a[0][1] = inn.a[0][2] = inn.a[1][3] = inn.a[1][4] = inn.a[2][6] = inn.a[2][7] = inn.a[2][8] = inn.a[3][0] = inn.a[3][2] = inn.a[4][3] = inn.a[4][5] = inn.a[5][6] = inn.a[5][8] = inn.a[6][0] = inn.a[6][1] = inn.a[6][2] = inn.a[7][4] = inn.a[7][5] = inn.a[8][6] = inn.a[8][7] = 1;
			outt = qpow(inn, N - 2);
			per(i, 0, 10) {
				ll x = 0;
				per(j, 0, 10) {
					x = (x + outt.a[i][j]) % mod;
				}
				out1 = (out1 + x) % mod;
			}
		}
		cout << out1 << endl;
	}
}
