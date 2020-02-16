class UnionFind {
private:
    int *parent;   // 标注当前元素的父节点的位置
    int size;       // 并查集中的元素个数

    //将父节点指向自身表示此为根结点，初始化层数1，所有元素独立成集合。
    void init() {
        for (int i = 0; i < size; i++) {
            parent[i] = i;
        }
    }
    
public:
    UnionFind (int _size): size(_size) {
        parent = new int[size];
        init();
    }
    //寻找父节点
    int find(int target) {
        if(target >= size)//数组越界
            return -1;
        if(target == parent[target])
            return target;
        parent[target] = find(parent[target])
        return parent[target];
    }
    //合并集合
    void get_together(int p, int q) {
        int pRoot = find(p);
        int qRoot = find(q);
        if(pRoot == qRoot)//本来就是同一个集合
            return;
        parent[qRoot] = pRoot;
    }
    // 如果两个节点的根节点一致则表示这两个节点是相连接的
    bool isConnected(int p, int q) {
        return find(p) == find(q);
    }
};
