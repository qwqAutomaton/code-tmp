#include <iostream>
using type = int;
struct num
{
    type r, i;
    num(type r = 0, type i = 0): r(r), i(i) {}
};
type i_sqr; // i^2
type randgen(type mod)
{
    return (rand()) % mod;
}
num mul(num a, num b, type p)
{
    return num((a.r * b.r % p + a.i * b.i % p * i_sqr % p) % p, (a.r * b.i % p + a.i * b.r % p) % p);
}
type qpow(type a, type n, type p)
{
    type res = 1;
    while (n)
    {
        if (n & 1)
            (res *= a) %= p;
        (a *= a) %= p;
        n >>= 1;
    }
    return res;
}
num qpow(num a, type n, type p)
{
    num res(1, 0);
    while (n)
    {
        if (n & 1)
            res = mul(res, a, p);
        a = mul(a, a, p);
        n >>= 1;
    }
    return mul(res, num(1, 0), p);
}
type cipolla(type n, type p) // x^2 = n (mod p)
{
    n %= p;
    if (p == 2)
        return n;
    if (qpow(n, (p + 1) >> 1, p) == p - 1)
        return -1;
    type a;
    while (1)
    {
        a = randgen(p);
        std::clog << "Generated a = " << a << '\n';
        if (qpow(a, (p + 1) >> 1, p) == p - 1)
            break;
    }
    i_sqr = (a * a % p - n + p) % p;
    return qpow(num(a, 1), (p + 1) >> 1, p).r % p;
}
int main()
{
    freopen("log", "w", stderr);
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++)
    {
        std::cout << "Case #" << i << ": \n";
        type n, p;
        std::cin >> n >> p;
        type qr1 = cipolla(n, p);
        if (qr1 == -1)
        {
            std::cout << "Hola!\n";
            continue;
        }
        type qr2 = (p * 2 - qr1) % p;
        if (qr1 == qr2)
            std::cout << qr1 << '\n';
        else
            std::cout << std::min(qr1, qr2) << ' ' << std::max(qr1, qr2) << '\n';
    }
    std::cout.flush();
    return 0;
}

