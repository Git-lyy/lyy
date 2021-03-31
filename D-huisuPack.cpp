#include<iostream>
using namespace std;
int C;				//背包容量 
bool selected[10000];		//当前选择方案 
bool best[100];		//最佳选择方案 
int max_Value = 0;		//最大价值 
int v = 0;		//当前背包价值
int C1;		//剩余背包价值
int weight[200];			//背包重量 
int value[200];			//背包价值 

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
		if(C1 >= 0){	//遍历左子树 
			selected[i] = 1;
			v += value[i];
			dfs(i+1);
			selected[i] = 0;
			v -= value[i];
			C1+= weight[i];
		}else{//不满足原路返回 
			C1 += weight[i];
		}
	}
	//遍历右子树
	dfs(i+1); 
}


int main(){
	int i,n;
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
	dfs(1);
	cout<<"最佳方案为："<<endl;
	for(int i = 1 ; i <= n ; i++){
		if(best[i] == 1){
			cout<<i<<" "; 
		}
	}
	cout<<endl<<"最大背包价值为："<<endl<<max_Value;
	
	return 0;
}
