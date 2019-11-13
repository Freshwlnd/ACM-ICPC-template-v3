#define per(i, a, b) for(int i=a; i<b; i++)
#define rep(i, a, b) for(int i=b-1; i>=a; i--)
typedef long long ll;
const int MAXN(1e6+7);

string str;             //[1,len]
int y[MAXN],x[MAXN];
int c[MAXN];            //桶
int sa[MAXN],rk[MAXN];  //排名i的后缀是谁/第i个后缀的排名 [1,len]
int height[MAXN];       //LCP(i, i-1)                 [1,len]
int len,m;              //长度/字符最大值（初始化为ascii码最大值）

void get_SA() {
    per(i, 1, len+1) ++c[x[i]=str[i]];
//c数组是桶
//x[i]是第i个元素的第一关键字
    per(i,2,m+1) c[i]+=c[i-1];
//做c的前缀和，我们就可以得出每个关键字最多是在第几名
    rep(i,1,len+1) sa[c[x[i]]--]=i;
    for (int k=1; k<=len; k<<=1) {
        int num = 0;
        per(i,len-k+1,len+1) y[++num] = i;
//y[i]表示第二关键字排名为i的数，第一关键字的位置
//第n-k+1到第n位是没有第二关键字的 所以排名在最前面
        per(i,1,len+1) if (sa[i] > k) y[++num] = sa[i] - k;
//排名为i的数 在数组中是否在第k位以后
//如果满足(sa[i]>k) 那么它可以作为别人的第二关键字，就把它的第一关键字的位置添加进y就行了
//所以i枚举的是第二关键字的排名，第二关键字靠前的先入队
        per(i,1,m+1) c[i] = 0;
//初始化c桶
        per(i,1,len+1) ++c[x[i]];
//因为上一次循环已经算出了这次的第一关键字 所以直接加就行了
        per(i,2,m+1) c[i] += c[i - 1]; //第一关键字排名为1~i的数有多少个
        rep(i,1,len+1) sa[c[x[y[i]]]--] = y[i], y[i] = 0;
//因为y的顺序是按照第二关键字的顺序来排的
//第二关键字靠后的，在同一个第一关键字桶中排名越靠后
//基数排序
        swap(x, y);
//这里不用想太多，因为要生成新的x时要用到旧的，就把旧的复制下来，没别的意思
        x[sa[1]] = 1;
        num = 1;
        per(i,2,len+1)
            x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++num;
//因为sa[i]已经排好序了，所以可以按排名枚举，生成下一次的第一关键字
        if (num == len) break;
        m = num;
//这里就不用那个122了，因为都有新的编号了
    }
}

void get_height() {
    int k=0;
    per(i,1,len+1) rk[sa[i]]=i;
    per(i,1,len+1) {
        if (rk[i]==1) continue;//第一名height为0
        if (k) --k;//h[i]>=h[i-1]-1;
        int j=sa[rk[i]-1];
        while (j+k<=len && i+k<=len && str[i+k]==str[j+k]) ++k;
        height[rk[i]]=k;//h[i]=height[rk[i]];
    }
}


int main() {

    cin >> str;
    len = str.length();
    str.insert(0, " ");
    m = int('z');
    get_SA();
    get_height();
    
}
