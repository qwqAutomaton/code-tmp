#include <iostream>
const int MAXN = 50010;
bool vis[MAXN];
int mu[MAXN], prime[MAXN], m = 0;
void solve()
{
    int a, b, d;
    std::cin >> a >> b >> d;
    a /= d;
    b /= d;
    int n = std::min(a, b);
    int l = 1, r, sum = 0;
    while (l <= n)
    {
        r = std::min(a / (a / l), b / (b / l));
        sum += (mu[r] - mu[l - 1]) * (a / l) * (b / l);
        l = r + 1;
    }
    std::cout << sum << std::endl;
}
int main()
{
    mu[1] = 1;
    for (int i = 2; i < MAXN; i++)
    {
        if (!vis[i])
            prime[++m] = i, mu[i] = -1;
        for (int j = 1; prime[j] * i < MAXN && j <= m; j++)
        {
            mu[prime[j] * i] = i % prime[j] ? -mu[i] : 0;
            vis[prime[j] * i] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
    for (int i = 2; i <= MAXN; i++)
        mu[i] += mu[i - 1];
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++)
        solve();
    return 0;
}

