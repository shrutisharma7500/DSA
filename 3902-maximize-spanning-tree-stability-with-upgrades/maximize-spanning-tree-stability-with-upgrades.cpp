class DSU {
public:
    vector<int> parent, rank;
    
    DSU(int n){
        parent.resize(n);
        rank.resize(n,0);
        for(int i=0;i<n;i++) parent[i]=i;
    }
    
    int find(int x){
        if(parent[x]!=x)
            parent[x]=find(parent[x]);
        return parent[x];
    }
    
    bool unite(int a,int b){
        a=find(a);
        b=find(b);
        if(a==b) return false;
        
        if(rank[a]<rank[b]) swap(a,b);
        parent[b]=a;
        if(rank[a]==rank[b]) rank[a]++;
        return true;
    }
};

class Solution {
public:

    bool check(int n, vector<vector<int>>& edges, int k, int mid){
        DSU dsu(n);
        int used=0;
        int upgrades=0;
        
        vector<pair<int,int>> good;
        vector<pair<int,int>> up;
        
        for(auto &e:edges){
            int u=e[0],v=e[1],s=e[2],must=e[3];
            
            if(must){
                if(s<mid) return false;
                if(!dsu.unite(u,v)) return false;
                used++;
            }
            else{
                if(s>=mid) good.push_back({u,v});
                else if(2*s>=mid) up.push_back({u,v});
            }
        }
        
        for(auto &p:good){
            if(dsu.unite(p.first,p.second))
                used++;
        }
        
        for(auto &p:up){
            if(used==n-1) break;
            if(upgrades==k) break;
            
            if(dsu.unite(p.first,p.second)){
                used++;
                upgrades++;
            }
        }
        
        return used==n-1;
    }

    int maxStability(int n, vector<vector<int>>& edges, int k) {
        
        int mx=0;
        for(auto &e:edges) mx=max(mx,e[2]);
        
        int lo=1, hi=2*mx;
        int ans=-1;
        
        while(lo<=hi){
            int mid=(lo+hi)/2;
            
            if(check(n,edges,k,mid)){
                ans=mid;
                lo=mid+1;
            }
            else
                hi=mid-1;
        }
        
        return ans;
    }
};