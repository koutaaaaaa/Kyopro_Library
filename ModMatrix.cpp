struct ModMatrix{
    using V = vector<vector<long long>>;
    V mat;
    int mod;
    int R,C;
    ModMatrix(int n, int m, int Mod){
        R = n;
        C = m;
        mod = Mod;
        mat.resize(n);
        for(int i = 0; i < n; i++)mat[i].resize(m);
    }

    ModMatrix& operator *= (ModMatrix& A){
        V B(R , vector<long long>(C));
        for(int i = 0; i < R; i++){
            for(int j = 0; j < A.C; j++){
                for(int k = 0; k < C; k++){
                    B[i][j] += (mat[i][k] * A.mat[k][j]) % mod;
                    B[i][j] %= mod;
                }
            }
        }
        mat = B;
        C = A.C;
        return *this;
    }
    
    ModMatrix operator * (ModMatrix& A){
        return (ModMatrix(*this) *= A);
    }

    friend ModMatrix pow(ModMatrix &A , long long n){
        if(n == 0){
            ModMatrix I(A.R , A.R , A.mod);
            for(int i = 0; i < A.R; i++)I.mat[i][i] = 1;
            return I;
        }
        auto t = pow(A , n/2);
        t *= t;
        if(n & 1)t *= A;
        return t;
    }
};