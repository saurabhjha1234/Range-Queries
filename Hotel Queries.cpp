#include<iostream>
#include<set>

#define INT_MIN -2147483648
#define INT_MAX 2147483647
 
using namespace std;
typedef long long ll;
const ll mod = 1e9+7; 
int arr[200000];
pair<int,int> segtree[800000];
void build(int i,int low,int high){
	if(low==high){
		segtree[i] = {arr[low],low};
		return ;
	}
	int mid =(low+high)/2;
	build(2*i+1,low,mid);
	build(2*i+2,mid+1,high);
	if(segtree[2*i+1].first>=segtree[2*i+2].first)
		segtree[i] = segtree[2*i+1];
	else
	segtree[i] = segtree[2*i+2];
}
void update(int i,int low,int high,int ind,int val){
	if(low==high){
		arr[low] = val;
		segtree[i] = {arr[low],low};
		return ;
	}
	int mid=(low+high)/2;
	if(ind<=mid)
		update(2*i+1,low,mid,ind,val);
	else
		update(2*i+2,mid+1,high,ind,val);
	if(segtree[2*i+1].first>segtree[2*i+2].first)
		segtree[i] = segtree[2*i+1];
	else if(segtree[2*i+1].first<segtree[2*i+2].first)
	segtree[i] = segtree[2*i+2];
	else{
		if(segtree[2*i+1].second>segtree[2*i+2].second)
			segtree[i] = segtree[2*i+2];
		else
		segtree[i] = segtree[2*i+1];	
	}
}
pair<int,int> query(int i,int low,int high,int x){
	if(low==high){
		return segtree[i];
	}
	int mid  =(low+high)/2;
	if(segtree[2*i+1].first>=x)
		return query(2*i+1,low,mid,x);
	else
	 return query(2*i+2,1+mid,high,x);
}
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=0;i<n;i++){
		cin>>arr[i];
	}
	build(0,0,n-1);
	for(int i=0;i<m;i++){
		int x;
		cin>>x;
		if(segtree[0].first<x){
			cout<<0<<" ";
			continue;
		}
		auto tmp = query(0,0,n-1,x);
		update(0,0,n-1,tmp.second,tmp.first-x);
		cout<<tmp.second+1<<" ";
	}
	return 0;	
}
