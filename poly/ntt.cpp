#include <iostream>
const int MOD = 998244353, G = 3, MAXN = 1000010;
using ll = long long;
ll qpow(ll a, ll b = MOD - 2)
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
int InvG = qpow(G), tr[MAXN << 2];
ll f[MAXN << 2], g[MAXN << 2];
void NTT(ll *f, int n, bool rev = false)
{
    for (int i = 0; i < n; i++)
        tr[i] = (tr[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);
    for (int i = 0; i < n; i++)
        if (i < tr[i])
            std::swap(f[i], f[tr[i]]);
    for (int l = 2; l <= n; l <<= 1)
    {
        ll root = qpow(rev ? InvG : G, (MOD - 1) / l);
        for (int k = 0; k < n; k += l)
        {
            ll cur = 1;
            for (int i = k; i < (l >> 1) + k; i++)
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
    if (rev)
    {
        ll invl = qpow(n);
        for (int i = 0; i < n; i++)
            (f[i] *= invl) %= MOD;
    }
}
int n, m;
int main()
{
    int lim = 1;
    std::cin >> n >> m;
    for (int i = 0; i <= n; i++)
        std::cin >> f[i];
    for (int j = 0; j <= m; j++)
        std::cin >> g[j];
    while (lim <= n + m)
        lim <<= 1;
    NTT(f, lim);
    NTT(g, lim);
    for (int i = 0; i < lim; i++)
        (f[i] *= g[i]) %= MOD;
    NTT(f, lim, 1);
    ll invlim = 1;//qpow(lim);
    for (int i = 0; i <= n + m; i++)
        std::cout << f[i] * invlim % MOD << ' ';
    return 0;
}
