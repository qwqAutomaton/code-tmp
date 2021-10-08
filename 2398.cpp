#include <iostream>
const int MAXN = 100010;
using ll = long long;
ll mu[MAXN], prime[MAXN / 10], cnt = 0;
bool vis[MAXN];
inline void seive(int n)
{
    mu[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (!vis[i])
        {
            mu[i] = -1;
            prime[++cnt] = i;
        }
        for (int j = 1; j <= cnt && prime[j] * i <= n; j++)
        {
            mu[i * prime[j]] = i % prime[j] ? -mu[i] : 0;
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
    for (int i = 2; i <= n; i++)
        mu[i] += mu[i - 1];
}
inline long long calc(int n, int m)
{
    int k = std::min(n, m);
    int l = 1, r;
    long long ans = 0;
    while (l <= k)
    {
        r = std::min(n / (n / l), m / (m / l));
        ans += (mu[r] - mu[l - 1]) * (n / l) * (m / l);
        l = r + 1;
    }
    return ans;
}
int main()
{
    int n;
    std::cin >> n;
    seive(n);
    int l = 1, r;
    long long res = 0;
    while (l <= n)
    {
        r = n / (n / l);
        res += (r - l + 1LL) * (r + l) * calc(n / l, n / l) / 2;
        l = r + 1;
    }
    std::cout << res << std::endl;
    return 0;
}

