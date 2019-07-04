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

const int maxn(1e3 + 7);
int book[maxn][maxn];
int books[maxn][maxn];
int T, Q;
char type;
int x1, x2, Y1, y2, n1;

inline int lowbit(int x) {
    return x&(-x);
}

void change(int x, int y, int num) {
    for (int tx = x; tx < maxn;tx+=lowbit(tx)) {
        for (int ty = y; ty < maxn; ty += lowbit(ty)) {
            books[tx][ty] += num;
        }
    }
}

int query(int x, int y) {
    int result = 0;
    for (; x > 0; x -= lowbit(x)) {
        for (int i = y; i > 0; i -= lowbit(i)) {
            result += books[x][i];
        }
    }
    return result;
}
//需判断x、y<=0情况

inline int dex(int x1, int y1, int x2, int y2) {
    return query(x2, y2) - query(x2, y1 - 1) - query(x1 - 1, y2) + query(x1 - 1, Y1 - 1);
}

void build_tree() {
    mem(books, 0);
    per(i, 1, maxn) {
        per(j, 1, maxn) {
            book[i][j] = 1;
            change(i, j, 1);
        }
    }
}

void ask() {
    cin >> type;
    switch (type) {
        case 'S': {
            cin >> x1 >> Y1 >> x2 >> y2;
            ++x1;++Y1;++x2;++y2;
            if(x1>x2) { swap(x1, x2); }
            if(Y1>y2) { swap(Y1, y2); }
            cout << dex(x1, Y1, x2, y2) << endl;
        }
            break;
        case 'A': {
            cin >> x1 >> Y1 >> n1;
            ++x1;++Y1;
            book[x1][Y1] += n1;
            change(x1, Y1, n1);
        }
            break;
        case 'D': {
            cin >> x1 >> Y1 >> n1;
            ++x1;++Y1;
            n1 = min(n1, book[x1][Y1]);
            book[x1][Y1] -= n1;
            change(x1, Y1, -n1);
        }
            break;
        case 'M': {
            cin >> x1 >> Y1 >> x2 >> y2 >> n1;
            ++x1;++Y1;++x2;++y2;
            n1 = min(n1, book[x1][Y1]);
            book[x1][Y1] -= n1;
            book[x2][y2] += n1;
            change(x1, Y1, -n1);
            change(x2, y2, n1);
        }
            break;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> T;
    for (int _ = 1; _ <= T; _++) {
        build_tree();
        cin >> Q;
        cout << "Case " << _ << ":" << endl;
        while (Q--) {
            ask();
        }
    }
}
