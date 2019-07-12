string str;
int outt;

int numm[2*MAXN];   //记录各点为中心回文串半径(开区间)
void manacher() {   //计算回文串个数（包括长度为1串）
    string pptr;
    int len, len1;
    outt = 0;
    len1 = str.length();
    //init
    //‘%’ ‘#’ ‘@’ 可以是任意不存在str串中的字符
    pptr+='%';
    pptr+='#';
    for(int i=0; i<len1; i++) {
        pptr+=str[i];
        pptr+='#';
    }
    pptr+='@';
    len = pptr.length();
    //judge
    int mx, cent;   //cent:中心点  mx:已遍历过最右边的点(闭区间)
    numm[0] = mx = cent = 0;
    for(int i=1; i<len-1; i++) {    //头尾节点不遍历
        if (i > mx) {
            numm[i] = 1;
        } else {
            numm[i] = min(numm[2 * cent - i], mx - i + 1);
        }
        while (pptr[i + numm[i]] == pptr[i - numm[i]]) {
            ++numm[i];
        }
        if (i + numm[i] > mx) {
            mx = i + numm[i] - 1;
            cent = i;
        }
        outt += numm[i] / 2;
    }
}
