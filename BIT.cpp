class BIT
    {
    private:
        vl bit;
        ll n;
    public:
        BIT(ll k){
            n = k;
            bit.resize(n+10,0);
        }
        void add(ll ind,ll a){
            for(ll i = ind; i <= n ; i += i & -i){
                bit[i] += a;
            }
        }
        ll get_sum(ll a){
            ll ret = 0;
            for(ll i = a; i > 0; i -= (i&-i)){
                ret += bit[i];
            }
            return ret;
        }
        ll get_sum(ll l,ll r){
            ll ret1 = get_sum(l-1);
            ll ret2 = get_sum(r);
            return ret2 - ret1;
        }
    };
    
