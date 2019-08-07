
/*性质
 *  1.设线性基的异或集合中不存在0.
 *  2.线性基的异或集合中每个元素的异或方案唯一，其实这个跟性质1是等价的.
 *  3.线性基二进制最高位互不相同.
 *  4.如果线性基是满的,它的异或集合为[1,1<<n−1].
 *  5.线性基中元素互相异或,异或集合不变.
 *维护
 *  插入(insert)
 *    如果向线性基中插入数x,从高位到低位扫描它为1的二进制位.
 *    扫描到第i时,如果ai不存在,就令ai=x,否则x=x⊗ai.
 *    x的结局是,要么被扔进线性基,要么经过一系列操作过后,变成了0。
 *  合并(merge)
 *    将一个线性基暴力插入另一个线性基即可.
 *查询
 *  存在性
 *    如果要查询x是否存于异或集合中.
 *    从高位到低位扫描x的为1的二进制位.扫描到第i位的时候x=x⊗ai
 *    如果中途x变为了0，那么表示x存于线性基的异或集合中。
 *  最大值(query_max)
 *    从高位到低位扫描线性基.如果异或后可以使得答案变大,就异或到答案中去.
 *  最小值(query_min)
 *    最小值即为最低位上的线性基
 *  k小值(rebuild , kthquery)
 *    根据性质3.
 *    我们要将线性基改造成每一位相互独立.
 *    具体操作就是如果i<j,aj的第i位是1,就将aj异或上ai.(消去a[j]的其他低位上全部的1只保留了j位上的1)
 *    经过一系列操作之后，对于二进制的某一位i。只有ai的这一位是1，其他都是0.
 *    所以查询的时候将k二进制拆分，对于1的位，就异或上对应的线性基.
 *    最终得出的答案就是k小值.
*/
struct Linear_Basis{
    long long d[61],p[61];  //d[]重构前的线性基，p[]重构后的线性基
    int cnt;                //记录线性基的秩
    Linear_Basis()              //初始化
    {
        memset(d,0,sizeof(d));
        memset(p,0,sizeof(p));
        cnt=0;
    }
    //
    bool insert(long long val)  //插入线性基
    {
        for (int i=60;i>=0;i--)
            if (val&(1LL<<i))
            {
                if (!d[i])
                {
                    d[i]=val;
                    break;
                }
                val^=d[i];
            }
        return val>0;
    }
    //可生成0就返回true
    bool check(long long val) {
        for (int i = 32; i >= 0; i--)
            if (val & (1LL << i)) {
                if (!d[i])
                    return false;
                val ^= d[i];
            }
        return true;
    }
    //计算线性基向量空间内最大值
    long long query_max()
    {
        long long ret=0;
        for (int i=60;i>=0;i--)
            if ((ret^d[i])>ret)
                ret^=d[i];
        return ret;
    }
    //计算线性基向量空间内最小值
    long long query_min()
    {
        for (int i=0;i<=60;i++)
            if (d[i])
                return d[i];
        return 0;
    }
    //重构线性基(改造成每一位相互独立),便于求解向量空间第k小值（小到大第k个）
    void rebuild()
    {
        for (int i=60;i>=0;i--)
            for (int j=i-1;j>=0;j--)
                if (d[i]&(1LL<<j))
                    d[i]^=d[j];
        for (int i=0;i<=60;i++)
            if (d[i])
                p[cnt++]=d[i];
    }
    //求向量空间第k小的数
    long long kthquery(long long k)
    {
        int ret=0;
        if (k>=(1LL<<cnt))
            return -1;
        for (int i=60;i>=0;i--)
            if (k&(1LL<<i))
                ret^=p[i];
        return ret;
    }
};
//合并两个线性基
Linear_Basis merge(const Linear_Basis &n1,const Linear_Basis &n2)
{
    Linear_Basis ret=n1;
    for (int i=60;i>=0;i--)
        if (n2.d[i])
            ret.insert(n1.d[i]);
    return ret;
}
