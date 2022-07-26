ll p[20][500500];
ll dep[500500];
class LCA_tree
{
private:
	ll len;
public:

	LCA_tree(ll m){
		len = m;
	}
	ll la(ll x,ll h){
		for(int i = 19;i >= 0;--i){
			if((1<<i) <= h){
				x = p[i][x];
				h -= (1<<i);
			}
		}
		return x;
	}
	ll lca(ll u,ll v){
		if(dep[u] < dep[v])swap(u,v);//dep[u] >= dep[v]
		u = la(u, dep[u] - dep[v]);
		if(u == v)return u;
		for(int i = 19; i >= 0; --i){
			if(p[i][u] != p[i][v]){
				u = p[i][u];
				v = p[i][v];
			}
		}
		return p[0][u];
	}
	void input(ll ch,ll pa){
		p[0][ch] = pa;
		dep[ch] = dep[p[0][ch]] + 1;
	}
    void tree_set(){
		//Doubling
		for(int i = 1; i < 20;i++){
			for(ll j = 0;j < len; j++){
				p[i][j] = p[i-1][p[i-1][j]];
			}
		}
	}
};