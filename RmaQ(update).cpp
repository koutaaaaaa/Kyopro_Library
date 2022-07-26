//0indexed , [a,b);
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
            for(ll i = len-1; i > 0; --i)seg[i] = max(seg[2*i] , seg[2*i+1]);
        }

        void uptade(ll ind, ll x){
            ind += len;
            seg[ind] = x;
            ind /= 2;
            while(true){
                if(ind == 0)break;
                seg[ind] = max(seg[2*ind] , seg[2*ind+1]);
                ind /= 2;
            }
        } 

        ll get_max(ll l,ll r){
            l += len; r += len;
            ll ans = 0;
            while(l < r){
                if(l%2 == 1){
                    ans = max(seg[l] , ans);
                    l++;
                }
                l /= 2;
                if(r%2 == 1){
                    ans = max(seg[r-1] , ans);
                    --r;
                }
                r /= 2;
            }
            return ans;
        }
};