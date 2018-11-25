#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <deque>
#include <fstream>
#include <set>

template<typename T>
using vec = std::vector<T>;
using ui = uint32_t;
using uill = uint64_t;
using namespace std;

int main() {
	std::ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ifstream fin("guyaury.in");
	ofstream fout("guyaury.out");
	ui n;
	fin >> n;
	if (n == 1) {
		fout << "1\n";
	}
	else {
		vec<vec<bool>> g(n, vec<bool>(n));
		for (ui i = 1; i < n; ++i) {
			string s;
			fin >> s;
			for (ui j = 0; j < i; ++j) {
				g[i][j] = static_cast<bool>(s[j] - '0');
				g[j][i] = !g[i][j];
			}
		}
		list<ui> path;
		path.push_back(0);
		for (size_t i = 1; i < n; i++)
		{
			auto it = path.begin();
			while (it != path.end() && g[*it][i]) {
				it++;
			}
			path.insert(it, i);
		}
		list<ui> cycle;
		cycle.push_back(*path.begin());
		cycle.push_back(*(++path.begin()));
		path.pop_front();
		path.pop_front();
		auto it = path.begin();
		for (size_t i = 2; i < n; i++)
		{
			while (it != path.end() && g[*it][*cycle.begin()]) {
				cycle.push_back(*it);
				it++;
			}
		}
		path.erase(path.begin(), it);
		if (it == path.end()) {
			for (ui item : cycle)
			{
				fout << ++item << " ";
			}
			fout << "\n";
		}
		else {
			while (path.size() > 0) {
				ui v = *path.begin();
				if (g[*(--cycle.end())][v] && g[v][*(cycle.begin())]) {
					cycle.push_front(v);
					path.pop_front();
				}
				else {
					auto it_f = cycle.begin();
					auto it_s(it_f);
					it_s++;
					while (it_s != cycle.end() && !(g[*it_f][v] && g[v][*it_s])) {
						it_s++;
						it_f++;
					}
					if (it_s != cycle.end()) {
						cycle.insert(it_s, v);
						path.pop_front();
					}
					else {
						if (g[v][*it_f]) {
							cycle.insert(cycle.begin(), v);
							path.pop_front();
						}
						else {
							auto it = path.begin();
							it++;
							bool flag = true;
							auto pos = cycle.begin();
							while (flag) {
								pos = cycle.begin();
								while (pos != cycle.end()) {
									if (g[*it][*pos]) {
										flag = false;
										break;
									}
									pos++;
								}
								it++;
							}
							cycle.insert(pos, path.begin(), it);
							path.erase(path.begin(), it);
						}
					}
				} 
			}
			for (auto t : cycle) {
				fout << t + 1 <<  " ";
			}
			fout << "\n";
		}
		
	}
	fout.close();
	return 0;
}