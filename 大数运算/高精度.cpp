const int Mod = 10000;
struct HP {
    int p[505], len;
    HP() {
        memset(p, 0, sizeof p);
        len = 1;
    }
    void print() {
        printf("%d", p[len]);
        drf(i, len - 1, 1) {
            if (p[i] == 0) {
                printf("0000");
                continue;
            }
            for (int k = 10; k * p[i] < Mod; k *= 10) {
                printf("0");
            }
            printf("%d", p[i]);
        }
        printf("\n");
    }
};

HP operator + (const HP& a, const HP& b) {
    HP c;
    c.len = max(a.len, b.len);
    int x = 0;
    upf(i, 1, c.len) {
        c.p[i] = a.p[i] + b.p[i] + x;
        x = c.p[i] / Mod;
        c.p[i] %= Mod;
    }
    if (x > 0)c.p[++c.len] = x;
    return c;
}
//小数据验证成功
HP operator + (const HP& a, const int& b) {
    HP c;
    c.len = a.len;
    upf(i, 1, a.len)c.p[i] = a.p[i];
    int x = 0;
    c.p[1] = a.p[1] + b + x;
    x = c.p[1] / Mod;
    c.p[1] %= Mod;
    int pos = 2;
    while (pos <= c.len && x != 0) {
        c.p[pos] = a.p[pos] + x;
        x = c.p[pos] / Mod;
        c.p[pos++] /= Mod;
    }
    if (x > 0)c.p[++c.len] = x;
    return c;
}

HP operator * (const HP& a, const int& b) {
    HP c;
    c.len = a.len;
    int x = 0;
    upf(i, 1, c.len) {
        c.p[i] = a.p[i] * b + x;
        x = c.p[i] / Mod;
        c.p[i] %= Mod;
    }
    while (x > 0) {
        c.p[++c.len] = x % Mod;
        x /= Mod;
    }
    return c;
}
//小数据验证成功
HP operator * (const HP& a, const HP& b) {
    HP c;
    upf(i, 1, a.len) {
        upf(j, 1, b.len) {
            c.p[i + j - 1] = c.p[i + j - 1] + a.p[i] * b.p[j];
            c.p[i + j] += c.p[i + j - 1] / Mod;
            c.p[i + j - 1] %= Mod;
        }
    }
    drf(i, a.len + b.len + 1, 1)if (c.p[i] != 0) { c.len = i; break; }
    return c;
}
HP max(const HP& a, const HP& b) {
    if (a.len < b.len)return b;
    else if (a.len > b.len)return a;
    else {
        drf(i, a.len, 1) {
            if (a.p[i] > b.p[i])return a;
            else if (a.p[i] < b.p[i])return b;
        }
        return a;
    }
}