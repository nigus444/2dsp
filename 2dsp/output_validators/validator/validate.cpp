#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <map>
#include <string>
#include "validate.h"

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef long double ld;

void read_judge_paths(int l1){
    if(l1 == -1)return;
    rep(c1,0,l1){
        int a;
        judge_ans >> a; 
    }
    int a;
    judge_ans >> a;
    rep(c1,0,a){
        int b;
        judge_ans >> b; 
    }
}

vi read_path(int n){
    int len;
    vi result;
    if(!(author_out >> len)){
        wrong_answer("Could not read first number of contestants output.\n");
    }
    if(len == -1)return result;
    rep(c1,0,len){
        int a;
        if(!(author_out >> a)){
            wrong_answer("Could not read an element of output.\n");
        }
        if(a <= 0 || a > n){
            wrong_answer("Element out of bounds.\n");
        }
        result.push_back(a-1);
    }
    if(sz(result) <= 1)wrong_answer("Too short path.\n");
    return result;
}

bool disjoint(vi &P1, vi &P2){
    set<int> both;
    rep(c1,0,sz(P1)){
        both.insert(P1[c1]);
    }
    rep(c1,0,sz(P2)){
        both.insert(P2[c1]);
    }
    return (sz(both) == sz(P1) + sz(P2));
}

void dijkstra(vector<vi> &graph, vector<vi> &weights, int start, vi &dist){
    int n = sz(graph);
    vector<bool> mark(n, 0);
    priority_queue<pii> pq;
    dist[start] = 0;
    pq.push({0, start});
    while(!pq.empty()){
        int a = pq.top().second;
        pq.pop();
        if(!mark[a]){
            mark[a] = 1;
            rep(c1,0,sz(graph[a])){
                int b = graph[a][c1];
                int w = weights[a][c1];
                if(dist[b] == -1 || dist[b] > dist[a]+w){
                    dist[b] = dist[a]+w;
                    pq.push({-dist[b], b});
                }
            }
        }
    }
}

int path_length(int s, int t, vi &P, map<int,int> &W){
    if(s != P[0])return -1;
    if(t != P.back())return -1;
    int res = 0;
    for(int c1 = 1; c1 < sz(P); c1++){
        int a = P[c1-1];
        int b = P[c1];
        int h = a*3000+b;
        if(W.find(h) == W.end())return -1;
        res += W[h];
    }
    return res;
}


string str(int x){
    if(x == 0)return "0";
    string res = "";
    string dig = "0123456789";
    while(x > 0){
        res += dig[x%10];
        x /= 10;
    }
    reverse(all(res));
    return res;
}

string tc(int s1, int t1, int s2, int t2, vector<vi> &G, vector<vi> &W, int n, int m){
    string res = "";
    res += str(n) + " " + str(m) + "\n";
    res += str(s1+1) + " " + str(t1+1) + " " + str(s2+1) + " " + str(t2+1) + "\n";
    rep(c1,0,n){
        rep(c2,0,sz(G[c1])){
            int i = G[c1][c2];
            int w = W[c1][c2];
            if(c1 < i){
                res += str(c1+1) + " " + str(i+1) + " " + str(w) + "   ,   ";
            }
        }
    }
    return res;
}


void check_case(){
    int T;
    judge_in >> T;
    for(int c1 = 0; c1 < T; c1++){
        int n,m,s1,t1,s2,t2;
        judge_in >> n >> m;
        vector<vi> graph;
        vector<vi> weights;
        map<int,int> weight_map;
        graph.assign(n, vi());
        weights.assign(n, vi());
        judge_in >> s1 >> t1 >> s2 >> t2;
        s1--;t1--;s2--;t2--;
        for(int c1 = 0; c1 < m; c1++){
            int a,b,c;
            judge_in >> a >> b >> c;
            a--;
            b--;
            graph[a].push_back(b);
            weights[a].push_back(c);
            weight_map[a*3000+b] = c;
        }

        int size_j;
        vi P1, P2;

        P1 = read_path(n);
        judge_ans >> size_j;
        read_judge_paths(size_j);
        if(sz(P1) == 0){
            if(size_j != -1){
                wrong_answer("%d: Contestant printed '-1' but an answer existed.\n", c1+1);
            }
            continue;
        }
        P2 = read_path(n);

        if(!disjoint(P1, P2)){
            wrong_answer("%d: Paths were not disjoint.\n", c1+1);
        }

        vi dist1(n, -1), dist2(n, -1);
        dijkstra(graph, weights, s1, dist1);
        dijkstra(graph, weights, s2, dist2);
        int L1 = path_length(s1, t1, P1, weight_map);
        int L2 = path_length(s2, t2, P2, weight_map);
        if(L1 != dist1[t1])wrong_answer("%d: Invalid first path.\n", c1+1);
        if(L2 != dist2[t2])wrong_answer("%d: Invalid second path.\n", c1+1);

        if(size_j == -1){
            string gg = tc(s1,t1,s2,t2,graph,weights,n,m);
          //  cout << gg << "\n";
          //  wrong_answer("%d", T);
            judge_error("%d: Judge says '-1' but contestants solution was valid.\n%s", c1+1, gg.c_str());
        }
    }
}

int main(int argc, char **argv) {
  init_io(argc, argv);
  check_case();

  /* Check for trailing output. */
  string trash;
  if (author_out >> trash) {
      wrong_answer("Trailing output\n");
  }

  accept();
  return 0;
}
