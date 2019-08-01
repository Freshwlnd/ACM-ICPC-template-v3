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

int main() {
	int i, j, s;
	while (scanf("%d", &n) != EOF) {
		memset(c, 0, (n + 3) * sizeof(c[0]));
		for (i = 1; i <= n; i++) {
			scanf("%d", &s);
			update(s, 1);
		}
	}
	return 0;
}

