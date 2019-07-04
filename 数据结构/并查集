class UnionFind {
private:
    int *parent;   // 标注当前元素的父节点的位置
    int *rank;     // 标注当前元素的层级数
    int size;       // 并查集中的元素个数

    //将父节点指向自身表示此为根结点，初始化层数1，所有元素独立成集合。
    void init() {
        for (int i = 0; i < size; i++) {
            parent[i] = i;
            rank[i] = 1;
        }
    }
    
public:
    UnionFind (int size){
        this->size = size;

        parent = new int[size];
        rank = new int[size];

        init();
    }
    //寻找父节点
    int find(int target) {
        if(target >= size)//数组越界
            return -1;
        if(target == parent[target])
            return target;
        return find(parent[target]);
    }
    //合并集合
    void get_together(int p, int q) {
        int pRoot = find(p);
        int qRoot = find(q);
        if(pRoot == qRoot)//本来就是同一个集合
            return;
        if(rank[pRoot] > rank[qRoot]) { // p 所在的树的高度比 q 所在树的高度高，这时应该让 q 的根节点元素连接到 p 的根节点元素
            parent[qRoot] = pRoot; // 此时树的高度不变
        } else if(rank[pRoot] < rank[qRoot]) {
            parent[pRoot] = qRoot; // 此时树的高度不变
        } else {
            parent[pRoot] = qRoot; // 此时树的高度 +1
            rank[qRoot] += 1;
        }
    }
    // 如果两个节点的根节点一致则表示这两个节点是相连接的
    bool isConnected(int p, int q) {
        return find(p) == find(q);
    }

};
