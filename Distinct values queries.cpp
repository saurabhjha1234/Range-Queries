#include<iostream>
#include<unordered_map>
#include<vector>
#define INT_MIN -2147483648
#define INT_MAX 2147483647
 
using namespace std;
typedef long long ll;
const ll mod = 1e9+7; 

int arr[200002];
int segtree[800004];
unordered_map<int,int> lastind;

void update(int i,int low,int high,int ind,int val){
	
	if(low==high){
		segtree[i] = val;
		return ;
	}
	int mid =(low+high)/2;
	if(ind<=mid)
		update(2*i+1,low,mid,ind,val);
	else
		update(2*i+2,mid+1,high,ind,val);
	segtree[i] =segtree[2*i+1]+segtree[2*i+2];
	
}
int query(int i,int low,int high,int l,int r){
	if(l>high || r<low)
		return 0;
	if(low>=l && high<=r)
		return segtree[i];
	int mid=(low+high)/2;
	return query(2*i+1,low,mid,l,r)+query(2*i+2,mid+1,high,l,r);
}

int main(){
	int n,q;
	cin>>n>>q;
	for(int i=0;i<n;i++){
		cin>>arr[i];
	}
	vector<pair<int,int>> queries[n];
	for(int i=0;i<q;i++){
		int a,b;
		cin>>a>>b;
		a--,b--;
		queries[b].push_back({a,i});
	}
	int ans[q];
	for(int i=0;i<n;i++){
		update(0,0,n-1,i,1);
		if(lastind.find(arr[i])!=lastind.end()){
			update(0,0,n-1,lastind[arr[i]],0);
		}
		lastind[arr[i]]=i;
		for(auto& j:queries[i]){
			ans[j.second] = query(0,0,n-1,j.first,i);
		}
	}
	for(int i=0;i<q;i++)
		cout<<ans[i]<<endl;
	return 0;
}
	