int a[maxn], dp[maxn], T, n;
void acm() {
    cin >> T;
    Tcase(T) {
        cin >> n;
        upf(i, 1, n) cin >> a[i];
        int len = 0;
        for (int i = 1; i <= n; i++) {
            int pos = lower_bound(dp, dp + len, a[i]) - dp; //����½���������upper_bound,�������������lower_bound
            if (pos == len)//������Խ���len����ͽ��ϣ����������������У�������
                dp[len++] = a[i];
            else//�������һ������滻���滻��
                dp[pos] = a[i];
        }//����len����Ҫ�������������г���
    }
}