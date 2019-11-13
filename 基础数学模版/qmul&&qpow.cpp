long long q_mul(long long a, long long b, long long mod) //快速乘法取模
{
    long long ans = 0;
    while (b)
    {
        if (b & 1)
        {
            ans += a;
        }
        b /= 2;
        a = (a + a) % mod;

    }
    return ans;
}

long long q_pow(long long a, long long b, long long mod) //快速乘法下的快速幂
{
    long long ans = 1;
    while (b)
    {
        if (b & 1)
        {
            ans = q_mul(ans, a, mod);
        }
        b /= 2;
        a = q_mul(a, a, mod);
    }
    return ans;
}
