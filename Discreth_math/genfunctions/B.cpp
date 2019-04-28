#include <iostream>
#include <vector>

using namespace std;

using ll = int64_t;
static const ll mod = 998244353;

ll gcd(ll a, ll b, ll &x, ll &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    ll x1, y1;
    ll d = gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

ll rev(ll x) {
    ll res, y;
    gcd(x, mod, res, y);
    return (res % mod + mod) % mod;
}

void delete_zeros(vector<ll> &vec) {
    while (!vec.empty() && vec.back() == 0) {
        vec.pop_back();
    }
}

ll get(const vector<ll> &a, size_t ind) {
    if (ind >= a.size())
        return 0;
    return a[ind];
}

void show(bool flag, const vector<ll> &a) {
    if (flag)
        cout << (a.size() > 0 ? a.size() - 1 : 0) << "\n";
    if (a.size() == 0) {
        cout << 0 << "\n";
        return;
    }
    for (int i = 0; i < a.size(); ++i) {
        cout << (a[i] >= 0 ? a[i] : mod + a[i]) << " ";
    }
    cout << "\n";
}

vector<ll> sum(vector<ll> &a, vector<ll> &b) {
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

vector<ll> mult(vector<ll> &a, vector<ll> &b, ll m) {
    vector<ll> res;
    size_t size = a.size() + b.size();
    res.resize(size, 0);
    for (size_t i = 0; i < a.size(); ++i) {
        for (size_t j = 0; j < b.size(); ++j) {
            res[i + j] = (res[i + j] + a[i] * b[j]) % mod;
        }
    }
    res.resize(m);
    return res;
}

vector<ll> divide(vector<ll> &a, vector<ll> &b) {
    vector<ll> res;
    const size_t coef_count = 1000;
    res.resize(coef_count, 0);
    for (size_t i = 0; i < coef_count; ++i) {
        ll sum = 0;
        for (size_t j = 0; j < i; ++j) {
            sum = (sum + res[j] * get(b, i - j) % mod) % mod;
        }
        res[i] = (get(a, i) - sum) / b[0] % mod;
    }
//    delete_zeros(res);
    return res;
}

vector<ll> sqrt(vector<ll> &a, size_t coef_count) {
    vector<ll> res(coef_count, 0);
    vector<ll> coefs(coef_count, 0);
    vector<ll> fact_sq(coef_count, 1);
    vector<ll> fact_2(coef_count, 1);
    vector<ll> power_4(coef_count, 1);
    for (size_t i = 1; i < coef_count; ++i) {
        fact_2[i] = fact_2[i - 1] * 2 * i % mod * (2 * i - 1) % mod;
        fact_sq[i] = fact_sq[i - 1] * i % mod * i % mod;
        power_4[i] = power_4[i - 1] * 4 % mod;
        ll top = (i % 2 == 1? mod -fact_2[i] : fact_2[i]);
        ll bot = (mod + (1 - 2 * (ll)i)) * (fact_sq[i]) % mod * (power_4[i]) % mod;
        coefs[i] = top * rev(bot) % mod;
//        if (i % 2 == 1)
//            coefs[i] *= -1;
        if (coefs[i] < 0)
            coefs[i] = mod + coefs[i];
    }
    vector<vector<ll>> powers_of_a(coef_count + 1, vector<ll>(coef_count));
    powers_of_a[1] = a;
    for (int i = 2; i < coef_count; ++i) {
        powers_of_a[i] = mult(powers_of_a[i - 1], a, coef_count);
    }
    for (int i = 1; i < coef_count; ++i) {
        for (int j = 0; j < powers_of_a[i].size(); ++j) {
            powers_of_a[i][j] = powers_of_a[i][j] * coefs[i] % mod;
        }
    }
    for (int i = 0; i < coef_count; ++i) {
        for (int j = 0; j < powers_of_a[i].size(); ++j) {
            res[j] = (powers_of_a[i][j] + res[j]) % mod;
        }
    }
    res[0] = 1;
    return res;
}

vector<ll> exp(vector<ll> &a, size_t coef_count) {
    vector<ll> res(coef_count, 0);
    vector<ll> coefs(coef_count, 1);
    for (int i = 1; i < coef_count; ++i) {
        coefs[i] = coefs[i - 1] * i % mod;
    }
    vector<vector<ll>> powers_of_a(coef_count + 1, vector<ll>(coef_count));
    powers_of_a[1] = a;
    for (int i = 2; i < coef_count; ++i) {
        powers_of_a[i] = mult(powers_of_a[i - 1], a, coef_count);
    }
    for (int i = 1; i < coef_count; ++i) {
        for (int j = 0; j < powers_of_a[i].size(); ++j) {
            powers_of_a[i][j] = powers_of_a[i][j] * rev(coefs[i]) % mod;
        }
    }
    for (int i = 0; i < coef_count; ++i) {
        for (int j = 0; j < powers_of_a[i].size(); ++j) {
            res[j] = (powers_of_a[i][j] + res[j]) % mod;
        }
    }
    res[0] = 1;
    return res;
}

vector<ll> ln(vector<ll> &a, size_t coef_count) {
    vector<ll> res(coef_count, 0);
    vector<ll> coefs(coef_count, 1);
    for (int i = 1; i < coef_count; ++i) {
        coefs[i] = i % 2 == 0? mod -i : i;
    }
    vector<vector<ll>> powers_of_a(coef_count + 1, vector<ll>(coef_count));
    powers_of_a[1] = a;
    for (int i = 2; i < coef_count; ++i) {
        powers_of_a[i] = mult(powers_of_a[i - 1], a, coef_count);
    }
    for (int i = 1; i < coef_count; ++i) {
        for (int j = 0; j < powers_of_a[i].size(); ++j) {
            powers_of_a[i][j] = powers_of_a[i][j] * rev(coefs[i]) % mod;
        }
    }
    for (int i = 0; i < coef_count; ++i) {
        for (int j = 0; j < powers_of_a[i].size(); ++j) {
            res[j] = (powers_of_a[i][j] + res[j]) % mod;
        }
    }
    return res;
}


int main() {
    vector<ll> test1 = {1, 1, 1, 5, 7, 21,33,-429 + mod,715};
    vector<ll> test2 = {2, -8, 16, -128, 256, -1024, 2048, 32768, 65536};
//    vector<ll> test1 = {1, -1 + mod, 1, -1 + mod, 1, -1 + mod,1,-1 + mod,1};
//    vector<ll> test2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
//    for (int i = 0; i < test1.size(); ++i) {
//        cout << test1[i] * rev(test2[i]) % mod << " ";
//    }
//    cout << "\n";
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, m;
    cin >> n >> m;

    vector<ll> a(n + 1);
    for (int i = 0; i <= n; ++i) {
        cin >> a[i];
    }
    a.resize(m);
    show(false, sqrt(a, m));
    show(false, exp(a, m));
    show(false, ln(a, m));
    return 0;
}