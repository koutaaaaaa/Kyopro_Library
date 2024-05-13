vector<pl> g[114514];
int n,m; 
vl dijkstra(ll s){
	priority_queue<pl , vector<pl> , greater<pl>> q;
	vl dist(n , -1);
	q.push({0,s});
	dist[s] = 0;
	while(!q.empty()){
		auto p = q.top(); q.pop();
		ll d = p.first; 
		ll from = p.second;
		if(dist[from] < d)continue;
		for(auto c:g[from]){
			ll to = c.first;
			ll di = c.second;
			if(dist[to] == -1 || dist[from] + di < dist[to]){
				dist[to] = dist[from] + di;
				q.push({dist[to] , to});
			}
		}
	}
	return dist;
}