#include<bits/stdc++.h>

using namespace std;
const int MAXN = 1e5 + 10;
struct Tree {
	int l, r, sum;
} T[MAXN * 20];
vector<int> v;//用于离散化
int cnt, root[MAXN], a[MAXN];

void Init() {
	cnt = 0;
	T[cnt].l = 0;
	T[cnt].r = 0;
	T[cnt].sum = 0;
	root[cnt] = 0;
	v.clear();
}
//离散化后需要用
int getid(int x) { return lower_bound(v.begin(), v.end(), x) - v.begin() + 1; }
//单点更新
void Update(int l, int r, int &x, int y, int pos) {
	T[++cnt] = T[y], T[cnt].sum++, x = cnt;
	if (l == r) return;
	int mid = (l + r) >> 1;
	if (mid >= pos)
		Update(l, mid, T[x].l, T[y].l, pos);
	else
		Update(mid + 1, r, T[x].r, T[y].r, pos);
}
//建树
void Build(int n) {
	for (int i = 1; i <= n; i++)
		Update(1, n, root[i], root[i - 1], a[i]);//有离散化需要a[i]改为getid(a[i]);
}
//查询区间内>=k的数的个数,返回number
int Query(int l, int r, int x, int y, int k) {
	if (l == r) {
		if (l < k)return 0;
		else return T[y].sum - T[x].sum;
	}
	int mid = (l + r) >> 1;
	int sum = T[T[y].r].sum - T[T[x].r].sum;
	if (mid + 1 >= k)
		return Query(l, mid, T[x].l, T[y].l, k) + sum;
	else
		return Query(mid + 1, r, T[x].r, T[y].r, k);
}
/*
	离散化过程：
	for i in [1,n]
		v.push_back(a[i]);
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	用gitid来获取a[i]对应离散化后的值
*/