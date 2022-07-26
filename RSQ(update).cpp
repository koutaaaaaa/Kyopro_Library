//0indexed , [a,b)
template<class T>
class SegmentTree{
    private:
        vector<T> seg;
        ll len;
    public:
        SegmentTree(vector<T> v){
            ll sz = v.size();
            len = 1; while(len < sz)len *= 2;
            seg.resize(2*len , 0);
            for(ll i = 0; i < sz; i++)seg[i+len] = v[i];
            for(ll i = len-1; i > 0; --i)seg[i] = seg[2*i] + seg[2*i+1];
        }

        void update(ll ind, T x){
            ind += len;
            seg[ind] = x;
            ind /= 2;
            while(true){
                if(ind == 0)break;
                seg[ind] = seg[2*ind] + seg[2*ind+1];
                ind /= 2;
            }
        } 

        T get_sum(ll l,ll r){
            l += len; r += len;
            T ans = 0;
            while(l < r){
                if(l%2 == 1){
                    ans += seg[l];
                    l++;
                }
                l /= 2;
                if(r%2 == 1){
                    ans += seg[r-1];
                    --r;
                }
                r /= 2;
            }
            return ans;
        }
};
