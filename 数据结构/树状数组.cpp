<<<<<<< HEAD
#include<bits/stdc++.h>
#define per(i,a,b) for(int i=a;i<b;i++)
#define rep(i,a,n) for (int i=n-1;i>=a;i--)
#define mem(a,b) memset(a,b,sizeof(a))
#define ll long long 
using namespace std; 

const int sizze = 100111;
int c[sizze], n;

int Lowbit(int k) {
	return (k&-k);
}

void update(int pos, int num) {
	while (pos <= sizze){ //注意这里 
		c[pos] += num;
		pos += Lowbit(pos);
	}
}

int sum(int pos) {
	int s = 0;
	while (pos>0) {
		s += c[pos];
		pos -= Lowbit(pos);
	}
	return s;
}
=======
//树状数组一般适用于三类问题：
//1，修改一个点求一个区间
//2，修改一个区间求一个点
//3，求逆序列对
//用树状数组能够解决的问题，用线段树肯定能够解决，反之则不一定。
//树状数组较为节省空间，实现要比线段树要容易得多，而且在处理某些问题的时候使用树状数组效率反而会高得多。 
//线段树擅长处理横向区间的问题，树状数组擅长处理纵向区间的问题。

inline int Lowbit(int k) { return (k&-k); }
const int sizze(100111);
const int MAXN(1e5+7);

struct Binary_Indexed_Tree {
	int c[MAXN];

	inline void init() {
		for(int i=0; i<=sizze; i++) { c[i]=0; }	//[1,sizze]置0
	}
	inline void update(int pos, int num) {
		while (pos <= sizze){ //注意这里 
			c[pos] += num;
			pos += Lowbit(pos);
		}
	}
	inline int sum(int pos) {
		int s = 0;
		while (pos>0) {
			s += c[pos];
			pos -= Lowbit(pos);
		}
		return s;
	}
}BIT;
>>>>>>> upstream/master

int main() {
	int i, j, s;
	while (scanf("%d", &n) != EOF) {
<<<<<<< HEAD
		memset(c, 0, (n + 3) * sizeof(c[0]));
=======
		BIT.init();
>>>>>>> upstream/master
		for (i = 1; i <= n; i++) {
			scanf("%d", &s);
			update(s, 1);
		}
	}
	return 0;
}

