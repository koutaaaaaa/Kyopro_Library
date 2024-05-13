mint lagrange_interpolation(vector<mint> y,ll T){
    const ll n = y.size()-1;
    if(T <= n)return y[T];
    mint d = 1;
    vector<mint> dp(n+1);
    vector<mint> dp2(n+1);
    dp[0] = T;
    dp2[n] = T-n;
    for(ll i = 1; i <= n; i++)dp[i] = dp[i-1] * (T-i);
    for(ll i = n-1; i >= 0; --i)dp2[i] = dp2[i+1] * (T-i);
    for(ll i = n; i >= 1; i--)d *= i;
    mint ret = 0;
    d = mint(1)/d;
    for(ll i = n; i >= 0; --i){
        mint tmp = y[i];
        tmp *= d;
        if(i != 0)tmp *= dp[i-1];
        if(i != n)tmp *= dp2[i+1];
        ret += tmp;
        if(i == 0)break;
        d /= (i-1-n);
        d *= i;
    }
    return ret;
}