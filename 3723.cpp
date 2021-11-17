#include <algorithm>
#include <iostream>
#include <cmath>
#define int long long
const int MOD = 998244353, MAXN = 100010, G = 3, invG = 332748118;
int tr[MAXN << 2];
inline int qpow(int a, int b = MOD - 2)
{
    int ret = 1;
    while (b)
    {
        if (b & 1)
            (ret *= a) %= MOD;
        (a *= a) %= MOD;
        b >>= 1;
    }
    return ret;
}
void NTT(int *f, int n, bool rev = false)
{
    for (int i = 0; i < n; i++)
        tr[i] = (tr[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);
    for (int i = 0; i < n; i++)
        if (i < tr[i])
            std::swap(f[i], f[tr[i]]);
    for (int l = 2; l <= n; l <<= 1)
    {
        int root = qpow(rev ? G : invG, (MOD - 1) / l);
        for (int k = 0; k < n; k += l)
        {
            int cur = 1;
            for (int i = k; i < k + (l >> 1); i++)
            {
                int qwq = cur * f[i + (l >> 1)] % MOD;
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
        int invs = qpow(n);
        for (int i = 0; i < n; i++)
            (f[i] *= invs) %= MOD;
    }
}
int f[MAXN << 2], g[MAXN << 2];
int getMin(int a, int b)
{
    double pos = -b / (2.0 * a);
    int pos1 = floor(pos), pos2 = ceil(pos);
    return std::min(a * pos2 * pos2 + b * pos2, a * pos1 * pos1 + b * pos1);
}
signed main()
{
    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
        std::cin >> f[i];
    for (int i = 1; i <= n; i++)
    {
        std::cin >> g[i];
        g[i + n] = g[i];
    }
    std::reverse(g + 1, g + 1 + n * 2);
    int f2 = 0, f1 = 0, g2 = 0, g1 = 0;
    for (int i = 1; i <= n; i++)
    {
        f2 += f[i] * f[i];
        g2 += g[i] * g[i];
        f1 += f[i];
        g1 += g[i];
    }
    int lim = 1;
    while (lim <= n * 3)
        lim <<= 1;
    NTT(f, lim);
    NTT(g, lim);
    for (int i = 0; i < lim; i++)
        (f[i] *= g[i]) %= MOD;
    NTT(f, lim, 1);
    int ans = -1;
    for (int i = 0; i <= n; i++)
        ans = std::max(ans, f[i + 1 + n]);
    int qwq = getMin(n, 2 * (f1 - g1)), ovo = f2 + g2;
    std::cout << ovo + qwq - ans * 2 << std::endl;
    return 0;
}