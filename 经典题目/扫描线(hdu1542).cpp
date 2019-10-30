/*
	该程序计算的是平面上所有矩形得面积
	如果需要计算重叠部分面积，只需总面积减去ans即可
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 110;
struct node {
	int status;			//记录当前入边数量
	double len;			//记录矩形宽度
	int l, r;			//线段树理论表示的区间
}t[maxn << 3];			//存储线段树
double x[maxn << 2];	//x用于离散化
int xtot;
struct edge {
	double l, r, h;		//按y轴分，某条边的左边界，右边界，高度(y轴位置)
	int status;			//记录入边还是出边
	edge() {}
	edge(double a, double b, double c, int cover) :l(a), r(b), h(c), status(cover) {}
	bool operator<(const edge &E) {
		return h < E.h;
	}
}e[maxn << 2];
int etot;
bool cmp(int a, int b) {
	return a < b;
}
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
//先建空树，后来插入
void build(int l, int r, int rt) {
	t[rt].l = l;
	t[rt].r = r;
	t[rt].status = t[rt].len = 0;
	if (l == r)return;
	int mid = l + r >> 1;
	build(lson);
	build(rson);
}
void pushup(int now) {
	if (t[now].status) {				//如果当前y轴维度有入边
		t[now].len = x[t[now].r + 1] - x[t[now].l];
	}
	else if (t[now].l == t[now].r) {	//该节点没有入边，矩形长度就是0
		t[now].len = 0;
	}
	else {
		t[now].len = t[now << 1].len + t[now << 1 | 1].len;
	}
}
//线段树维护了在线段表示范围内存在矩形的宽度
void update(int l, int r, int rt, int val) {
	if (t[rt].l == l && t[rt].r == r) {
		t[rt].status += val;
		pushup(rt);
		return;
	}
	int mid = t[rt].l + t[rt].r >> 1;
	if (r <= mid)update(l, r, rt << 1, val);
	else if (l > mid)update(l, r, rt << 1 | 1, val);
	else {
		update(l, mid, rt << 1, val);
		update(mid + 1, r, rt << 1 | 1, val);
	}
	pushup(rt);
}
int main() {
	int n, test = 0;
	while (scanf("%d", &n), n) {
		double x1, x2, y1, y2;
		test++;
		for (int i = 1; i <= n; i++) {
			scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
			e[etot++] = edge(x1, x2, y1, 1);
			e[etot++] = edge(x1, x2, y2, -1);
			x[xtot++] = x1;
			x[xtot++] = x2;
		}
		sort(e, e + etot);
		sort(x, x + xtot);
		xtot = unique(x, x + xtot) - x;//离散化x坐标
		double ans = 0;
		build(0, xtot - 1, 1);
		for (int i = 0; i < etot; i++) {
			int l = lower_bound(x, x + xtot, e[i].l) - x;		//线段左端点排名第l大
			int r = lower_bound(x, x + xtot, e[i].r) - x - 1;	//右端点第r大
			//区间这里并不是完全包含比如10，15，20，25 的区间 查询10-15 那么去查的就是10-10
			//什么意思 因为线段树仍然是离散的统计结构 仍然还是按照起点查询区间线段
			update(l, r, 1, e[i].status);
			ans += (e[i + 1].h - e[i].h)*t[1].len;				//两条线之间的高度差，乘上，第i处高度的总宽度，即得最后的面积
		}
		printf("Test case #%d\nTotal explored area: %.2f\n\n", test, ans);
		etot = 0;
		xtot = 0;
	}
	return 0;
}