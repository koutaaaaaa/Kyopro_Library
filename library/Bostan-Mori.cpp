mint bostan_mori(vector<mint> &P , vector<mint> &Q , ll n){
    if(n == 0){
        return P[0];
    }
    vector<mint> Q_m(Q.size());
    rep(i,0,Q.size()){
        if(i & 1)Q_m[i] = -Q[i];
        else Q_m[i] = Q[i];
    }
    vector<mint> V(Q.size() + Q_m.size() - 1);
    V = convolution(Q , Q_m);
    vector<mint> U(P.size() + Q_m.size() - 1);
    U = convolution(P , Q_m);
    if(n % 2 == 0){
        vector<mint> n_P;
        for(int i = 0; i < U.size(); i += 2)n_P.push_back(U[i]);
        vector<mint> n_Q;
        for(int i = 0; i < V.size(); i += 2)n_Q.push_back(V[i]);
        return bostan_mori(n_P , n_Q , n/2);
    }
    vector<mint> n_P;
    for(int i = 1; i < U.size(); i += 2)n_P.push_back(U[i]);
    vector<mint> n_Q;
    for(int i = 0; i < V.size(); i += 2)n_Q.push_back(V[i]);
    return bostan_mori(n_P , n_Q , (n-1)/2);
}