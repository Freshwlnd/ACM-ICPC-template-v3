//1. 当n,m都很小的时候可以利用杨辉三角直接求。
//C(n,m)=C(n-1,m)+C(n-1,m-1)；

//2. 利用乘法逆元
//	组合数答案即 (n!)%mod*inv(m!*(n-m)!)%mod

//	求乘法逆元：(a/b)%mod=a*(b^(mod-2)) mod为素数。
//	逆元x 可以利用扩展欧几里德或欧拉函数求得：
//		1).扩展欧几里德：b*x+p*y=1 有解，x就是所求
//		2).费马小定理：b^(p-1)=1(mod p),故b*b^(p-2)=1(mod p),所以x=b^(p-2)

//如果mod是素数，则
// b的逆元其实就是b^(mod-2)
// (m!(n-m)!)的逆元为 (m!(n-m)!)^(mod-2)

//否则对于组合数x=C(n, m)
//	(n!)/(m!*(n-m)! =x%p 
//	先算出n！、m！、(n-m)!对p取模的余数a、b、c，令b1=b*c
//	就转换为a/b1 = x%p
//	因为p为素数，所以等价于 b1*x+pk=a
//	然后用扩展的欧几里得定理算出 b1*x’+pk’=1的解，x=x’*a，就得到了最终的x的值，即C(m,n)%p得值。

#define per(i,a,n) for (int i=a;i<n;i++)
#define rep(i,a,n) for (int i=n-1;i>=a;i--)
ll powmod(ll a, ll b) { ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) { if (b & 1)res = res * a%mod; a = a * a%mod; }return res; }

ll inv[MAXN];
void getInv(const int& maxx) {
    inv[0]=1;
    inv[maxx]=powmod(fac[maxx],mod-2);
    rep(i, 1, maxx) inv[i]=inv[i+1]*(i+1)%mod;
}

ll fac[MAXN];
void getFac(const int& maxx) {
	fac[0]=1;
    per(i, 1, maxx+1) fac[i]=fac[i-1]*i%mod;
}

ll C(ll n, ll m) {
	if(m<0 || n<m) return 0; 
	if(m>n-m) m=n-m; 
    return fac[n]*inv[n-m]%mod*inv[m]%mod;
}