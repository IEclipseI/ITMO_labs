#include <iostream>
#include <vector>

using namespace std;

using ll = int64_t;
static const ll mod = 998244353;

void delete_zeros(vector<ll>& vec) {
    while (!vec.empty() && vec.back() == 0) {
        vec.pop_back();
    }
}

ll get(const vector<ll>& a, size_t ind) {
    if (ind >= a.size())
        return 0;
    return a[ind];
}

void show(bool flag, const vector<ll>& a) {
    if (flag)
        cout << (a.size() > 0? a.size() - 1 : 0) << "\n";
    for (int i = 0; i < a.size(); ++i) {
        cout << (a[i] >= 0 ? a[i] : mod + a[i]) << " ";
    }
    cout << "\n";
}

vector<ll> sum(vector<ll>& a, vector<ll>& b) {
    size_t mi = min(a.size(), b.size());
    vector<ll> res;
    for (size_t i = 0; i < mi; ++i) {
        res.push_back((a[i] + b[i]) % mod);
    }
    if (a.size() < b.size()) {
        for (size_t i = mi; i < b.size(); ++i) {
            res.push_back(b[i]);
        }
    } else {
        for (size_t i = mi; i < a.size(); ++i) {
            res.push_back(a[i]);
        }
    }
    delete_zeros(res);
    return res;
}

vector<ll> mult(vector<ll>& a, vector<ll>& b) {
    vector<ll> res;
    size_t size = a.size() + b.size();
    res.resize(size, 0);
    for (size_t i = 0; i < a.size(); ++i) {
        for (size_t j = 0; j < b.size(); ++j) {
            res[i + j] = (res[i + j] + a[i] * b[j]) % mod;
        }
    }
    delete_zeros(res);
    return res;
}

vector<ll> divide(vector<ll>& a, vector<ll>& b) {
    vector<ll> res;
    const size_t coef_count = 1000;
    res.resize(coef_count, 0);
    for (size_t i = 0; i < coef_count; ++i) {
        ll sum = 0;
        for (size_t j = 0; j < i; ++j) {
            sum = (sum + res[j] * get(b, i - j)% mod) % mod;
        }
        res[i] = (get(a, i) - sum) / b[0] % mod;
    }
//    delete_zeros(res);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, m;
    cin >> n >> m;

    vector<ll> a(n + 1);
    vector<ll> b(m + 1);
    for (int i = 0; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i <= m; ++i) {
        cin >> b[i];
    }
    show(true, sum(a, b));
    show(true, mult(a, b));
    show(false, divide(a, b));
    return 0;
}