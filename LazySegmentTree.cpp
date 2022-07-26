template <class S , 
            S (*GET)(S , S) , 
            S (*e)() ,
            class F , 
            S (*UPDATE)(F , S), 
            F(*COMPOSITE)(F , F),
            F(*id)()>
struct LazySegmentTree{
    vector<S> seg;
    vector<F> lazy;
    vector<int> order;
    ll len;
    S tannigen;
    F koutousyazou;
    LazySegmentTree(vector<S> v){
        ll sz = v.size();
        len = 1; while(len < sz)len *= 2;
        tannigen = e();
        koutousyazou = id(); 
        seg.resize(2*len , tannigen);
        lazy.resize(2*len ,koutousyazou);
        order.resize(2*len , 0);
        for(ll i = 0; i < sz; i++)seg[i+len-1] = v[i];
        for(ll i = len-2; i >= 0; --i)seg[i] = GET(seg[2*i+1] , seg[2*i+2]);
    }
    void eval(ll k,ll l, ll r){
        if(order[k] == 0)return;
        seg[k] = UPDATE(lazy[k] , seg[k]);
        if(r - l  > 1){
            lazy[2*k+1] = COMPOSITE(lazy[2*k+1] , lazy[k]);
            lazy[2*k+2] = COMPOSITE(lazy[2*k+2] , lazy[k]);
            order[2*k+1] = 1;
            order[2*k+2] = 1;
        }
        lazy[k] = koutousyazou;
        order[k] = 0;
    }
    void update(int a, int b, F f,int k=0, int l=0, int r=-1){
        if(r < 0) r = len;
        eval(k, l , r);
        if(b <= l || r <= a)return;
        if(a <= l && r <= b){
            lazy[k] = COMPOSITE(lazy[k] , f);
            order[k] = 1;
            eval(k, l, r);
        }
        else{
            update(a,b,f,2*k+1,l,(l+r)/2);
            update(a,b,f,2*k+2,(l+r)/2,r);
            seg[k] = GET(seg[2*k+1] , seg[2*k+2]);
        }
    }
    S get(int a,int b,int k=0,int l=0,int r=-1){
        if(r < 0)r = len;
        if(b <= l || r <= a)return tannigen;
        eval(k,l,r);
        if(a <= l && r <= b)return seg[k];
        S vl = get(a,b,2*k+1,l,(l+r)/2);
        S vr = get(a,b,2*k+2,(l+r)/2,r);
        return GET(vl ,vr);
    }
};

struct S{
};

S get(S a  , S b){
}

S e(){
    return S{};
}

struct F{
};

S update(F f , S x){
    return S{};
}

F composition(F a , F b){
    return F{};
}

F id(){
    return F{};
}