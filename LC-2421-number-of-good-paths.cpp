// youtube --> codestoryWithMik

class DisjointSet{
	vector<int> parent, size;
    
public:
	DisjointSet(int n){
		parent.resize(n+1, 0);
		size.resize(n+1, 1);
		for(int i = 0; i < n+1; i++) parent[i] = i;
	}
    
	int findLeader(int x){
		if(parent[x] == x)
			return x;
		
		return parent[x] = findLeader(parent[x]);
	}
    
	void unionBySize(int a, int b){
		int a_leader = findLeader(a);
		int b_leader = findLeader(b);

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
class Solution {
    int goodPaths(map<int, vector<int>> &mp, vector<bool> &is_active, vector<int> adj[]){
        int n = is_active.size();
        DisjointSet dsu(n);
        int cnt = n;
        for(auto it: mp){
            vector<int> nodes = it.second;
            
            
            // union of active nodes
            for(auto &u: nodes){
                
                // make current value node active
                is_active[u] = true;
                
                for(auto &v: adj[u]){
                    
                    if(is_active[v]) dsu.unionBySize(u, v);
                }
            }
            
            
            unordered_map<int, int> freq;
            for(auto &node: nodes){
                freq[dsu.findLeader(node)]++;
            }
            
            for(auto it: freq){
                int f = it.second;
                if(f > 1){
                    cnt += (f*(f-1)/2);
                }
            }
            
        }
        return cnt;
    }
public:
    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        int n = vals.size();
        vector<int> adj[n];
        for(auto &e: edges){
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        vector<bool> is_active(n, false);
        // to get smaller value nodes first
        map<int, vector<int>> mp;
        for(int i = 0; i < n; i++){
            int value = vals[i];
            mp[value].push_back(i);
        }
        
        return goodPaths(mp, is_active, adj);
    }
};