//0indexed , [a,b);
class SegmentTree{
    private:
        vector<ll> seg;
        ll len;
    public:
        SegmentTree(vl v){
            ll sz = v.size();
            len = 1; while(len < sz)len *= 2;
            seg.resize(2*len , LINF);
            for(ll i = 0; i < sz; i++)seg[i+len] = v[i];
            for(ll i = len-1; i > 0; --i)seg[i] = min(seg[2*i] , seg[2*i+1]);
        }

        void update(ll ind, ll x){
            ind += len;
            seg[ind] = x;
            ind /= 2;
            while(true){
                if(ind == 0)break;
                seg[ind] = min(seg[2*ind] , seg[2*ind+1]);
                ind /= 2;
            }
        } 

        ll get_min(ll l,ll r){
            l += len; r += len;
            ll ans = LINF;
            while(l < r){
                if(l%2 == 1){
                    ans = min(seg[l] , ans);
                    l++;
                }
                l /= 2;
                if(r%2 == 1){
                    ans = min(seg[r-1] , ans);
                    --r;
                }
                r /= 2;
            }
            return ans;
        }
};