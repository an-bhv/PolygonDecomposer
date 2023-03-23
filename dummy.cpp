#include<bits/stdc++.h>
using namespace std;

int main(){
	// freopen("input.txt","r", stdin);
	int n;std::cin>>n; //number of points
	int flip;cin>>flip; //flip the input if anti clockwise
	std::vector<pair<int,int>> vertices(n);
	for(int i=0;i<n;i++){
		cin>>vertices[i].first>>vertices[i].second;
	}

	if(flip) reverse(vertices.begin(),vertices.end());
}