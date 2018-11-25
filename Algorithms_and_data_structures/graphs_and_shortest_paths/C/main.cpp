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

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ui n;
	cin >> n;
	vec<vec<int>> E(n, vec<int>(n));
	vec<vec<int>> backE(n, vec<int>(n));
	vec<vec<int>> d(n + 1, vec<int>(n, INT_MAX/2));
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			int w;
			cin >> w;
			if (i == j && w < 0) {
				cout << "YES\n1\n" << i + 1;
				return 0;
			}
			if (w == 100000) w = INT_MAX/2;
			E[i][j] = w;
			backE[j][i] = w;
		}
	}
	if (n == 1) {
		if (E[0][0] < 0) {
			cout << "YES\n1\n1\n";
			return 0;
		}
		else {
			cout << "NO\n";
			return 0;
		}
	}
	d[0][0] = 0;
	for (size_t i = 1; i < n + 1; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			for (size_t k = 0; k < n; k++)
			{
				d[i][j] = min(min(d[i][j], d[i - 1][k] + E[k][j]), d[i - 1][j]);
			}
		}
	}
	size_t id = SIZE_MAX;
	for (size_t i = 0; i < n; i++)
	{
		if (d[n][i] != d[n - 1][i]) {
			id = i;
			break;
		}
	}
	if (id >= n) {
		cout << "NO\n";
	}
	else {
		set<ui> answer;
		vec<ui> result;
		vec<ui> res;
		bool flag = true;
		answer.insert(id);
		result.push_back(id);
		ui m = n;
		while (flag) {
			for (size_t i = 0; i < n; i++)
			{
				if (d[m - 1][i] == d[m][id] - backE[id][i]) {
					if (i == id) {
						continue;
					}
					else {
						if (answer.find(i) == answer.end()) {
							answer.insert(i);
							result.push_back(i);
							id = i;
							break;
						}
						else {
							flag = false;
							auto it = --result.end();
							while (*it != i) {
								res.push_back(*it);
								it--;
							}
							res.push_back(i);
							break;
						}
					}
				}
			}
			m--;
		}
		//reverse(res.begin(), res.end());
		cout << "YES\n" << res.size() << "\n";
		for (auto t : res)
			cout << t + 1 << " ";
	}
	//system("pause");
	return  0;
}