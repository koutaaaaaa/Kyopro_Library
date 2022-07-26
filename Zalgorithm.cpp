vector<int> Zalgorithm(string s){
    int n = s.size();
    vector<int> a(n , 0);
    int from = -1;
    int last = -1;
    for(int i = 1; i < n; i++){
        auto &same = a[i];
        if(from != -1){
            same = min(a[i-from] , last - i);
            same = max(same , 0);
        }
        while(i+same < n && s[same] == s[i+same])same++;
        if(i+same > last){
            last = i+same;
            from = i;
        }
    }
    a[0] = n;
    return a;
}