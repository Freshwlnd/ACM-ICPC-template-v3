#include<bits/stdc++.h>

using namespace std;

const int N = 55;

int n;//图中的点数
int bestn;//最优解
int a[N][N];//图用邻接表表示
int cn;//当前已放入团中节点数量
bool x[N];//是否将第i个节点加入团中
bool bestx[N];//记录最优解

bool can_join(int t){//判断是否可以把节点t放入团中
	bool can=true;
	for(int i=1;i<t;i++){
		if(x[i]&&a[t][i]==0){//x[i]表示i是被选中的节点，a[t][i]==0表示t和j没有边相连
			can=false;
			break;
		}
	}
	return can;
}

void dfs(int t){
	if(t>n){//到达叶子节点
		for(int i=1;i<=n;i++){
			bestx[i]=x[i];
		}
		bestn=cn;
		return;
	}
	if(can_join(t)){//满足约束条件，进入左子树，即把节点t加入团
		x[t]=1;
		cn++;
		dfs(t+1);
		cn--;
	}
	if(cn+n-t>bestn){//满足限界条件，进入右子树
		x[t]=0;
		dfs(t+1);
	}
}

int main(){
	ios_base::sync_with_stdio(false);//关同步
	while(cin>>n,n){
		for(int i=1;i<=n;i++){//下标从1开始
			for(int j=1;j<=n;j++){
				cin>>a[i][j];
			}
		}
		bestn=0;
		cn=0;
		dfs(1);
		cout<<bestn<<endl;
	}
}
