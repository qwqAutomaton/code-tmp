#include <iostream>
const int MAXN = 500010;
long long mu[MAXN], tau[MAXN], prime[MAXN / 10], num[MAXN], cnt = 0;
bool vis[MAXN];
void solve(int x, int y)
{
    int n = std::min(x, y);
    int l = 1, r;
    long long res = 0;
    while (l <= n)
    {
        r = std::min(x / (x / l), y / (y / l));
        res += (mu[r] - mu[l - 1]) * tau[x / l] * tau[y / l];
        l = r + 1;
    }
    std::cout << res << std::endl;
}
void seive(int n)
{
    mu[0] = tau[0] = 0;
    mu[1] = tau[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (!vis[i])
        {
            mu[i] = -1;
            tau[i] = 2;
            num[i] = 1;
            prime[++cnt] = i;
        }
        for (int j = 1; j <= cnt && i * prime[j] <= n; j++)
        {
            vis[i * prime[j]] = 1;
            if (i % prime[j])
            {
                num[i * prime[j]] = 1;
                tau[i * prime[j]] = tau[i] * 2;
                mu[i * prime[j]] = -mu[i];
            }
            else
            {
                num[i * prime[j]] = num[i] + 1;
                tau[i * prime[j]] = tau[i] / num[i * prime[j]] * (num[i * prime[j]] + 1);
                mu[i * prime[j]] = 0;
                break;
            }
        }
    }
    for (int i = 1; i <= n; i++)
        mu[i] += mu[i - 1], tau[i] += tau[i - 1];
}
int main()
{
    seive(MAXN - 1);
    int t;
    std::cin >> t;
    while (t--)
    {
        int x, y;
        std::cin >> x >> y;
        solve(x, y);
    }
    return 0;
}

