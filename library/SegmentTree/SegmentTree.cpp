//0indexed , [a,b)
template<typename T>
class SegmentTree{
    private:
        vector<T> seg;
        ll len;
        function<T(T , T)> GET;
        function<T(T , T)> UPDATE;
        T e;
    public:
        SegmentTree(vector<T> v , T tannigen , function<T(T , T)> updates , function<T(T , T)> gets){
            ll sz = v.size();
            len = 1; while(len < sz)len *= 2;
            e = tannigen;
            GET = gets;
            UPDATE = updates;
            seg.resize(2*len , e);
            for(ll i = 0; i < sz; i++)seg[i+len] = v[i];
            for(ll i = len-1; i > 0; --i)seg[i] = GET(seg[2*i] , seg[2*i+1]);
        }
        
        void update(ll ind, T x){
            ind += len;
            seg[ind] = UPDATE(seg[ind] , x);
            ind /= 2;
            while(true){
                if(ind == 0)break;
                seg[ind] = GET(seg[2*ind] , seg[2*ind+1]);
                ind /= 2;
            }
        } 

        T get(ll l,ll r){
            l += len; r += len;
            T ans = e;
            deque<ll> q;
            deque<ll> q2;
            while(l < r){
                if(l%2 == 1){
                    q.push_back(l);
                    l++;
                }
                l /= 2;
                if(r%2 == 1){
                    q2.push_front(r-1);
                    --r;
                }
                r /= 2;
            }
            while(!q.empty()){
                ans = GET(ans , seg[q.front()]);
                q.pop_front();
            }
            while(!q2.empty()){
                ans = GET(ans , seg[q2.front()]);
                q2.pop_front();
            }
            return ans;
        }
};