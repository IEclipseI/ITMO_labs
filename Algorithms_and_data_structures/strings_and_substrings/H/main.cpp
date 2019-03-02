#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <fstream>
#include <set>

using namespace std;

template<class T>
using vec = vector<T>;
using ll = int64_t;
using ui = uint64_t;

struct node {
    ll parent;
    char ch;
    bool terminal;
    ll link;
    map<char, ll> kids;
    bool visited_by_sift;
    bool visited_by_dfs;
    set<ll> ides;
    ll time = -1;

    node(ll parent = -1, char ch = 0, bool terminal = false)
            : parent(parent),
            ch(ch),
            terminal(terminal),
            link(-1),
            kids(map<char, ll>{}),
            visited_by_sift(false),
            visited_by_dfs(false),
            ides(set<ll>{})
            {}
    void add_kid(char ch, ll ind) {
        kids.insert({ch, ind});
    }
    ll kid(char ch) {
        auto p = kids.find(ch);
        return  p != kids.end()? p->second: -1;
    }
    void add_id(ll id) {
        ides.insert(id);
    }
};

struct aho_corasick {
    vec<node> nodes; //root is 0;
    ll strings_count;
    aho_corasick(): nodes(vec<node>{node()}), strings_count(0){}
    void add(const string& s) {
        ll cur = 0;
        ll i = 0;
        while (i < s.size()) {
            if (nodes[cur].kid(s[i]) == -1) {
                nodes[cur].add_kid(s[i], nodes.size());
                nodes.push_back(node(cur, s[i], i + 1 == s.size()));
            }
            cur = nodes[cur].kid(s[i]);
            i++;
        }
        nodes[cur].terminal = true;
        nodes[cur].add_id(strings_count++);
    }

    void build_suf_links() {
        deque<ll> left{0};
        while (!left.empty()) {
            add_suf_link(left.front());
            for(auto p : nodes[left.front()].kids)
                left.push_back(p.second);
            left.pop_front();
        }
    }

    map<ll, ll> sift_string(string s) {
        map<ll, ll> res;
        ll i = 0;
        ll cur = 0;
        while (i < s.size()) {
            cur = next(s[i++], cur);
            nodes[cur].visited_by_sift = true;
            nodes[cur].times++;
        }
        deque<ll> left{0};
        deque<ll> to_do;
        while (!left.empty()) {
            for(auto p : nodes[left.front()].kids){
                to_do.push_front(p.second);
                left.push_back(p.second);
            }
            left.pop_front();
        }
        for (int j = 0; j < nodes.size(); ++j) {
            if (!nodes[j].visited_by_dfs && nodes[j].visited_by_sift)
                sift_dfs(j);
        }
        for (auto it : to_do)
            sum(it);
        for (int j = 1; j < nodes.size(); ++j) {
            if (nodes[j].terminal)
                for(auto p : nodes[j].ides){
                    res.insert({p,nodes[j].times});
                }
//                res.insert(nodes[j].ides.begin(), nodes[j].ides.end());
            nodes[j].visited_by_sift = false;
        }
        return res;
    }
private:
    void sum(ll cur) {
        nodes[nodes[cur].link].times += nodes[cur].times;
    }
    void sift_dfs(ll cur) {
        nodes[cur].visited_by_dfs = true;
        if (nodes[cur].link != - 1 && !nodes[nodes[cur].link].visited_by_dfs)
            sift_dfs(nodes[cur].link);
    }
    void add_suf_link(ll ind) {
        if (ind == 0)
            return;
        ll ind_cur = nodes[nodes[ind].parent].link;
        while (ind_cur != - 1 && nodes[ind_cur].kid(nodes[ind].ch) == -1) {
            ind_cur = nodes[ind_cur].link;
        }
        if (ind_cur == -1) {
            nodes[ind].link = 0;
        } else {
            nodes[ind].link = nodes[ind_cur].kid(nodes[ind].ch);
        }
    }
    ll next(char ch, ll ind) {
        while (ind != -1 && nodes[ind].kid(ch) == -1) {
            ind = nodes[ind].link;
        }
        if (ind == -1)
            return 0;
        else
            return nodes[ind].kid(ch);
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin("search5.in");
    ofstream fout("search5.out");
    int n;
    fin >> n;
    aho_corasick tree;
    for (int i = 0; i < n; ++i) {
        string tmp;
        fin >> tmp;
        tree.add(tmp);
    }
    tree.build_suf_links();
    string t;
    fin >> t;
    auto res = tree.sift_string(t);
    for (int i = 0; i < n; ++i) {
        if (res.find(i) != res.end())
            fout << res.find(i)->second << "\n";
        }
    return 0;
}