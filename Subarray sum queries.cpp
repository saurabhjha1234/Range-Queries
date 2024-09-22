#include<iostream>
#include<unordered_map>
#include<vector>
#include<algorithm>
#define INT_MIN -2147483648
#define INT_MAX 2147483647
 
using namespace std;
typedef long long ll;
const ll mod = 1e9+7; 
struct node{
	ll rmax;
	ll rmaxl;
	ll rmaxr;
	ll rsum;

};
ll arr[200002];
node segtree[800004];
node fun(node a,node b){
	node c;
	c.rmax = max(a.rmaxr+b.rmaxl,max(a.rmax,b.rmax));
	c.rsum = a.rsum+b.rsum;
	c.rmaxl = max(a.rmaxl,a.rsum+b.rmaxl);
	c.rmaxr = max(b.rmaxr,b.rsum+a.rmaxr);
	return c;
}
void build(int i,int low,int high){
	if(low==high){
		segtree[i].rmax = max(0LL,arr[low]);
		segtree[i].rmaxl = arr[low];
		segtree[i].rmaxr = arr[low];
		segtree[i].rsum = arr[low];
		return ;
	}
	int mid =(low+high)/2;
	build(2*i+1,low,mid);
	build(2*i+2,mid+1,high);
	segtree[i] =fun(segtree[2*i+1],segtree[2*i+2]);
	
}

void update(int i,int low,int high,int ind){
	
	if(low==high){
		segtree[i].rmax = max(0LL,arr[low]);
		segtree[i].rmaxl = arr[low];
		segtree[i].rmaxr = arr[low];
		segtree[i].rsum = arr[low];
		return ;
	}
	int mid =(low+high)/2;
	if(ind<=mid)
		update(2*i+1,low,mid,ind);
	else
		update(2*i+2,mid+1,high,ind);
	segtree[i] =fun(segtree[2*i+1],segtree[2*i+2]);
	
}


int main(){
	int n,q;
	cin>>n>>q;
	for(int i=0;i<n;i++){
		cin>>arr[i];
	}
	build(0,0,n-1);
	while(q--){
		int a,b;
		cin>>a>>b;
		arr[a-1]= b;
		update(0,0,n-1,a-1);
		cout<<segtree[0].rmax<<endl;
	}
	return 0;
}
	