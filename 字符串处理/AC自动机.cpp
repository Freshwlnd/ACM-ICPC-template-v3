#include <bits/stdc++.h>
using namespace std;
#define per(i, a, b) for(int i=a; i<b; ++i)

/*
    ac自动机
*/
const int MAXM(1e5+7);
struct acnode{
    int sum;
    int next[26];
    int fail;
    acnode(): fail(0), sum(0) {
        per(i, 0, 26) next[i]=0;
    }
}Node[MAXM];
int root=1;   //初始化为1
int cnt=1;    //从1开始

//插入函数
void Insert(const string& str) {
    acnode& p = Node[root];
    for(auto it: str) {
        int x = it - 'a';
        if(!p.next[x]) {
            int nn = cnt;
            Node[cnt++] = acnode();
            p.next[x]=nn;
        }
        p = Node[p.next[x]];
    }
    p.sum++;
}

//获取fail指针，在插入结束之后使用
void getfail(){
    queue<int> q;
    q.push(root);
    while(!q.empty()){
        int tem = q.front();
        q.pop();
        per(i, 0, 26) {
            int tmp = Node[tem].next[i];
            if(tmp) {
                int p = Node[tem].fail;
                while(p) {
                    if(Node[p].next[i]){
                        Node[tmp].fail = Node[p].next[i];
                        break;
                    }
                    p=Node[p].fail;
                }
                if(!p) {
                    Node[tmp].fail = root;
                }
                q.push(tmp);
            }
        }
    }
}

//匹配函数
void ac_automation(const string& str) {
    int p = root;
    for(auto it: str) {
        int x = it - 'a';
        while(!Node[p].next[x] && p != root)//没匹配到，那么就找fail指针。
            p = Node[p].fail;
        p = Node[p].next[x];
        if(!p) p = root;
        int tmp = p;
        while(tmp != root) {
            if(Node[tmp].sum >= 0) {// 在这里已经匹配成功了，执行想执行的操作即可，怎么改看题目需求+
                cnt += Node[tmp].sum;
                Node[tmp].sum = -1;
            } else break;
            tmp = Node[tmp].fail;
        }
    }
}

int main() {
    cnt = 1;
    root = cnt++;

    int n;
    cin >> n;
    string str;
    per(i, 0, n) {
        cin >> str;
        Insert(str);
    }
    getfail();

    int m;
    cin >> m;
    per(i, 0, m) {
        cin >> str;
        ac_automation(str);
    }
    cout << cnt << endl;
}
