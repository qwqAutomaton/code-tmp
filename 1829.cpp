 #include <iostream>
#define int long long
const int MAXN = 1e7 + 10, MOD = 20101009;
int n, m, mu[MAXN], prime[MAXN], sum[MAXN], cnt;
bool vis[MAXN];
int ids(int x)
{
    x %= MOD;
    int res = x * (x + 1) % MOD;
    (res *= 10050505LL) %= MOD;
    return res % MOD;
}
long long calc(int x, int y)
{
    long long res = 0;
    int l = 1, r, k = std::min(x, y);
    while (l <= k)
    {
        r = std::min(x / (x / l), y / (y / l));
        (res += ((sum[r] - sum[l - 1] + 2LL * MOD) % MOD) * ids(x / l) % MOD * ids(y / l) % MOD) %= MOD;
        l = r + 1;
    }
    return res;
}
/*int*/signed main()
{
    std::cin >> n >> m;
    mu[1] = 1;
    for (int i = 2; i <= std::min(n, m); i++)
    {
        if (!vis[i])
        {
            prime[++cnt] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= cnt && prime[j] * i <= std::min(n, m); j++)
        {
            vis[prime[j] * i] = 1;
            mu[prime[j] * i] = i % prime[j] ? -mu[i] : 0;
            if (i % prime[j] == 0)
                break;
        }
    }
    for (int i = 1; i <= std::min(n, m); i++)
        sum[i] = (sum[i - 1] + 1LL * i * i % MOD * (mu[i] + MOD) % MOD) % MOD;
    int l = 1, r, k = std::min(n, m);
    long long ans = 0;
    while (l <= k)
    {
        r = k / (k / l);
        (ans += calc(n / l, m / l) * ((r + l) * (r - l + 1) % MOD * 10050505LL % MOD) % MOD) %= MOD;
        l = r + 1;
    }
    std::cout << ans << std::endl;
    return 0;
}

