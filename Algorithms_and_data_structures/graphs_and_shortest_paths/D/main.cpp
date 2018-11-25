#include <iostream>	
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>

template<typename T>
using vec = std::vector<T>;
using ui = uint32_t;
using uill = uint64_t;
using namespace std;

struct edge {
	ui st;
	ui end;
	int64_t w;
};

set<ui> dfs(ui v, vec<bool>& vis, vec<vec<ui>>& g, set<ui>& answer);
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ui n, m, s;
	cin >> n >> m >> s;
	vec<edge> E;
	vec<vec<ui>> g(n, vec<ui>());
	vec<vec<int64_t>> d(2*n + 1, vec<int64_t>(n, INT64_MAX));
	for (size_t i = 0; i < m; i++)
	{
		edge e;
		cin >> e.st >> e.end >> e.w;
		--e.st;
		--e.end;
		E.push_back(e);
		g[e.st].push_back(e.end);
	}
	d[0][s - 1] = 0;
	for (size_t i = 0; i < 2*n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			d[i + 1][j] = d[i][j];
		}
		for (edge e : E) {
			if (d[i][e.st] < INT64_MAX)
			d[i + 1][e.end] = min(d[i + 1][e.end], d[i][e.st] + e.w);
		}
	}
	set<ui> good;
	vec<bool> vis(n, false);
	vec<ui> bad;
	for (int i = 0; i < n; i++) {
		if (d[n - 1][i] == d[2 * n][i]) {
			/*if (d[n - 1][i] == INT64_MAX)
				cout << "*" << "\n"*/
		}
		else { 
			bad.push_back(i);
			//cout << "-" << "\n";
		}
			//cout << ((t == INT_MAX)?-1:t) << "\n";
	}
	for (auto t : bad) {
		if (!vis[t])
			dfs(t, vis, g, good);
	}
	for (int i = 0; i < n; i++) {
		if (d[n - 1][i] == d[2 * n][i]) {
			if (d[n - 1][i] == INT64_MAX) {
				cout << "*" << "\n";
			}
			else {
				if (good.find(i) != good.end()) {
					cout << "-" << "\n";
				}
				else {
					cout << d[n - 1][i] << "\n";
				}
			}
		}
		else {
				cout << "-" << "\n";
		}
		//cout << ((t == INT_MAX)?-1:t) << "\n";
	}
	//cout << 10000000000000000000;
	//system("pause");
	return  0;
}

set<ui> dfs(ui v, vec<bool>& vis, vec<vec<ui>>& g, set<ui>& answer) {
	vis[v] = true;
	answer.insert(v);	
	for (auto t : g[v]) {
		if (!vis[t])
			dfs(t, vis, g, answer);
	}
	return answer;
}