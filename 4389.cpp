#include <iostream>
#include <cstring>
const int MAXN = 100010;
const int MOD = 998244353, G = 3, InvG = 332748118;
using ll = long long;
ll inv[MAXN << 2];
ll qpow(ll b, ll p = MOD - 2)
{
    ll ans = 1;
    while (p)
    {
        if (p & 1)
            (ans *= b) %= MOD;
        (b *= b) %= MOD;
        p >>= 1;
    }
    return ans;
}
void NTT(ll *f, int n, bool inv = false)
{
    static int tr[MAXN << 2] = {0};
    for (int i = 0; i < n; i++)
        tr[i] = (tr[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);
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
                ll qwq = f[i + (l >> 1)] * cur % MOD;
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
        ll invn = qpow(n);
        for (int i = 0; i < n; i++)
            (f[i] *= invn) %= MOD;
    }
}
void Inv(ll *f, ll *r, int n)
{
    static ll tmp[MAXN << 2], tmpf[MAXN << 2];
    memset(tmp, 0, sizeof(tmp));
    memset(tmpf, 0, sizeof(tmpf));
    r[0] = qpow(f[0]);
    for (int l = 2; l <= n; l <<= 1)
    {
        for (int i = 0; i < l; i++)
            tmp[i] = r[i], tmpf[i] = f[i];
        for (int i = l; i < l << 1; i++)
            tmp[i] = tmpf[i] = 0;
        NTT(tmp, l << 1);
        NTT(tmpf, l << 1);
        for (int i = 0; i < l << 1; i++)
            tmp[i] = (2 - tmp[i] * tmpf[i] % MOD + MOD) % MOD * tmp[i] % MOD;
        NTT(tmp, l << 1, 1);
        for (int i = 0; i < l; i++)
            r[i] = tmp[i];
    }
}
void Directive(ll *f, int n)
{
    for (int i = 1; i < n; i++)
        f[i - 1] = f[i] * i % MOD;
    f[n - 1] = 0;
}
void Intergral(ll *f, int n)
{
    for (int i = n; i; i--)
        f[i] = f[i - 1] * inv[i] % MOD;
    f[0] = 0;
}
void Ln(ll *f, int n)
{
    static ll res[MAXN << 2];
    memset(res, 0, sizeof(res));
    Inv(f, res, n);
    Directive(f, n);
    NTT(f, n << 1);
    NTT(res, n << 1);
    for (int i = 0; i < n << 1; i++)
        (f[i] *= res[i]) %= MOD;
    NTT(f, n << 1, 1);
    Intergral(f, n << 1);
    for (int i = n; i < n << 1; i++)
        f[i] = 0;
}
void pExp(ll *f, ll *res, int n)
{
    static ll tmpf[MAXN << 2], tmpln[MAXN << 2], tmpr[MAXN << 2];
    res[0] = 1;
    for (int l = 2; l <= n; l <<= 1)
    {
        for (int i = 0; i < l; i++)
            tmpf[i] = f[i], tmpln[i] = tmpr[i] = res[i];
        for (int i = l; i < l << 1; i++)
            tmpf[i] = tmpln[i] = tmpr[i] = 0;
        Ln(tmpln, l);
        NTT(tmpln, l << 1);
        NTT(tmpf, l << 1);
        NTT(tmpr, l << 1);
        for (int i = 0; i < l << 1; i++)
            (tmpr[i] *= (1 - tmpln[i] % MOD + MOD + tmpf[i] % MOD) % MOD) %= MOD;
        NTT(tmpr, l << 1, true);
        for (int i = 0; i < l; i++)
            res[i] = tmpr[i];
        for (int i = l; i < l << 1; i++)
            res[i] = 0;
    }
}
ll f[MAXN << 2], res[MAXN << 2], v[MAXN << 2], vis[MAXN << 2];
int main()
{
    memset(f, 0, sizeof(f));
    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
        std::cin >> v[i], vis[v[i]]++;
    inv[1] = 1;
    for (int i = 2; i < m << 2; i++)
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
    for (int i = 1; i <= m; i++)
        if (vis[i])
            for (int j = i, k = 1; j <= m; j += i, k++)
                (f[j] += vis[i] * inv[k] % MOD) %= MOD;
    int lim = 1;
    while (lim <= m)
        lim <<= 1;
    pExp(f, res, lim);
    for (int i = 1; i <= m; i++)
        std::cout << res[i] << '\n';
    return 0;
}


