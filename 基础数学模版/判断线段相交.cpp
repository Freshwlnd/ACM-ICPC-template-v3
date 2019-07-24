//基础介绍：https://www.cnblogs.com/kannyi/p/9043424.html
//进阶介绍：https://segmentfault.com/a/1190000004070478

const int MAXN(1e3+7);
const double EPS(1e-9);

double x[MAXN], y[MAXN];

//TwoLineCrossProduct 两条线叉积
inline double LCP(int a1, int a2, int b1, int b2) {
    return (x[a2]-x[a1])*(y[b2]-y[b1])-(x[b2]-x[b1])*(y[a2]-y[a1]);
}

//Line Intersect 线段相交：true相交/false不相交
inline int LI(int line1, int line2) {
    int a1 = line1*2, a2 = a1+1;    //起点-终点
    int b1 = line2*2, b2 = b1+1;    //起点-终点

    //快速排斥
    if((min(x[a1], x[a2])>max(x[b1], x[b2]) || 
    	min(x[b1], x[b2])>max(x[a1], x[a2]) || 
    	min(y[a1], y[a2])>max(y[b1], y[b2]) || 
    	min(y[b1], y[b2])>max(y[a1], y[a2])))
        return 0;

    //跨立
    double f[4];
    f[0] = LCP(a1, a2, a1, b1);   //a1-a2 X a1 b1
    f[1] = LCP(a1, a2, a1, b2);   //a1-a2 X a1 b2
    f[2] = LCP(b1, b2, b1, a1);   //b1-b2 X b1 a1
    f[3] = LCP(b1, b2, b1, a2);   //b1-b2 X b1 a2
    return (f[0]*f[1]<=EPS && f[2]*f[3]<=EPS);      //<0则意味着在不同方向，用eps消除精度误差
}
