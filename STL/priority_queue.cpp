//升序队列
priority_queue<int, vector<int>, greater<int> > q;
//降序队列
priority_queue<int, vector<int>, less<int> > q;
//pair比较,pair.first再pair.second高到低排序
priority_queue<pair<int, int> > q;
//重载<运算符
struct tmp1
{
    int x;
    tmp1(int a) { x = a; }
    bool operator<(const tmp1& a) const
    {
        return x < a.x;//大到小排序(大顶堆)
    }
};
//重写仿函数
struct tmp2
{
    bool operator()(tmp1 a, tmp1 b)
    {
        return a.x < b.x;//大顶堆
    }
};
//调用比较函数方法
int main() {
    tmp1 a(1);
    tmp2 b(2);
    tmp3 c(3);
    priority_queue<tmp1> d;
    d.push(a);
    d.push(b);
    d.push(c);//排序结果3.2.1
    //自写排序函数
    priority_queue<tmp1, vector<tmp1>, tmp2> f;
    f.push(c);
    f.push(a);
    f.push(b);//排序结果3.2.1

}