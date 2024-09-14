#include<iostream>
#include<cstring>

#define INT_MIN -2147483648
#define INT_MAX 2147483647
 
using namespace std;
typedef long long ll;
const ll mod = 1e9+7; 
int main(){
	int n,q;
	cin>>n>>q;
	string str[n];
	int prefix[n+1][n+1];
	memset(prefix,0,sizeof(prefix));
	for(int i=1;i<=n;i++){
		cin>>str[i-1];
		for(int j=1;j<=n;j++){
			prefix[i][j] = prefix[i][j-1]+(str[i-1][j-1]=='*');
		}
	}
	while(q--){
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		int ans = 0;
		for(int i=a;i<=c;i++)
			ans += (prefix[i][d]-prefix[i][b-1]);
		cout<<ans<<endl;
	}

	return 0;	
}
