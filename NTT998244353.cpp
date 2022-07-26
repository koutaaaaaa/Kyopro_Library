struct NumberTheoreticTransform{
    vector<int> rev;
    vector<mint> roots;
    int base,max_base;
    mint root;
    NumberTheoreticTransform():base(1),rev{0,1},roots{mint(0),mint(1)}{
        int tmp = MOD2-1;
        for(max_base=0; tmp%2 == 0; ++max_base) tmp>>=1;
        root = 2;
        while(modpow(root,(MOD2-1)>>1)==1)root += 1;
        root = modpow(root,(MOD2-1)>>max_base);
    }
    void ensure_base(int nbase){
        if (nbase <= base) return;
        rev.resize(1<<nbase);
        for (int i = 0; i<(1<<nbase); ++i){
            rev[i] = (rev[i>>1]>>1)|((i&1)<<(nbase-1));
        }
        roots.resize(1<<nbase);
        for(;base<nbase;++base){
            mint z = modpow(root , 1<<(max_base-1-base));
            for(int i=1<<(base-1);i<(1<<base);++i){
                roots[i<<1] = roots[i];
                roots[i<<1|1] = roots[i] * z;
            }
        }
    }
    void NTT(vector<mint> &a){
        const int n=a.size();
        int zeros=__builtin_ctz(n);
        ensure_base(zeros);
        int shift=base-zeros;
        for (int i=0;i<n;++i){
            if (i<(rev[i]>>shift)){
                swap(a[i],a[rev[i]>>shift]);
            }
        }
        for(int k=1;k<n;k<<=1){
            for(int i=0;i<n;i+=(k<<1)){
                for(int j=0;j<k;++j){
                    mint z = a[i+j+k]*roots[j+k];
                    a[i+j+k]=a[i+j]-z;
                    a[i+j]=a[i+j]+z;
                }
            }
        }
    }
    vector<mint> convolution(vector<mint> a,vector<mint> b){
        int need=a.size()+b.size()-1;
        int nbase=1;
        while((1<<nbase)<need) ++nbase;
        ensure_base(nbase);
        int sz=1<<nbase;
        a.resize(sz,mint(0)); b.resize(sz,mint(0));
        NTT(a); NTT(b);
        mint inv_sz=(mint)1/sz;
        for (int i=0;i<sz;++i) a[i]*=b[i]*inv_sz;
        reverse(a.begin()+1,a.end());
        NTT(a);
        a.resize(need);
        return a;
    }
};