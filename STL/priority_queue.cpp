//�������
priority_queue<int, vector<int>, greater<int> > q;
//�������
priority_queue<int, vector<int>, less<int> > q;
//pair�Ƚ�,pair.first��pair.second�ߵ�������
priority_queue<pair<int, int> > q;
//����<�����
struct tmp1
{
    int x;
    tmp1(int a) { x = a; }
    bool operator<(const tmp1& a) const
    {
        return x < a.x;//��С����(�󶥶�)
    }
};
//��д�º���
struct tmp2
{
    bool operator()(tmp1 a, tmp1 b)
    {
        return a.x < b.x;//�󶥶�
    }
};
//���ñȽϺ�������
int main() {
    tmp1 a(1);
    tmp2 b(2);
    tmp3 c(3);
    priority_queue<tmp1> d;
    d.push(a);
    d.push(b);
    d.push(c);//������3.2.1
    //��д������
    priority_queue<tmp1, vector<tmp1>, tmp2> f;
    f.push(c);
    f.push(a);
    f.push(b);//������3.2.1

}