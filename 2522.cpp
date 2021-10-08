#include <iostream>

const int MAXN = 50010;
int mu[MAXN], prime[MAXN], m = 0;
bool vis[MAXN];
long long calc(int x, int y, int k)
{
    int a = x / k, b = y / k;
    int n = std::min(a, b);
    int l = 1, r;
    long long ans = 0;
    while (l <= n)
    {
        r = std::min(a / (a / l), b / (b / l));
        ans += 1LL * (a / l) * (b / l) * (mu[r] - mu[l - 1]);
        l = r + 1;
    }
    return ans;
}
int main()
{
    mu[1] = 1;
    for (int i = 2; i < MAXN; i++)
    {
        if (!vis[i])
        {
            prime[++m] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= m && prime[j] * i < MAXN; j++)
        {
            mu[i * prime[j]] = i % prime[j] ? -mu[i] : 0;
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
    for (int i = 2; i < MAXN; i++)
        mu[i] += mu[i - 1];
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++)
    {
        int a, b, c, d, k;
        std::cin >> a >> b >> c >> d >> k;
        std::cout << calc(b, d, k) - calc(b, c - 1, k) - calc(a - 1, d, k) + calc(a - 1, c - 1, k) << std::endl;
    }
    return 0;
}

