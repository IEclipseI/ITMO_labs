#include <iostream>
#include <vector>

using namespace std;

using ll = int64_t;
using vll = vector<ll>;

string input;
size_t pos = 0;
size_t size = 7;
static const ll mod = 1000000007;


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

vector<ll> mult(const vector<ll> &a, ll c) {
    if (c < 0)
        c = mod + c;
    vector<ll> res(a);
    for (int i = 0; i < a.size(); ++i) {
        res[i] = res[i] * c % mod;
    }
    return res;
}



vector<ll> sum(const vector<ll> &a, const vector<ll> &b) {
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

vector<ll> minuse(const vector<ll> &a, const vector<ll> &b) {
    vector<ll> tmp(mult(b, -1));
    return sum(a, tmp);
}


vector<ll> mult(const vector<ll> &a, const vector<ll> &b, ll m) {
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

vector<ll> divide(const vector<ll> &a, const vector<ll> &b) {
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

vector<ll> sqrt(const vector<ll> &a, size_t coef_count) {
    vector<ll> res(coef_count, 0);
    vector<ll> coefs(coef_count, 0);
    vector<ll> fact_sq(coef_count, 1);
    vector<ll> fact_2(coef_count, 1);
    vector<ll> power_4(coef_count, 1);
    for (size_t i = 1; i < coef_count; ++i) {
        fact_2[i] = fact_2[i - 1] * 2 * i % mod * (2 * i - 1) % mod;
        fact_sq[i] = fact_sq[i - 1] * i % mod * i % mod;
        power_4[i] = power_4[i - 1] * 4 % mod;
        ll top = (i % 2 == 1 ? mod - fact_2[i] : fact_2[i]);
        ll bot = (mod + (1 - 2 * (ll) i)) * (fact_sq[i]) % mod * (power_4[i]) % mod;
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

vector<ll> exp(const vector<ll> &a, size_t coef_count) {
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

vector<ll> ln(const vector<ll> &a, size_t coef_count) {
    vector<ll> res(coef_count, 0);
    vector<ll> coefs(coef_count, 1);
    for (int i = 1; i < coef_count; ++i) {
        coefs[i] = i % 2 == 0 ? mod - i : i;
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
//
void skip_whitespaces() {
    while (pos < input.size() && isspace(input[pos]))
        pos++;
}

void incr_pos(size_t sh) {
    for (size_t i = 0; i < sh; ++i) {
        skip_whitespaces();
        pos++;
    }
}

vll calc() {
    vll res(size, 0);
    vll z;
    vll p;
    vector<vll> dp(size, vll(size, 0));
    switch (input[pos]) {
        case 'L':
            incr_pos(2);
            z = calc();
            incr_pos(1);
            res[0] = 1;
            for (int i = 1; i < size; ++i) {
                ll tmp = 0;
                for (int j = 1; j <= i; ++j) {
                    tmp += z[j] * res[i - j];
                }
                res[i] = tmp;
            }
            break;
        case 'S':
            incr_pos(2);
            z = calc();
            incr_pos(1);
            for (int i = 0; i < size; i++) {
                dp[0][i] = 1;
            }

            res[0] = 1;
            for (ll i = 1; i < size; i++) {
                for (ll j = 1; j < size; j++) {
                    ll dpij = 0;
                    for (ll k = 0; k <= i / j ; k++) {
                        ll tmp = max(z[j] + k - 1ll, 0ll);
                        ll tmp2 = 1;
                        for (ll i = tmp - k + 1; i <= tmp; ++i)
                            tmp2 *= i;
                        for (ll i = 2; i <= k; ++i)
                            tmp2 /= i;
                        dpij += tmp2 * dp[i - k * j][j - 1];
                    }
                    dp[i][j] = dpij;
                }
                res[i] = dp[i][i];
            }
            break;
        case 'P':
            incr_pos(2);
            z = calc();
            incr_pos(1);
            p = calc();
            incr_pos(1);
            for (ll i = 0; i < size; i++) {
                ll sum = 0;
                for (int j = 0; j <= i; j++) {
                    sum += z[j] * p[i - j];
                }
                res[i] = sum;
            }
            break;
        case 'B':
            res[1] = 1;
            incr_pos(1);
            break;
    }
    return res;
}


using ll = int64_t;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    getline(cin, input);
    incr_pos(0);
    auto res = calc();
    for ( auto item : res) {
        cout << item << " ";
    }
    cout << "\n";
    return 0;
}