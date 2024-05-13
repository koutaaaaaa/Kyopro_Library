class StronglyConnectedComponents{
    private:
    vector<vi> gragh;
    vector<vi> t_gragh;
    vi label;
    vector<bool> seen;
    int sz;
    vi tmp;
    queue<vi> ans;
    void dfs(int v){
        if(seen[v])return;
        seen[v] = 1;
        for(auto c:gragh[v]){
            dfs(c);
        }
        label.push_back(v);
        return;
    }
 
    void dfs2(int v){
        if(seen[v])return;
        seen[v] = 1;
        for(auto c:t_gragh[v]){
            dfs2(c);
        }
        tmp.push_back(v);
        return ;
    }
    
    public:
    StronglyConnectedComponents(int n){
        sz = n;
        gragh.resize(n);
        t_gragh.resize(n);
        seen.resize(n);
    }

    void add_edge(int from,int to){
        gragh[from].push_back(to);
        t_gragh[to].push_back(from);
    }

    queue<vi> SCC(){
        for(int i = 0; i < sz; i++){
            if(seen[i])continue;
            dfs(i);
        }
        for(int i = 0; i < sz; i++)seen[i] = 0;
        for(int i = sz-1; i >= 0; --i){
            if(seen[label[i]])continue;
            dfs2(label[i]);
            ans.push(tmp);
            tmp.resize(0);
        }
        return ans;
    }
};
