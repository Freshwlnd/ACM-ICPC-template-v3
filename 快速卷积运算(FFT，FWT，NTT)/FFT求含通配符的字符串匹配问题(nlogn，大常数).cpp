//FFT求*为通配符的字符串匹配位置
#include<bits/stdc++.h>
#define db double
#define RI register//register将变量放置在寄存器中，可少量加速但不能调用变量地址
using namespace std;
const int N=1e6+10,M=3e5+2;
const db pi=acos(-1);

int n,m,L,len,rv[N],ans[M],tot,A[M],B[M];
char s[2][M];
//自定义的复数，可使用stl库的complex
struct cc{
	db r,i;
	cc(){r=i=0;};
	cc(db r_,db i_){r=r_;i=i_;}
	cc operator +(const cc&ky){return cc(r+ky.r,i+ky.i);}
	cc operator -(const cc&ky){return cc(r-ky.r,i-ky.i);}
	cc operator *(const cc&ky){return cc(r*ky.r-i*ky.i,r*ky.i+i*ky.r);}
	cc operator /(const int&ky){return cc(r/(db)ky,i/(db)ky);}
	inline cc conj(){return cc(r,-i);}
}a[N],b[N],f[N];//f[N]为最终的多项式数组
//FFT模板，传入1为FFT其余为IFFT
inline void FFT(cc *e,int ptr)
{
	RI int i,j,k;cc bs,ori,ix,iy;
	for(i=1;i<len;++i) if(i<rv[i]) swap(e[i],e[rv[i]]);
	for(i=1;i<len;i<<=1){
		ori=cc(cos(pi/i),ptr*sin(pi/i));
		for(j=0;j<len;j+=(i<<1)){
			bs=cc(1,0);
			for(k=0;k<i;++k,bs=bs*ori){
				ix=e[j+k];iy=bs*e[i+j+k];
				e[j+k]=ix+iy;e[i+j+k]=ix-iy;
			}
		}
	}
	if(ptr==1) return;
	for(i=0;i<len;++i) e[i]=e[i]/len;
}

int main(){
    RI int i,j,k,t;
    scanf("%d%d%s%s",&m,&n,s[0],s[1]);
    //将通配符*转换成0，其余字符转换成其他数字
    for(i=0;i<m;++i) A[m-1-i]= s[0][i]=='*'?0:(s[0][i]-'a'+1);
    for(i=0;i<n;++i) B[i]= s[1][i]=='*'?0:(s[1][i]-'a'+1);
    len=1;L=0;
    //n是文本串长度，需要求得大于n的最小2的整数次幂(FFT要求)
    for(;len<=n;len<<=1) L++;
    for(i=1;i<len;++i) rv[i]=(rv[i>>1]>>1)|((i&1)<<(L-1));//反转二进制的预处理(FFT推导过程证明了需要反转二进制)
    //赋初值0+0i
    for(i=0;i<len;++i) a[i]=b[i]=cc(0,0);
    //a[]=A[]^3，b[]=B[]^3
    for(i=0;i<m;++i) a[i].r=A[i]*A[i]*A[i];
    for(i=0;i<n;++i) b[i].r=B[i];
    FFT(a,1);FFT(b,1);
    //F[]=A[]^3*B[]
    for(i=0;i<len;++i) f[i]=a[i]*b[i];
    
    for(i=0;i<len;++i) a[i]=b[i]=cc(0,0);
    for(i=0;i<m;++i) a[i].r=A[i];
    for(i=0;i<n;++i) b[i].r=B[i]*B[i]*B[i];
    FFT(a,1);FFT(b,1);
    for(i=0;i<len;++i) f[i]=f[i]+a[i]*b[i];
    
    for(i=0;i<len;++i) a[i]=b[i]=cc(0,0);
    for(i=0;i<m;++i) a[i].r=A[i]*A[i];
    for(i=0;i<n;++i) b[i].r=B[i]*B[i];
    FFT(a,1);FFT(b,1);
    for(i=0;i<len;++i) f[i]=f[i]-a[i]*b[i]*cc(2,0);
    //f[x]=sigma[i,0,m-1](A[x-i]^3*B[m-1-i]+A[x-i]*B[m-1-i]^3-2*A[x-i]^2*B[m-1-i]^2),根据此公式需要如上六次FFT操作
    FFT(f,-1);
    for(i=m-1;i<n;++i) 
	if(int(f[i].r+0.5)==0) 
	    ans[tot++]=i+2-m;
	printf("%d\n",tot);//匹配数
    for(i=0;i<tot;++i) printf("%d ",ans[i]);//匹配位置
	return 0;
}
