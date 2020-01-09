#define pii pair<int,int>
struct Maze01 {
    // ԭʼ01���� 1-n 1-m
    bool a[maxn][maxn];
    // ��(i,j)�������߶ȵ�����Ӿ������pos\��pos\�߶�
    int l[maxn][maxn], r[maxn][maxn], h[maxn][maxn];
    // �������ǰ׺1�����λ��, ���(i,j)Ϊ0��ml=j+1
    int ml[maxn][maxn];
    // �����С
    int n, m;

    void prework() {
        for (int i = 1; i <= m; i++) {
            l[0][i] = 0;
            r[0][i] = m;
        }
        for (int i = 1; i <= n; i++) {
            int maxl = 1;
            int maxr = m;
            for (int j = 1; j <= m; j++) {
                if (a[i][j] == 0) {
                    maxl = j + 1;
                    h[i][j] = l[i][j] = 0;
                }
                else {
                    h[i][j] = h[i - 1][j] + 1;
                    l[i][j] = max(maxl, l[i - 1][j]);
                }
                ml[i - 1][j] = maxl;
                ml[i][j] = j + 1;
            }
            for (int j = m; j >= 1; --j) {
                if (a[i][j] == 0) {
                    maxr = j - 1;
                    r[i][j] = m;
                }
                else {
                    r[i][j] = min(maxr, r[i - 1][j]);
                }
            }
        }
    }

    // ����ջ
    pii st[maxn];

    int calc() {
        prework();
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            int top = 0;
            for (int j = 1; j <= m; j++) {
                if (h[i][j] == 0) continue;
                if (top == 0 || st[top] != make_pair(l[i][j], r[i][j])) {
                    st[++top] = make_pair(l[i][j], r[i][j]);
                }
                while (top && st[top].second == j) {
                    int pos = st[top--].first;
                    if (pos < ml[i][j]) {
                        // l[i][j]-r[i][j]Ϊ��, h[i][j]Ϊ��
                        // ���Եõ����е�Ψһ�Ӿ���, ������maze1��ȫ����maze2
                        ans++;
                    }
                }
            }
        }
        return ans;
    }
} dp;