#include <bits/stdc++.h>
using namespace std;
const int INF = 1000000;
template <typename Cap>
struct ford_fulkerson{
    struct edge{
        int to, rev;
        Cap cap;
        edge(int to, int rev, Cap cap): to(to), rev(rev), cap(cap){
        }
    };
    int N;
    vector<vector<edge>> G;
    ford_fulkerson(){
    }
    ford_fulkerson(int N): N(N), G(N){
    }
    void add_edge(int from, int to, Cap cap){
        int id1 = G[from].size();
        int id2 = G[to].size();
        G[from].push_back(edge(to, id2, cap));
        G[to].push_back(edge(from, id1, 0));
    }
    Cap max_flow(int s, int t){
        Cap flow = 0;
        while (true){
            vector<Cap> m(N, INF);
            vector<int> pv(N, -1);
            vector<int> pe(N, -1);
            vector<bool> used(N, false);
            queue<int> Q;
            Q.push(s);
            used[s] = true;
            while (!Q.empty()){
                int v = Q.front();
                Q.pop();
                int cnt = G[v].size();
                for (int i = 0; i < cnt; i++){
                    int w = G[v][i].to;
                    if (!used[w] && G[v][i].cap > 0){
                        used[w] = true;
                        m[w] = min(m[v], G[v][i].cap);
                        pv[w] = v;
                        pe[w] = i;
                        Q.push(w);
                    }
                }
            }
            if (!used[t]){
                break;
            }
            Cap f = m[t];
            for (int i = t; i != s; i = pv[i]){
                G[pv[i]][pe[i]].cap -= f;
                G[i][G[pv[i]][pe[i]].rev].cap += f;
            }
            flow += f;
        }
        return flow;
    }
};
int main(){
  int T;
  cin >> T;
  for (int i = 0; i < T; i++){
    vector<vector<int>> c(4, vector<int>(4));
    for (int j = 0; j < 4; j++){
      for (int k = 0; k < 4; k++){
        cin >> c[j][k];
      }
    }
    vector<int> A = {c[3][0], c[3][1], c[2][3], c[2][0], c[1][2], c[1][3], c[0][1], c[0][2]};
    int mx1 = min(c[3][0], c[2][0]);
    int mx2 = min(c[1][2], c[0][2]);
    int ma = 0;
    for (int j = 0; j <= mx1; j++){
      for (int k = 0; k <= mx2; k++){
        vector<int> A2 = A;
        A2[0] -= j;
        A2[3] -= j;
        A2[4] -= k;
        A2[7] -= k;
        ford_fulkerson<int> G(10);
        G.add_edge(8, 0, A2[0]);
        G.add_edge(8, 3, A2[3]);
        G.add_edge(8, 5, A2[5]);
        G.add_edge(8, 6, A2[6]);
        G.add_edge(1, 9, A2[1]);
        G.add_edge(2, 9, A2[2]);
        G.add_edge(4, 9, A2[4]);
        G.add_edge(7, 9, A2[7]);
        G.add_edge(0, 1, INF);
        G.add_edge(0, 4, INF);
        G.add_edge(3, 2, INF);
        G.add_edge(3, 7, INF);
        G.add_edge(5, 1, INF);
        G.add_edge(5, 2, INF);
        G.add_edge(5, 4, INF);
        G.add_edge(6, 1, INF);
        G.add_edge(6, 2, INF);
        G.add_edge(6, 7, INF);
        ma = max(ma, j + k + G.max_flow(8, 9));
      }
    }
    int sum = 0;
    for (int j = 0; j < 8; j++){
      sum += A[j];
    }
    int ans = sum - ma;
    ans = max({ans, c[0][3], c[1][0], c[2][1], c[3][2]});
    cout << ans << endl;
  }
}