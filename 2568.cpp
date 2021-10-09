#include <iostream>
const int MAXN = 10000010;
bool vis[MAXN];
int prime[MAXN], mu[MAXN], cnt = 0;
long long f(int n)
{
    int l = 1, r;
    long long res = 0;
    while (l <= n)
    {
        r = n / (n / l);
        res += (mu[r] - mu[l - 1]) * 1LL * (n / l) * (n / l);
        l = r + 1;
    }
    return res;
}
void seive(int n)
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
            vis[prime[j] * i] = 1;
            if (i % prime[j] == 0)
            {
                mu[prime[j] * i] = 0;
                break;
            }
            else
                mu[prime[j] * i] = -mu[i];
        }
    }
    for (int i = 2; i <= n; i++)
        mu[i] += mu[i - 1];
}
int main()
{
    seive(MAXN - 1);
    int n;
    std::cin >> n;
    long long ans = 0;
    for (int i = 1; i <= cnt && prime[i] <= n; i++)
        ans += f(n / prime[i]);
    std::cout << ans << std::endl;
    return 0;
}

