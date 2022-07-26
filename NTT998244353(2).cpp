struct NTT{
    int sz = 0,cnt = 0;
    mint genshikon[24];
    mint inv[24];
    void DFT(vector<mint> &f,int n,int ruijou,bool inverse){
        if(n == 1)return;
        vector<mint> f0(n/2) , f1(n/2);
        for(int i = 0; i < n/2; i++){
            f0[i] = f[2*i];
            f1[i] = f[2*i+1];
        }
        DFT(f0, n/2, ruijou-1, inverse);
        DFT(f1, n/2, ruijou-1 , inverse);
        mint zeta = 0;
        if(inverse)zeta = inv[ruijou];
        else zeta = genshikon[ruijou];
        mint pow_zeta = 1;
        for(int i = 0; i < n; i++){
            f[i] = f0[i % (n/2)] + pow_zeta * f1[i % (n/2)];
            pow_zeta *= zeta;
        } 
    }

    vector<mint> Convolution(vector<mint> f, vector<mint> g){
        vector<mint> nf,ng;
        sz = 1;
        cnt = 0;
        int mxsz = f.size() + g.size() - 1;
        while(sz < f.size() + g.size() - 1){
            sz *= 2;
            cnt++;
        }
        genshikon[23] = modpow((mint)3, 119);
        inv[23] = modpow(genshikon[23] , MOD2-2);
        for(int i = 22; i >= 0; --i){
            genshikon[i] = genshikon[i+1] * genshikon[i+1];
            inv[i] = inv[i+1] * inv[i+1];
        }
        f.resize(sz); 
        g.resize(sz);
        DFT(f , sz , cnt, 0);
        DFT(g , sz , cnt, 0);
        for(int i = 0; i < sz; i++)f[i] *= g[i];
        DFT(f , sz , cnt, 1);
        f.resize(mxsz);
        for(auto &c:f)c /= sz;
        return f;
    }
};
