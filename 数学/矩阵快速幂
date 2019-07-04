//矩阵快速幂.cpp
const int MAXN(9);
int Size;

struct Mat {
    ll a[MAXN][MAXN];
    void init1() {  //初始化为单位矩阵
        mem(a, 0);
        per(i,0,Size) {
            a[i][i] = 1;
        }
    }
    Mat operator*(Mat& t) {
        Mat r;
        r.init1();
        ll x;
        per(i,0,Size) {
            per(j,0,Size) {
                x = 0;
                per(k, 0, Size) {
                    x += (a[i][k] * t.a[k][j]) % mod;
                }
                r.a[i][j] = x % mod;
            }
        }
        return r;
    }
    Mat qpow(Mat& r, ll m) {
        Mat ans;
        ans.init1();
        while (m) {
            if (m & 1)
                ans = ans * r;
            r = r * r;
            m >>= 1;
        }
        return ans;
    }
};
