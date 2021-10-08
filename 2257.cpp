#include <iostream>
const int MAXN = 1e7 + 5;
using ll = long long;
ll mu[MAXN], prime[MAXN / 10], f[MAXN], cnt = 0;
bool vis[MAXN];
int main()
{
    mu[1] = 1;
    for (int i = 2; i <= 10000000; i++)
    {
        if (!vis[i])
        {
            mu[i] = -1;
            prime[++cnt] = i;
        }
        for (int j = 1; j <= cnt && i * prime[j] <= 10000000; j++)
        {
            mu[i * prime[j]] = i % prime[j] ? -mu[i] : 0;
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
    for (int i = 1; i <= cnt; i++)
        for (int j = 1; j * prime[i] <= 10000000; j++)
            f[j * prime[i]] += mu[j];
    for (int i = 2; i <= 10000000; i++)
        f[i] += f[i - 1];
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++)
    {
        int n, m;
        std::cin >> n >> m;
        long long res = 0;
        int l = 1, r, k = std::min(n, m);
        while (l <= k)
        {
            r = std::min(n / (n / l), m / (m / l));
            res += (f[r] - f[l - 1]) * (n / l) * (m / l);
            l = r + 1;
        }
        std::cout << res << '\n';
    }
    return 0;
}

