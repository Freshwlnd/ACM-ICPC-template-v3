set//不重复的顺序集合
  //  set<int > s;              //默认从小到大 
  //  set<int,greater<int> > s; //从大到小 greater<int>
  //  set<int,less<int> > s;    //从小到大 
  //  set<int,cmp> s;		//自写cmp排序函数
  multiset<int> s;//可重复的集合
  s.lower_bound(value);//二分查找第一个大于等于value的值，找不到返回s.end();
  s.upper_bound(value);//二分查找第一个大于value的值
  set_union():对集合取并集。附:不能用作并查集。
    set_union()函数接受5个迭代器参数。前两个迭代器定义了第一个集合的区间，接下来的俩个迭代器定义了第二个集合
    的区间，最后一个迭代器是输出迭代器，指出将结果集合复制到什么位置。例如：要将A与B的集合复制到C中，可以这样
    写：
      用法如下：
	#define ALL(x) x.begin(),x.end()
	#define INS(x) inserter(x,x.begin())
	
	set<int> A = {1,2,3}, B= {2,4,5},C;
   	set_union(ALL(A),ALL(B),INS(C));
    	for(auto it = C.begin();it != C.end();it++)
      		cout << *it <<" ";
	//输出1 2 3 4 5 
  set_intersection():对集合取交集，它的接口与set_union()相同。
    附：使用set_union()和set_intersection()还有另一种技巧。由于需要五个迭代器，看起来会很累赘和麻烦，如果多次
    使用会增加出错的几率，所以我们可以试试用宏定义的方法来简化代码。如下：
      用法如下：
	set<int> A = {1,2,3}, B= {2,4,5},C;
   	set_intersection(ALL(A),ALL(B),INS(C));
    	for(auto it = C.begin();it != C.end();it++)
      		cout << *it <<" ";
