const int MAXN(3e4+7);
double x[MAXN], y[MAXN];

//Culculate Triangle Area  计算多边形面积（点按逆时针顺序）
//
//       |  1  1  1 |
// 1/2 * | x1 x2 x3 |
//       | y1 y2 y3 |
//
// 行列式值即为三角形面积
// （ x1*y2 + x2*y3 + x3*y1 - x3*y2 - x2*y1 - x1*y3 ) / 2
inline double CTA(int p1, int p2, int p3) {
    return (x[p1]*y[p2]+x[p2]*y[p3]+x[p3]*y[p1]-x[p3]*y[p2]-x[p2]*y[p1]-x[p1]*y[p3])/2;
}

//Culculate Polygon Area  计算多边形面积（点按逆时针顺序）
inline double CPA(int PN) {  //PN为点数
    double Area=0;
    per(i, 2, PN) {     //点： 1～PN
        Area += CTA(1, i, i+1);
    }
    return Area;
}

//输出小数点方法
//cout << fixed << setprecision(1) << CPA(n) << endl;