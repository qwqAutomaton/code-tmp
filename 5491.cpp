#include <iostream>
using ll = long long;
ll iSqr;
struct comp
{
    ll x, y;
    comp(ll r = 0, ll i = 0)
        : x(r), y(i) {}
};
inline comp mulmod(comp a, comp b, ll p)
{
    return comp(
        (a.x * b.x % p + a.y * b.y % p * iSqr % p) % p,
        (a.x * b.y % p + a.y * b.x % p) % p
    );
}
inline comp qpow(comp a, ll b, ll p)
{
    comp res(1, 0);
    while (b)
    {
        if (b & 1)
            res = mulmod(res, a, p);
        a = mulmod(a, a, p);
        b >>= 1;
    }
    return res;
}
inline ll qpow(ll a, ll b, ll p)
{
    a %= p;
    ll res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= p;
        (a *= a) %= p;
        b >>= 1;
    }
    return res;
}
inline ll legendre(ll n, ll p)
{
    return qpow(n, (p - 1) >> 1, p) % p;
}
inline ll randgen(ll p)
{
    return (rand()) % p;
}
ll cipolla(ll n, ll p)
{
    n %= p;
    if (!n)
        return 0;
    if (legendre(n, p) == p - 1)
        return -1;
    ll a;
    while (1)
    {
        a = randgen(p);
        ll w = (a * a % p - n + p) % p;
        if (legendre(w, p) == p - 1)
            break;
    }
    iSqr = (a * a % p - n + p) % p;
    comp res = qpow(comp(a, 1), (p + 1) >> 1, p);
    return res.x;
}
void solve(ll n, ll p)
{
    ll qr1 = cipolla(n, p);
    if (qr1 == -1)
    {
        std::cout << "Hola!\n";
        return;
    }
    else if (qr1)
    {
        ll qr2 = p - qr1;
        std::cout << std::min(qr1, qr2) << ' ' << std::max(qr1, qr2) << '\n';
        return;
    }
    else
        std::cout << "0\n";
}
int main()
{
    int t;
    std::cin >> t;
    while (t--)
    {
        ll n, p;
        std::cin >> n >> p;
        solve(n, p);
    }
    return 0;
}

