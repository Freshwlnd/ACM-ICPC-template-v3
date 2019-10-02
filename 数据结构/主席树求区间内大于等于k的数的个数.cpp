#include<bits/stdc++.h>

using namespace std;
const int MAXN = 1e5 + 10;
struct Tree {
	int l, r, sum;
} T[MAXN * 20];
vector<int> v;//������ɢ��
int cnt, root[MAXN], a[MAXN];

void Init() {
	cnt = 0;
	T[cnt].l = 0;
	T[cnt].r = 0;
	T[cnt].sum = 0;
	root[cnt] = 0;
	v.clear();
}
//��ɢ������Ҫ��
int getid(int x) { return lower_bound(v.begin(), v.end(), x) - v.begin() + 1; }
//�������
void Update(int l, int r, int &x, int y, int pos) {
	T[++cnt] = T[y], T[cnt].sum++, x = cnt;
	if (l == r) return;
	int mid = (l + r) >> 1;
	if (mid >= pos)
		Update(l, mid, T[x].l, T[y].l, pos);
	else
		Update(mid + 1, r, T[x].r, T[y].r, pos);
}
//����
void Build(int n) {
	for (int i = 1; i <= n; i++)
		Update(1, n, root[i], root[i - 1], a[i]);//����ɢ����Ҫa[i]��Ϊgetid(a[i]);
}
//��ѯ������>=k�����ĸ���,����number
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
	��ɢ�����̣�
	for i in [1,n]
		v.push_back(a[i]);
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	��gitid����ȡa[i]��Ӧ��ɢ�����ֵ
*/