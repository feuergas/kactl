/*
	���Թ滮������
	�㷨����㷨���� ���ﲻ������
	��Ŀ��xjoi����ƶ����� ����Ϊ�������ݴ� ���Ի�T ����Ҳ����
	������������һ���ͼ �������ɿ��� ���������ܵ�
	��ʵ�����ò���������Щ��� ����Ϊ��ģ�� �һ���д��
	�����¼���ע���
	1��-x0�����ֵ���ȡ����0 ��ô����impossible
	2�������긨�����Թ滮�� x0���ܲ��ǻ������� ���Ի�Ҫ��һ��
	3���������xi������ֵ�е�ϵ��Ϊ�� ���κ�Լ�����޷���Լ�� ��ô���� No boundary
	4�����ע����������
	5��ע��ĳЩ���ĵľ�������
	6�����Ĵ𰸾���z[0][0]
	7��ʵ�ʲ�����float��double�첻�˶��� ����long double �Ϳӵ���
*/

#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

int n,i,j,len,lenx,k,a[1001],zhu[2100];
double z[2100][4100];														// 7
bool can;

void xiao(int lenx,int x,int y)
{
	if (z[y][zhu[x]]==0)	return ;
	for (int i=0;i<=lenx;i++)
	if (i!=zhu[x])	z[y][i]+=z[y][zhu[x]]*z[x][i];
	z[y][zhu[x]]=0;
}

void ti(int len,int lenx,int x,int y)
{
	int i;
	z[x][zhu[x]]=-1;
	zhu[x]=y;
	for (i=0;i<=lenx;i++)
	if (i!=y)	z[x][i]/=-z[x][y];
	z[x][y]=0;
	for (i=0;i<=len;i++)	if (i!=x)	xiao(lenx,x,i);
}

bool avoid(int len,int lenx)
{
	int i,k,kk;
	for (k=0,i=lenx;i;i--)	if (z[0][i]>0)	k=i;
	if (!k)	return false;
	for (kk=0,i=1;i<=len;i++)
	if (z[i][k]<0&&(!kk||(z[i][0]/z[i][k]>z[kk][0]/z[kk][k])))	kk=i;
	if (!kk)																// 3
	{
		can=false;
		return true;
	}
	ti(len,lenx,kk,k);
	return true;
}

int main()
{
	scanf("%d",&n);
	for (i=1;i<=n;i++)	scanf("%d",&a[i]);
	for (i=1;i<=n;i++)
	{
		zhu[i]=i+n*2;
		z[i][i==1?n:i-1]=1;
		z[i][i]=-1;
		z[i][i==n?n+1:i+n+1]=1;
		z[i][i+n]=-1;
		z[i][0]=a[i];
	}
	for (i=n+1;i<=2*n;i++)
	{
		zhu[i]=i+n*2;
		z[i][i==1+n?n:i-n-1]=-1;
		z[i][i-n]=1;
		z[i][i==2*n?n+1:i+1]=-1;
		z[i][i]=1;
		z[i][0]=1-a[i-n];
	}
	len=2*n;
	lenx=n*4;
	for (z[0][lenx+1]=-1,i=1;i<=len;i++)	z[i][lenx+1]=1;
	for (can=true,i=1;i<=len;i++)
	if (z[i][0]<z[k][0])	k=i;
	if (z[k][0]<0)
	{
		ti(len,lenx+1,k,lenx+1);
		while (avoid(len,lenx+1));
		if (abs(z[0][0])>0.00000001)	can=false;							// 1 5 6
	}
	if (!can)
	{
		printf("Impossible\n");												// 1
		return 0;
	}
	for (i=1;i<=len;i++)
	if (zhu[i]==lenx+1)
	{
		for (j=1;j<=lenx;j++)
		if (z[i][j]!=0)	break;
		ti(len,lenx+1,i,j);											// 2
	}
	for (i=0;i<=lenx;i++)	z[0][i]=0;
	for (i=1;i<=2*n;i++)	z[0][i]=-1;
	for (i=1;i<=len;i++)	xiao(lenx,i,0);
	while (avoid(len,lenx))
	if (!can)
	{
		printf("No boundary\n");									// 3
		return 0;
	}
	printf("%d\n",int(-z[0][0]+0.5));								// 4 6
}
