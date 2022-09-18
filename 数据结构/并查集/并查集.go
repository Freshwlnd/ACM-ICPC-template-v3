type UFSet struct {
	Parents []int
    Size []int
	N int
}

func NewUFSet(n int) UFSet {
	parents := make([]int,n)
    size := make([]int, n)
	for i:=0; i<n; i++ {
		parents[i]=i
        size[i]=1
	}
	return UFSet{
		Parents: parents,
        Size: size,
		N: n,
	}
}

func (ufs UFSet)Find(target int) int {
	if target>ufs.N {
		return -1	// 越界
	}
	if target==ufs.Parents[target] {
		return target
	}
    ufs.Parents[target] = ufs.Find(ufs.Parents[target])
	return ufs.Parents[target]
}

func (ufs UFSet)Union(p,q int) {
	pRoot,qRoot := ufs.Find(p),ufs.Find(q)
	if pRoot!=qRoot {
		ufs.Parents[pRoot] = qRoot
        ufs.Size[qRoot] += ufs.Size[pRoot]
	}
}

func main() {
	ufs := NewUFSet(10)
	ufs.Union(0,4)
	fmt.Println(ufs.Find(4),ufs.Size[ufs.Find(4)])
}