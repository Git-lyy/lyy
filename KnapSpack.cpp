#include <iostream>
#include <algorithm>
using namespace std;
int n=100,C;//C为背包总容量 
int p[100],M[1000];
int V[100][100];
int x[1000]={'0'};
int k=0,w=0,y=0,z=0;
bool selected[10000];		//当前选择方案 
bool best[100];		//最佳选择方案 
int max_Value = 0;		//最大价值 
int v = 0;		//当前背包价值
int C1;		//剩余背包价值
int weight[200];			//背包重量 
int value[200];			//背包价值 

void huisu(int i)
{
	if(i > n){
		if(v >= max_Value){
			for(int i = 1 ; i <= n ; i++){
				best[i] = selected[i];
			}
			max_Value = v;
		}
		return;
	}else{
		C1 -= weight[i];
		if(C1 >= 0){	//遍历左子树 
			selected[i] = 1;
			v += value[i];
			huisu(i+1);
			selected[i] = 0;
			v -= value[i];
			C1+= weight[i];
		}else{//不满足原路返回 
			C1 += weight[i];
		}
	}
	//遍历右子树
	huisu(i+1); 
}

int KnapSack(int n,int C, int w[ ], int v[ ])
{
	int i=0;
	int j=0;
	for ( i=0; i<=n; i++) //初始化第0列
	{
		V[i][0]=0;
	} 
	
	for ( j=0; j<=C; j++) //初始化第0行
	{
		V[0][j]=0;
	}

	for (i = 1; i <= n; i++) //计算第i行，进行第i次迭代
	{
		for (j = 1; j <= C; j++)
		{
			if (j < w[ i ])
			{
				V[ i ][ j ] =V[ i-1][ j ]; 
			 } 
				
			else
			{
				if(V[i-1][j]<=V[i-1][j-w[i]]+v[i])
				{
					V[i][j] = V[i-1][j-w[i]]+v[i];
				}
				else
				{
					V[i][j] = V[i-1][j];
				}
				//V[i][j] =max(V[i-1][j],V[i-1][j-w[i]]+v[i]);
			} 
		}
	}					
	j = C; //求装入背包的物品
	for ( i = n; i > 0; i--)
	{
		if (V[ i ][ j ]>V[i-1][ j ]) 
		{
			x[ i ] = 1; j = j - w[ i ]; 
		}
		else 
		{
			x[ i ] = 0; 
		}
			
	}
	for(int i=0;i<n;i++)
	{
		if(x[i]==1)
		{
			printf("选择物品为第","%d","个",x[i]);
		}
	} 
	
	return V[n][C]; //返回背包取得的最大价值
}

int sort(int w[ ], int v[ ],int low,int high)//二分排序 
{
	int R = 0 ;
	int  result[]={'0'};
	for(int i = 0;i <= sizeof(w); i++)
	{
		result[i]=w[i]/v[i];
	}
	int i = low;
    int j = high;
    
    while(i<j)
    {
    	while (i<j && result[i]<= result[j]) 
    		j--;
    	if(i<j)
    	{
       		int temp=w[i];
       		w[i]=w[j];
       		w[j]=temp;
       		int temp1=v[i];
       		v[i]=v[j];
       		v[j]=temp;
       		i++;
		}
    	while (i < j && result[i] <= result[j])
    		i++;
    	if (i<j){
    		int temp;
    		temp=w[i];
    		w[i]=w[j];
    		w[j]=temp;
    		int temp1;
    		temp1=v[i];
    		v[i]=v[j];
    		v[j]=temp1;
    		j--;
    	}
	}
    
   return i;
}

void QuickSort(int P[ ],int M[] ,int low, int high) 
{ 
	int pivot;
	if (low < high) 
	{ //问题分解，pivot是轴值在序列中的位置 
		pivot = sort(P, M,low, high); 
		QuickSort(P, M,low, pivot-1); //递归地对左侧子序列进行快排 
		QuickSort(P,M, pivot+1, high); //递归地对右侧子序列进行快排 
	} 
}

int main()
{
	//用户自主选择算法求解最优解和时间（s） 
	//求解结果保存txt文档
	int n,C,w[100],v[100];
	cout<<"输入背包容量："<<endl;
	cin>>C;
	C1 = C; 
	cout<<"请输入背包个数："<<endl;
	cin>>n;
	cout<<"请输入每个背包重量："<<endl;
	for(int i = 1 ; i <= n ; i++){
		cin>>weight[i];
	}
	cout<<"请输入每个背包价值："<<endl;
	for(int i = 1 ; i <= n ; i++){
		cin>>value[i];
	} 
	cout<<"请选择解决背包问题的算法："<<endl;
	cout<<"1.动态规划"<<endl;
	cout<<"2.回溯法"<<endl;
	int x;
	cin>>x;
	switch(x){
		case 1:
			if(x==1)
			{
				KnapSack(n,C,w,v);
			}
		case 2:
			if(x==2)
			{
				huisu(1);
				cout<<"最佳方案为："<<endl;
				for(int i = 1 ; i <= n ; i++)
				{
					if(best[i] == 1)
					{
						cout<<i<<" "; 
					}
				}
			cout<<endl<<"最大背包价值为："<<endl<<max_Value;
	
			return 0;
			}
 		} 
	return 0;
}

