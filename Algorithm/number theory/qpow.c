//整数快速幂
#include <stdio.h>
typedef long long ll;

int a,b;
ll qpow(){
	int r=1,base=a;
	while(b){
		if(b%2){
			r*=base;
		}
		base*=base;
		b>>=1;
	}
	return r;
}

int main(){
	while(~scanf("%d%d",&a,&b)){
		printf("%lld\n",qpow());
	}
}
