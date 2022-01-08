class UnionFind
  {
  private:
      vector<ll> p;
      vector<ll> rank;
  public:
      UnionFind(ll n){
          p.resize(n,-1);
          rank.resize(n,1);
      }
      ll find(ll x){
          if(p[x]<0)return x;
          return p[x]=find(p[x]);
      }
      void unite(ll x,ll y){
          x = find(x);
          y = find(y);
      if(x == y)return;
          if(rank[x] > rank[y])swap(x,y);
          if(rank[x] == rank[y])rank[y]++;
          p[y] += p[x];
          p[x] = y;
      }
      ll size(ll x){
          return -p[find(x)];
      }
      bool same(ll x, ll y){
          return find(x) == find(y);
      }
  };
  
