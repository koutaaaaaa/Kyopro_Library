struct range_edge_graph{
    private:
        vector<vector<pair<int,long long>>> g;
        int len;
        int cnt;
        int e;
        int N;
    public:
    range_edge_graph(int n,int m){
        e = m;
        N = n;
        len = 1;
        while(len < n)len *= 2;
        cnt = len * 5;
        g.resize(len * 5 + 1 + 2*m);
        for(int i = 1; i < len; i++){
            g[i].push_back(make_pair(2*i,(long long)0));
            g[i].push_back(make_pair(2*i+1,(long long)0));
            g[2*i+2*len].push_back(make_pair(i+2*len,(long long)0));
            g[2*i+2*len+1].push_back(make_pair(i+2*len,(long long)0));
        }
        for(int i = 0; i < len; i++){
            g[len + i].push_back(make_pair(4*len + i,(long long)0));
            g[4*len + i].push_back(make_pair(3*len + i,(long long)0));
        }
    }
    void add_edge(int l1 , int r1 , int l2 , int r2 , long long c){//[l1,r1) -> [l2,r2) cost c
        g[cnt].push_back(make_pair(cnt+1,c));
        l2 += len; r2 += len;
        while(l2 < r2){
            if(l2 % 2 == 1){
                g[cnt+1].push_back(make_pair(l2,0));
                l2++;
            }
            l2 /= 2;
            if(r2 % 2 == 1){
                g[cnt+1].push_back(make_pair(r2-1,0));
                r2--;
            }
            r2 /= 2;
        }
        l1 += len; r1 += len;
        while(l1 < r1){
            if(l1 % 2 == 1){
                g[l1+2*len].push_back(make_pair(cnt,0));
                l1++;
            }
            l1 /= 2;
            if(r1 % 2 == 1){
                g[r1+2*len-1].push_back(make_pair(cnt,0));
                r1--;
            }
            r1 /= 2;
        }
        cnt += 2;
    }

    vector<long long> get_dist(int from){
        vector<long long> dist(len*5 + 2*e + 1 , -1);
        dist[from + 4*len] = 0;
        priority_queue<pair<long long,long long>> q;
        q.push(make_pair(0,from + 4*len));
        while(!q.empty()){
            auto p = q.top();
            q.pop();
            long long d = -p.first;
            long long v = p.second;
            if(dist[v] < d)continue;
            for(auto c:g[v]){
                if(dist[c.first] == -1){
                    dist[c.first] = d + c.second;
                    q.push(make_pair(-dist[c.first] , c.first));
                }
                else if(dist[c.first] > d + c.second){
                    dist[c.first] = d + c.second;
                    q.push(make_pair(-dist[c.first] , c.first));
                }
            }
        }
        vector<long long> res(N);
        for(int i = 0; i < N; i++)res[i] = dist[len*4 + i];
        return res;
    }
};