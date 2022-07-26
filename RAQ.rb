//0indexed , [a,b)
class SegmentTree{
    private:
        vector<ll> seg;
        ll len;
    public:
        SegmentTree(vl v){
            ll sz = v.size();
            len = 1; while(len < sz)len *= 2;
            seg.resize(2*len , 0);
            for(ll i = 0; i < sz; i++)seg[i+len] = v[i];
        }

        ll get(ll ind){
            ind += len;
            ll ans = 0;
            while(true){
                if(ind == 0)break;
                ans += seg[ind];
                ind /= 2;
            }
            return ans;
        } 

        void add(ll l,ll r,ll x){
            l += len; r += len;
            while(l < r){
                if(l%2 == 1){
                    seg[l] += x;
                    l++;
                }
                l /= 2;
                if(r%2 == 1){
                    seg[r-1] += x;
                    --r;
                }
                r /= 2;
            }
        }
};
