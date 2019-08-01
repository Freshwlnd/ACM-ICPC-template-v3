//树状数组一般适用于三类问题：
//1，修改一个点求一个区间
//2，修改一个区间求一个点
//3，求逆序列对
//用树状数组能够解决的问题，用线段树肯定能够解决，反之则不一定。
//树状数组较为节省空间，实现要比线段树要容易得多，而且在处理某些问题的时候使用树状数组效率反而会高得多。 
//线段树擅长处理横向区间的问题，树状数组擅长处理纵向区间的问题。

const int MAXN = 50010;
int a[MAXN], ans[MAXN << 2], lazy[MAXN << 2];
//a[]为原序列信息，ans[]模拟线段树维护区间和，lazy[]为懒惰标记

//(1)更新结点信息
void PushUp(int rt) {
	ans[rt] = ans[rt << 1] + ans[rt << 1 | 1];
}

//(2)建树
void Build(int l, int r, int rt) {
	if (l == r) {
		ans[rt] = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	Build(l, mid, rt << 1);
	Build(mid + 1, r, rt << 1 | 1);
	PushUp(rt);
}

//(3)下推懒惰标记
//ln表示左子树元素结点个数，rn表示右子树结点个数
void PushDown(int rt, int ln, int rn) {
	if (lazy[rt]) {
		lazy[rt << 1] += lazy[rt];
		lazy[rt << 1 | 1] += lazy[rt];
		ans[rt << 1] += lazy[rt] * ln;
		ans[rt << 1 | 1] += lazy[rt] * rn;
		lazy[rt] = 0;
	}
}

//(4)点更新
void Add(int L, int C, int l, int r, int rt) {
	if (l == r) {
		ans[rt] += C;
		return;
	}
	int mid = (l + r) >> 1;
	//PushDown(rt,mid-l+1,r-mid); 若既有点更新又有区间更新，需要这句话
	if (L <= mid) { Add(L, C, l, mid, rt << 1); }
	else { Add(L, C, mid + 1, r, rt << 1 | 1); }
	PushUp(rt);
}

//(5)区间更新
void Update(int L, int R, int C, int l, int r, int rt) {
	if (L <= l && r <= R) {
		ans[rt] += C * (r - l + 1);
		lazy[rt] += C;
		return;
	}
	int mid = (l + r) >> 1;
	PushDown(rt, mid - l + 1, r - mid);
	if (L <= mid) { Update(L, R, C, l, mid, rt << 1); }
	if (R > mid) { Update(L, R, C, mid + 1, r, rt << 1 | 1); }
	PushUp(rt);
}

//(6)区间查询
ll Query(int L, int R, int l, int r, int rt) {
	if (L <= l && r <= R)
		return ans[rt];
	int mid = (l + r) >> 1;
	PushDown(rt, mid - l + 1, r - mid);//若更新只有点更新，不需要这句
	ll ANS = 0;
	if (L <= mid) { ANS += Query(L, R, l, mid, rt << 1); }
	if (R > mid) { ANS += Query(L, R, mid + 1, r, rt << 1 | 1); }
	return ANS;
}

int n, L, C, R;
int main() {
	//若重复，则需清空lazy
	//建树   
	Build(1, n, 1);
	//点更新  
	Add(L, C, 1, n, 1);
	//区间修改   
	Update(L, R, C, 1, n, 1);
	//区间查询   
	int ANS = Query(L, R, 1, n, 1);
}
/*
若只涉及点更新的题，只需用(1)(2)(4)(6)
若只涉及区间更新的题，需用(1)(2)(3)(5)(6)
若为两种更新都有，则在所有向子区间查询或更新前，都需PushDown()
*/
