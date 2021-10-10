#include <iostream>
const int MOD = 998244353;
using ll = long long;
ll f(ll n)
{
    ll res = 0;
    ll l = 1, r;
    while (l <= n)
    {
        r = n / (n / l);
        (res += (r - l + 1LL) * (n / l) % MOD) %= MOD;
	l = r + 1;
    }
    return res;
}
int main()
{
    ll l, r;
    std::cin >> l >> r;
    std::cout << ((f(r) - f(l - 1)) % MOD + MOD) % MOD << std::endl;
    return 0;
}

