template<class T>
class FastFourierTransform{
    private:
    int sz;
    vector<complex<long double>> DFT(vector<complex<long double>> f,int n,bool inverse){
        if(n == 1)return f;
        vector<complex<long double>> f0(n/2) , f1(n/2);
        rep(i,0,n/2){
            f0[i] = f[2*i];
            f1[i] = f[2*i+1];
        }
        f0 = DFT(f0, n/2, inverse);
        f1 = DFT(f1, n/2, inverse);
        long double cs = cos(2*PI / n);
        long double sn = sin(2*PI / n);
        if(inverse)sn *= -1;
        complex<long double> zeta = {cs , sn};
        complex<long double> pow_zeta = 1;
        rep(i,0,n){
            f[i] = f0[i % (n/2)] + pow_zeta * f1[i % (n/2)];
            pow_zeta *= zeta;
        } 
        return f;
    }
    public:
    vector<long double> FFT(vector<T> f, vector<T> g){
        vector<complex<long double>> nf,ng;
        sz = 1;
        while(sz < f.size() + g.size())sz *= 2;
        nf.resize(sz); 
        ng.resize(sz);
        rep(i,0,f.size())nf[i] = f[i];
        rep(i,0,g.size())ng[i] = g[i];
        nf = DFT(nf , sz , 0);
        ng = DFT(ng , sz , 0);
        rep(i,0,sz)nf[i] *= ng[i];
        nf = DFT(nf , sz , 1);
        vector<long double> res;
        rep(i,0,sz)res.push_back(nf[i].real()/sz+0.5);
        return res;
    }

    vector<int> Convolution(vector<T> f, vector<T> g){
        sz = 1;
        vi res;
        auto fft = FFT(f , g);
        rep(i,0,fft.size())res.push_back((int)fft[i]);
        return res;
    }

};
