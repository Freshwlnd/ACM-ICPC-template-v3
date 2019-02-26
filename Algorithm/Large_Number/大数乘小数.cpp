//ss = a*b
int Mul(char a[], char ss[], int b) {
	int i, j, len;
	char tmp[1000];
	len = strlen(a);
	for (i = 0; i < len; i++)
		tmp[len - i - 1] = a[i] - '0';              //将字符数组a转换成整型数组，并逆序记录在tmp中
	int c = 0, s;
	for (j = 0; j < len; j++)                  //模拟人工手算
	{
		s = tmp[j] * b + c;                   //记录每次相乘的结果(包括进位)
		tmp[j] = s % 10;
		c = s / 10;
	}
	while (c)                            //对数据位数修正
  {
		tmp[len++] = c % 10;
		c /= 10;
	}
	for (i = 0; i < len; i++)
		ss[i] = tmp[len - 1 - i] + '0';              //再次逆序并换成字符数组
	ss[len] = 0;
	return 0;
}
