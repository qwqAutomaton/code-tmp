#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
class DataGen
{
private:
    long long seed, vmax;
    inline long long getrand()
    {
        long long ret = seed;
        seed = (seed * 7 + 13) % 1000000007;
        return ret;
    }

public:
    inline DataGen()
        : seed(0), vmax(0) {}
    inline DataGen(long long seed, long long vmax)
        : seed(seed), vmax(vmax) {}
    inline long long operator()(long long mod)
    {
        return getrand() % mod + 1;
    }
};
struct node
{
    int l, r;
    mutable long long v;
    node(int l = 0, int r = 0, long long v = 0)
        : l(l), r(r), v(v) {}
    bool operator<(const node &n) const { return l < n.l; }
};
std::set<node> s;
std::vector<node> tmp;
inline long long qpow(long long a, int pow, long long mod)
{
    a %= mod;
    long long res = 1;
    while (pow)
    {
        if (pow & 1)
            (res *= a) %= mod;
        (a *= a) %= mod;
        pow >>= 1;
    }
    return res;
}
inline auto split(int pos)
{
    auto it = s.lower_bound(node(pos));
    if (it != s.end() && it->l == pos)
        return it;
    it--;
    node tmp = *it;
    s.erase(it);
    s.insert(node(tmp.l, pos - 1, tmp.v));
    return s.insert(node(pos, tmp.r, tmp.v)).first;
}
inline void add(int l, int r, long long v)
{
    auto rit = split(r + 1);
    for (auto lit = split(l); lit != rit; lit++)
        lit->v += v;
}
inline void assign(int l, int r, long long v)
{
    auto rit = split(r + 1);
    s.erase(split(l), rit);
    s.insert(node(l, r, v));
}
inline long long queryMinK(int l, int r, int k)
{
    auto rit = split(r + 1);
    tmp.clear();
    for (auto lit = split(l); lit != rit; lit++)
        tmp.push_back(*lit);
    std::sort(tmp.begin(), tmp.end(), [](node a, node b) -> bool { return a.v < b.v; });
    for (auto i : tmp)
    {
        k -= i.r - i.l + 1;
        if (k <= 0)
            return i.v;
    }
    return -1;
}
inline long long queryPowsum(int l, int r, int pow, long long mod)
{
    auto rit = split(r + 1);
    long long ret = 0;
    for (auto lit = split(l); lit != rit; lit++)
        (ret += (lit->r - lit->l + 1LL) % mod * qpow(lit->v, pow, mod) % mod) %= mod;
    return ret;
}
int main()
{
    int n, m;
    std::cin >> n >> m;
    long long seed, vmax;
    std::cin >> seed >> vmax;
    DataGen rng(seed, vmax);
    for (int i = 1; i <= n; i++)
        s.insert(node(i, i, rng(vmax)));
    for (int i = 1; i <= m; i++)
    {
        int op, l, r;
        long long x, y;
        op = rng(4);
        l = rng(n);
        r = rng(n);
        (l > r) && (std::swap(l, r), true);
        if (op == 3)
            x = rng(r - l + 1);
        else
            x = rng(vmax);
        if (op == 4)
            y = rng(vmax);
        switch (op)
        {
        case 1:
            add(l, r, x);
            break;
        case 2:
            assign(l, r, x);
            break;
        case 3:
            std::cout << /*"QMinK[" << l << ", " << r << "] : " << x << " = " << */queryMinK(l, r, x) << '\n';
            break;
        case 4:
            std::cout << /*"QPSum[" << l << ", " << r << "] : ^" << x << ", %" << y << " = " << */queryPowsum(l, r, x, y) << '\n';
            break;
        default:
            return 1;
            break;
        }
    }
    return 0;
}