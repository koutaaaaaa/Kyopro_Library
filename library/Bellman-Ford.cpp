void shortest_path(int s){
    d[s] = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(auto c:g[j]){
                if(d[j] != LINF && d[c.first] > d[j] + c.second){
                    d[c.first] = d[j] + c.second;
                }
            }
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(auto c:g[j]){
                if(d[j] != LINF && d[c.first] > d[j] + c.second){
                    d[c.first] = -LINF;
                }
                if(d[j] == -LINF)d[c.first] = -LINF;
            }
        }
    }
}