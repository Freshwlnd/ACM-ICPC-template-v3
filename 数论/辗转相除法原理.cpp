//辗转相除法求最大公约数

//原理
//	假设有两个数x和y，存在一个最大公约数z=(x,y)，即x和y都有公因数z， 
//		那么x一定能被z整除，y也一定能被z整除，所以x和y的线性组合mx±ny也一定能被z整除。（m和n可取任意整数）
//
//	对于辗转相除法来说，思路就是：
//		若x>y，设x/y=n余c，则x能表示成x=ny+c的形式，将ny移到左边就是x-ny=c，
//		由于一般形式的mx±ny能被z整除，所以等号左边的x-ny（作为mx±ny的一个特例）就能被z整除，
//		即x除y的余数c也能被z整除。
//原文：https://blog.csdn.net/a1065712890/article/details/79510352 


ll gcd(ll a, ll b) {
	return b ? gcd(b, a%b) : a; 
}
