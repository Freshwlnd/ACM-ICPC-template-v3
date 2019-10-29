#define Size 1111
int Package02_FullOfPackage_Compress(int Weight[], int nLen, int nCapacity)//nCapacity是背包最大容量。需要保证比Size小。  
{  
    int MethodTable[Size];
    memset(MethodTable,0,sizeof(MethodTable));  
  
    //initiallize all MethodTable[0] with 1  
    MethodTable[0] = 1;  
  
    for(int i = 0; i < nLen; i++)  
    {  
        for(int j = Weight[i]; j <= nCapacity; j++)  //从第i件物品的重量开始遍历到最大重量。
        {  
            if(j >= Weight[i])  
                MethodTable[j] += MethodTable[j-Weight[i]];  
        }  
    }  
  
    int nRet = MethodTable[nCapacity];  
    delete [] MethodTable;  
    return nRet;  
}  
