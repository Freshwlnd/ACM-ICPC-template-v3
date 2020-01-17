//将一个字符串对应成一个数字，直接比较两个字符串是否相同。

//对Hash来说：两个元素若全等，其哈希值必定也相等；但哈希值相等，两个元素未必全等
//因此Hash时要尽量使冲突概率趋近于0

//先选择一固定值P（一般用大质数），把字符串看作一个P进制的数。
//然后选择另一固定值M，求出该P进制数对M取余的结果，即为字符串哈希值。
//M我们一般取2的64次方，但实际操作时呢我们不需要对M取模（取模是个效率极低的运算）。
//我们用unsigned long long类型保存哈希值，让其自然溢出就好，因为此类型是不会出现负数的（无符号位）。

//如果还是不放心，那可以同时做好多组P与M，判断时多判断几次，如果所有的哈希值都相等，再得出结论。

//注意点：
//  不要把任意字符对应到数字0
//  比如假如把a对应到数字0，那么将不能只从Hash结果上区分ab和b（即前缀0无法判断）
//  一般而言，把a-z对应到数字1-26比较合适。

//P的选择:
//  大于所有字符对应的数字的最大值，不要含有模数的质因子(那还模什么)
//  比如一个字符集是a到z的题目，选择27、233、19260817都是可以的。

//用前缀和维护哈希值
//以下为判断两个字符串是否相等的代码

typedef unsigned long long ull;
const ull hash1 = 201326611;
const ull hash2 = 50331653;
ull ha[MAXN], pp[MAXN];

inline ull getha(int l, int r) {
    if (l == 0) return ha[r];
    return ha[r] - ha[l - 1] * pp[r - l + 1];
}

inline bool check(int l1, int r1, int l2, int r2) {
    return getha(l1, r1) == getha(l2, r2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    //预处理pow(hash1, i)
    pp[0] = 1;
    per(i, 1, MAXN) {
        pp[i] = hash1 * pp[i - 1];
    }

    //设置连续子串对应Hash值
    ha[0] = str[0];
    for (int i = 1; i < str.length(); i++) {
        ha[i] = ha[i - 1] * hash1 + str[i];
    }

    //比较[0,1], [1,2]是否相同
    check(0, 1, 1, 2);
    
    return 0;
}
