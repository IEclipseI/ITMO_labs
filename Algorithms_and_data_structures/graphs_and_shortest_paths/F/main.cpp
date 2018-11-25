//#define NOMINMAX
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

template<typename T>
using vec = std::vector<T>;
using ui = uint32_t;
using uill = uint64_t;
using namespace std;

struct E {
	ui st = 0;
	ui end = 0;
	int64_t w = 0;
	E(ui st, ui end) :st(st), end(end) {}
	E(ui st, ui end, int64_t w) :st(st), end(end), w(w) {}

};

struct V {
	bool visited = false;
	size_t id = 0;
	uill dist = 0;
	vec<E> edges;
	V(size_t id) :id(id) {};
	V() :id(0) {}
};
void sift_down(vec<V>& heap, int id, vec<ui>& indexes) {
	while (2 * id + 1 < heap.size()) {
		int l = 2 * id + 1;
		int r = 2 * id + 2;
		int j = l;
		if (r < heap.size() && heap[r].dist < heap[l].dist) {
			j = r;
		}
		if (heap[id].dist <= heap[j].dist)
			return;
		swap(heap[id], heap[j]);
		swap(indexes[heap[id].id], indexes[heap[j].id]);
		id = j;
	}
}
void sift_up(vec<V>& heap, int id, vec<ui>& indexes) {
	while (heap[id].dist < heap[(id - 1) / 2].dist) {
		swap(heap[id], heap[(id - 1) / 2]);
		swap(indexes[heap[id].id], indexes[heap[(id - 1) / 2].id]);

		id = (id - 1) / 2;
	}
}

V pop_min(vec<V>& heap, vec<ui>& indexes) {
	V result = heap[0];
	heap[0] = heap[heap.size() - 1];
	indexes[heap[heap.size() - 1].id] = 0;
	heap.pop_back();
	sift_down(heap, 0, indexes);
	return result;
}

struct G {
	vec<V> vert;
	bool check(ui a, ui b, ui c);
	friend istream& operator>>(istream&, G&);
	vec<uill> get_distances_to_all_verts(size_t id);

private:
	void clear_visited() {
		for (auto t : vert)
			t.visited = false;
	}
	void check_impl(ui v);
	vec<uill> get_distances_to_all_verts_impl(size_t id)
	{
		vec<V> heap;
		for (size_t i = 1; i < vert.size(); i++)
		{
			vert[i].dist = UINT64_MAX;
		}
		vert[id].dist = 0;
		heap.push_back(vert[id]);
		vec<ui> indexes(vert.size());
		indexes[id] = 0;
		for (size_t i = 1; i < vert.size(); i++)
		{
			if (i != id) {
				indexes[i] = heap.size();
				heap.push_back(vert[i]);
			}
		}
		vec<bool> included(vert.size(), false);

		for (size_t i = 1; i < vert.size(); i++)
		{
			V near_v = pop_min(heap, indexes);
			for (E e : near_v.edges) {
				if (vert[e.end].dist > vert[e.st].dist + e.w) {
					vert[e.end].dist = vert[e.st].dist + e.w;
					heap[indexes[e.end]].dist = vert[e.end].dist;
					sift_up(heap, indexes[e.end], indexes);
				}
			}
		}
		vec<uill> dist;
		for (size_t i = 1; i < vert.size(); i++)
		{
			dist.emplace_back(vert[i].dist);
		}
		return dist;
	}

};



int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	G g;
	cin >> g;
	ui a, b, c;
	cin >> a >> b >> c;
	//a--; b--; c--;
	if (g.check(a, b, c)) {
		vec<uill> answera = g.get_distances_to_all_verts(a);
		vec<uill> answerb = g.get_distances_to_all_verts(b);
		vec<uill> answerc = g.get_distances_to_all_verts(c);
		uill mini = answera[b - 1] + answerb[c - 1] + answerc[a - 1];
		mini -= max(answera[b - 1], max(answerb[c - 1], answerc[a - 1]));
		cout << mini;
	}
	else {
		cout << "-1";
	}
	cout << "\n";
	//system("pause");
	return 0;
}

istream & operator>>(istream &is, G &g)
{
	size_t n;
	size_t m;
	is >> n >> m;
	for (size_t i = 0; i <= n; i++)
	{
		g.vert.emplace_back(i);
	}
	for (size_t i = 0; i < m; i++)
	{
		ui st, end;
		int64_t w;
		is >> st >> end >> w;
		g.vert[st].edges.push_back(E(st, end, w));
		g.vert[end].edges.push_back(E(end, st, w));
	}
	return is;
}

bool G::check(ui a, ui b, ui c)
{
	check_impl(a);
	bool result = vert[a].visited && vert[b].visited && vert[c].visited;
	clear_visited();
	return result;
}

vec<uill> G::get_distances_to_all_verts(size_t id)
{
	return get_distances_to_all_verts_impl(id);
}

void make_min_heap(vec<V> &heap);

void G::check_impl(ui v)
{	
	vert[v].visited = true;
	for (auto e : vert[v].edges) {
		if (!vert[e.end].visited)
			check_impl(e.end);
	}

}
