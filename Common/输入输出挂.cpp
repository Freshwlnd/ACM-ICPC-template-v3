//input
template <typename T>
inline bool scan_d(T &x) {
	char c; 
	int sgn;
    if (c = getchar(), c == EOF) {
        return 0; //EOF 
    }
    while (c != '-' && (c < '0' || c > '9')) {
        c = getchar(); 
    }
    sgn = (c == '-') ? -1 : 1;
    x = (c == '-') ? 0 : (c - '0'); 
    while (c = getchar(), c >= '0' && c <= '9') {
        x = x * 10 + (c - '0'); 
    }
    x *= sgn;
    return 1;
}



//output
template <typename T>
inline void print_d(T x) { 
    if (x > 9) {
        print_d(x / 10); 
    }
    putchar(x % 10 + '0');
}
