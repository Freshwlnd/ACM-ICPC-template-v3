int T[maxn], n, a[maxn], b[maxn], k[maxn], length, num[maxn], f[maxn], t;
int lowbit(int x) {
    return x & (-x);
}
int query(int x) {
    int ans = 0;
    while (x) {
        if (ans < T[x])
            ans = T[x];
        x -= lowbit(x);
    }
    return ans;
}
void update(int x, int len) {
    while (x <= length) {
        if (T[x] < len) T[x] = len;
        x += lowbit(x);
    }
}
void acm() {
    cin >> t;
    Tcase(t) {
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            T[i] = 0;
            cin >> a[i];
            b[i] = a[i];
        }
        sort(b + 1, b + 1 + n);
        length = unique(b + 1, b + 1 + n) - b - 1;
        int ans = 0;
        //���1��ʼ��a[i]-1������������г��Ⱥ�����
        for (int i = 1; i <= n; ++i) {
            a[i] = lower_bound(b + 1, b + 1 + length, a[i]) - b - 1;//�ж��ٸ�С��a[i]��Ԫ��
            //a[i] = length-a[i]-1;//ɾȥ��//����ɴ�a[i]+1��ʼ����β�������������
            f[i] = query(a[i]) + 1;
            ans = max(ans, f[i]);
            update(a[i] + 1, f[i]);//cout<<f[i]<<endl;
        }
    }
}