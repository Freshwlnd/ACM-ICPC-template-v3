//2019牛客国庆集训派对day5 K -	2017 Revenge
//https://ac.nowcoder.com/acm/contest/1110/K

//题面
//  给n个数字(0<a[i]<2017)的集合，选一子集使之积(%2017)为r，问合法子集个数(%2)。
//（空集之积视为1）

//思路
//  2017有原根5，对0~2016

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define per(i, a, b) for(int i=a; i<b; i++)
const int MAXN(2e6+7);
const int g=5, p=2017;  //2017的原根为5
int n, r;
int a[MAXN];
int cg[3000];
bitset<2016> bs;

int main() {

    int nmm=1;
    per(i, 0, p-1) {
        cg[nmm] = i;        //g ^ cg[nmm] = nmm，将[1,p-1]映射为log5(nmm)
        nmm = nmm*g%p;
    }

    while(cin >> n >> r) {
        per(i, 1, n+1) {
            cin >> a[i]; a[i] = cg[a[i]];    //将输入映射为 log5(a[i])，即将题目乘法转为加法 a*b=c -> lga+lgb=lgc
        }
        bs.reset();     //将bs清0
        bs.set(cg[1]);  //将第1位置为1
        per(i, 1, n+1) {
            //dp操作{dp[i] = (dp[i]+dp[(i-a[i]+2016)%2016])%2}
            bs ^= (bs<<a[i])|(bs>>(2016-a[i]));
        }
        cout << bs[cg[r]] << endl;
    }

    return 0;
}
