//素数筛选
const int MAXN=100000;
int prime[MAXN+1];//得到小于等于MAXN的所有素数
void getPrime()
{
    memset(prime,0,sizeof(prime));
    for(int i=2;i<=MAXN;i++)
    {
        if(!prime[i])prime[++prime[0]]=i;
        for(int j=1;j<=prime[0]&&prime[j]*i<=MAXN;j++)      //除法改为乘法提速， 改为除法防止爆范围
        {
            prime[prime[j]*i]=1;
            if(i%prime[j]==0)break;
        }
    }
}
//合数分解（前面需要先素数筛选）
long long factor[100][2];//factor[fatCnt][0]记录目前最小整除数,factor[fatCnt][1]记录‘factor[fatCnt][0]’个数
int fatCnt;//fatCnt的值表示整除数种类
int getFactors(long long x)
{
    fatCnt=0;
    long long tmp=x;
    for(int i=1;prime[i]*prime[i]<=tmp;i++)                 //除法改为乘法提速，改为除法防止爆范围
    {
        factor[fatCnt][1]=0;
        if(tmp%prime[i]==0)
        {
            factor[fatCnt][0]=prime[i];
            while(tmp%prime[i]==0)
            {
                factor[fatCnt][1]++;
                tmp/=prime[i];
            }
            fatCnt++;
        }
    }
    if(tmp!=1)//最后如果tmp不为1表示还有一个未取到的素数约数。
    {
        factor[fatCnt][0]=tmp;
        factor[fatCnt++][1]=1;
    }
    return fatCnt;
}

