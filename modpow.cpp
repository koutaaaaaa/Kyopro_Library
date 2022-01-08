template <typename T>
T modpow(T& a,int b,int m = MOD){
    if(b == 0)return 1;
    if(b%2 == 0){
        T t = modpow(a,b/2,m);
        return t*t % m;
    }
    return a * modpow(a,b-1,m) % m;
}
