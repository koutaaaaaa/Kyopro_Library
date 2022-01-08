//—LŒüƒOƒ‰ƒt
struct Flow{
	struct edge {int to, cap, rev; };
	vector<vector<edge>> G;
    vector<int> level;
    vector<int> iter;
	int MAX_V;

	Flow(int v){
		G.resize(v);
		iter.resize(v);
        level.resize(v , -1);
		MAX_V = v;
	}

	void add_edge(int from, int to, int cap){
		G[from].push_back(edge{to, cap, (int)G[to].size()});
		G[to].push_back(edge{from, 0, (int)G[from].size()-1});
	};

    void bfs(int s){
        for(int i = 0; i < MAX_V; i++)level[i] = -1;
        queue<int> que;
        que.push(s);
        level[s] = 0;
        while(!que.empty()){
            int v = que.front(); que.pop();
            for(int i = 0; i < G[v].size(); i++){
                edge &e = G[v][i];
                if(e.cap > 0 && level[e.to] < 0){
                    level[e.to] = level[v] + 1;
                    que.push(e.to);
                }
            }
        }
    }

	int dfs(int v, int t, int f){
		if(v == t)return f;
		for(int &i = iter[v]; i < G[v].size(); i++){
			edge &e = G[v][i];
			if(e.cap > 0 && level[v] < level[e.to]){
				int d = dfs(e.to, t, min(f, e.cap));
				if(d > 0){
					e.cap -= d;
					G[e.to][e.rev].cap += d;
					return d;
				}
			}
		}
		return 0;
	}

	int max_flow(int s, int t){
		int flow = 0;
		while(114514){
			bfs(s);
			if(level[t] < 0)return flow;
            for(int i = 0; i < MAX_V; i++)iter[i] = 0;
			int f;
            while((f = dfs(s , t , INF)) > 0)flow += f;
		}
		return 0;
	}
};
