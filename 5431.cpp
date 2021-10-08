#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL n, MOD, k;
LL ksm(LL x, LL y)
{
    LL ret = 1, tmp = y;
    while(tmp > 0)
    {
        if(tmp & 1) ret = (ret * x) % MOD;
        tmp >>= 1;
        x = (x * x) % MOD;
    }
    ret %= MOD;
    return ret;
}
LL b[5000010], s[5000010], a[5000010], ans;
int main()
{
    std::cin >> n >> MOD >> k;
    s[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> a[i];
        s[i] = (s[i - 1] * a[i]) % MOD;
    }
    b[n + 1] = ksm(s[n], MOD - 2);
    for (int i = n; i >= 1; i--)
        b[i] = (b[i + 1] * a[i]) % MOD;
    LL tmp = k;
    for (int i = 1; i <= n; i++)
    {
        ans = (ans + ((b[i + 1] * s[i - 1]) % MOD) * tmp % MOD) % MOD;
        (tmp *= k) %= MOD;
    }
    std::cout << ans << std::endl;
    return 0;
}


