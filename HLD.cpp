struct Heavy_Light_Decomposion{
    int V; 
    vector<vector<int>> G;
    vector<int> depth;
    vector<int> sz;
    vector<int> shallowest;
    vector<int> order;
    vector<int> p;
    int time = 0;
    Heavy_Light_Decomposion(int n){
        V = n;
        G.resize(V);
        depth.resize(V,-1);
        sz.resize(V,1);
        shallowest.resize(V,-1);
        order.resize(V,-1);
        p.resize(V,-1);
    }

    void add_edge(int a, int b){
        G[a].push_back(b);
        G[b].push_back(a);
    }

    vector<int> build(){
        dfs1();
        dfs2();
        return order;
    }

    void dfs1(int now = 0, int dep = 0){
        depth[now] = dep;
        for(auto c:G[now]){
            if(depth[c] >= 0)continue;
            p[c] = now;
            dfs1(c , dep+1);
            sz[now] += sz[c];
        }
    }
    
    void dfs2(int now = 0, int shallowest_v = -1){
        order[now] = time;
        time++;
        if(shallowest_v == -1)shallowest[now] = now;
        else shallowest[now] = shallowest_v;
        if(G[now].size() == 1 && now != 0)return;
        int nxt = -1;
        int max_sz = -1;
        for(auto c:G[now]){
            if(depth[c] < depth[now])continue;
            if(max_sz < sz[c]){
                nxt = c;
                max_sz = sz[c];
            }
        }
        //haevy
        if(shallowest_v == -1){ 
            dfs2(nxt , now);
        }
        else{
            dfs2(nxt , shallowest_v);
        }
        //light
        for(auto c:G[now]){
            if(depth[c] < depth[now])continue;
            if(c == nxt)continue;
            dfs2(c,-1);
        }
    }

    vector<pair<int,int>> get_path(int u, int v){
        vector<pair<int,int>> ret;
        while(shallowest[u] != shallowest[v]){
            if(depth[shallowest[u]] <= depth[shallowest[v]]){
                ret.push_back({order[shallowest[v]],order[v]+1});
                v = p[shallowest[v]];
            }
            else{
                ret.push_back({order[shallowest[u]],order[u]+1});
                u = p[shallowest[u]];
            }
            //cout << u << " " << v << endl; 
        }
        ret.push_back({min(order[v],order[u]) , max(order[v],order[u])+1});
        return ret;
    }
};