#include<iostream> 
 
using namespace std; 
 
#define Size 1111  

int MethodTable[Size];  
int Max(int x,int y)  
{  
    return x>y?x:y;  
}  
int Package01_FullOfPackage(int Weight[], int nLen, int nCapacity)  
{  
    MethodTable[0]= 1;//初始化  
    for(int i = 1; i <= nLen; i++)  
    {  
        for(int j = nCapacity; j >=Weight[i];j--)  
        {  
        if(j >= Weight[i])    
                MethodTable[j] += MethodTable[j-Weight[i]];    
        }  
    }  
    cout << "MethodTable:" << endl;
    return MethodTable[nCapacity];  
}  
int main()  
{  
    int Weight[Size];  
    int nCapacity;//空间  
    int n_goods;//数量  
    cin>>n_goods>>nCapacity;  
    for(int k=1;k<=n_goods;k++)  
        cin>>Weight[k];  
      
      
    cout << "AllCount:" << Package01_FullOfPackage(Weight,n_goods,nCapacity) << endl;  
    return 0;  
} 
