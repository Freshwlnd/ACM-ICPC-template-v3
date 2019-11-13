struct node {
	double val[555];//��¼��������ʹ�С
	int cost;
};
bool cmp(const node &a, const node &b)
{
	return a.cost < b.cost;
}
node p[555];//p��¼����
int pos[555];//��¼���浽���Ի��ڵ�����
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
		for (int j = 0; j < m; j++){// �����Ѿ����ɵ����Ի����˴�ֻ�Ǳ���ö��ÿһά����pos[j]����������ʾ�ɷ����
			if (fabs(p[i].val[j]) <= eps)//�������㣬��ά�ȱ�������������ʾ
				continue;
			if (pos[j] == -1){//���ܱ���ʾ���Ҹ�ά�Ȳ�����¼
				pos[j] = i;
				num++;
				f += p[i].cost;
				break;
			}
			else{//���ܱ���ʾ���Ǹ�ά���Ѿ�����¼
				double xs = p[i].val[j] / p[pos[j]].val[j];//jά����pos[j]��������ʾʱ�ı�ֵ
				for (int k = j; k < m; k++){
					p[i].val[k] -= p[pos[j]].val[k] * xs;//ÿ��ά�ȼ�ȥ��ֵ*pos[j]����ά��ֵ��������Ԫ
				}
			}
		}
	}
	cout << num << ' ' << f << endl;
}