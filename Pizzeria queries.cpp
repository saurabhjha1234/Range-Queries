#include<iostream>
#include<unordered_map>
#include<vector>
#include<algorithm>
#define INT_MIN -2147483648
#define INT_MAX 2147483647
 
using namespace std;
typedef long long ll;
const ll mod = 1e9+7; 
int arr[200002];
pair<int,int>segtree[800004];
void build(int i,int low,int high){
	if(low==high){
		segtree[i].first = arr[low]-low;
		segtree[i].second = arr[low]+low;
		return ;
	}
	int mid =(low+high)/2;
	build(2*i+1,low,mid);
	build(2*i+2,mid+1,high);
	segtree[i].first  =min(segtree[2*i+1].first,segtree[2*i+2].first);
	segtree[i].second  =min(segtree[2*i+1].second,segtree[2*i+2].second);
}

void update(int i,int low,int high,int ind){
	
	if(low==high){
		segtree[i].first = arr[low]-low;
		segtree[i].second = arr[low]+low;
		return ;
	}
	int mid =(low+high)/2;
	if(ind<=mid)
		update(2*i+1,low,mid,ind);
	else
		update(2*i+2,mid+1,high,ind);
	segtree[i].first  =min(segtree[2*i+1].first,segtree[2*i+2].first);
	segtree[i].second  =min(segtree[2*i+1].second,segtree[2*i+2].second);
	
}
int query(int i,int low,int high,int l,int r){
	if(low>r || high<l || low>high)
		return INT_MAX;
	else if(low>=l && high<=r)
		return segtree[i].first;
	else{
		int mid = (low+high)/2;
		return min(query(2*i+1,low,mid,l,r),query(2*i+2,mid+1,high,l,r));
	}
}
int query2(int i,int low,int high,int l,int r){
	if(low>r || high<l || low>high)
		return INT_MAX;
	else if(low>=l && high<=r)
		return segtree[i].second;
	else{
		int mid = (low+high)/2;
		return min(query2(2*i+1,low,mid,l,r),query2(2*i+2,mid+1,high,l,r));
	}
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
		if(a==1){
			int c;
			cin>>c;
			arr[b-1] = c;
			update(0,0,n-1,b-1);
			
		}
		else{
			int x1= query(0,0,n-1,0,b-2);
			int x2 = query2(0,0,n-1,b,n-1);
			cout<<min(arr[b-1],min(x1+b-1,x2-b+1))<<endl;
		}
	}
	return 0;
}
	