//大整数相乘的FFT做法
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<complex>
using namespace std;
int n;
typedef complex<double> cd;
#define maxl 2097153
#define PI 3.14159265358979
char s1[maxl],s2[maxl];
cd a[maxl];
cd b[maxl];
int rev[maxl];
//二进制位反转
void get_rev(int bit)
{
	for(int i=0;i<(1<<bit);i++)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
}
void fft(cd *a,int n,int dft)
{
	for(int i=0;i<n;i++) if(i<rev[i]) swap(a[i],a[rev[i]]);
	for(int step=1;step<n;step<<=1)
	{
		cd wn=exp(cd(0,dft*PI/step));
		for(int j=0;j<n;j+=step<<1)
		{
			cd wnk(1,0);
			for(int k=j;k<j+step;k++)
			{
				cd x=a[k];
				cd y=wnk*a[k+step];
				a[k]=x+y;
				a[k+step]=x-y;
				wnk*=wn;
			}
		}
	}
	if(dft==-1) for(int i=0;i<n;i++) a[i]/=n;
}
int output[maxl];
int main()
{
 	//freopen("fft.in","r",stdin);
 	scanf("%s%s",s1,s2);
 	int l1=strlen(s1);
 	int l2=strlen(s2);
 	int s=2,bit=1;
 	for(bit=1;(1<<bit)<l1+l2-1;bit++)s<<=1;//maybe wiping the"-1" is better
 	for(int i=0;i<l1;i++) a[i]=(double)(s1[l1-i-1]-'0');//给实部赋初值
 	for(int i=0;i<l2;i++) b[i]=(double)(s2[l2-i-1]-'0');
 	//for(int i=0;i<8;i++) printf("%d %d\n",i,rev[i]);
 	get_rev(bit);
	fft(a,s,1);
	fft(b,s,1);
	for(int i=0;i<s;i++) a[i]*=b[i];
	fft(a,s,-1);
	for(int i=0;i<s;i++) 
	{
		output[i]+=(int)(a[i].real()+0.5);//取实数四舍五入，此时虚数部分应当为0或由于浮点误差接近0
		output[i+1]+=output[i]/10;
		output[i]%=10;
	}
	int i;
	for(i=l1+l2;!output[i]&&i>=0;i--);//去掉前导0
	if(i==-1) printf("0");//乘法结果为0
	else for(;i>=0;i--) printf("%d",output[i]);
	putchar('\n');
}
