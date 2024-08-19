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
vector<vi> G(MAXN, vi()), R(MAXN, vi()), GW(MAXN, vi()), RW(MAXN, vi()), G1(MAXN, vi()), G2(MAXN, vi());
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

vi ind1, ind2;

int s_now;
bool comp(int i, int j){
    return dist[s_now][i] < dist[s_now][j];
}

vi path1, path2;
int mark2[MAXN] = {0};
void get_paths(bool start){
    path1.clear();
    path2.clear();
    rep(c1,0,n){
        mark2[c1] = 0;
    }
    int a = s1;
    if(start){
        while(1){
            path1.push_back(a);
            if(a == t1)break;
            a = G1[a][rand()%sz(G1[a])];
        }
        trav(y, path1){
            mark2[y] = 2;
        }
        for(int c1 = n-1; c1 >= 0; c1--){
            int i = ind2[c1];
            if(mark2[i] == 2)continue;
            if(i != t2)mark2[i] = 1;
            trav(y, G2[i]){
                if(mark2[y] == 0)mark2[i] = 0;
            }
        }
        int b = s2;
        if(mark2[b])return;
        while(1){
            path2.push_back(b);
            if(b == t2)break;
            trav(y, G2[b]){
                if(!mark2[y]){
                    b = y;
                    break;
                }
            }
        }
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
            G[c1].clear();
            GW[c1].clear();
            R[c1].clear();
            RW[c1].clear();
            G1[c1].clear();
            G2[c1].clear();
            rep(c2,0,n){
                dist[c1][c2] = -1;
                mark[c1][c2] = 0;
            }
            ind1.push_back(c1);
            ind2.push_back(c1);
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

        if(dist[s1][t1] == -1 || dist[s2][t2] == -1){
            cout << "-1\n";
            continue;
        }

        s_now = s1;
        sort(all(ind1), comp);
        s_now = s2;
        sort(all(ind2), comp);
        rep(c1,0,n){
            rep(c2,0,sz(G[c1])){
                int a = G[c1][c2];
                int w = GW[c1][c2];
                if(dist[s1][c1] + w + dist[t1][a] == dist[s1][t1] && dist[s1][c1] != -1 && dist[t1][a] != -1){
                    G1[c1].push_back(a);
                }
                if(dist[s2][c1] + w + dist[t2][a] == dist[s2][t2] && dist[s2][c1] != -1 && dist[t2][a] != -1){
                    G2[c1].push_back(a);
                }
            }
        }
        int lim = 100;
        rep(c1,0,lim){
            get_paths(1);
            if(sz(path1) > 0 && sz(path2) > 0)break;
        }
        if(sz(path1) > 0 && sz(path2) > 0){
            print_vector(path1);
            print_vector(path2);
        }
        else{
            cout << "-1\n";
        }
    }
    return 0;
}
