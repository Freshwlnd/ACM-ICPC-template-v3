struct node {
	double val[555];//记录向量方向和大小
	int cost;
};
bool cmp(const node &a, const node &b)
{
	return a.cost < b.cost;
}
node p[555];//p记录向量
int pos[555];//记录保存到线性基内的向量
double eps = 1e-5;
int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			scanf("%lf", &p[i].val[j]);
		}
	}
	for (int i = 0; i < n; i++){
		scanf("%d", &p[i].cost);
	}
	sort(p, p + n, cmp);
	memset(pos, -1, sizeof(pos));
	int num = 0, f = 0;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){// 对于已经建成的线性基，此处只是暴力枚举每一维度用pos[j]处的向量表示可否成立
			if (fabs(p[i].val[j]) <= eps)//经过运算，该维度被其他向量所表示
				continue;
			if (pos[j] == -1){//不能被表示并且该维度不曾记录
				pos[j] = i;
				num++;
				f += p[i].cost;
				break;
			}
			else{//不能被表示但是该维度已经被记录
				double xs = p[i].val[j] / p[pos[j]].val[j];//j维度用pos[j]处向量表示时的比值
				for (int k = j; k < m; k++){
					p[i].val[k] -= p[pos[j]].val[k] * xs;//每个维度减去比值*pos[j]处的维度值类似于消元
				}
			}
		}
	}
	cout << num << ' ' << f << endl;
}