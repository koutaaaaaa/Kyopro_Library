struct SuffixArray{
    string s;
    int n = 0;
    int k = 0;
    vector<int> rank;
    vector<int> sa;
    vector<int> tmp;

    SuffixArray(string t){
        s = t;
        n = s.size();
        rank.resize(n+1,0);
        sa.resize(n+1,0);
        tmp.resize(n+1,0);
    }

    bool compare_sa(int i, int j){
        if(rank[i] != rank[j])return rank[i] < rank[j];
        int ri = i+k <= n ? rank[i+k] : -1;
        int rj = j+k <= n ? rank[j+k] : -1;
        return ri < rj;
    }

    vector<int> construct_sa(){
        for(int i = 0; i <= n; i++){
            sa[i] = i;
            rank[i] = i < n ? s[i]-'a' : -1;
        }
        for(k = 1; k <= n;k *= 2){
            sort(sa.begin() , sa.end() , [&](int &i, int &j){return compare_sa(i,j);});
            tmp[sa[0]] = 0;
            for(int i = 1; i <= n; i++){
                tmp[sa[i]] = tmp[sa[i-1]] + (compare_sa(sa[i-1] , sa[i]) ? 1:0);
            }
            for(int i = 0; i <= n; i++){
                rank[i] = tmp[i];
            }
        }
        return sa;
    }
};