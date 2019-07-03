#include<bits/stdc++.h>
#define rtl rt<<1
#define rtr rt<<1|1
#define mod 998244353
#define N 2000020
#define LL long long
using namespace std;
LL ma[N], num[N], f[N], ff[N], a[N], b[N], n;//f[]记录询问长度,ff[]记录询问数量,ma[]长度线段树,num[]数量线段树
//向上更新，上方节点的num保存以此为尾的最长上升子序列的个数
inline void PushUp(LL rt) {
    if(ma[rtl]>ma[rtr]){ma[rt]=ma[rtl];num[rt]=num[rtl];}
    else if(ma[rtl]<ma[rtr]){ma[rt]=ma[rtr];num[rt]=num[rtr];}
    else{ma[rt]=ma[rtr];num[rt]=num[rtr]+num[rtl];num[rt]%=mod;}
}
void insert(LL l,LL r,LL pos,LL length,LL number,LL rt){
    if(l==r){
        if(ma[rt]==length)num[rt]+=number,num[rt]%=mod;//一样长数量叠加
        else num[rt]=number;//不一样长数量改变
        num[rt]%=mod;
        ma[rt]=length;
        return ;
    }
    LL m=(l+r)>>1;
    if(pos<=m)insert(l,m,pos,length,number,rtl);
    else insert(m+1,r,pos,length,number,rtr);
    PushUp(rt);
}
//建树
void build(LL l,LL r,LL rt) {
    if (l == r) {
        ma[rt]=num[rt]=0;
        return ;
    }
    LL m = (l + r) >> 1;
    build(l,m,rtl);
    build(m+1,r,rtr);
    PushUp(rt);
}

//询问
LL query_length(LL L,LL R,LL l,LL r,LL rt) {
    if (L <= l && r <= R) {
        return ma[rt];
    }
    LL m = (l + r) >> 1;
    LL ret=0;
    if (L <= m) ret = max(ret, query_length(L , R , l, m, rtl));
    if (m < R) ret = max(ret, query_length(L , R , m+1, r, rtr));
    return ret;
}
LL query_number(LL L,LL R,LL l,LL r,LL rt,LL max_length){
    if(L <= l && r <= R){
        if(ma[rt]==max_length){
            return num[rt];
        }
        return 0;
    }
    LL m=(l+r)>>1;
    LL ret=0;
    if(L<=m) ret=query_number(L,R,l,m,rtl,max_length);
    if(m<R) ret+=query_number(L,R,m+1,r,rtr,max_length);
    ret%=mod;
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    LL i,j;
    cin>>n;
    for(i=1;i<=n;++i){
        cin>>a[i];
        b[i]=a[i];
    }
    sort(a+1,a+1+n);
    LL len=unique(a+1,a+n+1)-a;
    //离散化
    for(i=1;i<=n;++i){
        b[i]=lower_bound(a+1,a+len,b[i])-a;
    }
    build(0,n,1);
    for(i=1;i<=n;++i){
        f[i]=query_length(0,b[i]-1,0,n,1) + 1;
        ff[i]=query_number(0,b[i]-1,0,n,1,f[i]-1);
        ff[i]=max(ff[i],1LL);
        insert(1,n,b[i],f[i],ff[i],1);
        //cout<<f[i]<<" "<<ff[i]<<endl;
    }
}
