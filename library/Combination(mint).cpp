mint kaijo[2000200];
mint inv[2000200];
void pre(int mod){
    kaijo[0] = 1;
    rep(i,1,2000200)kaijo[i] = kaijo[i-1] * i;
    inv[2000200-1] = modpow(kaijo[2000200-1] , mod-2);
    for(int i = 2000200-2; i >= 0; i--)inv[i] = inv[i+1] * (i+1);
}

mint Combination(int n, int r){
    return kaijo[n] * inv[r] * inv[n-r];
}

mint Permutation(int n, int r){
    return Combination(n , r) * kaijo[r];
}
