#include <bits/stdc++.h>
using namespace std;

vector<int> Next;   // Next[i]表示 ptr“0～i-1” 中，“最长前后缀”长度

void getNext(string ptr) {
    int len = ptr.size();
    Next = vector<int>(len,-1);
    int i=0, k=-1;
    while(i<len) {
        if(k==-1 || ptr[k]==ptr[i]) {
            ++i;++k;
            Next[i] = k;
        } else {
            k = Next[k];
        }
    }
}

int kmp(string str, string ptr) { // 在str中匹配ptr
    getNext(ptr);
    int i=0, j=0;
    int len1=str.size();
    int len2=ptr.size();
    while(i<len1&&j<len2) {
        if(j==-1 || str[i]==ptr[j]) {
            i++;j++;
        } else {
            j=Next[j];  //到前一个匹配点
        }
    }
    if(j>=len2) {
        return i-j;
    } else {
        return -1;
    }
}

int main() {

    string str, ptr;    // 文本串str 模式串ptr
    
    while( cin >> str >> ptr ) {
        int ans = kmp(str,ptr);
        if(ans>=0) {
            cout << ans << endl;
        } else {
            cout << "Not Find" << endl;
        }
    }

    return 0;
}
