//不下降子序列个数等于最长上升子序列长度
int a[maxn], dp[maxn], T, n;
void acm() {
    cin >> T;
    Tcase(T) {
        cin >> n;
        upf(i, 1, n) cin >> a[i];
        int len = 0;
        for (int i = 1; i <= n; i++) {
            int pos = lower_bound(dp, dp + len, a[i]) - dp; //最长不下降子序列用upper_bound,最长上升子序列用lower_bound
            if (pos == len)//如果可以接在len后面就接上，如果是最长上升子序列，这里变成
                dp[len++] = a[i];
            else//否则就找一个最该替换的替换掉    
                dp[pos] = a[i];
        }//最终len就是要求的最长上升子序列长度
    }
}