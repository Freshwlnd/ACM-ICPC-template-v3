void scan(__int128& x)//ÊäÈë
{
    x = 0;
    int f = 1;
    char ch;
    if ((ch = getchar()) == ' - ') f = -f;
    else x = x * 10 + ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9')
        x = x * 10 + ch - '0';
    x *= f;
}
void _print(__int128 x)
{
    if (x > 9) _print(x / 10);
    putchar(x % 10 + '0');
}
void print(__int128 x)//Êä³ö
{
    if (x < 0)
    {
        x = -x;
        putchar(' - ');
    }
    _print(x);
}
int main() {
    __int128 a, b;
    scan(a);
    scan(b);
    print(a + b);
}