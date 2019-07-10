//米勒拉宾算法
//大数素性测试
//原文：https://blog.csdn.net/qq_37957829/article/details/77335072 

//引言
//小费马定理为：若有素数p，则对任意的数a (a为正整数，且a<p)，a^( p-1 ) ≡ 1( mod p )
//但部分合数也满足 a^( p-1 ) ≡ 1( mod p )，被称为Carmichael数

//改进
//（在小费马定理的基础上有人设计出米勒拉宾随机素数测试法）
//（并非一定正确，但错误可能性却小到可以接受）
//对一个数字p，枚举多个a以测试n的素性，同时采用特殊方法处理a

//对a的特殊处理基于另一个定理
//如果p是素数，x是小于p的正整数，且x^2 mod p = 1，那么要么x=1，要么x=p-1
//证明：
//如果p为素数，x是小于p的正整数， 且x^2 mod p = 1 ，说明p能够整除（x+1）（x-1）。
//但是p是素数，那么只可能是x-1能被p整除(此时x=1)或x+1能被p整除(此时 x=p-1)。

//判断一个数是不是素数光靠上面的方法是不可靠的
//因为p如果是合数的话，也有可能有x^2 ≡ 1 mod(p)  且 x=1或者 x =p-1；
//但是多排除几次p不为合数的话，就增大了p是素数的可能性 ，这是这个算法的核心思想。

//解题过程
//首先判断要判断的数n是不是2，再判断n是不是奇数。
//然后尽可能的在令d=n-1，在d中除去2，使得n=d*(2^t),d为奇数，t的值并不关心。
//如果n是一个素数，那么或者a^d mod n=1，或者存在某个i使得a^(d*2^i) mod n=n-1 (0<=i<r) 
//（注意i可以等于0，这就把a^d mod n=n-1的情况统一到后面去了）



typedef long long LL;
 
LL mulmod( LL a, LL b , LL p )
{
    LL  d =1;
    a = a%p;
    while( b>0 )
    {
        if(b&1)
            d = (d*a)%p;
        a = (a*a)%p;
        b>>=1;
    }
    return d;
}
 
bool witness( LL a,LL n)
{
    LL d = n-1 ;
    if( n ==2 ) return true ;
    if( !(n&1) ) return false ;
    while(!(d&1)) d = d/2;
    LL t = mulmod(a,d,n);
    while((d!=n-1) && (t!=1)&&(t!=n-1))
    {
        t = mulmod( t ,2,n);
        d=d<<1;
    }
    return (t==n-1)||(d&1);
}
 
bool isprime( LL n)
{
    int a[3] = {2,7,61};
    for(int i=0;i<3;i++)
        if(!witness(a[i],n))
            return false;
    return true;
}
int main()
{
    LL s;
    cin>>s;
    if(isprime(s))
        cout<<"YES";
    else
        cout<<"NO";
    return 0;
}