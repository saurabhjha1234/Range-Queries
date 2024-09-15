#include<iostream>
#include<set>

#define INT_MIN -2147483648
#define INT_MAX 2147483647
 
using namespace std;
typedef long long ll;
const ll mod = 1e9+7; 
int arr[200001];
int segtree[800004];
void build(int i,int low,int high){
	if(low==high){
		segtree[i] = 1;
		return ;
	}
	int mid =(low+high)/2;
	build(2*i+1,low,mid);
	build(2*i+2,mid+1,high);
	segtree[i] = segtree[2*i+2]+segtree[2*i+1];
}
void update(int i,int low,int high,int ind){
	if(low==high){
		segtree[i] = 0;
		return ;
	}
	int mid=(low+high)/2;
	if(ind<=mid)
		update(2*i+1,low,mid,ind);
	else
		update(2*i+2,mid+1,high,ind);
	segtree[i] = segtree[2*i+2]+segtree[2*i+1];
}
int query(int i,int low,int high,int x){
	if(low==high){
		return low;
	}
	int mid  =(low+high)/2;
	if(segtree[2*i+1]<x)
		return query(2*i+2,1+mid,high,x-segtree[2*i+1]);
	else 
	 return query(2*i+1,low,mid,x);

}
int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>arr[i];
	}
	build(0,0,n-1);
	for(int i=0;i<n;i++){
		int x;
		cin>>x;
		int id =query(0,0,n-1,x);
		cout<<arr[id]<<" ";
		update(0,0,n-1,id);
	}
	return 0;
}
	