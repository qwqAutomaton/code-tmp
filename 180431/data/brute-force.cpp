#include <iostream>
using ll = long long;
const int MAXN = (1<<26)+1, MOD = 998244353;
ll f[MAXN];
ll g[MAXN];
ll tr[MAXN];
inline ll qpow(ll a, ll b = MOD - 2)
{
    ll ans = 1;
    while (b)
    {
        if (b & 1)
            (ans *= a) %= MOD;
        (a *= a) %= MOD;
        b >>= 1;
    }
    return ans;
}
const int G = 3, InvG = qpow(3);
void NTT(ll *f, int n, bool inv = false)
{
    for (int i = 0; i < n; i++)
        if (i < tr[i])
            std::swap(f[i], f[tr[i]]);
    for (int l = 2; l <= n; l <<= 1)
    {
        ll root = qpow(inv ? InvG : G, (MOD - 1) / l);
        for (int k = 0; k < n; k += l)
        {
            ll cur = 1;
            for (int i = k; i < k + (l >> 1); i++)
            {
                ll qwq = cur * f[i + (l >> 1)] % MOD;
                f[i + (l >> 1)] = f[i] - qwq;
                if (f[i + (l >> 1)] < 0)
                    f[i + (l >> 1)] += MOD;
                f[i] += qwq;
                if (f[i] >= MOD)
                    f[i] -= MOD;
                (cur *= root) %= MOD;
            }
        }
    }
    if (inv)
    {
        int invl = qpow(n);
        for (int i = 0; i < n; i++)
            (f[i] *= invl) %= MOD;
    }
}
int main()
{
    int n;
    std::cin >> n;
    ll fact = 1;
    for (int i = 1; i <= n; i++)
        f[i] = i, g[i] = qpow(i), (fact *= i) %= MOD;
    int lim = 1;
    while (lim <= n << 1)
        lim <<= 1;
    NTT(f, lim);
    NTT(g, lim);
    for (int i = 0; i < lim; i++)
        f[i] *= g[i];
    NTT(f, lim, 1);
    ll sum = 0;
    for (int i = 1; i <= n << 1; i++)
        (sum += f[i]) %= MOD;
    std::cout << (sum * fact) % MOD << std::endl;
    return 0;
}

