/*
	�ó���������ƽ�������о��ε����
	�����Ҫ�����ص����������ֻ���������ȥans����
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 110;
struct node {
	int status;			//��¼��ǰ�������
	double len;			//��¼���ο��
	int l, r;			//�߶������۱�ʾ������
}t[maxn << 3];			//�洢�߶���
double x[maxn << 2];	//x������ɢ��
int xtot;
struct edge {
	double l, r, h;		//��y��֣�ĳ���ߵ���߽磬�ұ߽磬�߶�(y��λ��)
	int status;			//��¼��߻��ǳ���
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
//�Ƚ���������������
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
	if (t[now].status) {				//�����ǰy��ά�������
		t[now].len = x[t[now].r + 1] - x[t[now].l];
	}
	else if (t[now].l == t[now].r) {	//�ýڵ�û����ߣ����γ��Ⱦ���0
		t[now].len = 0;
	}
	else {
		t[now].len = t[now << 1].len + t[now << 1 | 1].len;
	}
}
//�߶���ά�������߶α�ʾ��Χ�ڴ��ھ��εĿ��
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
		xtot = unique(x, x + xtot) - x;//��ɢ��x����
		double ans = 0;
		build(0, xtot - 1, 1);
		for (int i = 0; i < etot; i++) {
			int l = lower_bound(x, x + xtot, e[i].l) - x;		//�߶���˵�������l��
			int r = lower_bound(x, x + xtot, e[i].r) - x - 1;	//�Ҷ˵��r��
			//�������ﲢ������ȫ��������10��15��20��25 ������ ��ѯ10-15 ��ôȥ��ľ���10-10
			//ʲô��˼ ��Ϊ�߶�����Ȼ����ɢ��ͳ�ƽṹ ��Ȼ���ǰ�������ѯ�����߶�
			update(l, r, 1, e[i].status);
			ans += (e[i + 1].h - e[i].h)*t[1].len;				//������֮��ĸ߶Ȳ���ϣ���i���߶ȵ��ܿ�ȣ������������
		}
		printf("Test case #%d\nTotal explored area: %.2f\n\n", test, ans);
		etot = 0;
		xtot = 0;
	}
	return 0;
}