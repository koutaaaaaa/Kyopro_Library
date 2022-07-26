//0indexed , [a,b)
template<class T>
class LazySegmentTree{
    private:
        vector<T> seg,lazy;
        vector<bool> f;
        ll len;
    public:
        LazySegmentTree(vector<T> v){
            ll sz = v.size();
            len = 1; while(len < sz)len *= 2;
            seg.resize(2*len-1);
            lazy.resize(2*len-1,0);
            f.resize(2*len-1,0);
            for(ll i = 0; i < sz; i++)seg[i+len-1] = v[i];
            for(ll i = len-2; i >= 0; i--)seg[i] = seg[2*i+1] + seg[2*i+2];
        }

        void eval(ll k,ll l, ll r){
            if(!f[k])return;
            if(r - l  > 1){
                lazy[k * 2 + 1] = lazy[k] / 2;
                lazy[k * 2 + 2] = lazy[k] / 2;
                f[2*k+1] = 1;
                f[2*k+2] = 1;
            }
            seg[k] = lazy[k];
            lazy[k] = 0;
            f[k] = 0;
        }

        void update(ll a,ll b,T x,ll k = 0,ll l = 0,ll r = -1){
            if(r < 0)r = len;
            eval(k,l,r);
            if(b <= l || r <= a)return;
            if(a <= l && r <= b){
                lazy[k] = x * (r - l);
                f[k] = 1;
                eval(k,l,r);
            }
            else{
                update(a,b,x,2*k+1,l,(l+r)/2);
                update(a,b,x,2*k+2,(l+r)/2,r);
                seg[k] = seg[2*k+1] + seg[2*k+2];
            }
        }
            
        T get_sum(ll a,ll b,ll k = 0,ll l = 0,ll r = -1){
            if(r < 0)r = len;
            if(b <= l || r <= a)return 0;
            eval(k,l,r);
            if(a <= l && r <= b)return seg[k];
            T vl = get_sum(a,b,2*k+1,l,(l+r)/2);
            T vr = get_sum(a,b,2*k+2,(l+r)/2,r);
            return vl + vr;
        }
};
