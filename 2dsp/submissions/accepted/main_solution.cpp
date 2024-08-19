#include <bits/stdc++.h>
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

const int MAXN = 1000;
int n,m;
vector<vi> G(MAXN, vi()), R(MAXN, vi()), GW(MAXN, vi()), RW(MAXN, vi()), G1(MAXN, vi()), G2(MAXN, vi()), G2B(MAXN, vi());
int s1,s2,t1,t2;
ll dist[MAXN][MAXN] = {0};
bool mark[MAXN][MAXN] = {0};

void dijkstra(int start, vector<vi> &graph, vector<vi> &weights){
    priority_queue<pll> pq;
    pq.push({0, start});
    dist[start][start] = 0;

    while(!pq.empty()){
        int a = pq.top().second;
        pq.pop();
        if(!mark[a][start]){
            mark[a][start] = 1;
            rep(c1,0,sz(graph[a])){
                ll w = weights[a][c1];
                int i = graph[a][c1];
                if(dist[start][i] == -1 || dist[start][i] > w + dist[start][a]){
                    dist[start][i] = w + dist[start][a];
                    pq.push({-dist[start][i], i});
                }
            }
        }
    }
}

struct state{
    int v1,v2,f1,f2,go;
};

ll hash_state(state s){
    return MAXN*8*s.v1 + 8*s.v2 + 4*s.f1 + 2*s.f2 + s.go;
}

unordered_map<ll,ll> NEXT_MAP;
vector<state> NEXT;
vi ind1, ind2;

void add_to_next(state s1, state s2){
    ll h = hash_state(s1);
    if(NEXT_MAP.find(h) != NEXT_MAP.end())return;
    NEXT_MAP[h] = sz(NEXT);
    NEXT.push_back(s2);
}

bool comp1(int i, int j){
    return dist[s1][i] > dist[s1][j];
}

bool comp2(int i, int j){
    return dist[s2][i] > dist[s2][j];
}

bool DP[MAXN][MAXN][2][2][2];

bool solve(bool swapped){
    sort(all(ind1), comp1);
    sort(all(ind2), comp2);
    NEXT.clear();
    NEXT_MAP.clear();
    vl phi, psi;
    rep(c1,0,n){
        phi.push_back(dist[s1][c1] + dist[s2][c1]);
        psi.push_back(dist[s1][c1] - dist[s2][c1]);
    }
    if(swapped){
        swap(phi, psi);
        swap(s2,t2);
        reverse(all(ind2));
        G2 = G2B;
    }
    rep(i1,0,n){
        rep(i2,0,n){
            rep(f1,0,2){
                rep(f2,0,2){
                    rep(go,0,2){
                        int v1 = ind1[i1];
                        int v2 = ind2[i2];
                        if(v1 == v2){
                            DP[v1][v2][f1][f2][go] = 0;
                            continue;
                        }
                        if(v1 == t1 && v2 == t2){
                            DP[v1][v2][f1][f2][go] = 1;
                            continue;
                        }
                        DP[v1][v2][f1][f2][go] = 0;

                        trav(w1, G1[v1]){
                            if(v1 == t1)break;
                            if(v2 != t2 && phi[v2] < phi[v1])break;
                            if(phi[w1] == phi[v1] && psi[w1] > psi[v2] && f1)continue;
                            if(phi[w1] == phi[v1] && phi[v1] < phi[v2] && go)continue;
                            bool F1 = f1;
                            bool F2 = f2;
                            bool go2 = (phi[v1] == phi[v2] && phi[w1] > phi[v1]);
                            if(phi[w1] != phi[v1])F1 = 0;
                            if(phi[w1] == phi[v1] && psi[v1] < psi[v2] && phi[v1] == phi[v2])F2 = 1;
                            if(!DP[w1][v2][F1][F2][go2])continue;
                            DP[v1][v2][f1][f2][go] = 1;
                            add_to_next({v1,v2,f1,f2,go}, {w1,v2,F1,F2,go2});
                        }

                        trav(w2, G2[v2]){
                            if(v2 == t2)break;
                            if(v1 != t1 && phi[v1] < phi[v2])break;
                            if(phi[w2] == phi[v2] && psi[w2] < psi[v1] && f2)continue;
                            if(phi[w2] == phi[v2] && phi[v2] < phi[v1] && go)continue;
                            bool F1 = f1;
                            bool F2 = f2;
                            bool go2 = (phi[v1] == phi[v2] && phi[w2] > phi[v2]);
                            if(phi[w2] != phi[v2])F2 = 0;
                            if(phi[w2] == phi[v2] && psi[v2] > psi[v1] && phi[v1] == phi[v2])F1 = 1;
                            if(!DP[v1][w2][F1][F2][go2])continue;
                            DP[v1][v2][f1][f2][go] = 1;
                            add_to_next({v1,v2,f1,f2,go}, {v1,w2,F1,F2,go2});
                        }
                    }
                }
            }
        }
    }
    return DP[s1][s2][0][0][0];
}

vi path1, path2;
void get_paths(){
    path1.clear();
    path2.clear();
    state s = {s1, s2, 0, 0, 0};
    path1.push_back(s1);
    path2.push_back(s2);
    while(NEXT_MAP.find(hash_state(s)) != NEXT_MAP.end()){
        s = NEXT[NEXT_MAP[hash_state(s)]];
        if(s.v1 != path1.back())path1.push_back(s.v1);
        if(s.v2 != path2.back())path2.push_back(s.v2);
    }
}

void print_vector(vi &v){
    cout << sz(v) << "\n";
    trav(i, v){
        cout << i+1 << " ";
    }cout << "\n";
}

int main() {
    int T;
    cin >> T;
    rep(_,0,T){
        cin >> n >> m;
        cin >> s1 >> t1 >> s2 >> t2;
        s1--;t1--;s2--;t2--;
        ind1.clear();
        ind2.clear();
        rep(c1,0,n){
            ind1.push_back(c1);
            ind2.push_back(c1);
            G[c1].clear();
            GW[c1].clear();
            R[c1].clear();
            RW[c1].clear();
            G1[c1].clear();
            G2[c1].clear();
            G2B[c1].clear();
            rep(c2,0,n){
                dist[c1][c2] = -1;
                mark[c1][c2] = 0;
            }
        }
        rep(c1,0,m){
            int a,b,c;
            cin >> a >> b >> c;
            a--;b--;
            G[a].push_back(b);
            R[b].push_back(a);
            GW[a].push_back(c);
            RW[b].push_back(c);
        }
        dijkstra(s1, G, GW);
        dijkstra(t1, R, RW);
        dijkstra(s2, G, GW);
        dijkstra(t2, R, RW);
        rep(c1,0,n){
            rep(c2,0,sz(G[c1])){
                int a = G[c1][c2];
                ll w = GW[c1][c2];
                if(dist[s1][c1] + w + dist[t1][a] == dist[s1][t1] && dist[s1][c1] != -1 && dist[t1][a] != -1){
                    G1[c1].push_back(a);
                }
                if(dist[s2][c1] + w + dist[t2][a] == dist[s2][t2] && dist[s2][c1] != -1 && dist[t2][a] != -1){
                    G2[c1].push_back(a);
                    G2B[a].push_back(c1);
                }
            }
        }
        bool ans;
        ans = solve(0);
        if(ans){
            get_paths();
            print_vector(path1);
            print_vector(path2);
        }
        else{
            ans = solve(1);
            if(ans){
                get_paths();
                reverse(all(path2));
                print_vector(path1);
                print_vector(path2);
            }
            else{
                cout << "-1\n";
            }
        }
    }
    return 0;
}
