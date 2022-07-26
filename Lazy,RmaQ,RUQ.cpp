//0indexed , [a,b)
class LazySegmentTree{
	private:
		vector<ll> seg,lazy;
		ll len;
	public:
	LazySegmentTree(vl v){
		ll sz = v.size();
		len = 1; while(len < sz)len *= 2;
		seg.resize(2*len-1,-LINF);
		lazy.resize(2*len-1,-LINF);
		for(ll i = 0; i < sz; i++)seg[i+len-1] = v[i];
		for(ll i = len-2; i >= 0; i--)seg[i] = max(seg[2*i+1] , seg[2*i+2]);
	}
	void eval(ll k,ll l, ll r){
			if(lazy[k] == -LINF)return;
			if(r - l  > 1){
				lazy[k * 2 + 1] = lazy[k];
				lazy[k * 2 + 2] = lazy[k];
			}
			seg[k] = lazy[k];
			lazy[k] = -LINF;
	}
	void update(ll a,ll b,ll x,ll k = 0,ll l = 0,ll r = -1){
		if(r < 0)r = len;
		eval(k,l,r);
		if(a <= l && r <= b){
			lazy[k] = x;
			eval(k,l,r);
		}
		else if(a < r && l < b){
			update(a,b,x,2*k+1,l,(l+r)/2);
			update(a,b,x,2*k+2,(l+r)/2,r);
			seg[k] = max(seg[2*k+1] , seg[2*k+2]);
		}
		}
		ll get_max(ll a,ll b,ll k = 0,ll l = 0,ll r = -1){
			if(r < 0)r = len;
			eval(k,l,r);
			if(b <= l || r <= a)return -LINF;
			else if(a <= l && r <= b)return seg[k];
			else{
				ll vl = get_max(a,b,2*k+1,l,(l+r)/2);
				ll vr = get_max(a,b,2*k+2,(l+r)/2,r);
				return max(vl , vr);
			}
			return 0;
		}
};