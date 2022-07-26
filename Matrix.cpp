template<typename T>
struct Matrix{
    using V = vector<vector<T>>;
    V mat;
    int R,C;
    Matrix(int n, int m){
        R = n;
        C = m;
        mat.resize(n);
        for(int i = 0; i < n; i++)mat[i].resize(m);
    }

    Matrix& operator *= (Matrix& A){
        V B(R , vector<T>(C));
        for(int i = 0; i < R; i++){
            for(int j = 0; j < A.C; j++){
                for(int k = 0; k < C; k++){
                    B[i][j] += mat[i][k] * A.mat[k][j];
                }
            }
        }
        mat = B;
        C = A.C;
        return *this;
    }
    
    Matrix operator * (Matrix& A){
        return (Matrix(*this) *= A);
    }

    friend Matrix<T> pow(Matrix<T> &A , long long n){
        if(n == 0){
            Matrix<T> I(A.R , A.R);
            for(int i = 0; i < A.R; i++)I.mat[i][i] = 1;
            return I;
        }
        auto t = pow(A , n/2);
        t *= t;
        if(n & 1)t *= A;
        return t;
    }
};
