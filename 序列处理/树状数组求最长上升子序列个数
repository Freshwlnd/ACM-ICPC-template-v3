#define maxn 500005
#define int long long
using namespace std;
int T[maxn], n, a[maxn], b[maxn], length, num[maxn],f[maxn],ff[maxn],g[maxn],gg[maxn];
int lowbit(int x){
    return x&(-x);
}
int qpow(int a,int b){
    int ans=1;
    int tmp=a;
    while(b){
        if(b%2)
            ans*=tmp,ans%=mod;

        tmp=tmp*tmp;
        tmp%=mod;
        b=b/2;
    }
    return ans%mod;
}
int query(int x){
    int ans=0;
    while(x){
        if(ans<T[x])
            ans=T[x];
        x-=lowbit(x);
    }
    return ans;
}
void update(int x,int len,int number){
    while(x<=length){
        if(T[x]<len)
            T[x]=len,num[x]=number;
        else if(T[x]==len)
            num[x]+=number;
        num[x]%=mod;
        x+=lowbit(x);
    }
}
int query_number(int x,int length){
    int ans=0;
    while(x){
        if(T[x]==length)
            ans+=num[x];
        ans%=mod;
        x-=lowbit(x);
    }
    return ans;
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;++i){
        T[i]=0;
        cin>>a[i];
        b[i]=a[i];
    }
    T[n+1]=0;
    sort(b+1,b+1+n);
    length=unique(b+1,b+1+n)-b-1;
    int ans=0;
    //求从1开始到a[i]-1的最长上升子序列长度和数量
    for(int i=1;i<=n;++i){
        a[i] = lower_bound(b+1,b+1+length,a[i])-b-1;//有多少个小于a[i]的元素
        //a[i] = length-a[i]-1;//删去‘//’变成从a[i]+1开始到结尾的最长上升子序列
        f[i] = query(a[i])+1;
        ff[i] = query_number(a[i], f[i] - 1);
        ff[i]=max(ff[i],(ll)1);
        ans=max(ans, f[i]);
        update(a[i]+1, f[i], ff[i]);
        //cout<<f[i]<<' '<<ff[i]<<endl;
    }
    int nnn=query_number(length,ans);
    int tmp=qpow(nnn,mod-2);
    //cout<<ans<<endl;
    for(int i=0;i<=n+1;++i){
        T[i]=0;
        num[i]=0;
    }
    //求从a[i]+1开始到结尾的最长上升子序列长度和数量
    for(int i=n;i>=1;--i){
        a[i] = length-a[i]-1;
        g[i] = query(a[i])+1;
        gg[i] = query_number(a[i], g[i] - 1);
        gg[i]=max(gg[i],(ll)1);
        update(a[i]+1, g[i], gg[i]);
        //cout<<g[i]<<' '<<gg[i]<<endl;
    }
    for(int i = 1; i <= n; i ++){
		if(f[i] + g[i] - 1 == ans) cout<<ff[i] * gg[i] % mod * tmp % mod<<" "; else cout<<"0 ";//xjb输出
	}
}


