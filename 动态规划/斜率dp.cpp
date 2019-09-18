#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define per(i, a, b) for(int i=a; i<b; i++)
const int MAXN(1e4+7);

int n;
struct nd {
    ll x, y, p;
}bk[MAXN];
int stk[MAXN], top, botm;
ll dp[MAXN];

//用叉乘比较斜率（乘法）更精确更快
//若会爆范围则需使用slope计算斜率比较

//叉乘
//p0-p1 X p0-p2 （大于0（顺时针）斜率变小，小于0（逆时针）斜率变大）
inline double cross(const nd& p0, const nd& p1, const nd& p2){//计算叉乘，注意p0,p1,p2的位置，这个决定了方向
    return (p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x);
}

//计算斜率
inline double slope(const int& p0, const int& p1){
    if(bk[p1].x==bk[p0].x) return 1e25;
    return 1.0*(bk[p1].y-bk[p0].y)/(bk[p1+1].x-bk[p0+1].x);
}

//dp结果中用到的 “与点有关的函数”
inline ll f(const int& p) {
    return p;
}

int main() {

    top = botm = 1;
    stk[1] = 0;                 //设置初始点
    per(i, 1, n + 1) {   //遍历每个点
        while(botm<top && slope(stk[botm + 1], stk[botm]) <= bk[i].p) botm++;               //维护单调队列，找到临界点，前面的出队（大小根据式子更改）（等于情况也要出队）
        dp[i] = f(botm);                                                                             //botm点为最优点
        while(top>botm && slope(stk[top - 1], stk[top]) >= slope(stk[top], i)) top--;   //维护凸包（大小根据式子更改）（等于情况也要删除）
        stk[++top] = i;
    }
    cout << dp[n] << endl;

}
