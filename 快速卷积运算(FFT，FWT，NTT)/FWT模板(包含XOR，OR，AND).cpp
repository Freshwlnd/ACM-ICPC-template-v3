//两个人在玩一个取石子的游戏，每次在一堆数量不为 1 的石子中取石子，假设这堆石子的个数是 x，那么允许取的个数是 d,d|x且d!=x，如果没有办法再取石子了，该操作的那一方就输了。（d|x表示d是x的约数）
//已知这次游戏有 m 堆石子，每堆的个数为一个 1 到 n 中的一个正整数。现在由先取的人安排石子个数，他想知道有多少种摆放方案可以让他一定能赢呢？
//FWT_XOR的正变换后数组b的意义是b[i]=(sigma j满足i&j的奇偶性==0 a[j] )-(sigma j满足i&j的奇偶性==1 a[j])





#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mod MOD
const int MAXN(1e5+5);
const ll MOD(998244353);
ll N,inv2;
ll aa[MAXN];
ll powmod(ll a, ll b) { ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) { if (b & 1)res = res * a%mod; a = a * a%mod; }return res; }
void FWT_or(ll *a,int opt)
{
    for(int i=1;i<N;i<<=1)
        for(int p=i<<1,j=0;j<N;j+=p)
            for(int k=0;k<i;++k)
                if(opt==1)a[i+j+k]=(a[j+k]+a[i+j+k])%MOD;
                else a[i+j+k]=(a[i+j+k]+MOD-a[j+k])%MOD;
}
void FWT_and(ll *a,int opt)
{
    for(int i=1;i<N;i<<=1)
        for(int p=i<<1,j=0;j<N;j+=p)
            for(int k=0;k<i;++k)
                if(opt==1)a[j+k]=(a[j+k]+a[i+j+k])%MOD;
                else a[j+k]=(a[j+k]+MOD-a[i+j+k])%MOD;
}
//若数据量为2^n那么N=2^(n+1)
void FWT_xor(ll *a,int opt)
{
    for(int i=1;i<N;i<<=1)
        for(int p=i<<1,j=0;j<N;j+=p)
            for(int k=0;k<i;++k)
            {
                ll X=a[j+k],Y=a[i+j+k];
                a[j+k]=(X+Y)%MOD;a[i+j+k]=(X+MOD-Y)%MOD;
                if(opt==-1)a[j+k]=1ll*a[j+k]*inv2%MOD,a[i+j+k]=1ll*a[i+j+k]*inv2%MOD;//inv2为2在MOD意义下的逆元，若不需要模意义下的值则直接/2
            }
}
vector<ll> v;

void division_2(){
    N=0;
    ll tmp,flag,pos;
    while(!v.empty()){
	//大数除以二
        tmp=0;flag=0;
        pos=v.size()-1;
        for(ll i=pos;i>=0;--i){
            tmp=v[i]+flag*10;
            flag=tmp%2;
            v[i]=tmp/2;
        }
        //去掉前导0
        if(v[pos]==0){
            v.pop_back();
            pos--;
        }
        tmp=0;
        for(int i=pos;i>=0;--i){
            tmp=tmp*10+v[i];
            tmp%=mod;
        }
        N++;
        aa[N]=tmp;
    }
    N--;
    aa[N+1]=0;
}
signed main(){
    ll m;
    char tmp;
    ll tp=0;
    while(tmp=getchar(),tmp<='9'&&tmp>='0'){
        v.push_back((ll)(tmp-'0'));
        tp=tp*10+tmp-'0';
        tp%=mod;
    }
    reverse(v.begin(),v.end());
    aa[0]=tp;
    cin>>m;
    division_2();
    for(int i=0;i<=N;++i){
        aa[i]-=aa[i+1];
    }
    ll num=1;
    while(N>=num){
        num<<=1;//若数据量为2^n那么num=2^(n+1)
    }
    N=num;
    inv2=powmod(2,mod-2);
    FWT_xor(aa,0);
    for(int i=0;i<=N;++i){
        aa[i]=powmod(aa[i],m);
    }
    FWT_xor(aa,-1);
    ll sum=powmod(tp,m);
    sum=(sum-aa[0]+mod)%mod;
    cout<<sum<<endl;
}

