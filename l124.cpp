#include <unordered_map>
#include <iostream>
const int MAXN = 1e7 + 10, MOD = 1e9 + 7;
long long id[MAXN];
int prime[MAXN / 10], prcnt = 0;
bool vis[MAXN];
inline int qpow(long long a, int b)
{
    long long res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= MOD;
        (a *= a) %= MOD;
        b >>= 1;
    }
    return res;
}
void linear(int k)
{
    int n = 1e7;
    id[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (!vis[i])
        {
            id[i] = qpow(i, k);
            prime[++prcnt] = i;
        }
        for (int j = 1; j <= prcnt && prime[j] * i <= n; j++)
        {
            id[i * prime[j]] = id[i] * id[prime[j]] % MOD;
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
    for (int i = 2; i <= n; i++)
        (id[i] += id[i - 1]) %= MOD;
}

int main()
{
    int n, k;
    std::cin >> n >> k;
    linear(k);
    int ans = 0;
    int l = 1, r;
    while (l <= n)
    {
        r = n / (n / l);
        (ans += (id[r] - id[l - 1] + MOD) % MOD * (n / l) % MOD) %= MOD;
        l = r + 1;
    }
    std::cout << ans;
    return 0;
}