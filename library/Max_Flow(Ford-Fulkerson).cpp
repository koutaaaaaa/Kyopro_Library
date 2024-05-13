//—LŒüƒOƒ‰ƒt
struct Flow{
	struct edge {int to, cap, rev; };
	vector<vector<edge>> G;
	vector<bool> used;
	int MAX_V;

	Flow(int v){
		G.resize(v);
		used.resize(v);
		MAX_V = v;
	}

	void add_edge(int from, int to, int cap){
		G[from].push_back(edge{to, cap, (int)G[to].size()});
		G[to].push_back(edge{from, 0, (int)G[from].size()-1});
	};

	int dfs(int v, int t, int f){
		if(v == t)return f;
		used[v] = 1;
		rep(i,0,G[v].size()){
			edge &c = G[v][i];
			if(!used[c.to] && c.cap > 0){
				int d = dfs(c.to, t, min(f, c.cap));
				if(d > 0){
					c.cap -= d;
					G[c.to][c.rev].cap += d;
					return d;
				}
			}
		}
		return 0;
	}

	int max_flow(int s, int t){
		int flow = 0;
		while(114514){
			rep(i,0,MAX_V)used[i] = 0;
			int f = dfs(s, t, INF);
			if(f == 0)return flow;
			flow += f;
		}
		return 0;
	}
};