#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// head

//不支持负数 减法、乘法、除法
struct BigInteger {
    static const int BASE = 100000000;
    static const int WIDTH = 8;
    vector<int> s;

    BigInteger(long long num = 0) { *this = num; }
    BigInteger& operator = (long long num) {
        s.clear();
        do {
            s.push_back(num % BASE);
            num /= BASE;
        } while(num > 0);
        return *this;
    }
    BigInteger& operator = (const string &str) {
        s.clear();
        int x, len = (str.length() - 1) / WIDTH + 1;
        for(int i = 0; i < len; ++i) {
            int end = str.length()-i*WIDTH;
            int start = max(0, end-WIDTH);
            sscanf(str.substr(start, end-start).c_str(), "%d", &x);
            s.push_back(x);
        }
        return *this;
    }
    BigInteger operator +(const BigInteger &b) const {
        BigInteger c;
        c.s.clear();
        for(int i=0, g=0; ; i++) {
            if (g == 0 && i >= s.size() && i >= b.s.size()) break;
            if (i < s.size()) g += s[i];
            if (i < b.s.size()) g += b.s[i];
            c.s.push_back(g % BASE);
            g /= BASE;
        }
        return c;
    }
    BigInteger& operator +=(const BigInteger &b) {
        *this = *this + b;
        return *this;
    }
    BigInteger operator -(const BigInteger& b) const {
        BigInteger c;
        c.s.clear();
        if (b > *this) {
            c.s.push_back(0);
            return c;
        }
        for (int i = 0, g = 0;; i++) {
            if (g == 0 && i >= s.size() && i >= b.s.size()) break;
            g += s[i];
            if (i < b.s.size()) g -= b.s[i];
            c.s.push_back((g+BASE) % BASE);
            if(g<0) g -= BASE;
            g /= BASE;
        }
        while (c.s.size()>0 && !c.s[c.s.size() - 1]) {
            c.s.pop_back();
        }
        if(c.s.size()==0) {
            c.s.push_back(0);
        }
        return c;
    }
    BigInteger& operator -=(const BigInteger &b) {
        *this = *this - b;
        return *this;
    }
    BigInteger operator *(const BigInteger &b) const {
        BigInteger c;
        c.s.clear();
        vector<long long> ss;
        int i;
        ss.assign(s.size() + b.s.size(), 0);
        c.s.assign(s.size() + b.s.size(), 0);
        for (i = 0; i < s.size(); i++) {
            for (int j = 0; j < b.s.size(); j++) {
                ss[i + j] += (long long)s[i] * b.s[j];
            }
        }
        for (i = 0; i < ss.size() - 1; i++) {
            ss[i + 1] += ss[i] / BASE;
            c.s[i] = ss[i] % BASE;
        }
        c.s[ss.size() - 1] = ss[ss.size() - 1] % BASE;
        if (!c.s[c.s.size() - 1]) {
            c.s.pop_back();
        }
        return c;
    }
    BigInteger operator *=(const BigInteger &b) {
        *this = *this * b;
        return *this;
    }
    bool operator < (const BigInteger &b) const {
        if (s.size() != b.s.size()) return s.size() < b.s.size();
        for (int i = s.size() - 1; i >= 0; i--) {
            if (s[i] != b.s[i]) return s[i] < b.s[i];
        }
        return false;
    }
    bool operator > (const BigInteger &b) const { return b < *this; }
    bool operator <= (const BigInteger &b) const { return !(b < *this); }
    bool operator >= (const BigInteger &b) const { return !(*this < b);}
    bool operator != (const BigInteger &b) const { return b < *this || *this < b; }
    bool operator == (const BigInteger &b) const { return !(b < *this) && !(*this < b); }
    int trToInt() {
        return s[0];
    }
};

ostream& operator << (ostream &out, const BigInteger &x) {
    out << x.s.back();
    for(int i=x.s.size()-2; i>=0; i--) {
        char buf[20];
        sprintf(buf, "%08d", x.s[i]);
        for(int j=0; j<strlen(buf); j++) {
            out << buf[j];
        }
    }
    return out;
}

istream& operator >> (istream &in, BigInteger &x) {
    string s;
    if(!(in >> s)) {
        return in;
    }
    x = s;
    return in;
}

int main() {
    BigInteger a,b;
    while(cin >> a >> b) {
        cout << a << " + " << b << " = " << a+b << endl;
        cout << a << " - " << b << " = " << a-b << endl;
        cout << a << " * " << b << " = " << a*b << endl;
    }
}
