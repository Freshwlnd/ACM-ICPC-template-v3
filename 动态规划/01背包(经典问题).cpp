#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>

#include<string>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>

#define ll long long
//#define myfor(a,b,c) for(int c=a;a<=b?c<=b:c>=b;a<=b?++i:--i)

using namespace std;
const ll maxn=1005;

int main()
{
    ios::sync_with_stdio(false);
    ll sum[maxn];
    ll value[maxn],weight[maxn];
    int t,n,v;
    cin>>t;
    while(t--){
        memset(sum,0,sizeof(sum));
        cin>>n>>v;
        for(int i=1;i<=n;++i){
            cin>>value[i];
        }
        for(int i=1;i<=n;++i){
            cin>>weight[i];
        }
        for(int i=1;i<=n;++i){
            for(int j=v;j>=weight[i];j--){
                sum[j]=max(sum[j],sum[j-weight[i]]+value[i]);
            }
        }
        cout<<sum[v]<<endl;
    }
    return 0;
}

