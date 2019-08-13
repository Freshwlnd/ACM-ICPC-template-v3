#define MAXN 1010
using namespace std;
int sg[MAXN], f[MAXM];//f[]表示所有能操作的方案，sg[]存储必胜点到下一个必败点的人的操作方法。若sg[]=0就意味着这个点不是必胜点
bool Hash[MAXN];
//以经典的石头堆的博弈问题为例,复杂度为O(MAXN^2)
void getSG(int m)
{
    memset(sg, 0, sizeof(sg));
    for (int i = 1; i < MAXN; i++)//枚举石子的个数
    {
        memset(Hash, false, sizeof(Hash));
        for (int j = 0; j < m && f[j] <= i; j++)
            Hash[sg[i-f[j]]] = true;//枚举每次拿走的个数并标记
        for (int j = 0; j < MAXN; j++)
        {
            if (!Hash[j])
            {
                sg[i] = j;　//找到这个F[](该状态可以达到的状态)中不存在的最小的数
                break;
            }
        }
    }
}

