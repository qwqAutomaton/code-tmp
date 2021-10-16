#include <iostream>
#include <unordered_map>
const int MAXN = 2000010;
std::unordered_map<long long, long long> muSum, phiSum;
long long mu[MAXN], phi[MAXN], prime[MAXN / 2], prcnt = 0;
bool vis[MAXN];
void preprocMu()
{
    long long n = MAXN - 10;
    mu[1] = phi[1] = 1;
    for (long long i = 2; i <= n; i++)
    {
        if (!vis[i])
        {
            prime[++prcnt] = i;
            phi[i] = i - 1;
            mu[i] = -1;
        }
        for (long long j = 1; j <= prcnt && prime[j] * i <= n; j++)
        {
            vis[i * prime[j]] = 1;
            if (i % prime[j])
            {
                mu[i * prime[j]] = -mu[i];
                phi[i * prime[j]] = phi[i] * phi[prime[j]];
            }
            else
            {
                mu[i * prime[j]] = 0;
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
        }
    }
    for (long long i = 2; i <= n; i++)
    {
        mu[i] += mu[i - 1];
        phi[i] += phi[i - 1];
    }
}
long long musum(long long n)
{
    if (n <= MAXN - 10)
        return mu[n];
    if (muSum.count(n))
        return muSum[n];
    long long res = 1LL;
    long long l = 2, r;
    while (l <= n)
    {
        r = n / (n / l);
        res -= musum(n / l) * (r - l + 1);
        l = r + 1;
    }
    muSum.insert(std::make_pair(n, res));
    return res;
}
long long phisum(long long n)
{
    if (n <= MAXN - 10)
        return phi[n];
    if (phiSum.count(n))
        return phiSum[n];
    long long res = n * (n + 1) / 2;
    long long l = 2, r;
    while (l <= n)
    {
        r = n / (n / l);
        res -= (r - l + 1) * phisum(n / l);
        l = r + 1;
    }
    phiSum.insert(std::make_pair(n, res));
    return res;
}
int main()
{
    preprocMu();
    int t;
    std::cin >> t;
    while (t--)
    {
        int n;
        std::cin >> n;
        std::cout << phisum(n) << ' ' << musum(n) << '\n';
    }
    return 0;
}

