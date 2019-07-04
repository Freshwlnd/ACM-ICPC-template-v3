//归并算法求逆序对.cpp
//merge_sort

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

const int maxn(1e6 + 7);
int n;
ll times;
int row[maxn];
int col[maxn];

void mergec(int l, int r) {
	if (l != r) {
		int mid = (l + r) / 2;
		mergec(l, mid);
		mergec(mid + 1, r);
		int leftPoint = l, rightPoint = mid + 1, colPoint = 0;
		while (leftPoint < mid + 1 && rightPoint < r + 1) {
			if (row[leftPoint] < row[rightPoint]) {
				col[colPoint++] = row[leftPoint++];
			}
			else {
				col[colPoint++] = row[rightPoint++];
				times += mid + 1 - leftPoint;
			}
		}
		while (leftPoint < mid + 1) {
			col[colPoint++] = row[leftPoint++];
		}
		while (rightPoint < r + 1) {
			col[colPoint++] = row[rightPoint++];
		}
		per(i, l, r + 1) {
			row[i] = col[i - l];
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	while (cin >> n) {
		times = 0;
		per(i, 1, n + 1) {
			cin >> row[i];
		}
		mergec(1, n);
		cout << times << endl;
	}
}
