#include <iostream>
#include <algorithm>
using namespace std;
int n=100,C;//CΪ���������� 
int p[100],M[1000];
int V[100][100];
int x[1000]={'0'};
int k=0,w=0,y=0,z=0;
bool selected[10000];		//��ǰѡ�񷽰� 
bool best[100];		//���ѡ�񷽰� 
int max_Value = 0;		//����ֵ 
int v = 0;		//��ǰ������ֵ
int C1;		//ʣ�౳����ֵ
int weight[200];			//�������� 
int value[200];			//������ֵ 

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
		if(C1 >= 0){	//���������� 
			selected[i] = 1;
			v += value[i];
			huisu(i+1);
			selected[i] = 0;
			v -= value[i];
			C1+= weight[i];
		}else{//������ԭ·���� 
			C1 += weight[i];
		}
	}
	//����������
	huisu(i+1); 
}

int KnapSack(int n,int C, int w[ ], int v[ ])
{
	int i=0;
	int j=0;
	for ( i=0; i<=n; i++) //��ʼ����0��
	{
		V[i][0]=0;
	} 
	
	for ( j=0; j<=C; j++) //��ʼ����0��
	{
		V[0][j]=0;
	}

	for (i = 1; i <= n; i++) //�����i�У����е�i�ε���
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
	j = C; //��װ�뱳������Ʒ
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
			printf("ѡ����ƷΪ��","%d","��",x[i]);
		}
	} 
	
	return V[n][C]; //���ر���ȡ�õ�����ֵ
}

int sort(int w[ ], int v[ ],int low,int high)//�������� 
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
	{ //����ֽ⣬pivot����ֵ�������е�λ�� 
		pivot = sort(P, M,low, high); 
		QuickSort(P, M,low, pivot-1); //�ݹ�ض���������н��п��� 
		QuickSort(P,M, pivot+1, high); //�ݹ�ض��Ҳ������н��п��� 
	} 
}

int main()
{
	//�û�����ѡ���㷨������Ž��ʱ�䣨s�� 
	//���������txt�ĵ�
	int n,C,w[100],v[100];
	cout<<"���뱳��������"<<endl;
	cin>>C;
	C1 = C; 
	cout<<"�����뱳��������"<<endl;
	cin>>n;
	cout<<"������ÿ������������"<<endl;
	for(int i = 1 ; i <= n ; i++){
		cin>>weight[i];
	}
	cout<<"������ÿ��������ֵ��"<<endl;
	for(int i = 1 ; i <= n ; i++){
		cin>>value[i];
	} 
	cout<<"��ѡ��������������㷨��"<<endl;
	cout<<"1.��̬�滮"<<endl;
	cout<<"2.���ݷ�"<<endl;
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
				cout<<"��ѷ���Ϊ��"<<endl;
				for(int i = 1 ; i <= n ; i++)
				{
					if(best[i] == 1)
					{
						cout<<i<<" "; 
					}
				}
			cout<<endl<<"��󱳰���ֵΪ��"<<endl<<max_Value;
	
			return 0;
			}
 		} 
	return 0;
}

