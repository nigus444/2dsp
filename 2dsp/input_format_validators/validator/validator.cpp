#include "validator.h"
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;


void run() {
	int max_T = Arg("max_T");
	int max_n = Arg("max_n");
	int max_m = Arg("max_m");

	int T = Int(1, max_T);
	Endl();

	for(int c1 = 0; c1 < T; c1++){
		int n = Int(2, max_n);
		Space();
		int m = Int(1, max_m);
		Endl();
		vector<vector<int> > graph(n, vector<int>());
		set<pair<int,int> > edges;

		int s1 = Int(1, n);
		Space();
		int t1 = Int(1, n);
		Space();
		int s2 = Int(1, n);
		Space();
		int t2 = Int(1, n);
		Endl();

		for(int c2 = 0; c2 < m; c2++){
			int a = Int(1, n);
			Space();
			int b = Int(1, n);
			Space();
			int c = Int(1, 10000);
			Endl();
			a--;
			b--;
			assert(a != b);
			assert(edges.find({a,b}) == edges.end());
			edges.insert({a,b});
			graph[a].push_back(b);
		}
	}
}
