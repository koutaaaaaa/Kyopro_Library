//0indexed , [a,b)
class SegmentTree{
    private:
        vector<pl> seg;
        ll len;
        ll time = 0;
    public:
        SegmentTree(vl v){
            ll sz = v.size();
            len = 1; while(len < sz)len *= 2;
            seg.resize(2*len , {0,-1});
            for(ll i = 0; i < sz; i++)seg[i+len].second = v[i];
        }

        ll get(ll ind){
            ind += len;
            pl ans = {0,0};
            while(true){
                if(ind == 0)break;
                ans = max(ans , seg[ind]);
                ind /= 2;
            }
            return ans.second;
        } 

        void update(ll l,ll r,ll x){
            l += len; r += len;
            time++;
            while(l < r){
                if(l%2 == 1){
                    seg[l] = {time , x};
                    l++;
                }
                l /= 2;
                if(r%2 == 1){
                    seg[r-1] = {time , x};
                    --r;
                }
                r /= 2;
            }
        }
};