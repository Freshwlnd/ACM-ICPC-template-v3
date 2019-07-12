//凸包
#define per(i, a, b) for(int i=a; i<b; i++)
const int MAXN(4e4+7);

struct node{
    double x,y;
} a[MAXN],p[MAXN];
int top,n;

//p0-p1 X p0-p2
inline double cross(node p0, node p1, node p2){//计算叉乘，注意p0,p1,p2的位置，这个决定了方向
    return (p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x);
}

inline double dis(node a, node b){//计算距离，这个用在了当两个点在一条直线上
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

int cmp(node p1, node p2){//极角排序
    double z=cross(a[1], p1, p2);
    if(z>0 || (z==0 && dis(a[1], p1)<dis(a[0], p2))) return 1;
    return 0;
}

inline void Graham(){
    int k=1;
    per(i,1,n+1){
        if(a[i].y==a[k].y?a[i].x<a[k].x:a[i].y<a[k].y){
            k=i;
        }
    }
    swap(a[1], a[k]);   //将最下且左的点作为起点
    sort(a+2, a+n+1, cmp);  //按极角排序
    top=2;
    p[1]=a[1];
    p[2]=a[2];
    per(i,3,n+1) {//控制进栈出栈
        while(top>1 && cross(p[top-1],p[top],a[i])<0) top--;
        p[++top]=a[i];
    }
}

int main(){

    while(cin >> n && n){
        per(i,1,n+1){
            cin >> a[i].x >> a[i].y;
        }
        Graham();
        per(i,1,top+1) {
            cout << p[i].x << p[i].y << '\n';
        }
    }

    return 0;
}
