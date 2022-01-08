#include <bits/stdc++.h>
using namespace std;
using pi = pair<int,int>;

int main(){
    int n,x,y; cin >> n >> x >> y;
  //n*nの盤面
  //最初の位置が上からx番目で左からy番目(1~n)
  /*青だったら'#',白だったら'.'で渡す
    (例)
      3 1 1
      .#.
      .##
      #..
      
      出力されるのは最短距離とどう動かせばよいか
      アルファベットは上下左右の英語の頭文字
    */
    --x; --y;
    char g[n][n];
    int banmen = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> g[i][j];
            if(g[i][j] == '#'){
                banmen |= (1<<(i*n+j));
            }
        }
    }
    queue<pi> q;
    vector<vector<int>> dist(1<<(n*n) , vector<int>(n*n,114514810));
    vector<vector<pi>> memo(1<<(n*n) , vector<pi>(n*n));
    dist[banmen][x*n+y] = 0;
    q.push(pi(banmen,x*n+y));
    while(!q.empty()){
        pi tmp = q.front();
        q.pop();
        int bit = tmp.first;
        int now = tmp.second;
        vector<int> v = {now+1 , now-1 , now+n , now-n};
        for(int i = 0; i < 4; i++){
            int nxt = v[i];
            if(nxt < 0 || nxt >= n*n)continue;
            if(nxt % n == 0 && now % n == n-1)continue;
            if(nxt % n == n-1 && now % n == 0)continue;
            int nxtbit = bit ^ (1<<nxt);
            if(dist[nxtbit][nxt] == 114514810){
                dist[nxtbit][nxt] = dist[bit][now] + 1;
                memo[nxtbit][nxt] = {bit,now};
                q.push(pi(nxtbit,nxt));
            }
        }
    }
    string howto;
    int ans = 114514810;
    int now;
    int bit = (1<<(n*n))-1;
    for(int i = 0; i< n*n; i++){
        if(ans > dist[(1<<(n*n))-1][i]){
            ans = dist[(1<<(n*n))-1][i];
            now = i;
        }
    }
    int kasu = now;
    while(bit != banmen || now != x*n+y){
        int nxt = memo[bit][now].second;
        bit = memo[bit][now].first;
        if(nxt+1 == now)howto.push_back('R');
        else if(nxt-1 == now)howto.push_back('L');
        else if(nxt+n == now)howto.push_back('D');
        else howto.push_back('U');
        now = nxt;
    }
    reverse(howto.begin() , howto.end());
    cout << dist[((1<<(n*n))-1)][kasu] << endl;
    cout << howto << endl;
}
