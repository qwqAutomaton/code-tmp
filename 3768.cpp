#include <iostream>
#include <unordered_map>
long long mod, n;
inline long long qpow(long long a, long long b, long long p)
{
    long long res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= p;
        (a *= a) %= p;
        b >>= 1;
    }
    return res;
}
namespace Du // 杜教筛
{
    std::unordered_map<long long, long long> sumMap;
    const long long MAXN = 5e6;
    long long inv2, inv6; // 2 和 6 的逆元
    long long phi[MAXN + 10], sum[MAXN + 10], prime[MAXN / 2], prcnt = 0;
    bool vis[MAXN + 10];
    inline void preproc() // 线性筛预处理
    {
        inv2 = qpow(2, mod - 2, mod);
        inv6 = qpow(6, mod - 2, mod);
        phi[1] = 1;
        int n = MAXN;
        for (int i = 2; i <= n; i++)
        {
            if (!vis[i])
            {
                phi[i] = i - 1;
                prime[++prcnt] = i;
            }
            for (int j = 1; j <= prcnt && prime[j] * i <= n; j++)
            {
                vis[i * prime[j]] = 1;
                if (i % prime[j])
                    phi[i * prime[j]] = phi[i] * phi[prime[j]] % mod;
                else
                {
                    phi[i * prime[j]] = phi[i] * prime[j] % mod;
                    break;
                }
            }
        }
        sum[0] = 0;
        for (int i = 1; i <= n; i++)
            sum[i] = (i % mod * i % mod * phi[i] % mod + sum[i - 1] % mod) % mod;
    }
    inline long long linsum(long long n) // 1 + 2 + ... + n
    {
        n %= mod;
        return n % mod * (n + 1) % mod * inv2 % mod;
    }
    inline long long sqrsum(long long n) // 1^2 + 2^2 + ... + n^2
    {
        n %= mod;
        return n % mod * (n + 1) % mod * (2 * n + 1) % mod * inv6 % mod;
    }
    inline long long cubsum(long long n) // 1^3 + 2^3 + ... + n^3
    {
        long long tmp = linsum(n % mod);
        return tmp * tmp % mod;
    }
    long long getSum(long long n)
    {
        if (n <= MAXN)
            return sum[n];
        if (sumMap.count(n))
            return sumMap[n];
        long long res = cubsum(n % mod), l = 2, r;
        while (l <= n)
        {
            r = n / (n / l);
            (res -= (sqrsum(r) - sqrsum(l - 1) + mod) % mod * getSum(n / l) % mod) %= mod;
            (res += mod) %= mod;
            l = r + 1;
        }
        sumMap.insert(std::make_pair(n, res));
        return res;
    }
}
int main()
{
    std::cin >> mod >> n;
    Du::preproc();
    long long l = 1, r, res = 0;
    while (l <= n)
    {
        r = n / (n / l);
        long long tmp = Du::linsum(n / l) % mod;
        (res += (Du::getSum(r) - Du::getSum(l - 1) + mod) % mod * tmp % mod * tmp % mod) %= mod;
        l = r + 1;
    }
    std::cout << res << std::endl;
    return 0;
}

