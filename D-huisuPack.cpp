#include<iostream>
using namespace std;
int C;				//�������� 
bool selected[10000];		//��ǰѡ�񷽰� 
bool best[100];		//���ѡ�񷽰� 
int max_Value = 0;		//����ֵ 
int v = 0;		//��ǰ������ֵ
int C1;		//ʣ�౳����ֵ
int weight[200];			//�������� 
int value[200];			//������ֵ 

void dfs(int i,int n)
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
			dfs(i+1);
			selected[i] = 0;
			v -= value[i];
			C1+= weight[i];
		}else{//������ԭ·���� 
			C1 += weight[i];
		}
	}
	//����������
	dfs(i+1); 
}


int main(){
	int i,n;
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
	dfs(1);
	cout<<"��ѷ���Ϊ��"<<endl;
	for(int i = 1 ; i <= n ; i++){
		if(best[i] == 1){
			cout<<i<<" "; 
		}
	}
	cout<<endl<<"��󱳰���ֵΪ��"<<endl<<max_Value;
	
	return 0;
}
