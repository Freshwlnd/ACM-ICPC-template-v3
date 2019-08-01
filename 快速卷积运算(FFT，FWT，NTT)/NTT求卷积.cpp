//还没看懂NTT
//NTT是FFT的优化方案

//学习完FFT后可能会有下面的疑问：
//假如我要计算的多项式系数是别的具有特殊意义的整数，
//那么我通篇都在用浮点数运算，首先从时间上就会比整数运算慢，
//另外我最多只能用long double不能用long long类型，
//我能不能应用数论的变化从而避开浮点运算，达到“更高更快更强(*･ω< ) ”呢？

//NTT解决的是多项式乘法带模数的情况，可以说有些受模数的限制，数也比较大，
//但是因为没有复数部分，所以它比较方便

const int mod(998244353);
ll powmod(ll a, ll b) { ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) { if (b & 1)res = res * a%mod; a = a * a%mod; }return res; }

const int MAXN(2e6+7);

inline int D(int x) {
    ((x>=mod) && (x-=mod)) || ((x<0) && (x+=mod));
    return x;
}

inline void NTT(int a[],int n,int op) {
    for(int i=1,j=n>>1;i<n-1;++i) {
        if(i<j)
            swap(a[i],a[j]);
        int k=n>>1;
        while(k<=j) {
            j-=k;
            k>>=1;
        }
        j+=k;
    }
    for(int len=2;len<=n;len<<=1) {
        int rt=powmod(3,(mod-1)/len);
        for(int i=0;i<n;i+=len) {
            int w=1;
            for(int j=i;j<i+len/2;++j) {
                int u=a[j],t=1LL*a[j+len/2]*w%mod;
                a[j]=D(u+t),a[j+len/2]=D(u-t);
                w=1LL*w*rt%mod;
            }
        }
    }
    if(op==-1) {
        reverse(a+1,a+n);
        int in=powmod(n,mod-2);
        for(int i=0;i<n;++i)
            a[i]=1LL*a[i]*in%mod;
    }
}

inline vector<int> Conv(vector<int> const &A,vector<int> const &B,int N) {
    static int a[MAXN],b[MAXN];
    auto Make2=[](int x)->int {
        return 1<<((32-__builtin_clz(x))+((x&(-x))!=x));
    };
    int n=Make2(A.size()+B.size()-1);
    for(int i=0;i<n;++i) {
        a[i]=i<A.size()?A[i]:0;
        b[i]=i<B.size()?B[i]:0;
    }
    NTT(a,n,1);NTT(b,n,1);
    for(int i=0;i<n;++i)
        a[i]=1LL*a[i]*b[i]%mod;
    NTT(a,n,-1);
    vector<int> C(N);
    for (int i=0;i<N;i++)
        C[i]=a[i];
    return C;
}

int main() {

    //初始化两个矩阵
    vector<int> a(n);
    for(int i=0;i<n;++i) cin>>a[i];
    vector<int> h(n);
    for(int i=0;i<n;++i) cin>>h[i];
    //做卷积
    a=Conv(h,a,n);

    return 0;
}
