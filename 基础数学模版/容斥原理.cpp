int solve (int n, int r) {  //求[1,r]中与n互质的数的个数
    vector<int> p;
    for (int i=2; i*i<=n; ++i)  //因式分解n
        if (n % i == 0) {
            p.push_back (i);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        p.push_back (n);  //p中存储n的质因数
    int sum = 0;
    for (int msk=1; msk<(1<<p.size()); ++msk) {
        int mult = 1,
        bits = 0;
        for (int i=0; i<(int)p.size(); ++i)
            if (msk & (1<<i)) {
                ++bits;
                mult *= p[i];
            }
        int cur = r / mult;
        if (bits % 2 == 1)
            sum += cur;
        else
            sum -= cur;
    }//sum求出不与n互质的数的个数
    return r - sum;
}
