ll extgcd(ll a, ll b, ll &x , ll &y){//ax + by = 1�𖞂���x,y�����߂�
    ll d = a;
    if(b != 0){
        d = extgcd(b , a%b , y , x);
        y -= (a / b) * x;
    }
    else{
        x = 1;
        y = 0;
    }
    return d;
}