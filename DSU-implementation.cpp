#include<bits/stdc++.h>
using namespace std;

class UnionFind{
	int n;
	vector<int> parent;
	vector<int> rank;
	vector<int> size;
public:
	UnionFind(int n){
		this->n = n;
		parent.resize(n+1, 0);
		rank.resize(n+1, 0);
		size.resize(n+1, 1);
		for(int i = 0; i < n+1; i++) parent[i] = i;
	}
	int find(int x){
		if(parent[x] == x)
			return x;
		
		return parent[x] = find(parent[x]);
	}

	void unionByRank(int a, int b){
		int a_leader = find(a);
		int b_leader = find(b);
		if(a_leader == b_leader)
			return ;
		if(rank[a_leader] > rank[b_leader]){
			parent[b_leader] = a_leader;
		}
		else if(rank[b_leader] > rank[a_leader]){
			parent[a_leader] = b_leader;
		}
		else{
			parent[b_leader] = a_leader;
			rank[a_leader]++;
		}
	}

	void unionBySize(int a, int b){
		int a_leader = find(a);
		int b_leader = find(b);

		if(a_leader == b_leader)
			return ;
		
		if(size[a_leader] > size[b_leader]){
			parent[b_leader] = a_leader;
			size[a_leader] += size[b_leader];
		}
		else if(size[b_leader] > size[a_leader]){
			parent[a_leader] = b_leader;
			size[b_leader] += size[a_leader];
		}
		else {
			parent[b_leader] = a_leader;
			size[a_leader] += size[b_leader];
		}
	}
};

int main(){

	// int n;
	// cout << "Enter number of nodes: ";
	// cin >> n;
	DisjointSet dsu(7);
	dsu.unionBySize(1,2);
	dsu.unionBySize(2,3);
	dsu.unionBySize(4,5);
	cout << dsu.findLeader(2) << endl; 
	dsu.unionBySize(6,7);
	dsu.unionBySize(5,6);
	dsu.unionBySize(3,7);

	cout << dsu.findLeader(2) << endl; 
	return 0;
}