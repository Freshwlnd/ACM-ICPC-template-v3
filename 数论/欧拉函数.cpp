//广义欧拉降幂：a^b=a^(b%phi[p]+phi[p])%p
#include<bits/stdc++.h>
using namespace std;
const int maxn(1e5+5);
int prime[maxn],phi[maxn];

int Eular(int p)   //计算p的欧拉值
{
    int ans = p;
    for(int i=2;i*i<=p;++i)
    {
        if(p%i==0)
        {
            ans = ans - ans/i;
            while(p%i==0)
                p /= i;
        }
    }
    if(p>1) ans = ans - ans/p;
    return ans;
}

void Get_Eular()
{
    int n = 0;
    phi[1] = 1;
    for(int i=2;i<maxn;++i)
    {
        if(!phi[i])             //i为素数
        {
            phi[i] = i-1;
            prime[n++] = i;
        }
        for(int j=0; j<n&&i*prime[j]<=maxn;++j)
        {
            if(i%prime[j]==0)
            {
                phi[i*prime[j]] = phi[i]*prime[j]; //i*prime[j]的素因子和i是一样的,只相当与上文中的m扩大了
                break;
            }
            else phi[i*prime[j]] = phi[i]*phi[prime[j]];//积性函数的性质，i与prime[j]互质
        }
    }
}
int main(){
	Get_Eular();
	for(int i=0;i<maxn;i++){
	//	cout<<i<<" "<<prime[i]<<" "<<phi[i]<<"\n";
		cout<<i<<" "<<Eular(i)<<"\n";
	}
}
